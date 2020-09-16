import { SuiteService, SpecService, ExpectService, ReportService, ConfigService } from './service'
import { SpecEvent, TaskEvent, SuiteEvent } from './event'

class Core {
  constructor () {
    this.services = {
      suite: {},
      spec: {},
      config: {},
      expect: {},
      log: {},
      report: {}

    }
    this.events =
        {
          suite: {},
          spec: {},
          task: {}
        }
  }

  addService (name, service) {
    let serviceObj = {}
    if (!this.services[name]) {
      this.services[name] = serviceObj
    } else {
      serviceObj = this.services[name]
    }
    serviceObj[service.id] = service
  }

  getDefaultService (name) {
    return this.services[name].default
  }

  getServices (name) {
    return this.services[name]
  }

  registerEvent (serviceName, event) {
    let eventObj = {}
    if (!this.events[serviceName]) {
      this.events[serviceName] = eventObj
    } else {
      eventObj = this.events[serviceName]
    }
    eventObj[event.id] = event
  }

  unRegisterEvent (serviceName, eventID) {
    const eventObj = this.events[serviceName]
    if (eventObj) {
      delete eventObj[eventID]
    }
  }

  fireEvents (serviceName, eventName, params) {
    const eventObj = this.events[serviceName]
    if (eventObj) {
      for (const attr in eventObj) {
        eventObj[attr][eventName](params)
      }
    }
  }

  addToGlobal (apis) {
    if (typeof global !== 'undefined') {
      for (let api in apis) {
        global[api] = apis[api]
      }
    }else if(typeof globalThis !== 'undefined'){
      for (let api in apis) {
        globalThis[api] = apis[api]
      }
    } else {
      for (const api in apis) {
        this[api] = apis[api]
      }
    }
  }

  init (filter, flag, conditon) {
    this.addService('suite', new SuiteService({ id: 'default' }))
    this.addService('spec', new SpecService({ id: 'default' }))
    this.addService('expect', new ExpectService({ id: 'default' }))
    this.addService('report', new ReportService({ id: 'default' }))
    this.addService('config', new ConfigService({ id: 'default', config: { random: false, condition: conditon }, filter: filter, flag: flag }))
    this.registerEvent('task', new TaskEvent({ id: 'default' }))
    this.registerEvent('suite', new SuiteEvent({ id: 'default' }))
    this.registerEvent('spec', new SpecEvent({ id: 'default', coreContext: this }))
    const context = this
    for (const key in this.services) {
      const serviceObj = this.services[key]
      for (const serviceID in serviceObj) {
        const service = serviceObj[serviceID]
        service.init(context)

        if (typeof service.apis === 'function') {
          const apis = service.apis()
          if (apis) {
            this.addToGlobal(apis)
          }
        }
      }
    }
  }

  execute () {
    const suiteService = this.getDefaultService('suite')
    suiteService.execute()
  }
}

export default Core
