# UART使用指导<a name="ZH-CN_TOPIC_0000001052459079"></a>

## 使用流程<a name="section47784125013"></a>

使用UART的一般流程如[图1](#p58686354483)所示。

**图 1**  UART使用流程图<a name="fig1852173020185"></a>  


![](figures/zh-cn_image_0000001054006983.png)

## 获取UART设备句柄<a name="section146445153110"></a>

在使用UART进行通信时，首先要调用UartOpen获取UART设备句柄，该函数会返回指定端口号的UART设备句柄。

struct DevHandle \*UartOpen\(uint32\_t port\);

**表 1**  UartOpen参数和返回值描述

<a name="table14222165114310"></a>
<table><thead align="left"><tr id="row1022175133111"><th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.1"><p id="p13221551153117"><a name="p13221551153117"></a><a name="p13221551153117"></a>参数</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.2"><p id="p122211251103111"><a name="p122211251103111"></a><a name="p122211251103111"></a>参数描述</p>
</th>
</tr>
</thead>
<tbody><tr id="row6222451133114"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p92221518315"><a name="p92221518315"></a><a name="p92221518315"></a>port</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1322217518318"><a name="p1322217518318"></a><a name="p1322217518318"></a>UART设备号</p>
</td>
</tr>
<tr id="row1122245153112"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p102221451123118"><a name="p102221451123118"></a><a name="p102221451123118"></a><strong id="b1922235110318"><a name="b1922235110318"></a><a name="b1922235110318"></a>返回值</strong></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1122215143113"><a name="p1122215143113"></a><a name="p1122215143113"></a><strong id="b19222205193117"><a name="b19222205193117"></a><a name="b19222205193117"></a>返回值描述</strong></p>
</td>
</tr>
<tr id="row522275114317"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p422235114313"><a name="p422235114313"></a><a name="p422235114313"></a>NULL</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p5222351203112"><a name="p5222351203112"></a><a name="p5222351203112"></a>获取UART设备句柄失败</p>
</td>
</tr>
<tr id="row1222212513311"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p5222125115316"><a name="p5222125115316"></a><a name="p5222125115316"></a>设备句柄</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p192228515311"><a name="p192228515311"></a><a name="p192228515311"></a>UART设备句柄</p>
</td>
</tr>
</tbody>
</table>

假设系统中的UART端口号为3，获取该UART设备句柄的示例如下：

```
struct DevHandle *handle = NULL;    /* UART设备句柄*/
uint32_t port = 3;                  /* UART设备端口号 */
handle = UartOpen(port);
if (handle == NULL) {
    HDF_LOGE("UartOpen: failed!\n");
    return;
}
```

## UART设置波特率<a name="section1862705516339"></a>

在通信之前，需要设置UART的波特率，设置波特率的函数如下所示：

int32\_t UartSetBaud\(struct DevHandle \*handle, uint32\_t baudRate\);

**表 2**  UartSetBaud参数和返回值描述

<a name="table539135313325"></a>
<table><thead align="left"><tr id="row15391205311323"><th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.1"><p id="p11390453103216"><a name="p11390453103216"></a><a name="p11390453103216"></a>参数</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.2"><p id="p839065316328"><a name="p839065316328"></a><a name="p839065316328"></a>参数描述</p>
</th>
</tr>
</thead>
<tbody><tr id="row2039115373216"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p1639165310324"><a name="p1639165310324"></a><a name="p1639165310324"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p539115320328"><a name="p539115320328"></a><a name="p539115320328"></a>UART设备句柄</p>
</td>
</tr>
<tr id="row163911753143214"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p13911653203215"><a name="p13911653203215"></a><a name="p13911653203215"></a>baudRate</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p163919537322"><a name="p163919537322"></a><a name="p163919537322"></a>待设置的波特率值</p>
</td>
</tr>
<tr id="row539155343218"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p1039185313321"><a name="p1039185313321"></a><a name="p1039185313321"></a><strong id="b139195343217"><a name="b139195343217"></a><a name="b139195343217"></a>返回值</strong></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p123911753143213"><a name="p123911753143213"></a><a name="p123911753143213"></a><strong id="b143911353163218"><a name="b143911353163218"></a><a name="b143911353163218"></a>返回值描述</strong></p>
</td>
</tr>
<tr id="row2391853153218"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p17391185310322"><a name="p17391185310322"></a><a name="p17391185310322"></a>0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p14391653193210"><a name="p14391653193210"></a><a name="p14391653193210"></a>UART设置波特率成功</p>
</td>
</tr>
<tr id="row23912053143211"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p7391165320321"><a name="p7391165320321"></a><a name="p7391165320321"></a>负数</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p639185318322"><a name="p639185318322"></a><a name="p639185318322"></a>UART设置波特率失败</p>
</td>
</tr>
</tbody>
</table>

假设需要设置的UART波特率为9600，设置波特率的实例如下：

```
int32_t ret;
/* 设置UART波特率 */
ret = UartSetBaud(handle, 9600);
if (ret != 0) {
    HDF_LOGE("UartSetBaud: failed, ret %d\n", ret);
}
```

## UART获取波特率<a name="section1263651563414"></a>

设置UART的波特率后，可以通过获取波特率接口来查看UART当前的波特率，获取波特率的函数如下所示：

int32\_t UartGetBaud\(struct DevHandle \*handle, uint32\_t \*baudRate\);

**表 3**  UartGetBaud参数和返回值描述

<a name="table20393185311326"></a>
<table><thead align="left"><tr id="row19392653123215"><th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.1"><p id="p6392105315326"><a name="p6392105315326"></a><a name="p6392105315326"></a>参数</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.2"><p id="p53920531329"><a name="p53920531329"></a><a name="p53920531329"></a>参数描述</p>
</th>
</tr>
</thead>
<tbody><tr id="row103921553103211"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p1539220536326"><a name="p1539220536326"></a><a name="p1539220536326"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p6392553203217"><a name="p6392553203217"></a><a name="p6392553203217"></a>UART设备句柄</p>
</td>
</tr>
<tr id="row1539211532322"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p93921053123210"><a name="p93921053123210"></a><a name="p93921053123210"></a>baudRate</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p93926536328"><a name="p93926536328"></a><a name="p93926536328"></a>接收波特率值的指针</p>
</td>
</tr>
<tr id="row1239318531326"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p17392653123213"><a name="p17392653123213"></a><a name="p17392653123213"></a><strong id="b3392165383219"><a name="b3392165383219"></a><a name="b3392165383219"></a>返回值</strong></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1339365316327"><a name="p1339365316327"></a><a name="p1339365316327"></a><strong id="b63932053183218"><a name="b63932053183218"></a><a name="b63932053183218"></a>返回值描述</strong></p>
</td>
</tr>
<tr id="row143939531328"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p2393953153213"><a name="p2393953153213"></a><a name="p2393953153213"></a>0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p8393165383218"><a name="p8393165383218"></a><a name="p8393165383218"></a>UART获取波特率成功</p>
</td>
</tr>
<tr id="row5393105363210"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p17393125363215"><a name="p17393125363215"></a><a name="p17393125363215"></a>负数</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1539325393211"><a name="p1539325393211"></a><a name="p1539325393211"></a>UART获取波特率失败</p>
</td>
</tr>
</tbody>
</table>

获取波特率的实例如下：

```
int32_t ret;
uint32_t baudRate;
/* 获取UART波特率 */
ret = UartGetBaud(handle, &baudRate);
if (ret != 0) {
    HDF_LOGE("UartGetBaud: failed, ret %d\n", ret);
}
```

## UART设置设备属性<a name="section1770091483814"></a>

在通信之前，需要设置UART的设备属性，设置设备属性的函数如下图所示：

int32\_t UartSetAttribute\(struct DevHandle \*handle, struct UartAttribute \*attribute\)；

**表 4**  UartSetAttribute参数和返回值描述

<a name="table1453119335341"></a>
<table><thead align="left"><tr id="row3530433103416"><th class="cellrowborder" valign="top" width="49.980000000000004%" id="mcps1.2.3.1.1"><p id="p1853073310341"><a name="p1853073310341"></a><a name="p1853073310341"></a>参数</p>
</th>
<th class="cellrowborder" valign="top" width="50.019999999999996%" id="mcps1.2.3.1.2"><p id="p553083393417"><a name="p553083393417"></a><a name="p553083393417"></a>参数描述</p>
</th>
</tr>
</thead>
<tbody><tr id="row55303331347"><td class="cellrowborder" valign="top" width="49.980000000000004%" headers="mcps1.2.3.1.1 "><p id="p1530113313341"><a name="p1530113313341"></a><a name="p1530113313341"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="50.019999999999996%" headers="mcps1.2.3.1.2 "><p id="p3530173313346"><a name="p3530173313346"></a><a name="p3530173313346"></a>UART设备句柄</p>
</td>
</tr>
<tr id="row45309337342"><td class="cellrowborder" valign="top" width="49.980000000000004%" headers="mcps1.2.3.1.1 "><p id="p553083319348"><a name="p553083319348"></a><a name="p553083319348"></a>attribute</p>
</td>
<td class="cellrowborder" valign="top" width="50.019999999999996%" headers="mcps1.2.3.1.2 "><p id="p5530133314343"><a name="p5530133314343"></a><a name="p5530133314343"></a>待设置的设备属性</p>
</td>
</tr>
<tr id="row12530833103415"><td class="cellrowborder" valign="top" width="49.980000000000004%" headers="mcps1.2.3.1.1 "><p id="p185309331345"><a name="p185309331345"></a><a name="p185309331345"></a><strong id="b145302033193410"><a name="b145302033193410"></a><a name="b145302033193410"></a>返回值</strong></p>
</td>
<td class="cellrowborder" valign="top" width="50.019999999999996%" headers="mcps1.2.3.1.2 "><p id="p145309332344"><a name="p145309332344"></a><a name="p145309332344"></a><strong id="b553018331348"><a name="b553018331348"></a><a name="b553018331348"></a>返回值描述</strong></p>
</td>
</tr>
<tr id="row14530203310348"><td class="cellrowborder" valign="top" width="49.980000000000004%" headers="mcps1.2.3.1.1 "><p id="p1653014339343"><a name="p1653014339343"></a><a name="p1653014339343"></a>0</p>
</td>
<td class="cellrowborder" valign="top" width="50.019999999999996%" headers="mcps1.2.3.1.2 "><p id="p1453023323419"><a name="p1453023323419"></a><a name="p1453023323419"></a>UART设置设备属性成功</p>
</td>
</tr>
<tr id="row6531163373412"><td class="cellrowborder" valign="top" width="49.980000000000004%" headers="mcps1.2.3.1.1 "><p id="p16530123310345"><a name="p16530123310345"></a><a name="p16530123310345"></a>负数</p>
</td>
<td class="cellrowborder" valign="top" width="50.019999999999996%" headers="mcps1.2.3.1.2 "><p id="p1953118334347"><a name="p1953118334347"></a><a name="p1953118334347"></a>UART设置设备属性失败</p>
</td>
</tr>
</tbody>
</table>

设置UART的设备属性的实例如下：

```
int32_t ret;
struct UartAttribute attribute;
attribute.dataBits = UART_ATTR_DATABIT_7;   /* UART传输数据位宽，一次传输7个bit */
attribute.parity = UART_ATTR_PARITY_NONE;   /* UART传输数据无校检 */
attribute.stopBits = UART_ATTR_STOPBIT_1;   /* UART传输数据停止位为1位 */
attribute.rts = UART_ATTR_RTS_DIS;          /* UART禁用RTS */
attribute.cts = UART_ATTR_CTS_DIS;          /* UART禁用CTS */
attribute.fifoRxEn = UART_ATTR_RX_FIFO_EN;  /* UART使能RX FIFO */
attribute.fifoTxEn = UART_ATTR_TX_FIFO_EN;  /* UART使能TX FIFO */
/* 设置UART设备属性 */
ret = UartSetAttribute(handle, &attribute);
if (ret != 0) {
    HDF_LOGE("UartSetAttribute: failed, ret %d\n", ret);
}
```

## UART获取设备属性<a name="section117543316384"></a>

设置UART的设备属性后，可以通过获取设备属性接口来查看UART当前的设备属性，获取设备属性的函数如下图所示：

int32\_t UartGetAttribute\(struct DevHandle \*handle, struct UartAttribute \*attribute\);

**表 5**  UartGetAttribute参数和返回值描述

<a name="table17532123316342"></a>
<table><thead align="left"><tr id="row18531193383420"><th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.1"><p id="p85311833143420"><a name="p85311833143420"></a><a name="p85311833143420"></a>参数</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.2"><p id="p17531103319348"><a name="p17531103319348"></a><a name="p17531103319348"></a>参数描述</p>
</th>
</tr>
</thead>
<tbody><tr id="row35311533153413"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p453133333418"><a name="p453133333418"></a><a name="p453133333418"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p753193323420"><a name="p753193323420"></a><a name="p753193323420"></a>UART设备句柄</p>
</td>
</tr>
<tr id="row1953103315344"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p35315333346"><a name="p35315333346"></a><a name="p35315333346"></a>attribute</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p14531633133416"><a name="p14531633133416"></a><a name="p14531633133416"></a>接收UART设备属性的指针</p>
</td>
</tr>
<tr id="row45321433143415"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p653273363417"><a name="p653273363417"></a><a name="p653273363417"></a><strong id="b19531153314349"><a name="b19531153314349"></a><a name="b19531153314349"></a>返回值</strong></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1653203312347"><a name="p1653203312347"></a><a name="p1653203312347"></a><strong id="b185321330348"><a name="b185321330348"></a><a name="b185321330348"></a>返回值描述</strong></p>
</td>
</tr>
<tr id="row175320339342"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p10532163383412"><a name="p10532163383412"></a><a name="p10532163383412"></a>0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p5532143319341"><a name="p5532143319341"></a><a name="p5532143319341"></a>UART获取设备属性成功</p>
</td>
</tr>
<tr id="row125327337340"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p19532153317345"><a name="p19532153317345"></a><a name="p19532153317345"></a>负数</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p175321933163410"><a name="p175321933163410"></a><a name="p175321933163410"></a>UART获取设备属性失败</p>
</td>
</tr>
</tbody>
</table>

获取UART的设备属性的实例如下：

```
int32_t ret;
struct UartAttribute attribute;
/* 获取UART设备属性 */
ret = UartGetAttribute(handle, &attribute);
if (ret != 0) {
    HDF_LOGE("UartGetAttribute: failed, ret %d\n", ret);
}
```

## 设置UART传输模式<a name="section187233112369"></a>

在通信之前，需要设置UART的传输模式，设置传输模式的函数如下图所示：

int32\_t UartSetTransMode\(struct DevHandle \*handle, enum UartTransMode mode\)；

**表 6**  UartSetTransMode参数和返回值描述

<a name="table131892266313"></a>
<table><thead align="left"><tr id="row018922615318"><th class="cellrowborder" valign="top" width="49.980000000000004%" id="mcps1.2.3.1.1"><p id="p131891826835"><a name="p131891826835"></a><a name="p131891826835"></a>参数</p>
</th>
<th class="cellrowborder" valign="top" width="50.019999999999996%" id="mcps1.2.3.1.2"><p id="p101894269314"><a name="p101894269314"></a><a name="p101894269314"></a>参数描述</p>
</th>
</tr>
</thead>
<tbody><tr id="row11893261734"><td class="cellrowborder" valign="top" width="49.980000000000004%" headers="mcps1.2.3.1.1 "><p id="p81897261333"><a name="p81897261333"></a><a name="p81897261333"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="50.019999999999996%" headers="mcps1.2.3.1.2 "><p id="p5190142618310"><a name="p5190142618310"></a><a name="p5190142618310"></a>UART设备句柄</p>
</td>
</tr>
<tr id="row1119082615317"><td class="cellrowborder" valign="top" width="49.980000000000004%" headers="mcps1.2.3.1.1 "><p id="p1519012261314"><a name="p1519012261314"></a><a name="p1519012261314"></a>mode</p>
</td>
<td class="cellrowborder" valign="top" width="50.019999999999996%" headers="mcps1.2.3.1.2 "><p id="p121901026632"><a name="p121901026632"></a><a name="p121901026632"></a>待设置的传输模式，</p>
</td>
</tr>
<tr id="row19190152612317"><td class="cellrowborder" valign="top" width="49.980000000000004%" headers="mcps1.2.3.1.1 "><p id="p131900266316"><a name="p131900266316"></a><a name="p131900266316"></a><strong id="b61902026833"><a name="b61902026833"></a><a name="b61902026833"></a>返回值</strong></p>
</td>
<td class="cellrowborder" valign="top" width="50.019999999999996%" headers="mcps1.2.3.1.2 "><p id="p1519022616315"><a name="p1519022616315"></a><a name="p1519022616315"></a><strong id="b319014261837"><a name="b319014261837"></a><a name="b319014261837"></a>返回值描述</strong></p>
</td>
</tr>
<tr id="row919016261932"><td class="cellrowborder" valign="top" width="49.980000000000004%" headers="mcps1.2.3.1.1 "><p id="p10190526334"><a name="p10190526334"></a><a name="p10190526334"></a>0</p>
</td>
<td class="cellrowborder" valign="top" width="50.019999999999996%" headers="mcps1.2.3.1.2 "><p id="p1219012264318"><a name="p1219012264318"></a><a name="p1219012264318"></a>UART设置传输模式成功</p>
</td>
</tr>
<tr id="row1219017262313"><td class="cellrowborder" valign="top" width="49.980000000000004%" headers="mcps1.2.3.1.1 "><p id="p15190162616316"><a name="p15190162616316"></a><a name="p15190162616316"></a>负数</p>
</td>
<td class="cellrowborder" valign="top" width="50.019999999999996%" headers="mcps1.2.3.1.2 "><p id="p131906262311"><a name="p131906262311"></a><a name="p131906262311"></a>UART设置传输模式失败</p>
</td>
</tr>
</tbody>
</table>

假设需要设置的UART传输模式为UART\_MODE\_RD\_BLOCK，设置传输模式的实例如下：

```
int32_t ret;
/* 设置UART传输模式 */
ret = UartSetTransMode(handle, UART_MODE_RD_BLOCK);
if (ret != 0) {
    HDF_LOGE("UartSetTransMode: failed, ret %d\n", ret);
}
```

## 向UART设备写入指定长度的数据<a name="section82416423368"></a>

对应的接口函数如下所示：

int32\_t UartWrite\(struct DevHandle \*handle, uint8\_t \*data, uint32\_t size\);

**表 7**  UartWrite参数和返回值描述

<a name="table27825111368"></a>
<table><thead align="left"><tr id="row1578171123619"><th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.1"><p id="p078112115360"><a name="p078112115360"></a><a name="p078112115360"></a>参数</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.2"><p id="p37811711163612"><a name="p37811711163612"></a><a name="p37811711163612"></a>参数描述</p>
</th>
</tr>
</thead>
<tbody><tr id="row1878291143611"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p07818112360"><a name="p07818112360"></a><a name="p07818112360"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p178281113369"><a name="p178281113369"></a><a name="p178281113369"></a>UART设备句柄</p>
</td>
</tr>
<tr id="row7782811123614"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p8782911173610"><a name="p8782911173610"></a><a name="p8782911173610"></a>data</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p17782171120366"><a name="p17782171120366"></a><a name="p17782171120366"></a>待写入数据的指针</p>
</td>
</tr>
<tr id="row1578251112367"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p3782911183612"><a name="p3782911183612"></a><a name="p3782911183612"></a>size</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p17782161110366"><a name="p17782161110366"></a><a name="p17782161110366"></a>待写入数据的长度</p>
</td>
</tr>
<tr id="row1378281113363"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p87821411183616"><a name="p87821411183616"></a><a name="p87821411183616"></a><strong id="b157825113363"><a name="b157825113363"></a><a name="b157825113363"></a>返回值</strong></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p13782111116361"><a name="p13782111116361"></a><a name="p13782111116361"></a><strong id="b978211113366"><a name="b978211113366"></a><a name="b978211113366"></a>返回值描述</strong></p>
</td>
</tr>
<tr id="row47822112365"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p107821011103613"><a name="p107821011103613"></a><a name="p107821011103613"></a>0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p11782191103610"><a name="p11782191103610"></a><a name="p11782191103610"></a>UART写数据成功</p>
</td>
</tr>
<tr id="row11782911113611"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p1578221111367"><a name="p1578221111367"></a><a name="p1578221111367"></a>负数</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p9782151110366"><a name="p9782151110366"></a><a name="p9782151110366"></a>UART写数据失败</p>
</td>
</tr>
</tbody>
</table>

写入指定长度数据的实例如下：

```
int32_t ret;
uint8_t wbuff[5] = {1, 2, 3, 4, 5};
/* 向UART设备写入指定长度的数据 */
ret = UartWrite(handle, wbuff, 5);
if (ret != 0) {
    HDF_LOGE("UartWrite: failed, ret %d\n", ret);
}
```

## 从UART设备中读取指定长度的数据<a name="section192177171373"></a>

对应的接口函数如下所示：

int32\_t UartRead\(struct DevHandle \*handle, uint8\_t \*data, uint32\_t size\);

**表 8**  UartRead参数和返回值描述

<a name="table162341717123713"></a>
<table><thead align="left"><tr id="row023313171377"><th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.1"><p id="p1123331710376"><a name="p1123331710376"></a><a name="p1123331710376"></a>参数</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.2"><p id="p523321783715"><a name="p523321783715"></a><a name="p523321783715"></a>参数描述</p>
</th>
</tr>
</thead>
<tbody><tr id="row6234417133712"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p7233121716379"><a name="p7233121716379"></a><a name="p7233121716379"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p17234101753712"><a name="p17234101753712"></a><a name="p17234101753712"></a>UART设备句柄</p>
</td>
</tr>
<tr id="row18234151718372"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p16234191783711"><a name="p16234191783711"></a><a name="p16234191783711"></a>data</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p923417175378"><a name="p923417175378"></a><a name="p923417175378"></a>接收读取数据的指针</p>
</td>
</tr>
<tr id="row82341017193711"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p13234917103717"><a name="p13234917103717"></a><a name="p13234917103717"></a>size</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p182341817153717"><a name="p182341817153717"></a><a name="p182341817153717"></a>待读取数据的长度</p>
</td>
</tr>
<tr id="row102341617123717"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p172341617163712"><a name="p172341617163712"></a><a name="p172341617163712"></a><strong id="b1323411179373"><a name="b1323411179373"></a><a name="b1323411179373"></a>返回值</strong></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1623431763718"><a name="p1623431763718"></a><a name="p1623431763718"></a><strong id="b1123411173377"><a name="b1123411173377"></a><a name="b1123411173377"></a>返回值描述</strong></p>
</td>
</tr>
<tr id="row4234151719372"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p3234131716375"><a name="p3234131716375"></a><a name="p3234131716375"></a>非负数</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p7234171783718"><a name="p7234171783718"></a><a name="p7234171783718"></a>UART读取到的数据长度</p>
</td>
</tr>
<tr id="row112340173378"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p1423431743714"><a name="p1423431743714"></a><a name="p1423431743714"></a>负数</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p32349178378"><a name="p32349178378"></a><a name="p32349178378"></a>UART读取数据失败</p>
</td>
</tr>
</tbody>
</table>

读取指定长度数据的实例如下：

```
int32_t ret;
uint8_t rbuff[5] = {0};
/* 从UART设备读取指定长度的数据 */
ret = UartRead(handle, rbuff, 5);
if (ret < 0) {
    HDF_LOGE("UartRead: failed, ret %d\n", ret);
}
```

>![](public_sys-resources/icon-caution.gif) **注意：** 
>UART返回值为非负值，表示UART读取成功。若返回值等于0，表示UART无有效数据可以读取。若返回值大于0，表示实际读取到的数据长度，该长度小于或等于传入的参数size的大小，并且不超过当前正在使用的UART控制器规定的最大单次读取数据长度的值。

## 销毁UART设备句柄<a name="section63131236354"></a>

UART通信完成之后，需要销毁UART设备句柄，函数如下所示：

void UartClose\(struct DevHandle \*handle\);

该函数会释放申请的资源。

**表 9**  UartClose参数和返回值描述

<a name="table03348317351"></a>
<table><thead align="left"><tr id="row15334837351"><th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.1"><p id="p933411316354"><a name="p933411316354"></a><a name="p933411316354"></a>参数</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.2"><p id="p16334103143517"><a name="p16334103143517"></a><a name="p16334103143517"></a>参数描述</p>
</th>
</tr>
</thead>
<tbody><tr id="row733483103513"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p7334530358"><a name="p7334530358"></a><a name="p7334530358"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p133341331356"><a name="p133341331356"></a><a name="p133341331356"></a>UART设备句柄</p>
</td>
</tr>
</tbody>
</table>

销毁UART设备句柄的实例如下：

```
UartClose(handle); /* 销毁UART设备句柄 *
```

