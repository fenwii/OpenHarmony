# JavaScript语言通用编程规范

## 目的
规则并不是完美的，通过禁止在特定情况下有用的特性，可能会对代码实现造成影响。但是我们制定规则的目的“为了大多数程序员可以得到更多的好处”， 如果在团队运作中认为某个规则无法遵循，希望可以共同改进该规则。 
参考该规范之前，希望您具有相应的JavaScript语言基础能力，而不是通过该文档来学习JavaScript语言。 

## 总体原则
代码需要在保证功能正确的前提下，满足**可读、可维护、安全、可靠、可测试、高效、可移植**的特征要求。 

## 约定

**规则**：编程时必须遵守的约定  
**建议**：编程时必须加以考虑的约定

无论是“规则”还是“建议”，都必须理解该条目这么规定的原因，并努力遵守。  

## 例外

在不违背总体原则，经过充分考虑，有充足的理由的前提下，可以适当违背规范中约定。  
例外破坏了代码的一致性，请尽量避免。“规则”的例外应该是极少的。

下列情况，应风格一致性原则优先：  
**修改外部开源代码、第三方代码时，应该遵守开源代码、第三方代码已有规范，保持风格统一。**  

## 编程规范

### 命名规范

#### 规则1.1 须使用正确的英文拼写进行命名，禁止使用拼音拼写。

**反例：**`xingming`、`zhanghao`

**正例：**`username`、`account`

#### 规则1.2 命名尽量少用缩写，除非是常见词或者业务线的领域词汇。比如：`context`可以简写成`ctx`，`request`可简写成`req`，`response`可简写成`resp`。

**说明：**完整的单词拼写可以避免不必要的阅读障碍。

**例外：**循环语种中可以使用`i`、`j`循环条件变量名。

#### 规则1.3 类名、枚举名、命名空间名采用`upperCamelCase`风格。

**正例：**

```javascript
// 类名
class User {
  constructor(username) {
    this.username = username;
  }
  
  sayHi() {
    console.log(`hi, ${this.username}`);
  }
}

// 枚举名
const UserType = {
  TEACHER: 0,
  STUDENT: 1
};

// 命名空间
const Base64Utils = {
  encrypt: function(text) {
    // todo encrypt
  },
  decrypt: function(text) {
    // todo decrypt
  }
};
```

#### 规则1.4 变量名、方法名、参数名采用`lowerCamelCase`风格。

**正例：**

```javascript
let msg = 'Hello world';

function sendMsg(msg) {
  // todo send message
}

function findUser(userID) {
  // todo find user by user ID
}
```

#### 规则1.5 静态常量名、枚举值名采用全部大写，单词间使用下划线隔开。

**正例：**

```javascript
const MAX_USER_SIZE = 10000;

const UserType = {
  TEACHER: 0,
  STUDENT: 1
};
```

#### 建议1.6 避免使用否定的布尔变量名，布尔型的局部变量或方法须加上表达是非意义的前缀。

**反例：**

```javascript
let isNoError = true;
let isNotFound = false;
function empty() {}
function next() {}
```

**正例：**

```javascript
let isError = false;
let isFound = true;
function isEmpty() {}
function hasNext() {}
```

### 代码格式

#### 规则2.1 采用2个空格缩进，禁止使用`tab`字符

**说明：**只允许使用空格（space）进行缩进，每次缩进为2个空格。不允许使用Tab 符进行缩进。

**正例：**

```javascript
const dataSource = [
  {
    id: 1,
    title: 'Title 1',
    content: 'Content 1'
  },
  {
    id: 2,
    title: 'Title 2',
    content: 'Content 2'
  }
];

function render(container, dataSource) {
  if (!container || !dataSource || !dataSource.length) {
    return void 0;
  }

  const fragment = document.createDocumentFragment();
  for (let data of dataSource) {
    if (!data || !data.id || !data.title || !data.content) {
      continue;
    }
    const element = document.createElement("div");
    const textNode = document.createTextNode(`${data.title}: ${data.content}`);
    element.appendChild(textNode);
    element.setAttribute("id", data.id);
    fragment.appendChild(element);
  }
  container.appendChild(fragment);
}

```

