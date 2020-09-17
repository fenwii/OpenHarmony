RC API
----

引用计数(Reference Counting, RC)是计算机编程语言中的一种内存管理技术，是指将资源（可以是对象、内存或磁盘空间等等）的被引用次数保存起来，当被引用次数变为零时就将其释放的过程。使用引用计数技术可以实现自动资源管理的目的。同时引用计数还可以指使用引用计数技术回收未使用资源的垃圾回收算法。

由于需要支持RC操作，运行时为方舟编译器提供了如下API，以便其更好的生成相关代码。

## void MCC\_IncRef\_NaiveRCFast(address\_t obj)

**功能说明:**

将对象的RC值原子性的加一。

**入参说明:**

obj, 堆对象指针。

**返回值：**

无

## void MCC\_DecRef\_NaiveRCFast(address\_t obj)

**功能说明：**

将对象的RC值原子性的减一。

**入参说明:**

obj, 堆对象指针。

**返回值：**

无

## void MCC\_ClearLocalStackRef(address\_t \*addr)

**功能说明：**

用来清理线程栈上的局部引用（Local Reference）。当前编译框架下为支持异常和GC，此函数可以将对应栈地址上的局部引用清零，并将其老值的RC原子性的减一。

**入参说明:**

addr, 栈上局部引用的地址。

**返回值：**

无

## void MCC\_IncDecRef\_NaiveRCFast(address\_t incObj, address\_t decObj)

**功能说明：**

用来将incObj指向的对象的RC值原子性的加一和将decObj指向的对象的RC原子性的减一。

**入参说明:**

incObj，需要将RC原子性加一的对象地址。

decObj，需要将RC原子性减一的对象地址。

**返回值：**

无

## void MCC\_IncDecRefReset(address\_t incObj, address\_t \*decAddr)

**功能说明：**

将incObj指向的对象的RC值原子性的加一，并将栈地址指针decAddr存放的局部变量对象的RC原子性的减一，同时将栈地址指针decAddr指向的内存清零。

**入参说明:**

incObj，需要将RC原子性加一的堆对象。

decAddr，栈上局部引用的地址。

**返回值：**

无

## void MCC\_DecRefResetPair(address\_t \*decAddr0, address\_t \*decAddr1)

**功能说明：**

将所有参数指向的栈地址空间清零，并将对应包含的局部变量老值的RC原子性的减一。

**入参说明:**

decAddr0和decAddr1，栈上局部引用的地址。

**返回值：**

无

## void MCC\_SetObjectPermanent(address\_t obj)

**功能说明：**

将堆对象设置成永久存活的对象，调用之后obj对应的对象的RC会变成极大值。

**入参说明:**

obj的堆对象地址。

**返回值：**

无

## address\_t MCC\_LoadVolatileStaticField(address\_t \*fieldAddr)

**功能说明：**

从非易失性（Volatile）静态变量中取值，并且将取到的堆对象的RC原子性的加一。

**入参说明:**

fieldAddr，Volatile静态变量的地址。

**返回值：**

返回Volatile静态变量的值。

## address\_t MCC\_LoadRefStatic(address\_t \*fieldAddr)

**功能说明：**

从静态变量中取值，并且将取到的堆对象的RC原子性的加一。

**入参说明:**

fieldAddr，静态变量的地址。

**返回值：**

返回静态变量的值。

## address\_t MCC\_LoadVolatileWeakField(address\_t obj, address\_t \*fieldAddr)

**功能说明：**

从Weak的Volatile字段中取值， 如果取到非空的堆对象，会将该对象的RC原子性的加一。

**入参说明:**

obj，堆对象地址。

fieldAddr，标记为Weak的Volatile字段的地址

**返回值：**

返回标记为Weak的Volatile字段中的值，有可能返回空对象指针。

## address\_t MCC\_LoadWeakField(address\_t obj, address\_t \*field\_addr)

**功能说明：**

从Weak的字段中取值，如果取到非空的堆对象，会将该对象的RC原子性的加一。

**入参说明:**

obj，堆对象地址。

fieldAddr，标记为Weak的字段的地址

**返回值：**

返回标记为Weak的字段中的值，有可能返回空对象指针。

## address\_t MCC\_LoadRefField\_NaiveRCFast(address\_t obj, address\_t \*fieldAddr)

**功能说明：**

