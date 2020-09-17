# 虚函数表和接口函数表设计介绍

## 虚函数表

方舟编译器会为每一个类生成一个虚方法表。在这个表中，会存储父类的虚方法，再加上子类的虚方法以及实现的接口类的Default方法。如果子类重载了父类的实现，那么在虚方法表中同样的位置，则会覆盖掉父类的方法。

下面，展示一个具体 的例子：

```java
class A {
  public int first() {
    return 0;
  }
}

class B extends A {
  public void foo() {
  }
  public int first() {
    return 1;
  }
}

class C extends A {
  public void bar() {
  }
  public int first() {
    return 2;
  }
}

public class IsEmpty {
  public static void main(String [] args) {
    A x = new B();
    x.first();
    A y = new C()
    y.first();
  }

  public void add(A x) {
    x.first();
  }
}
```



方舟编译器生成的虚函数表的结构如下：

A:
```
 _vtb_LA_3B:
        .quad   Ljava_2Flang_2FObject_3B_7Cclone_7C_28_29Ljava_2Flang_2FObject_3B - .
        .quad   Ljava_2Flang_2FObject_3B_7Cequals_7C_28Ljava_2Flang_2FObject_3B_29Z - .
        .quad   Ljava_2Flang_2FObject_3B_7Cfinalize_7C_28_29V - .
        .quad   Ljava_2Flang_2FObject_3B_7CgetClass_7C_28_29Ljava_2Flang_2FClass_3B - .
        .quad   Ljava_2Flang_2FObject_3B_7ChashCode_7C_28_29I - .
        .quad   Ljava_2Flang_2FObject_3B_7Cnotify_7C_28_29V - .
        .quad   Ljava_2Flang_2FObject_3B_7CnotifyAll_7C_28_29V - .
        .quad   Ljava_2Flang_2FObject_3B_7CtoString_7C_28_29Ljava_2Flang_2FString_3B - .
        .quad   Ljava_2Flang_2FObject_3B_7Cwait_7C_28_29V - .
        .quad   Ljava_2Flang_2FObject_3B_7Cwait_7C_28J_29V - .
        .quad   Ljava_2Flang_2FObject_3B_7Cwait_7C_28JI_29V - .
        .quad   LA_3B_7Cfirst_7C_28_29I - .
```

B:

```
 __vtb_LB_3B:
        .quad   Ljava_2Flang_2FObject_3B_7Cclone_7C_28_29Ljava_2Flang_2FObject_3B - .
        .quad   Ljava_2Flang_2FObject_3B_7Cequals_7C_28Ljava_2Flang_2FObject_3B_29Z - .
        .quad   Ljava_2Flang_2FObject_3B_7Cfinalize_7C_28_29V - .
        .quad   Ljava_2Flang_2FObject_3B_7CgetClass_7C_28_29Ljava_2Flang_2FClass_3B - .
        .quad   Ljava_2Flang_2FObject_3B_7ChashCode_7C_28_29I - .
        .quad   Ljava_2Flang_2FObject_3B_7Cnotify_7C_28_29V - .
        .quad   Ljava_2Flang_2FObject_3B_7CnotifyAll_7C_28_29V - .
        .quad   Ljava_2Flang_2FObject_3B_7CtoString_7C_28_29Ljava_2Flang_2FString_3B - .
        .quad   Ljava_2Flang_2FObject_3B_7Cwait_7C_28_29V - .
        .quad   Ljava_2Flang_2FObject_3B_7Cwait_7C_28J_29V - .
        .quad   Ljava_2Flang_2FObject_3B_7Cwait_7C_28JI_29V - .
        .quad   LB_3B_7Cfirst_7C_28_29I - .
        .quad   LB_3B_7Cfoo_7C_28_29V - .
```
C：
```
__vtb_LC_3B:
前面11个和A和B一样
       … …
       .quad   LC_3B_7Cfirst_7C_28_29I - .
       .quad   LC_3B_7Cbar_7C_28_29V - .

```

对比一下，我们可以发现：

1. 所有的类都是继承自Object类，所以虚函数表的前面11个函数都是继承自Object，且和父类Object布局保持一致。
2. 对于第12个函数，子类B覆盖了父类A，所以在同样的位置，父类是LA_3B_7Cfirst_7C_28_29I，子类是LB_3B_7Cfirst_7C_28_29I。类C继承至类A并重写了first函数，且实现了接口iD，所以12的位置为 LC_3B_7Cfirst_7C_28_29I，接口函数LiD_3B_7Csecond_7C_28_29I被放在了13的位置。

## 虚函数访问处理(编译时)

因为要保持多态性，所以在编译时，不能确定具体调用是哪个函数。在当前例子里面体现在这个位置：

```java
public class IsEmpty {
  public static void main(String [] args) {
    A x = new B();
    x.first();
    A y = new C();
    y.first();
  }

  public void add(A x) {
    x.first();
  }
}
```


像这种情况，我们编译时不能知道运行时调用的是B里面的first函数，还是C里面的first函数。