#### 规则2.2 行宽不超过`120`个字符

**说明：**建议每行字符数不要超过 120 个。如果超过120个字符，请选择合理的方式进行换行。

**例外：**如果一行注释包含了超过120 个字符的命令或URL，则可以保持一行，以方便复制、粘贴和通过grep查找； 预处理的 error 信息在一行便于阅读和理解，即使超过 120 个字符。

#### 规则3.3 大括号的使用须遵循约定：

1. 如果大括号内为空，则允许简写成`{}`，且无需换行；
2. 左大括号前不换行，括号后换行；
3. 右大括号前换行，括号后还有`else`、`catch`等情况下不换行，其他情况都换行。

#### 规则3.4 条件语句和循环语句的实现必须使用大括号包裹，即使只有一条语句。

**反例：**

```javascript
if (condition)
  console.log('success');

for(let idx = 0; idx < 5; ++idx)
  console.log(idx);
```

**正例：**

```javascript
if (condition) {
  console.log('success');
}

for(let idx = 0; idx < 5; ++idx) {
  console.log(idx);
}
```

#### 规则2.5 条件语句和循环语句都不允许写在同一行。

**反例：**

```javascript
if (condition) { /* todo something */ } else { /* todo other */ }

let idx = 0;
while(idx < 10) console.log(idx);
```

**正例：**

```javascript
if (condition) {
  /* todo something */
} else {
  /* todo other */
}

let idx = 0;
while(idx < 10) {
  console.log(idx);
}
```

#### 规则2.6 `switch`语句的`case`和`default` 须缩进一层。

**正例：**

```javascript
switch(condition) {
  case 0:
    doSomething();
    break;
  case 1: { // 可以带括号也可以不带
    doOtherthing();
    break;
  }
  default:
    break;
}
```

#### 规则2.7 表达式换行须保持一致性，运算符放行末。

**说明：**较长的表达式，不满足行宽要求时，需要在适当的位置进行换行。一般在较低优先级运算符或连接符后面阶段，运算符或连接符放行末。运算符、连接符放在行末，表示“未结束，后续还有”。

**正例：**

```javascript
// 假设条件语句超出行宽
if (userCount > MAX_USER_COUNT ||
  userCount < MIN_USER_COUNT) {
  doSomething();
}

const sum =
  number1 +
  number2 +
  number3 +
  number4 +
  number5 +
  number6 +
  number7 +
  number8 +
  number9;
```

#### 规则2.8 多个变量定义和赋值语句不允许写在一行。

**反例：**

```javascript
let maxCount = 10, isCompleted = false;

let pointX, pointY;
pointX = 10; pointY = 0;
```

**正例：**

```javascript
let maxCount = 10;
let isCompleted = false;

let pointX = 0;
let pointY = 0;
```

#### 规则2.9 空格应该突出关键字和重要信息，避免不必要的空格。

**说明：**空格可以减低代码密度，增加代码的可读性。总体规则如下：

1. `if`、`elseif`、`else`、`switch`、`while`、`for`等关键字之后加空格；
2. 小括号内部两侧不加空格；
3. 大括号内部两侧须加空格，但`{}`等简单场景例外；
4. 多重括号之间不加空格；
5. 一元操作符（`&`、`*`、`+`、`-`、`!`等）之后不加空格；
6. 二元操作符（`=`、`+`、`-`、`*`、`/`、`%`、`|`、`&`、`||`、`&&`、`<`、`>`、`<=`、`>=`、`==`、`!=`、`===`、`!==`等）左右两侧加空格；
7. 三元运算符（`?: `）的两侧添加空格；
8. 前置或后置的自增、自减（`++`、`--`）和变量之间不加空格；
9. 逗号（`,`）前面不加空格，后面加空格；
10. 单行注释`//`后加空格；
11. 行尾不加空格。

#### 规则2.10 表达式语句须以分号结尾。

**反例：**

```javascript
let username = 'jack'
let birthday = '1997-09-01'

console.log(`${username}'s birthday is ${birthday}`)
```

**正例：**

```javascript
let username = 'jack';
let birthday = '1997-09-01';

