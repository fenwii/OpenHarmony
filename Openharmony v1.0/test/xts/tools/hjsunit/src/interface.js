let core = null
let setCore = function (tmp) {
  core = tmp
}

let describe = function (desc, func) {
  if (typeof globalThis !== 'undefined') {
    return globalThis.describe(desc,func)
  }else {
    return core.describe(desc, func)
  }
}

let it = function (desc,filter, func) {
  if (typeof globalThis !== 'undefined') {
    return globalThis.it(desc,filter,func)
  }else {
    return core.it(desc, filter,func)
  }
}

let beforeEach = function (func) {
  if (typeof globalThis !== 'undefined') {
    return globalThis.beforeEach(func)
  }else {
    return core.beforeEach(func)
  }
}

let afterEach = function (func) {
  if (typeof globalThis !== 'undefined') {
    return globalThis.afterEach(func)
  }else {
    return core.afterEach(func)
  }
}

let beforeAll = function (func) {
  if (typeof globalThis !== 'undefined') {
    return globalThis.beforeAll(func)
  }else {
    return core.beforeAll(func)
  }
}

let afterAll = function (func) {
  if (typeof globalThis !== 'undefined') {
    return globalThis.afterAll(func)
  }else {
    return core.afterAll(func)
  }
}

let expect = function (actual) {
  if (typeof globalThis !== 'undefined') {
    return globalThis.expect(actual)
  }else {
    return core.expect(actual)
  }
}


const IT_FILTER_DEFAULT = 0B0000

const IT_TESTTYPE_FUNCTION = 0B1
const IT_TESTTYPE_PERFORMANCE = 0B1<<1
const IT_TESTTYPE_POWER = 0B1<<2
const IT_TESTTYPE_RELIABILITY = 0B1<<3
const IT_TESTTYPE_SECURITY = 0B1<<4
const IT_TESTTYPE_GLOBAL = 0B1<<5
const IT_TESTTYPE_COMPATIBILITY = 0B1<<6
const IT_TESTTYPE_USER = 0B1<<7
const IT_TESTTYPE_SANDARD = 0B1<<8
const IT_TESTTYPE_SAFETY = 0B1<<9

const IT_SIZE_SMALLTEST = 0B1<<16
const IT_SIZE_MEDIUMTEST = 0B1<<17
const IT_SIZE_LARGERTEST = 0B1<<18

const IT_LEVEL_LEVEL0 = 0B1<<24
const IT_LEVEL_LEVEL1 = 0B1<<25
const IT_LEVEL_LEVEL2 = 0B1<<26
const IT_LEVEL_LEVEL3 = 0B1<<27
const IT_LEVEL_LEVEL4 = 0B1<<28

export {
  setCore, describe, it, beforeAll, beforeEach, afterEach, afterAll, expect,IT_FILTER_DEFAULT
}
