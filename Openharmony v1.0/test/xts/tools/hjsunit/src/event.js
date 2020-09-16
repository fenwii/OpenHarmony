class SpecEvent {
  constructor (attr) {
    this.id = attr.id
    this.coreContext = attr.coreContext
  }

  specStart (specContext) {
    console.info('start running case \'' + specContext.description + '\'')
  }

  specDone (specContext) {
    // 获取报告打印服务
    let reportService = this.coreContext.getDefaultService('report')
    if (specContext.error) {
      reportService.formatPrint('fail', specContext.description)
      reportService.formatPrint('failDetail', specContext.error)
    } else if (specContext.result) {
      if (specContext.result.failExpects.length > 0) {
        reportService.formatPrint('fail', specContext.description)
        specContext.result.failExpects.forEach(failExpect => {
          const msg = failExpect.message || ('expect ' + failExpect.actualValue + ' ' + failExpect.checkFunc + ' ' + (failExpect.expectValue || ''))
          reportService.formatPrint('failDetail', msg)
        })
      } else {
        reportService.formatPrint('pass', specContext.description)
      }
    }
  }
}

class SuiteEvent {
  constructor (attr) {
    this.id = attr.id
  }

  suiteStart (suiteContext) {
    console.info('[suite start]' + suiteContext.description)
  }

  suiteDone () {
    console.info('[suite end]')
  }
}

class TaskEvent {
  constructor (attr) {
    this.id = attr.id
  }

  taskStart () {
    console.info('[start] start run suites')
  }

  taskDone () {

    console.info('[end] run suites end')
  }
}

export { SpecEvent, TaskEvent, SuiteEvent }