但是，因为first函数在A，B，C中布局一致，而这个例子当中first函数在vtab中的偏移是12，因此我们可以生成这样的访问代码：从相应的对象中拿到vtable指针，然后加上offset12。这样我们就能访问到正确的函数。

## 虚函数调用处理(运行时)

在程序执行过程中，以(图1)为例，当遇到虚拟函数调用的时候，我们执行如下步骤：
1. 判断对象(this_指针)是哪个类的实例(在图1中，this是类C的实例)；
2. 使用函数索引在对应类的虚拟函数表中查找；
3. 返回实际调用的函数指针。

![](media/javavmt.png)
<center>图1: Java虚拟函数调用的静态化</center>

## 接口函数表

Interface call类似于多重继承，比java单继承要复杂。多继承无法天然地确定唯一一个继承顺序。

在一个封闭的环境下，可以通过拓扑排序的方法确定一个顺序(iA，iB，iC)。好处是可以实现像虚函数表一样的访问方式来处理interface call。但是这样得到的一个类的itable会非常大，而且大部分是空洞。考虑到性能和代码大小，这种方法是不可用的。

![](media/Topology.png)


对于开放的环境，编译时刻是无法通过拓扑排序来确定一个顺序的，导致接口函数表里的方法顺序不固定，所以实际实现中没办法像虚函数调用一样实现一个顺序一致的方法表和访问形式为 offset 的访问机制。在编译时刻，可以确定一个类实现的所有接口，以及接口的继承关系。运行时对函数签名进行比较来确定需要调用的函数。因为字符串比较开销比较大，所以方舟编译器会在编译时刻对函数名字和签名进行哈希计算得出哈希值。运行时首先比较哈希值；如果哈希值相同，且不存在哈希冲突，则调用这个函数。如果存在哈希冲突，则进行函数名字和签名的比较，取得函数指针。

同时，考虑到运行时效率和 ROM 空间的原因，我们把 Itable 分成了两级表，第一级表为真正的 hash ，考虑到ROM空间的压力，我们把 hash 值设为23，然后，依据 hash 得到的值把函数地址填到这个值对应的位置上去（0~22）。如果我们一级 hash 表不发生冲突的话，那么在最后一个包含函数地址的位置之后的表项都是空白的，这样后面的表项可以被去掉而不需要占用空间。如果一级 hash 表发生冲突了，则在发生冲突的位置填0，然后在第23个 slot 的位置填上二级表的地址。

一级函数表结构如下：

|表序| 接口函数表项| 说明                                         |
|----|------------|---------------------------------------------|
|0   | &Func 或 0 | 对应Hash值的函数地址，没有则为0; 如果出现冲突，|
|1   | &Func 或 0 | 那么冲突的位置也为0，并且在第23个表项填上二级表 |
|2   | &Func 或 0 | 的地址; 如果没有冲突，那么将最后一个有对应函数的|
|... | &Func 或 0 | hash值( n )之后的表项删除                     |
|n   | &Func      |
|23  | &itbC      | 二级表的地址。如果一级表没有出现冲突，则该项不存在|


二级函数表的结构如下：

| 接口函数表项          | 说明                                             |
|----------------------|--------------------------------------------------|
| Size                 | 不冲突的接口函数表的大小                         |
| 1                    | 对齐站位作用，无实际意义                         |
| Func1_sig            | Func1签名的哈希值                                |
| &Func1               | Fun1的地址                                       |
| Func2_sig            | Func2签名的哈希值                                |
| &Func2               | Func2的地址                                      |
| ......               |                                                  |
| Func3_sig和Func4_sig | Func3签名的哈希值和Func4签名的哈希值，两个值相同 |
| 1                    | 表示冲突，因为func3和func4签名的哈希值一样       |
| ……                   |                                                  |
| Func3_sig            | Func3签名                                        |
| &Func3               | Func3的地址                                      |
| Func4_sig            | Func4签名                                        |
| &Func4               | Func4的地址                                      |
| ……                   |                                                  |

## 接口函数调用：

对于声明为如下形式的接口函数调用的情况，我们的调用过程如图2所示：

```java
interface B { funcB(); }
interface C { funcC(); }
interface D { funcD(); }
Class A implements B, C, D {}
```

![](media/interface1.jpg)

<center>图2：Java接口函数调用的静态化</center>


如图2所示，在程序执行过程中，我们执行如下步骤：

1. 判断对象(obj)是哪个类的实例，当前为类A的实例；
2. 根据hash值，在一级表中查找，存在则返回函数指针，如果对应位置为0，则通过二级表查找。在二级表中，使用函数签名的哈希值查找，如果找到就返回函数指针，否则用函数名查找；
3. 间接调用函数指针，并把相关的参数(args)传给间接调用。

下面，举一个具体的例子：

这个IsEmpty类实现了接口A和B，每个接口中声明有两个方法。

