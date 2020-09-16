function processFunc (coreContext, func) {
  if (func.length > 0 || Object.prototype.toString.call(func) === '[object AsyncFunction]') {
    coreContext.getDefaultService('config').setSupportAsync(true)
  }
  let processedFunc
  if (func.length > 0) {
    processedFunc = function () {
      return new Promise(resolve => {
        function done () {
          resolve()
        }
        func(done)
      })
    }
  } else {
    processedFunc = func
  }
  return processedFunc
}

class SuiteService {
  constructor (attr) {
    this.id = attr.id
    this.rootSuite = new SuiteService.Suite({})
    this.currentRunningSuite = this.rootSuite
  }

  describe (desc, func) {
    const suite = new SuiteService.Suite({ description: desc })
    const currentSuiteCache = this.currentRunningSuite
    this.currentRunningSuite.childSuites.push(suite)
    this.currentRunningSuite = suite
    func.call()
    this.currentRunningSuite = currentSuiteCache
  }

  beforeAll (func) {
    this.currentRunningSuite.beforeAll.push(processFunc(this.coreContext, func))
  }

  beforeEach (func) {
    this.currentRunningSuite.beforeEach.push(processFunc(this.coreContext, func))
  }

  afterAll (func) {
    this.currentRunningSuite.afterAll.push(processFunc(this.coreContext, func))
  }

  afterEach (func) {
    this.currentRunningSuite.afterEach.push(processFunc(this.coreContext, func))
  }

  getCurrentRunningSuite () {
    return this.currentRunningSuite
  }

  init (coreContext) {
    this.coreContext = coreContext
  }

  execute () {
    this.coreContext.fireEvents('task', 'taskStart')
    if (this.coreContext.getDefaultService('config').isSupportAsync()) {
      let asyncExecute = async () => {
        await this.rootSuite.asyncRun(this.coreContext)
      }
      asyncExecute().then(() => {
        this.coreContext.fireEvents('task', 'taskDone')
        this.countResult()
      })
    } else {
      this.rootSuite.run(this.coreContext)
      this.coreContext.fireEvents('task', 'taskDone')
      this.countResult()
    }
  }

  countResult() {
    let total = 0;
    let error = 0;
    let failure = 0;
    if (this.rootSuite && this.rootSuite.childSuites) {
      for (let i = 0; i < this.rootSuite.childSuites.length; i++) {
        let testsuite = this.rootSuite.childSuites[i]
        let specs = testsuite['specs'];
        for (let j = 0 ; j < specs.length; j++) {
          total++;
          let testcase = specs[j]
          if (testcase.error) {
            error++;
          } else if (testcase.result.failExpects.length > 0) {
            failure++;
          }
        }
      }
      console.info('total cases:' + total + ';failure ' + failure + ',' + 'error ' + error + ',pass ' + (total - error - failure));
    }
  }

  apis () {
    const _this = this
    return {
      describe: function (desc, func) {
        return _this.describe(desc, func)
      },
      beforeAll: function (func) {
        return _this.beforeAll(func)
      },
      beforeEach: function (func) {
        return _this.beforeEach(func)
      },
      afterAll: function (func) {
        return _this.afterAll(func)
      },
      afterEach: function (func) {
        return _this.afterEach(func)
      }
    }
  }
}