从fieldAddr字段取值，并将取到的堆对象的RC原子性的加一。

**入参说明:**

obj，堆对象地址。

fieldAddr，对象对应字段的地址

**返回值：**

返回对象字段中存储的值。

## address\_t MCC\_LoadVolatileField(address\_t obj, address\_t \*fieldAddr)

**功能说明：**

从Volatile字段中取值，并将取到的堆对象的RC原子性的加一。

**入参说明:**

obj，堆对象地址。

fieldAddr，对象对应Volatile字段的地址

**返回值：**

返回对象Volatile字段中存储的值。

## void MCC\_WriteReferent(address\_t obj, address\_t value)

**功能说明：**

写入java.lang.ref.Reference的referent字段，如果取到非空的堆对象，会将该对象的RC原子性的加一。

**入参说明:**

obj，java.lang.ref.Reference对象地址。

value，作为referent的堆对象地址

**返回值：**

无。

## void MCC\_WriteVolatileStaticFieldNoInc(address\_t \*fieldAddr, address\_t value)

**功能说明：**

向Volatile静态变量中写入堆对象，此调用不改变写入的堆对象的RC，但是会将静态变量存储的老值的RC原子性的减一。

**入参说明:**

fieldAddr，Volatile静态变量的地址。

value，待写入堆对象地址

**返回值：**

无。

## void MCC\_WriteVolatileStaticFieldNoDec(address\_t \*fieldAddr, address\_t value)

**功能说明：**

向Volatile静态变量中写入堆对象，此调用会将新写入的堆对象value的RC原子性的加一，但是不将静态变量的老值减一。

**入参说明:**

fieldAddr，Volatile静态变量的地址。

value，待写入堆对象地址

**返回值：**

无。

## void MCC\_WriteVolatileStaticFieldNoRC(address\_t \*fieldAddr, address\_t value)

**功能说明：**

向Volatile静态变量中写入堆对象，此调用不会改变写入的新值（value）的RC，也不会改变老值（fieldAddr存放的值）的RC。

**入参说明:**

fieldAddr，Volatile静态变量的地址。

value，待写入堆对象地址

**返回值：**

无。

## void MCC\_WriteVolatileStaticField(address\_t \*fieldAddr, address\_t value)

**功能说明：**

向Volatile静态变量中写入堆对象，此调用会将新写入的堆对象value的RC原子性的加一，但是并将静态变量的老值的RC减一。

**入参说明:**

fieldAddr，Volatile静态变量的地址。

value，待写入堆对象地址

**返回值：**

无。

## void MCC\_WriteRefFieldStaticNoInc(address\_t \*fieldAddr, address\_t value)

**功能说明：**

向对象普通静态变量字段中写入堆对象value，此调用不会将新写入的堆对象value的RC原子性的加一，但是会将其存储的老值的RC减一。

**入参说明:**

fieldAddr，对象静态变量字段的地址。

value，待写入堆对象地址

**返回值：**

无。

## void MCC\_WriteRefFieldStaticNoDec(address\_t \*fieldAddr, address\_t value)

**功能说明：**

向对象普通静态变量字段中写入堆对象value，此调用会将新写入的堆对象value的RC原子性的加一，但是不会将其存储的老值的RC减一。

**入参说明:**

fieldAddr，对象静态变量字段的地址。

value，待写入堆对象地址

**返回值：**

无。

## void MCC\_WriteRefFieldStaticNoRC(address\_t \*fieldAddr, address\_t value)

**功能说明：**

向对象普通静态变量字段中写入堆对象value，此调用不会将新写入的堆对象value的RC原子性的加一，也不会将其存储的老值的RC减一。

**入参说明:**

fieldAddr，对象静态变量字段的地址。

value，待写入堆对象地址

**返回值：**

无。

## void MCC\_WriteRefFieldStatic(address\_t \*fieldAddr, address\_t value)

**功能说明：**

向对象普通静态变量字段中写入堆对象value，此调用会将新写入的堆对象value的RC原子性的加一，同时会将其存储的老值的RC减一。

**入参说明:**

fieldAddr，对象静态变量字段的地址。

value，待写入堆对象地址

**返回值：**

无。

## void MCC\_WriteVolatileFieldNoInc(address\_t obj, address\_t \*fieldAddr, address\_t value)

**功能说明：**

