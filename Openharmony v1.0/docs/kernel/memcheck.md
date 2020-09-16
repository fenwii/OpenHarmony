# memcheck<a name="ZH-CN_TOPIC_0000001052170276"></a>

## 命令功能<a name="section191633812516"></a>

检查动态申请的内存块是否完整，是否存在内存越界造成节点损坏。

## 命令格式<a name="section428816435510"></a>

memcheck

## 参数说明<a name="section1939943304411"></a>

无。

## 使用指南<a name="section228914491951"></a>

-   当内存池所有节点完整时，输出"system memcheck over, all passed!"。
-   当内存池存在节点不完整时，输出被损坏节点的内存块信息。

## 使用实例<a name="section17373205314515"></a>

举例：输入memcheck

## 输出说明<a name="section13406205385413"></a>

**图 1**  当前没有内存越界<a name="fig1115313610438"></a>  
![](figures/当前没有内存越界.png "当前没有内存越界")

**图 2**  出现内存越界<a name="fig6414131084419"></a>  
![](figures/出现内存越界.png "出现内存越界")

