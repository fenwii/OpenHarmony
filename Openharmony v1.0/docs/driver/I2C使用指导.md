# I2C使用指导<a name="ZH-CN_TOPIC_0000001053058269"></a>

## 使用流程<a name="section333203315215"></a>

使用I2C设备的一般流程如[图1](#fig166181128151112)所示。

**图 1**  I2C设备使用流程图<a name="fig166181128151112"></a>  


![](figures/zh-cn_image_0000001054056393.png)

## 打开I2C控制器<a name="section123631358135713"></a>

在进行I2C通信前，首先要调用I2cOpen打开I2C控制器。

struct DevHandle \*I2cOpen\(int16\_t number\);

**表 1**  I2cOpen参数和返回值描述

<a name="table7603619123820"></a>
<table><thead align="left"><tr id="row1060351914386"><th class="cellrowborder" valign="top" width="20.66%" id="mcps1.2.3.1.1"><p id="p14603181917382"><a name="p14603181917382"></a><a name="p14603181917382"></a><strong id="b16510829133012"><a name="b16510829133012"></a><a name="b16510829133012"></a>参数</strong></p>
</th>
<th class="cellrowborder" valign="top" width="79.34%" id="mcps1.2.3.1.2"><p id="p36031519183819"><a name="p36031519183819"></a><a name="p36031519183819"></a><strong id="b65222293309"><a name="b65222293309"></a><a name="b65222293309"></a>参数描述</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row1960431983813"><td class="cellrowborder" valign="top" width="20.66%" headers="mcps1.2.3.1.1 "><p id="p3604719123817"><a name="p3604719123817"></a><a name="p3604719123817"></a>number</p>
</td>
<td class="cellrowborder" valign="top" width="79.34%" headers="mcps1.2.3.1.2 "><p id="p221392414442"><a name="p221392414442"></a><a name="p221392414442"></a>I2C控制器号</p>
</td>
</tr>
<tr id="row11410612183019"><td class="cellrowborder" valign="top" width="20.66%" headers="mcps1.2.3.1.1 "><p id="p460381915385"><a name="p460381915385"></a><a name="p460381915385"></a><strong id="b4349113243013"><a name="b4349113243013"></a><a name="b4349113243013"></a>返回值</strong></p>
</td>
<td class="cellrowborder" valign="top" width="79.34%" headers="mcps1.2.3.1.2 "><p id="p96031619153812"><a name="p96031619153812"></a><a name="p96031619153812"></a><strong id="b63502322308"><a name="b63502322308"></a><a name="b63502322308"></a>返回值描述</strong></p>
</td>
</tr>
<tr id="row15410111273017"><td class="cellrowborder" valign="top" width="20.66%" headers="mcps1.2.3.1.1 "><p id="p1060418195389"><a name="p1060418195389"></a><a name="p1060418195389"></a>NULL</p>
</td>
<td class="cellrowborder" valign="top" width="79.34%" headers="mcps1.2.3.1.2 "><p id="p760471912388"><a name="p760471912388"></a><a name="p760471912388"></a>打开I2C控制器失败</p>
</td>
</tr>
<tr id="row1241081213303"><td class="cellrowborder" valign="top" width="20.66%" headers="mcps1.2.3.1.1 "><p id="p5604719133811"><a name="p5604719133811"></a><a name="p5604719133811"></a>设备句柄</p>
</td>
<td class="cellrowborder" valign="top" width="79.34%" headers="mcps1.2.3.1.2 "><p id="p3604181933818"><a name="p3604181933818"></a><a name="p3604181933818"></a>打开的I2C控制器设备句柄</p>
</td>
</tr>
</tbody>
</table>

假设系统中存在8个I2C控制器，编号从0到7，那么我们现在获取3号控制器

```
struct DevHandle *i2cHandle = NULL;  /* I2C控制器句柄 */

/* 打开I2C控制器 */
i2cHandle = I2cOpen(3);
if (i2cHandle == NULL) {
    HDF_LOGE("I2cOpen: failed\n");
    return;
}
```

## 进行I2C通信<a name="section11091522125812"></a>

消息传输

int32\_t I2cTransfer\(struct DevHandle \*handle, struct I2cMsg \*msgs, int16\_t count\);

**表 2**  I2cTransfer参数和返回值描述

<a name="table1934414174212"></a>
<table><thead align="left"><tr id="row1134415176216"><th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.1"><p id="p13295152320217"><a name="p13295152320217"></a><a name="p13295152320217"></a><strong id="b17389641205115"><a name="b17389641205115"></a><a name="b17389641205115"></a>参数</strong></p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.2"><p id="p1295112352115"><a name="p1295112352115"></a><a name="p1295112352115"></a><strong id="b19401541175118"><a name="b19401541175118"></a><a name="b19401541175118"></a>参数描述</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row5344101702113"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p19295132382111"><a name="p19295132382111"></a><a name="p19295132382111"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1051172572919"><a name="p1051172572919"></a><a name="p1051172572919"></a>I2C控制器设备句柄</p>
</td>
</tr>
<tr id="row17344171722117"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p9295122332113"><a name="p9295122332113"></a><a name="p9295122332113"></a>msgs</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p202951238218"><a name="p202951238218"></a><a name="p202951238218"></a>待传输数据的消息结构体数组</p>
</td>
</tr>
<tr id="row45812466213"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p1659246112117"><a name="p1659246112117"></a><a name="p1659246112117"></a>count</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p259124622119"><a name="p259124622119"></a><a name="p259124622119"></a>消息数组长度</p>
</td>
</tr>
<tr id="row04701426105110"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p17295142322113"><a name="p17295142322113"></a><a name="p17295142322113"></a><strong id="b2159044145115"><a name="b2159044145115"></a><a name="b2159044145115"></a>返回值</strong></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p142959232211"><a name="p142959232211"></a><a name="p142959232211"></a><strong id="b16160044135114"><a name="b16160044135114"></a><a name="b16160044135114"></a>返回值描述</strong></p>
</td>
</tr>
<tr id="row74701226125110"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p929532313211"><a name="p929532313211"></a><a name="p929532313211"></a>正整数</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p829512237217"><a name="p829512237217"></a><a name="p829512237217"></a>成功传输的消息结构体数目</p>
</td>
</tr>
<tr id="row204701126195115"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p12958234217"><a name="p12958234217"></a><a name="p12958234217"></a>负数</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1295192312112"><a name="p1295192312112"></a><a name="p1295192312112"></a>执行失败</p>
</td>
</tr>
</tbody>
</table>

I2C传输消息类型为I2cMsg，每个传输消息结构体表示一次读或写，通过一个消息数组，可以执行若干次的读写组合操作。

```
int32_t ret;
uint8_t wbuff[2] = { 0x12, 0x13 };
uint8_t rbuff[2] = { 0 };
struct I2cMsg msgs[2]; /* 自定义传输的消息结构体数组 */
msgs[0].buf = wbuff;    /* 写入的数据 */
msgs[0].len = 2;        /* 写入数据长度为2 */
msgs[0].addr = 0x5A;    /* 写入设备地址为0x5A */
msgs[0].flags = 0;      /* 传输标记为0，默认为写 */
msgs[1].buf = rbuff;    /* 要读取的数据 */
msgs[1].len = 2;        /* 读取数据长度为2 */
msgs[1].addr = 0x5A;    /* 读取设备地址为0x5A */
msgs[1].flags = I2C_FLAG_READ /* I2C_FLAG_READ置位 */
/* 进行一次自定义传输，传输的消息个数为2 */
ret = I2cTransfer(i2cHandle, msgs, 2);
if (ret != 2) {
    HDF_LOGE("I2cTransfer: failed, ret %d\n", ret);
    return;
}
```

>![](public_sys-resources/icon-caution.gif) **注意：** 
>-   I2cMsg结构体中的设备地址不包含读写标志位，读写信息由flags成员变量的读写控制位传递。
>-   本函数不对消息结构体个数count做限制，其最大个数度由具体I2C控制器决定。
>-   本函数也不对每个消息结构体中的数据长度做限制，同样由具体I2C控制器决定。
>-   本函数可能会引起系统休眠，不允许在中断上下文调用

## 关闭I2C控制器<a name="section13519505589"></a>

I2C通信完成之后，需要关闭2C控制器，关闭函数如下所示：

void I2cClose\(DevHandle \*handle\); 

**表 3**  I2cClose参数和返回值描述

<a name="table72517953115"></a>
<table><thead align="left"><tr id="row1525793312"><th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.1"><p id="p115402031153111"><a name="p115402031153111"></a><a name="p115402031153111"></a>参数</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.2"><p id="p65406313319"><a name="p65406313319"></a><a name="p65406313319"></a>参数描述</p>
</th>
</tr>
</thead>
<tbody><tr id="row1926109193116"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p105419317318"><a name="p105419317318"></a><a name="p105419317318"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1213245577"><a name="p1213245577"></a><a name="p1213245577"></a>I2C控制器设备句柄</p>
</td>
</tr>
</tbody>
</table>

```
I2cClose(i2cHandle); /* 关闭I2C控制器 */
```