console.log(`${username}'s birthday is ${birthday}`);
```

#### 建议2.11 优先使用单引号包裹字符串。

**正例：**

```javascript
let message = 'wolrd';
console.log(message);
```

### 代码规范

#### 规则3.1 声明变量时须使用`var`、`let`或`const`关键字进行声明，避免变量暴露到全局作用域上。

**说明：**不使用`var`、`let`或`const`关键字声明变量，会导致将变量暴露到全局作用域上，这样可能会覆盖全局作用域上的同名变量，进而引发GC无法有效回收内存的问题；另外，当变量中包含敏感信息时，暴露到全局作用域可能会导致信息泄露问题。另外，**尽量对所有的引用使用`const`，不要使用 `var`；如果你一定需要可变动的引用，使用 `let` 代替 `var`**。因为`const`和`let`的作用域更小，写代码更容易控制；const可确保无法对引用重新赋值，const引用的指针不可变，重新赋值会报错，避免了不小心的重新赋值给覆盖了。

**反例：**

```javascript
function open() {
  url = 'http://127.0.0.1:8080'; //url会暴露到全局作用域上
  //todo something
}
open();
console.log(url); //url可以被访问到，输出内容：http://127.0.0.1:8080
```

**正例：**

```javascript
// ES5.1使用var声明变量
function open() {
  var url = 'http://127.0.0.1:8080';
  // todo something
}
open();
console.log(url); //报错：Uncaught ReferenceError: url is not defined
```

```javascript
// ES6中，优先推荐使用let和const关键字来声明变量
function open() {
  const url = 'http://127.0.0.1:8080';
  //todo something
}
open();
console.log(url); //报错：Uncaught ReferenceError: url is not defined
```

#### 规则3.2 函数块内须使用函数表达式声明函数

**说明：**虽然很多 JS 引擎都支持块内声明函数，但它不属于 ECMAScript规范，各个浏览器糟糕的实现相互不兼容，有些也与未来 ECMAScript草案相违背。另外，ECMAScript5不支持块作用域，对于所有的控制流都不是独立的作用域，其内部声明的变量或者函数都是在其父函数或者脚本的作用域中，导致块内函数或者变量的声明会存在覆盖现象。如果确实需要在块中定义函数,应该使用函数表达式来初始化。

**反例：**

```javascript
function bar(name) {
  if (name === "hotel") {
    // 1、定义一个foo函数，其作用域不是if代码块，而是bar函数作用域。
    function foo() {
      console.log("hotel foo A");
    }
  } else {
    // 2、再重复定义一次foo函数，覆盖上面if条件分支下的foo函数定义。
    function foo() {
      console.log("hotel foo 2");
    }
  }
  foo && foo();
}
bar("hotel"); // 输出结果总是显示"hotel foo 2"
```

**正例：**

```javascript
function bar(name) {
  var foo;
  if (name == "hotel") {
    foo = function () {
      console.log("hotel foo 1");
    };
  } else {
    foo = function () {
      console.log("hotel foo 2");
    }
  }
  foo && foo();
}
bar("hotel"); // 正确输出"hotel foo 1"
```

#### 规则3.3 禁止封装基本类型

**说明：**JavaScript中有五种基本数据类型：Undefined、Null、Boolean、Number和String。基本数据类型的值是不可更改的。JavaScript中使用基本数据类型对象只是值，不包含器封装对象的方法和属性，在不需要使用属性和方法的时候，不需要使用其封装类型。

**反例：**

```javascript
var isShow = new Boolean(false);
if (isShow) {
  alert('hi'); //被执行，界面弹出显示：hi
}
```

**正例：**

```javascript
var isShow = false;
if (isShow) {
  alert('hi');
}
```

#### 规则3.4 禁止使用`with`

**说明：**使用 with让你的代码在语义上变得不清晰，因为with的对象，可能会与局部变量产生冲突，从而改变程序原本的用义。

**反例：**

```javascript
var foo = { x: 5 };
with(foo) {
  var x = 3;
  console.log(x); //输出：5
}
```

#### 规则3.5 `this`仅可在对象构造函数、方法、闭包中使用

**说明：**在JavaScript里面，this指针代表的是执行当前代码的对象的所有者。this具有特殊的语义：

+ 全局对象(大多数情况下)
+ 调用者的作用域(使用eval时)
+ DOM 树中的节点(添加事件处理函数时)
+ 新创建的对象(使用一个构造器)
+ 其他对象(如果函数被 call() 或 apply())

```javascript
var User = function(username) {
  this.username = username;
};
var user = new User('John');
console.log(user.username); // 输出：John