```java
interface A{
  public int add();
  public int minus();
}

interface B{
  public int mult();
  public int div();
}

public class IsEmpty implements A, B {
    public static void main(String[]args) {
    }

    public void test(B x) {
      x.mult();
    }

    public int add() {
      return 6 + 3;
    }

    public int minus() {
      return 6 - 3;
    }

    public int mult() {
      return 6 * 3;
    }

    public int div() {
      return 6 / 3;
    }
}
```

首先，我们来看一下 IsEmpty 的 itable 在 maple 代码里面是怎么样的：

```
var $__itb_LIsEmpty_3B fstatic <[24] <* void>> = [0, 0, 0, 0, 0, 0, 0, 0, addroffunc ptr &LIsEmpty_3B_7Cdiv_7C_28_29I, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, addroffunc ptr &LIsEmpty_3B_7Cadd_7C_28_29I, 0, 0, addrof ptr $__itabC_LIsEmpty_3B]

var $__itbC_LIsEmpty_3B fstatic <[6] <* void>> = [2, 1, 0xb97, addroffunc ptr &LIsEmpty_3B_7Cmult_7C_28_29I, 0x1f7f, addroffunc ptr &LIsEmpty_3B_7Cminus_7C_28_29I]
```

对应的汇编结构：

```
__itb_LIsEmpty_3B:
        .quad   0
        .quad   0
        .quad   0
        .quad   0
        .quad   0
        .quad   0
        .quad   0
        .quad   0
        .quad   LIsEmpty_3B_7Cdiv_7C_28_29I - .
        .quad   0
        .quad   0
        .quad   0
        .quad   0
        .quad   0
        .quad   0
        .quad   0
        .quad   0
        .quad   0
        .quad   0
        .quad   0
        .quad   LIsEmpty_3B_7Cadd_7C_28_29I - .
        .quad   0
        .quad   0
        .quad   __itabC_LIsEmpty_3B - .
```
```
__itbC_LIsEmpty_3B:
        .quad   2
        .quad   1
        .quad   2967
        .quad   LIsEmpty_3B_7Cmult_7C_28_29I - .
        .quad   8063
        .quad   LIsEmpty_3B_7Cminus_7C_28_29I - .
```

其中表项内容如下：

1. 一级表中(__itb_LIsEmpty_3B)，共23项，其中第9项和第20项为函数地址，第23项为二级表地址，由此可见一级表发生了冲突，从而需要二级表来确认具体的函数地址；

2. 二级表中第一项为2，表示有2个不冲突的函数，第二项为1，起到对齐占位的作用，而后面4项分别为函数签名产生的hash值和对应的函数地址。

接下来我们看到这个例子里面，源码中test函数中会产生一个interface-call，对应的maple代码如下：

```
if (eq u1 u64 (regread u64 %4, constval u64 0)) {
  callassigned &MCC_getFuncPtrFromItabSecondHash64 (regread ptr %3, constval u64 0xb97, conststr ptr "mult|()I") { regassign u64 %4}
}
icallassigned (regread u64 %4, regread ref %2) {}
```

可以看出调用逻辑是这样的：

首先判断一级itable表当中hash值对应位置表项是否为空，如果不空则直接使用该地址；如果为空，则调用 getFuncPtrFromItabSecondHash64 函数。

getFuncPtrFromItabSecondHash64 函数有三个参数，itable 地址，函数 basename 对应的 hash 值，和函数的签名。完整的调用过程是先通过 classinfo 找到对应的 itable 地址，然后进行 hash 值的比对，如果比对成功且不冲突就能得到正确的地址；如果比对冲突，则直接使用 signature name 进行比对(字符串比对)。

这里所访问的 itable 和上面列出的 IsEmpty 的itable表项形式一致。

##  Interface override

Java 8中引入了 `Default` 函数。父类中的实现会覆盖接口中的Default函数；接口之间的Default函数需要根据接口的继承关系来确定Override。如下所示，类cA继承类cB实现了接口iD，在cB和iD中都有foo的实现。对于cA来说，foo的实现来自父类cB而不是接口iD。

```java

interface iD {
  public default void foo(){System.out.println("iD foo");}
}

class cB {
  public void foo(){System.out.println("cB foo");}
}

class cA extends cB implements iD {
}

public class IsEmpty {
  public static void main(String [] args) {
    iD obj = new cA();
    obj.foo();
  }
}
```


如下所示，接口Parent和Son都定义了getValue。对于类Sson来说，getValue的实现来自Son，而不是来自Parent。

```java
interface Parent{
  default void getValue(){
    System.out.println("Parent getVatue……");
  }
}

interface Son extends Parent{
  default void getValue(){
    System.out.println("OfInt getValue……")
  }
}

abstract class OfPrimitive implements Parent{
}

class SSon extends OfPrimitive implements Son{
}

public class Main {
  static int get() {
    return 1;
  }
  
  public static void main(String[] args) {
    Parent son = (Parent)new SSon();
    son.getValue();

    SSon son2;
    if(get()==1) {
      son2 = new SSon();
    }
    else son2 = new SSon();
    son2.getValue();
  }
}
```