向对象Volatile变量字段中写入堆对象value，此调用不会将新写入的堆对象value的RC原子性的加一，但是会将其存储的老值的RC减一。

**入参说明:**

obj，对象的地址

fieldAddr，对象volatile变量字段的地址。

value，待写入堆对象地址

**返回值：**

无。

## void MCC\_WriteVolatileFieldNoDec(address\_t obj, address\_t \*fieldAddr, address\_t value)

**功能说明：**

向对象Volatile变量字段中写入堆对象value，此调用会将新写入的堆对象value的RC原子性的加一，但是不会并将其存储的老值的RC减一。

**入参说明:**

obj，对象的地址

fieldAddr，对象volatile变量字段的地址。

value，待写入堆对象地址

**返回值：**

无。

## void MCC\_WriteVolatileFieldNoRC(address\_t obj, address\_t \*fieldAddr, address\_t value)

**功能说明：**

向对象Volatile变量字段中写入堆对象value，此调用不会将新写入的堆对象value的RC原子性的加一，也不会将其存储的老值的RC减一。

**入参说明:**

obj，对象的地址

fieldAddr，对象volatile变量字段的地址。

value，待写入堆对象地址

**返回值：**

无。

## void MCC\_WriteVolatileField(address\_t obj, address\_t \*fieldAddr, address\_t value)

**功能说明：**

向对象Volatile变量字段中写入堆对象value，此调用会将新写入的堆对象value的RC原子性的加一，也会将其存储的老值的RC减一。

**入参说明:**

obj，对象的地址

fieldAddr，对象volatile变量字段的地址。

value，待写入堆对象地址

**返回值：**

无。

## void MCC\_WriteRefFieldNoInc(address\_t obj, address\_t \*fieldAddr, address\_t value)

**功能说明：**

向对象普通变量字段中写入堆对象value，此调用不会将新写入的堆对象value的RC原子性的加一，但是会将其存储的老值的RC减一。

**入参说明:**

obj，对象的地址

fieldAddr，对象普通变量字段的地址。

value，待写入堆对象地址

**返回值：**

无。

## void MCC\_WriteRefFieldNoDec(address\_t obj, address\_t \*fieldAddr, address\_t value)

**功能说明：**

向对象普通变量字段中写入堆对象value，此调用会将新写入的堆对象value的RC原子性的加一，但是不会将其存储的老值的RC减一。

**入参说明:**

obj，对象的地址

fieldAddr，对象普通变量字段的地址。

value，待写入堆对象地址

**返回值：**

无。

## void MCC\_WriteRefFieldNoRC(address\_t obj, address\_t \*fieldAddr, address\_t value)

**功能说明：**

向对象普通变量字段中写入堆对象value，此调用不会将新写入的堆对象value的RC原子性的加一，也不会将其存储的老值的RC减一。

**入参说明:**

obj，对象的地址

fieldAddr，对象普通变量字段的地址。

value，待写入堆对象地址

**返回值：**

无。

## void MCC\_WriteRefField(address\_t obj, address\_t \*fieldAddr, address\_t value)

**功能说明：**

向对象普通变量字段中写入堆对象value，此调用会将新写入的堆对象value的RC原子性的加一，也会将其存储的老值的RC减一。

**入参说明:**

obj，对象的地址

fieldAddr，对象普通变量字段的地址。

value，待写入堆对象地址

**返回值：**

无。

## void MCC\_WriteVolatileWeakField(address\_t obj, address\_t \*fieldAddr, address\_t value)

**功能说明：**

向对象标记为Weak的volatile变量字段中写入堆对象value，此调用会将新写入的堆对象value的Weak RC原子性的加一，也会将其存储的老值的Weak RC减一。

**入参说明:**

obj，对象的地址

fieldAddr，对象标记为Weak的volatile变量字段的地址。

value，待写入堆对象地址

**返回值：**

无。

## void MCC\_WriteWeakField(address\_t obj, address\_t \*fieldAddr, address\_t value)

**功能说明：**

向对象标记为Weak的普通变量字段中写入堆对象value，此调用会将新写入的堆对象value的Weak RC原子性的加一，也会将其存储的老值的Weak RC减一。

**入参说明:**

obj，对象的地址

fieldAddr，对象标记为Weak的普通变量字段的地址。

value，待写入堆对象地址

**返回值：**

无。