var ClickCounter = {
  value: 0,
  click: function() {
    ++this.value;
  },
  getValue() {
    return this.value;
  }
};
console.log(Counter.getValue()); //输出：0
Counter.click();
console.log(Counter.getValue()); //输出：1
```

#### 规则3.6 禁止使用IE下的条件注释

**说明：**在IE下使用`\@cc_on`语句或使用`\@if`或`\@set`语句可以激活条件编译。尽管可以通过注释来兼容IE以外的浏览器，但它妨碍自动化工具的执行，因为在运行时，它们会改变JavaScript 语法树。

**反例：**

```javascript
var f = function () {
  /*@cc_on @*/
  /*@if (@_jscript_version >= 4)
       alert("JavaScript version 4 or better");
    @else @*/
  alert("Conditional compilation not supported by this scripting engine.");
  /*@end @*/
};
```

#### 规则3.7 禁止修改内置对象的原型

**说明：**内置对象作为一套公共接口，具有约定俗成的行为方式，修改其原型，可能破坏接口语义，或导致调试时的诡异现象。

**反例：**

```javascript
Array.prototype.indexOf = function () { return -1 }
var arr = [1, 1, 1, 1, 1, 2, 1, 1, 1];
console.log(aar.indexOf(2)); // 输出：-1
```

#### 规则3.8 禁止直接使用`Object.prototype`的内置属性

**说明：**ECMAScript5.1新增了`Object.create`，它创建一个新对象，使用现有的对象来提供新创建的对象的proto。`Object.create(null)`是用于创建用作map的对象的常用模式。当该对象具有`Object.prototype`同名的属性时，可能会导致意外行为或漏洞。例如，web服务器解析来自客户端的JSON输入并且使用`hasOwnProperty`直接调用生成的对象是不安全的，因为恶意客户端可能会发送类似的JSON值`'{ "hasOwnProperty": 1 }'` 并导致服务器崩溃。

**反例：**

```javascript
var hasBarProperty = foo.hasOwnProperty("bar");
var isPrototypeOfBar = foo.isPrototypeOf(bar);
var barIsEnumerable = foo.propertyIsEnumerable("bar");
```

**正例：**

```javascript
var hasBarProperty = Object.prototype.hasOwnProperty.call(foo, "bar");
var isPrototypeOfBar = Object.prototype.isPrototypeOf.call(foo, bar);
var barIsEnumerable = {}.propertyIsEnumerable.call(foo, "bar");
```

#### 规则3.9 使用`Object.getPrototypeOf`函数而不要使用`_proto_`

说明：ES5引入`Object.getPrototypeOf`函数作为获取对象原型的标准API，但在这之前大量的JavaScript引擎早就使用一个特殊的`proto`属性来达到相同的目的。然而，`proto`它本质上是一个内部属性，而不是一个正式的对外的API，目前浏览器必须部署这个属性，但其他运行环境不一定部署，因此，该属性并不是完全兼容的。例如，对于拥有null原型的对象，不同的环境处理的不一样。

```javascript
var empty = Object.create(null);
"_proto_" in empty; //有些环境返回false，有些环境返回true
```

所以无论从语义的角度，还是从兼容性的角度，都不要使用proto这个属性，而是使用`Object.getPrototypeOf()`来代替。无论在什么环境中，`Object.getPrototypeOf`函数都是有效的，而且也是提取对象原型更加标准、可移植的方法。

#### 规则3.10 不要使用函数构造器创建函数

说明：定义函数的方法包括3种：函数声明、Function构造函数和函数表达式。不管用哪种方法定义函数，它们都是Function对象的实例，并将继承Function对象所有默认或自定义的方法和属性。以函数构造器创建函数的方式类似于字符串`eval()`,可以接受任何字符串形式作为它的函数体，这就会有安全漏洞的风险。

**反例：**

```javascript
var func = new Function('a', 'b', 'return a + b');
var func2 = new Function('alert("Hello")');
```

**正例：**

```javascript
function func(a, b) {
  return a + b;
}