// 保存每个测试套的对象，感觉应该跟服务区分开来
SuiteService.Suite = class {
  constructor (attrs) {
    this.description = attrs.description || ''
    this.childSuites = []
    this.specs = []
    this.beforeAll = []
    this.afterAll = []
    this.beforeEach = []
    this.afterEach = []
  }

  pushSpec (spec) {
    this.specs.push(spec)
  }

  run (coreContext) {
    if (this.description != '') {
      coreContext.fireEvents('suite', 'suiteStart', this)
    }

    this.runHookFunc('beforeAll')
    if (this.specs.length > 0) {
      // 随便random一下
      const configService = coreContext.getDefaultService('config')
      if (configService.isRandom()) {
        this.specs.sort(function () { return Math.random() > 0.5 ? -1 : 1 })
      }
      this.specs.forEach(spec => {
        this.runHookFunc('beforeEach')
        spec.run(coreContext)
        this.runHookFunc('afterEach')
      })
    }

    if (this.childSuites.length > 0) {
      this.childSuites.forEach(childSuite => {
        childSuite.run(coreContext)
      })
    }

    this.runHookFunc('afterAll')
    if (this.description != '') {
      coreContext.fireEvents('suite', 'suiteDone')
    }
  }

  asyncRun (coreContext) {
    return new Promise(async resolve => {
      if (this.description != '') {
        coreContext.fireEvents('suite', 'suiteStart', this)
      }

      await this.runAsyncHookFunc('beforeAll')
      if (this.specs.length > 0) {
        // 随便random一下
        const configService = coreContext.getDefaultService('config')
        if (configService.isRandom()) {
          this.specs.sort(function () { return Math.random() > 0.5 ? -1 : 1 })
        }
        for (let i = 0; i < this.specs.length; i++) {
          await this.runAsyncHookFunc('beforeEach')
          await this.specs[i].asyncRun(coreContext)
          await this.runAsyncHookFunc('afterEach')
        }
      }

      if (this.childSuites.length > 0) {
        for (let i = 0; i < this.childSuites.length; i++) {
          await this.childSuites[i].asyncRun(coreContext)
        }
      }

      await this.runAsyncHookFunc('afterAll')
      if (this.description != '') {
        coreContext.fireEvents('suite', 'suiteDone')
      }
      resolve()
    })
  }

  runHookFunc (hookName) {
    if (this[hookName] && this[hookName].length > 0) {
      this[hookName].forEach(func => {
        try {
          func()
        } catch (e) {
          console.error(e)
        }
      })
    }
  }

  runAsyncHookFunc (hookName) {
    if (this[hookName] && this[hookName].length > 0) {
      return new Promise(async resolve => {
        for (let i = 0; i < this[hookName].length; i++) {
          try {
            await this[hookName][i]()
          } catch (e) {
            console.error(e)
          }
        }
        resolve()
      })
    }
  }
}

class SpecService {
  constructor (attr) {
    this.id = attr.id
  }

  init (coreContext) {
    this.coreContext = coreContext
  }

  setCurrentRunningSpec (spec) {
    this.currentRunningSpec = spec
  }

  getCurrentRunningSpec () {
    return this.currentRunningSpec
  }

  it (desc, filter, func) {
    let processedFunc = processFunc(this.coreContext, func)
    const spec = new SpecService.Spec({ description: desc, fi: filter, fn: processedFunc })
    const suiteService = this.coreContext.getDefaultService('suite')
    suiteService.getCurrentRunningSuite().pushSpec(spec)
  }

  apis () {
    const _this = this
    return {
      it: function (desc, filter, func) {
        return _this.it(desc, filter, func)
      }
    }
  }
}

SpecService.Spec = class {
  constructor (attrs) {
    this.description = attrs.description || ''
    this.fi = attrs.fi
    this.fn = attrs.fn || function () {}
    this.result = {
      failExpects: [],
      passExpects: []
    }
    this.error = undefined
  }

  run (coreContext) {
    if (!this.filterCheck(coreContext)) {
      return
    }
    coreContext.fireEvents('spec', 'specStart', this)
    try {
      this.fn()
    } catch (e) {
      this.error = e
    }
    coreContext.fireEvents('spec', 'specDone', this)
  }

  asyncRun (coreContext) {
    if (!this.filterCheck(coreContext)) {
      return
    }
    return new Promise(async resolve => {
      coreContext.fireEvents('spec', 'specStart', this)
      try {
        await this.fn()
      } catch (e) {
        this.error = e
      }
      coreContext.fireEvents('spec', 'specDone', this)
      resolve()
    })
  }

  filterCheck (coreContext) {
    const configService = coreContext.getDefaultService('config')
    let filter = configService.filterSpe(this.fi)
    if (filter) {
      console.info('[filter] case ' + this.description)
      return false
    }
    const specService = coreContext.getDefaultService('spec')
    specService.setCurrentRunningSpec(this)
    return true
  }

  addExpectationResult (expectResult) {
    if (expectResult.pass) {
      this.result.passExpects.push(expectResult)
    } else {
      this.result.failExpects.push(expectResult)
    }
  }
}

