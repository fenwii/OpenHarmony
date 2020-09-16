/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// AUTO GENERATED, PLEASE DO NOT EDIT DIRECTLY

#ifndef ACELITE_FRAMEWORK_RAW_BUFFER
#error THIS FILE CAN ONLY BE INCLUDED BY RAW BUFFER CPP
#endif

#ifndef OHOS_ACELITE_FRAMEWORK_MIN_JS_BUFFER
#define OHOS_ACELITE_FRAMEWORK_MIN_JS_BUFFER
const char * const g_frameworkJSBuffer =
    "!function(t,e){'object'==typeof exports&&'undefined'!=typeof module?module.exports=e():'fun"
    "ction'==typeof define&&define.amd?define(e):(t=t||self).ViewModel=e()}(this,(function(){'u"
    "se strict';var t={stack:[],push:function(t){this.stack.push(t)},pop:function(){return this"
    ".stack.pop()},top:function(){return this.stack[this.stack.length-1]}},e=function(t){return"
    "'object'==typeof t},n=function(t,e,n){Object.defineProperty(t,e,{enumerable:!1,value:n})};"
    "function i(t,e,n,i){this._ctx=t,this._getter=e,this._fn=n,this._meta=i,this._lastValue=thi"
    "s._get()}function o(e){this._hijacking=!0,n(e,'__ob__',this),Array.isArray(e)&&function(t)"
    "{r.forEach((function(e){var i=t[e];n(t,e,(function(){var n,r=Array.prototype.slice.call(ar"
    "guments);i.apply(this,r),s.PUSH===e||s.UNSHIFT===e?n=r:s.SPLICE&&(n=r.slice(2)),n&&n.lengt"
    "h&&n.forEach(o.of);var c=t.__ob__;c&&c.notifyParent()}))}))}(e),Object.keys(e).forEach((fu"
    "nction(n){return function(e,n,i){var s=e.__ob__;Object.defineProperty(e,n,{enumerable:!0,g"
    "et:function(){var e=t.top();e&&e.subscribe(s,n);var r=o.of(i);return o.is(r)&&r.setParent("
    "s,n),i},set:function(t){i=t,s.notify(n)}})}(e,n,e[n])}))}i.prototype._get=function(){try{r"
    "eturn t.push(this),this._getter.call(this._ctx)}finally{t.pop()}},i.prototype.update=funct"
    "ion(){var t=this._lastValue,n=this._get(),i=this._ctx,o=this._meta;(n!==t||e(n))&&(this._f"
    "n.call(i,n,t,o),this._lastValue=n)},i.prototype.subscribe=function(t,e){var n=t.attach(e,t"
    "his);'function'==typeof n&&(this._detaches||(this._detaches=[]),this._detaches.push(n))},i"
    ".prototype.unsubscribe=function(){var t=this._detaches;if(t)for(;t.length;)t.pop()()},o.of"
    "=function(t){return t&&e(t)?t.__ob__?t.__ob__:new o(t):t},o.is=function(t){return t&&t._hi"
    "jacking},o.prototype.attach=function(t,e){if(void 0!==t&&e){this._obsMap||(this._obsMap={}"
    "),this._obsMap[t]||(this._obsMap[t]=[]);var n=this._obsMap[t];return n.indexOf(e)<0?(n.pus"
    "h(e),function(){n.splice(n.indexOf(e),1)}):void 0}},o.prototype.notify=function(t){void 0!"
    "==t&&this._obsMap&&this._obsMap[t]&&this._obsMap[t].forEach((function(t){return t.update()"
    "}))},o.prototype.setParent=function(t,e){this._parent=t,this._key=e},o.prototype.notifyPar"
    "ent=function(){this._parent&&this._parent.notify(this._key)};var s={PUSH:'push',POP:'pop',"
    "UNSHIFT:'unshift',SHIFT:'shift',SPLICE:'splice',REVERSE:'reverse'},r=Object.keys(s).map((f"
    "unction(t){return s[t]}));function c(t){if(!(this instanceof c))return new c(t);var e=this"
    "._vm=this;Object.keys(t).forEach((function(n){var i=t[n];'render'===n?e.$render=i:'data'=="
    "=n?function(t,e){'function'==typeof e&&(e=e.call(t,t));Object.keys(e).forEach((function(n)"
    "{return function(t,e,n){Object.defineProperty(t,n,{enumerable:!1,configurable:!0,get:funct"
    "ion(){return e[n]},set:function(t){e[n]=t}})}(t,e,n)})),o.of(e)}(e,i):'styleSheet'===n?ini"
    "tStyleSheet(i):'function'==typeof i&&(e[n]=i.bind(e))}))}return c.prototype.$watch=functio"
    "n(t,e,n){return new i(this,t,e,n)},c}));";
#endif