var func2 = function(a, b) {
  return a + b;
}
```

#### 建议3.11 在使用原型`prototype`实现继承时，尽量使用现有稳定的库方法而非自行实现

**说明：**多级原型结构是指JavaScript中的继承关系。当定义一个D类，且把B类作为其原型，那么就获得了一个多级原型结构。这些原型结构会变得很复杂。使用现有的稳定的库方法如`the Closure`库的`goog.inherits()`或其他类似的函数，可避免不必要的编码失误，将是更好的选择。

#### 建议3.12 定义类时，应在原型下定义方法，在构造方法内定义属性

**说明：**JavaScript中有多种方法可以给构造函数添加方法或成员，但是使用原型定义方法，可以降低内存占用，提高运行效率。

**反例：**

```javascript
function Animals() {
  this.walk = function() {}; // 这样会导致每个实例上都创建一个walk方法
}
```

**正例：**

```javascript
function Animals() {}

Animals.prototype.walk = function() {};
```

#### 建议3.13 使用闭包时，应避免构成循环引用，导致内存泄露

**说明：**JavaScript是一种垃圾收集式语言，其对象的内存是根据对象的创建分配给该对象的，并且会在没有对该对象的引用时由浏览器收回。JavaScript的垃圾收集机制本身并没有问题，但浏览器在为DOM对象分配和恢复内存的方式上有些出入。IE和Firefox均使用引用计数来为DOM对象处理内存。在引用计数系统中，每个所引用的对象都会保留一个计数，以获悉有多少对象正在引用它。如果计数为零，那么该对象就会被销毁，其占用的内存也会返回给堆。虽然这种解决方案总的来说还算有效，但是在循环引用方面却存在一些盲点。 当两个对象互相引用时，就构成了循环引用，其中对象的引用计数值都被赋为1。在纯垃圾收集系统中，循环引用问题不大：如果涉及的两个对象中有一个对象被任何其他对象引用，那么这两个对象都将被垃圾收集。而在引用计数系统中，这两个对象都不能被销毁，原因是引用计数永远不能为0。在同时使用了垃圾收集和引用计数的混合系统中，将会发生泄漏，因为系统不能正确识别循环引用。在这种情况下，DOM对象和JavaScript对象均不能被销毁。 循环引用很容易创建。在JavaScript最为方便的编程结构之一——闭包中，循环引用尤其突出。闭包会持有其外部作用域（包括局部变量、参数及方法）的引用，当闭包本身又被作用域成员（常见于DOM对象）持有时便构成循环引用，进一步导致内存泄露。

**反例：**

```javascript
function setClickListener(element, a, b) {
  element.onclick = function() {
    // 在这里用到a和b
  };
};
```

在上述代码中，即使没有使用element，闭包也保留了element、a和b的引用。由于element也保留了对闭包的引用，因此产生了循环引用，不能被GC回收。

**正例：**

```javascript
function setClickListener(element, a, b) {
  element.onclick = createHandler(a, b);
}

function createHandler(a, b) {
  // 通过添加另外一个函数来避免闭包本身，进而组织内存泄露
  return function() {
    // 在这里用到a和b
  }
}
```

#### 建议3.14 警惕JavaScript的浮点数

**说明：**JavaScript具有单一数字类型：`IEEE 754`双精度浮点数。拥有单一数字类型是JavaScript的最佳功能之一。多种数字类型可能是复杂性，混淆和错误的根源。但是，二进制浮点类型有一个最大的缺点是，它不能准确地表示小数部分，会导致让人意外的精度问题，见下面示例。

示例代码1：

```javascript
console.log(0.1 + 0.2 === 0.3); // 输出：false。所以通常禁止直接使用==或===来比较浮点数。
```

示例代码2：

```javascript
var sum1 = (0.1 + 0.2) + 0.3;
console.log(sum1); // 输出：0.6000000000000001