class ExpectService {
  constructor (attr) {
    this.id = attr.id
    this.matchers = {}
  }

  expect (actualValue) {
    return this.wrapMatchers(actualValue)
  }

  init (coreContext) {
    this.coreContext = coreContext
    this.addMatchers(this.basicMatchers())
  }

  addMatchers (matchers) { // 方便扩展
    for (const matcherName in matchers) {
      this.matchers[matcherName] = matchers[matcherName]
    }
  }

  basicMatchers () {
    return {
      assertTrue: function (actualValue) {
        return {
          pass: actualValue === true
        }
      },
      assertEqual: function (actualValue, args) {
        return {
          pass: actualValue == args[0],
          expectValue: args[0]
        }
      },
      assertThrow: function (actual, args) {
        const result = {
          pass: false
        }
        if (typeof actual !== 'function') {
          result.message = 'toThrow\'s Actual should be a Function'
        } else {
          let hasThrow = false
          let throwError
          try {
            actual()
          } catch (e) {
            hasThrow = true
            throwError = e
          }
          if (!hasThrow) {
            result.message = 'function did not throw an exception'
          } else {
            if (throwError && throwError.message === args[0]) {
              result.pass = true
            } else {
              result.message = `expect to throw ${args[0]} , actual throw ${throwError.message}`
            }
          }
        }
        return result
      }
    }
  }

  wrapMatchers (actualValue) {
    const _this = this
    const wrappedMatchers = {}
    const specService = _this.coreContext.getDefaultService('spec')
    const currentRunningSpec = specService.getCurrentRunningSpec()
    for (const matcherName in this.matchers) {
      wrappedMatchers[matcherName] = function () {
        const result = _this.matchers[matcherName](actualValue, arguments)
        result.actualValue = actualValue
        result.checkFunc = matcherName
        currentRunningSpec.addExpectationResult(result)
      }
    }
    return wrappedMatchers
  }

  apis () {
    const _this = this
    return {
      expect: function (actualValue) {
        return _this.expect(actualValue)
      }
    }
  }
}

class ReportService {
  constructor (attr) {
    this.id = attr.id
  }

  init () {

  }

  formatPrint (type, msg) {
    switch (type) {
      case 'pass':
        console.info('[pass]' + msg)
        break
      case 'fail':
        console.info('[fail] ' + msg)
        break
      case 'failDetail':
        console.info('[fail]' + msg)
        break
    }
  }
}

class ConfigService {
  constructor (attr) {
    this.id = attr.id
    this.filter = attr.filter
    this.flag = attr.flag || { flag: false }
    this.config = attr.config || { random: false }
    this.condition = attr.config.condition
    this.supportAsync = false
  }

  init () {

  }

  setFilter (filter, flag) {
    this.filter = filter
    this.flag = flag
  }

  filterSpe (fi) {
    if (this.filter == undefined || this.filter === 0 || fi === 0) {
      return false
    }
    let testTypeFi = fi & 0B1111111111111111
    let testType = this.filter & 0B1111111111111111
    if (testType != testTypeFi && testTypeFi != 0 && testType != 0) {
      console.info('testType:' + testType + ',testTypeFi:' + testTypeFi)
      return true
    }
    let sizeFi = fi & 0B11111111 << 16
    let size = this.filter & 0B11111111 << 16
    if (size != 0 && sizeFi != 0 && size != sizeFi) {
      return true
    }
    let levelFi = fi & 0B1111111 << 24
    let level = this.filter & 0B1111111 << 24
    if (level != 0 && levelFi != 0 && level != levelFi) {
      return true
    }
    return false
  }

  isRandom () {
    return this.config.random || false
  }

  setSupportAsync (value) {
    this.supportAsync = value
  }

  isSupportAsync () {
    return this.supportAsync
  }

  execute () {

  }
}

export {
  SuiteService,
  SpecService,
  ExpectService,
  ReportService,
  ConfigService
}
