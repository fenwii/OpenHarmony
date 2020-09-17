# 朴素版RC操作插入原理

引用计数（Reference Counting, RC）是计算机编程语言中的一种内存管理技术，是指将资源（可以是对象、内存或磁盘空间等等）的被引用次数保存起来，当被引用次数变为零时就将其释放的过程。使用引用计数技术可以实现自动资源管理的目的。同时引用计数还可以指使用引用计数技术回收未使用资源的垃圾回收算法。朴素版RC（Naive RC）是一种简单直接的RC插入操作。


Naive RC插入的基本原理
======================

- 对象的引用计数的来源：

   - 堆内对象（其它对象、本身）的引用   

   - 栈上的引用（包含寄存器）

   - 静态、全局变量

- 引用计数操作的插入规则（编译器和运行时），对应上面的:   

   - Object field的赋值，需要将field指向的新对象+1，原对象计数-1

   - 读取对象到栈上局部变量（含寄存器），需要对读取的对象引用计数+1

   - 局部变量Last Use后引用计数-1

   - 返回对象，引用计数+1，补偿局部变量Last Use后-1

-   简单示例

    - 插入前

     ```cpp
    class A {
      static Object static_field;
      Object instance_field;
      A() {
        static_field = new Object();
      }
    }
    Object foo(){
      A a = new A();
      bar(a, new Object())
      return a.instance_field;
    }
    void bar(A a, Object o) {
      a.instance_field = o;
    }
    ```	
   
    - 插入后

    ```cpp 
    class A {
      A() {
       local_var t = new Object(); // t是赋值给static_field过程中使用的临时变量
       old = static_field;
       static_field = t;
       IncRef(t); DecRef(old);  // 更新堆上RC
       DecRef(t); // 函数退出释放栈上RC
      }
    }
    Object foo(){
      A a = new A();
      bar(a, new Object());
      locl_var t = a.instance_field;
      IncRef(t) // 栈上变量引用RC+1
      IncRef(t) // 函数返回，返回值RC+1
      DecRef(a) // 函数退出释放栈上RC，释放a
      DecRef(t) // 函数退出释放栈上RC
      return t;
    }
    void bar(A a, Object o) {
      old = a.instance_field
      a.instance_field = o;
      IncRef(o); DecRef(old);
    }
     ```


- 引用计数函数MIntrinsicsId:

   - 基础函数
    使用方法：使用IrMap中的CreateIntrinsicCallMeStmt创建IntrinsiccallMeStmt语句，并插入到RC需要加减之处。

      - INTRN_MCCIncRef

      - INTRN_MCCDecRef

   - Load/Write函数
    使用方法：Write函数使用IrMap中的CreateIntrinsicCallMeStmt创建IntrinsiccallMeStmt语句替换左值具有static、global、volatile等属性的iassign语句、Load函数使用CreateIntrinsicCallAssignedMeStmt创建IntrinsiccallMeStmt语句，并替换右值具有static、global、volatile等属性的dassign语句，Load/Write函数均具有IncRef操作。

      -   INTRN_MCCLoadRef

      -   INTRN_MCCLoadRefS

      -   INTRN_MCCLoadRefVol

      -   INTRN_MCCLoadRefSVol

      -   INTRN_MCCWrite

      -   INTRN_MCCWriteS

      -   INTRN_MCCWriteVol

      -   INTRN_MCCWriteSVol

RefVar IncRef 处理规则：
========================

- 赋值语句处理：

   - 按照左值（赋值语句中被赋值的变量）、右值（赋值语句中被引用的值）表达式不同处理

   - 先处理右值：比如选择什么Load接口；不需要+1的右值（New、Call）

      - Global属性选择INTRN_MCCLoadRef

      - Static属性选择INTRN_MCCLoadRefS

      - Volatile属性选择INTRN_MCCLoadRefVol

   - 再处理左值：选择什么Write接口；是否需要保存老值等等

      - Global属性选择INTRN_MCCWriteRef

      - Static属性选择INTRN_MCCWriteRefS

      - Volatile属性选择INTRN_MCCWriteRefVol

-   返回值处理：

    - 返回值+1

- 局部变量处理：

   - 在当前函数退出前（异常、正常退出）引用计数减一

Rclowering处理流程：
====================

- 设置rclowering处理标志位
- 标记localrefvar

- rclowering预处理

   - 标记需要RC操作的变量

      - 需要标记DecRef的左值（赋值语句中被赋值的变量）：

         - Ref变量

   - 需要标记IncRef的右值（赋值语句中被引用的值或返回值等）：

      - Return值

      - Ref变量

     - hrow Value的寄存器

   - 清理栈变量

- rclowering处理

   - 处理包含Ref类型变量的赋值语句

      - DecRef原值

      - IncRef新值，参照RefVar IncRef 处理规则

- rclowering后处理

   - 在函数入口对参数做IncRef并标记为LocalRefVar属性

   - 处理函数返回值， 属性为LocalRefVar，则InRef，其他参照RefVar IncRef处理规则右值部分