var sum2 = 0.1 + (0.2 + 0.3);
console.log(sum2); // 输出：0.6。所以对于二进制浮点数，(a + b) + c 不能保证产生于a + (b + c)相同的结果。
```

有效的解决方法有以下几种：

1. 尽可能的采用整数值运算，因为整数在表示是不需要舍入；

2. 使用JavaScript的原生方法`Number.prototype.toFixed(digits)`,`digist`参数表示小数点后数字的个数，不使用指数法，在必要时会进行四舍五入。使用该方法，在判断浮点数运算结果前对计算结果进行精度缩小。示例代码如下所示：

   ```javascript
   parseFloat(0.1 + 0.2).toFixed(1); //0.3
   ```

3. ES6 新增了一个极小的常量`Number.EPSILON =.220446049250313e-16 `，约等于`0.00000000000000022204`。`Number.EPSILON`的出现是用来判断浮点数的计算误差，如果浮点数计算得到的误差不超过`Number.EPSILON`的值，就表示可以接受这样的误差。示例代码如下所示：

   ```javascript
   function isNumberEquals(one, other) {
     return Math.abs(one - other) < Number.EPSILON;
   }
   var one = 0.1 + 0.2;
   var other = 0.3;
   console.log(isNumberEquals(one, other)); // 输出：true
   ```

4. 使用一些支持精确运算的类库方法，如`math.js`

   ```html
   <!DOCTYPE html>
   <html>
     <head>
       <script src="https://cdnjs.cloudflare.com/ajax/libs/mathjs/5.0.0/math.js"></script>
       <script type="text/javascript">
         function fn_click() {
           math.config({
             number: "BigNumber",
           });
           var result = math.add(math.bignumber(0.1), math.bignumber(0.2));
           alert(result);
         }
       </script>
     </head>
     <body>
       <input type="button" value="mathjs(0.1+0.2)" onclick="fn_click();" />
     </body>
   </html>
   
   ```

#### 建议3.15 不要使用可变参数的Array构造函数说

**说明：**通常不鼓励使用构造函数`new Array`的方法来构造新数组，因为当构造函数只有一个参数的时候，可能会导致意外情况，另外Array的全局定义也可能被重新修改，所以提倡使用数组文字表示法来创建数组，也就是`[]`表示法。
**反例：**

```javascript
const arr1 = new Array(x1, x2, x3);
const arr2 = new Array(x1, x2);
const arr3 = new Array(x3);
const arr4 = new Array();
```

除了第三种情况之外，其他都可以正常工作，如果`x1`是个整数，那么`arr3`就是长度为`x1`，值都为`undefined`的数组。如果`x1`是其他任何数字，那么将抛出异常，如果它是其他任何东西，那么它将是单元数组。

**正例：**

```javascript
const arr1 = [x1, x2, x3];
const arr2 = [x1, x2];
const arr3 = [x1];
const arr4 = [];
```

这种写法，就会省去很多麻烦。

同理，对于对象，同样不要使用`new Object()`，而是使用`{}`来创建。

#### 规则3.16 构建字符串时，优先使用字符串模板而不是字符串链接。

**说明：**模板字符串表达更简洁，更具可读性。

**反例：**

```javascript
function sayHi(name) {
  console.log('hi, ' + name);
}
```

**正例：**

```javascript
function sayHi(name) {
  console.log(`hi, ${name}`);
}
```

#### 规则3.17 数组遍历采用`for...of`，对象遍历采用`for...in`。

**反例：**

```javascript
let numbers = [1, 2, 3, 4];
let sum = 0;
for (let number in numbers) {
  sum += number;
}
// sum === 00123;
```

**正例：**

```javascript
let numbers = [1, 2, 3, 4];
let sum = 0;
for (let number in numbers) {
  sum += number;
}
// sum === 10
```

