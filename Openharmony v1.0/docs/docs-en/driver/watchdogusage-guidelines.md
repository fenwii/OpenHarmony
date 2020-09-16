# Watchdog Usage Guidelines<a name="EN-US_TOPIC_0000001052777641"></a>

## How to Use<a name="section0719414187"></a>

[Figure 1](#fig19134125410189)  illustrates the process of using a watchdog.

**Figure  1**  Process of using a watchdog<a name="fig19134125410189"></a>  


![](figures/en-us_image_0000001054058088.png)

## Opening a Watchdog<a name="section198171379261"></a>

Use  **WatchdogOpen**  to open a watchdog. A system may have multiple watchdogs. You can open a specified watchdog by using the ID.

int32\_t WatchdogOpen\(int16\_t wdtId\);

**Table  1**  Description of WatchdogOpen

<a name="table1413702552814"></a>
<table><thead align="left"><tr id="row131371325142819"><th class="cellrowborder" valign="top" width="44.99%" id="mcps1.2.3.1.1"><p id="p191372254283"><a name="p191372254283"></a><a name="p191372254283"></a><strong id="b192422195415"><a name="b192422195415"></a><a name="b192422195415"></a>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="55.010000000000005%" id="mcps1.2.3.1.2"><p id="p113819255284"><a name="p113819255284"></a><a name="p113819255284"></a><strong id="b105061227135414"><a name="b105061227135414"></a><a name="b105061227135414"></a>Description</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row813812259282"><td class="cellrowborder" valign="top" width="44.99%" headers="mcps1.2.3.1.1 "><p id="p101381625162813"><a name="p101381625162813"></a><a name="p101381625162813"></a>wdtId</p>
</td>
<td class="cellrowborder" valign="top" width="55.010000000000005%" headers="mcps1.2.3.1.2 "><p id="p191381425142813"><a name="p191381425142813"></a><a name="p191381425142813"></a>Watchdog ID.</p>
</td>
</tr>
<tr id="row2138202515281"><td class="cellrowborder" valign="top" width="44.99%" headers="mcps1.2.3.1.1 "><p id="p141387252287"><a name="p141387252287"></a><a name="p141387252287"></a><strong id="b710114010544"><a name="b710114010544"></a><a name="b710114010544"></a>Return Value</strong></p>
</td>
<td class="cellrowborder" valign="top" width="55.010000000000005%" headers="mcps1.2.3.1.2 "><p id="p12138192512281"><a name="p12138192512281"></a><a name="p12138192512281"></a><strong id="b9210941135414"><a name="b9210941135414"></a><a name="b9210941135414"></a>Description</strong></p>
</td>
</tr>
<tr id="row9138182519287"><td class="cellrowborder" valign="top" width="44.99%" headers="mcps1.2.3.1.1 "><p id="p5138102532814"><a name="p5138102532814"></a><a name="p5138102532814"></a>NULL</p>
</td>
<td class="cellrowborder" valign="top" width="55.010000000000005%" headers="mcps1.2.3.1.2 "><p id="p3138192512815"><a name="p3138192512815"></a><a name="p3138192512815"></a>Failed to open the watchdog.</p>
</td>
</tr>
<tr id="row15138192518283"><td class="cellrowborder" valign="top" width="44.99%" headers="mcps1.2.3.1.1 "><p id="p1850115512916"><a name="p1850115512916"></a><a name="p1850115512916"></a>struct <strong id="b1691314013201"><a name="b1691314013201"></a><a name="b1691314013201"></a>DevHandle</strong> pointer</p>
</td>
<td class="cellrowborder" valign="top" width="55.010000000000005%" headers="mcps1.2.3.1.2 "><p id="p16138122512817"><a name="p16138122512817"></a><a name="p16138122512817"></a>Pointer to the watchdog handle.</p>
</td>
</tr>
</tbody>
</table>

```
struct DevHandle *handle = NULL;
handle = WatchdogOpen(0); /* Open watchdog 0.*/
if (handle == NULL) {
    HDF_LOGE("WatchdogOpen: failed, ret %d\n", ret);
    return;
}
```

## Obtaining the Watchdog Status<a name="section206592910275"></a>

int32\_t WatchdogGetStatus\(struct DevHandle \*handle, int32\_t \*status\);

**Table  2**  Description of WatchdogGetStatus

<a name="table1018490043"></a>
<table><thead align="left"><tr id="row31848013417"><th class="cellrowborder" valign="top" width="44.99%" id="mcps1.2.3.1.1"><p id="p1415816132411"><a name="p1415816132411"></a><a name="p1415816132411"></a><strong id="b1768815152567"><a name="b1768815152567"></a><a name="b1768815152567"></a>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="55.010000000000005%" id="mcps1.2.3.1.2"><p id="p11158111316410"><a name="p11158111316410"></a><a name="p11158111316410"></a><strong id="b147391716105615"><a name="b147391716105615"></a><a name="b147391716105615"></a>Description</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row3264122711222"><td class="cellrowborder" valign="top" width="44.99%" headers="mcps1.2.3.1.1 "><p id="p15264727182211"><a name="p15264727182211"></a><a name="p15264727182211"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="55.010000000000005%" headers="mcps1.2.3.1.2 "><p id="p2026452772210"><a name="p2026452772210"></a><a name="p2026452772210"></a>Watchdog handle.</p>
</td>
</tr>
<tr id="row928111518418"><td class="cellrowborder" valign="top" width="44.99%" headers="mcps1.2.3.1.1 "><p id="p4282955412"><a name="p4282955412"></a><a name="p4282955412"></a>status</p>
</td>
<td class="cellrowborder" valign="top" width="55.010000000000005%" headers="mcps1.2.3.1.2 "><p id="p7282752412"><a name="p7282752412"></a><a name="p7282752412"></a>Pointer to the watchdog status.</p>
</td>
</tr>
<tr id="row17393154515328"><td class="cellrowborder" valign="top" width="44.99%" headers="mcps1.2.3.1.1 "><p id="p8158313248"><a name="p8158313248"></a><a name="p8158313248"></a><strong id="b1758511412567"><a name="b1758511412567"></a><a name="b1758511412567"></a>Return Value</strong></p>
</td>
<td class="cellrowborder" valign="top" width="55.010000000000005%" headers="mcps1.2.3.1.2 "><p id="p161591413741"><a name="p161591413741"></a><a name="p161591413741"></a><strong id="b11967742115615"><a name="b11967742115615"></a><a name="b11967742115615"></a>Description</strong></p>
</td>
</tr>
<tr id="row339324593215"><td class="cellrowborder" valign="top" width="44.99%" headers="mcps1.2.3.1.1 "><p id="p103191916578"><a name="p103191916578"></a><a name="p103191916578"></a>0</p>
</td>
<td class="cellrowborder" valign="top" width="55.010000000000005%" headers="mcps1.2.3.1.2 "><p id="p1231981611712"><a name="p1231981611712"></a><a name="p1231981611712"></a>The watchdog status is obtained.</p>
</td>
</tr>
<tr id="row15393184519323"><td class="cellrowborder" valign="top" width="44.99%" headers="mcps1.2.3.1.1 "><p id="p531916166716"><a name="p531916166716"></a><a name="p531916166716"></a>Negative value</p>
</td>
<td class="cellrowborder" valign="top" width="55.010000000000005%" headers="mcps1.2.3.1.2 "><p id="p93191161174"><a name="p93191161174"></a><a name="p93191161174"></a>Failed to obtain the watchdog status.</p>
</td>
</tr>
</tbody>
</table>

```
int32_t ret;
int32_t status;
/* Obtain the watchdog status. */
ret = WatchdogGetStatus(handle, &status);
if (ret != 0) {
    HDF_LOGE("WatchdogGetStatus: failed, ret %d\n", ret);
    return;
}
```

## Setting the Timeout Duration<a name="section19605128182714"></a>

int32\_t WatchdogSetTimeout\(PalHandle \*handle, uint32\_t seconds\);

**Table  3**  Description of WatchdogSetTimeout

<a name="table9159112182210"></a>
<table><thead align="left"><tr id="row1216012212212"><th class="cellrowborder" valign="top" width="44.99%" id="mcps1.2.3.1.1"><p id="p1416017262215"><a name="p1416017262215"></a><a name="p1416017262215"></a><strong>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="55.010000000000005%" id="mcps1.2.3.1.2"><p id="p16160182192213"><a name="p16160182192213"></a><a name="p16160182192213"></a><strong>Description</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row199536232314"><td class="cellrowborder" valign="top" width="44.99%" headers="mcps1.2.3.1.1 "><p id="p17685481236"><a name="p17685481236"></a><a name="p17685481236"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="55.010000000000005%" headers="mcps1.2.3.1.2 "><p id="p196852811232"><a name="p196852811232"></a><a name="p196852811232"></a>Watchdog handle.</p>
</td>
</tr>
<tr id="row141601729228"><td class="cellrowborder" valign="top" width="44.99%" headers="mcps1.2.3.1.1 "><p id="p191601126226"><a name="p191601126226"></a><a name="p191601126226"></a>seconds</p>
</td>
<td class="cellrowborder" valign="top" width="55.010000000000005%" headers="mcps1.2.3.1.2 "><p id="p5160172182214"><a name="p5160172182214"></a><a name="p5160172182214"></a>Timeout duration, in seconds.</p>
</td>
</tr>
<tr id="row18160192172212"><td class="cellrowborder" valign="top" width="44.99%" headers="mcps1.2.3.1.1 "><p id="p101601123222"><a name="p101601123222"></a><a name="p101601123222"></a><strong>Return Value</strong></p>
</td>
<td class="cellrowborder" valign="top" width="55.010000000000005%" headers="mcps1.2.3.1.2 "><p id="p17160192182212"><a name="p17160192182212"></a><a name="p17160192182212"></a><strong>Description</strong></p>
</td>
</tr>
<tr id="row171600202220"><td class="cellrowborder" valign="top" width="44.99%" headers="mcps1.2.3.1.1 "><p id="p121601226224"><a name="p121601226224"></a><a name="p121601226224"></a>0</p>
</td>
<td class="cellrowborder" valign="top" width="55.010000000000005%" headers="mcps1.2.3.1.2 "><p id="p151607218222"><a name="p151607218222"></a><a name="p151607218222"></a>The setting is successful.</p>
</td>
</tr>
<tr id="row916012252211"><td class="cellrowborder" valign="top" width="44.99%" headers="mcps1.2.3.1.1 "><p id="p19160026224"><a name="p19160026224"></a><a name="p19160026224"></a>Negative value</p>
</td>
<td class="cellrowborder" valign="top" width="55.010000000000005%" headers="mcps1.2.3.1.2 "><p id="p816092142210"><a name="p816092142210"></a><a name="p816092142210"></a>Setting failed.</p>
</td>
</tr>
</tbody>
</table>

```
int32_t ret;
uint32_t timeOut = 60;
/* Set the timeout duration, in seconds. */
ret = WatchdogSetTimeout(handle, timeOut);
if (ret != 0) {
    HDF_LOGE("WatchdogSetTimeout: failed, ret %d\n", ret);
    return;
}
```

## Obtaining the Timeout Duration<a name="section11111516208"></a>

int32\_t WatchdogGetTimeout\(PalHandle \*handle, uint32\_t \*seconds\);

**Table  4**  Description of WatchdogGetTimeout

<a name="table10147164819233"></a>
<table><thead align="left"><tr id="row14147848142313"><th class="cellrowborder" valign="top" width="44.99%" id="mcps1.2.3.1.1"><p id="p4147124892316"><a name="p4147124892316"></a><a name="p4147124892316"></a><strong>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="55.010000000000005%" id="mcps1.2.3.1.2"><p id="p12147144817232"><a name="p12147144817232"></a><a name="p12147144817232"></a><strong>Description</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row8147124819230"><td class="cellrowborder" valign="top" width="44.99%" headers="mcps1.2.3.1.1 "><p id="p21471248142313"><a name="p21471248142313"></a><a name="p21471248142313"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="55.010000000000005%" headers="mcps1.2.3.1.2 "><p id="p12147134815233"><a name="p12147134815233"></a><a name="p12147134815233"></a>Watchdog handle.</p>
</td>
</tr>
<tr id="row514754818232"><td class="cellrowborder" valign="top" width="44.99%" headers="mcps1.2.3.1.1 "><p id="p1614713484235"><a name="p1614713484235"></a><a name="p1614713484235"></a>seconds</p>
</td>
<td class="cellrowborder" valign="top" width="55.010000000000005%" headers="mcps1.2.3.1.2 "><p id="p71478484238"><a name="p71478484238"></a><a name="p71478484238"></a>Pointer to the timeout duration, in seconds.</p>
</td>
</tr>
<tr id="row214784814239"><td class="cellrowborder" valign="top" width="44.99%" headers="mcps1.2.3.1.1 "><p id="p5147848152314"><a name="p5147848152314"></a><a name="p5147848152314"></a><strong>Return Value</strong></p>
</td>
<td class="cellrowborder" valign="top" width="55.010000000000005%" headers="mcps1.2.3.1.2 "><p id="p914724811236"><a name="p914724811236"></a><a name="p914724811236"></a><strong>Description</strong></p>
</td>
</tr>
<tr id="row714744892312"><td class="cellrowborder" valign="top" width="44.99%" headers="mcps1.2.3.1.1 "><p id="p1014764832315"><a name="p1014764832315"></a><a name="p1014764832315"></a>0</p>
</td>
<td class="cellrowborder" valign="top" width="55.010000000000005%" headers="mcps1.2.3.1.2 "><p id="p1314824872310"><a name="p1314824872310"></a><a name="p1314824872310"></a>The timeout duration is obtained.</p>
</td>
</tr>
<tr id="row1514884815230"><td class="cellrowborder" valign="top" width="44.99%" headers="mcps1.2.3.1.1 "><p id="p10148114822319"><a name="p10148114822319"></a><a name="p10148114822319"></a>Negative value</p>
</td>
<td class="cellrowborder" valign="top" width="55.010000000000005%" headers="mcps1.2.3.1.2 "><p id="p1314864822311"><a name="p1314864822311"></a><a name="p1314864822311"></a>Failed to obtain the watchdog status.</p>
</td>
</tr>
</tbody>
</table>

```
int32_t ret;
uint32_t timeOut;
/* Obtain the timeout duration, in seconds. */
ret = WatchdogGetTimeout(handle, &timeOut);
if (ret != 0) {
    HDF_LOGE("WatchdogGetTimeout: failed, ret %d\n", ret);
    return;
}
```

## Starting a Watchdog<a name="section141174192814"></a>

int32\_t WatchdogStart\(struct DevHandle \*handle\);

**Table  5**  Description of WatchdogStart

<a name="table529165182515"></a>
<table><thead align="left"><tr id="row92915122513"><th class="cellrowborder" valign="top" width="44.99%" id="mcps1.2.3.1.1"><p id="p5292582517"><a name="p5292582517"></a><a name="p5292582517"></a><strong>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="55.010000000000005%" id="mcps1.2.3.1.2"><p id="p929554258"><a name="p929554258"></a><a name="p929554258"></a><strong>Description</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row629852250"><td class="cellrowborder" valign="top" width="44.99%" headers="mcps1.2.3.1.1 "><p id="p22975122515"><a name="p22975122515"></a><a name="p22975122515"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="55.010000000000005%" headers="mcps1.2.3.1.2 "><p id="p7290515256"><a name="p7290515256"></a><a name="p7290515256"></a>Watchdog handle.</p>
</td>
</tr>
<tr id="row183035162514"><td class="cellrowborder" valign="top" width="44.99%" headers="mcps1.2.3.1.1 "><p id="p8302511255"><a name="p8302511255"></a><a name="p8302511255"></a><strong>Return Value</strong></p>
</td>
<td class="cellrowborder" valign="top" width="55.010000000000005%" headers="mcps1.2.3.1.2 "><p id="p16307522515"><a name="p16307522515"></a><a name="p16307522515"></a><strong>Description</strong></p>
</td>
</tr>
<tr id="row12305552510"><td class="cellrowborder" valign="top" width="44.99%" headers="mcps1.2.3.1.1 "><p id="p1730175132513"><a name="p1730175132513"></a><a name="p1730175132513"></a>0</p>
</td>
<td class="cellrowborder" valign="top" width="55.010000000000005%" headers="mcps1.2.3.1.2 "><p id="p630754259"><a name="p630754259"></a><a name="p630754259"></a>The watchdog is started.</p>
</td>
</tr>
<tr id="row4306516252"><td class="cellrowborder" valign="top" width="44.99%" headers="mcps1.2.3.1.1 "><p id="p15304502515"><a name="p15304502515"></a><a name="p15304502515"></a>Negative value</p>
</td>
<td class="cellrowborder" valign="top" width="55.010000000000005%" headers="mcps1.2.3.1.2 "><p id="p0301559254"><a name="p0301559254"></a><a name="p0301559254"></a>Failed to start the watchdog.</p>
</td>
</tr>
</tbody>
</table>

```
int32_t ret;
/* Start the watchdog. */
ret = WatchdogStart(handle);
if (ret != 0) {
    HDF_LOGE("WatchdogStart: failed, ret %d\n", ret);
    return;
}
```

## Feeding a Watchdog<a name="section179101435113910"></a>

int32\_t WatchdogFeed\(struct DevHandle \*handle\);

**Table  6**  Description of WatchdogFeed

<a name="table091163515394"></a>
<table><thead align="left"><tr id="row891133515393"><th class="cellrowborder" valign="top" width="44.99%" id="mcps1.2.3.1.1"><p id="p1911143513918"><a name="p1911143513918"></a><a name="p1911143513918"></a><strong>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="55.010000000000005%" id="mcps1.2.3.1.2"><p id="p1191173553917"><a name="p1191173553917"></a><a name="p1191173553917"></a><strong>Description</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row189111635143918"><td class="cellrowborder" valign="top" width="44.99%" headers="mcps1.2.3.1.1 "><p id="p189111435173917"><a name="p189111435173917"></a><a name="p189111435173917"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="55.010000000000005%" headers="mcps1.2.3.1.2 "><p id="p11911143511397"><a name="p11911143511397"></a><a name="p11911143511397"></a>Watchdog handle.</p>
</td>
</tr>
<tr id="row15911835173916"><td class="cellrowborder" valign="top" width="44.99%" headers="mcps1.2.3.1.1 "><p id="p7911123516396"><a name="p7911123516396"></a><a name="p7911123516396"></a><strong>Return Value</strong></p>
</td>
<td class="cellrowborder" valign="top" width="55.010000000000005%" headers="mcps1.2.3.1.2 "><p id="p169118356399"><a name="p169118356399"></a><a name="p169118356399"></a><strong>Description</strong></p>
</td>
</tr>
<tr id="row189119352393"><td class="cellrowborder" valign="top" width="44.99%" headers="mcps1.2.3.1.1 "><p id="p1391113513917"><a name="p1391113513917"></a><a name="p1391113513917"></a>0</p>
</td>
<td class="cellrowborder" valign="top" width="55.010000000000005%" headers="mcps1.2.3.1.2 "><p id="p149111435143911"><a name="p149111435143911"></a><a name="p149111435143911"></a>The watchdog is fed.</p>
</td>
</tr>
<tr id="row5911123520392"><td class="cellrowborder" valign="top" width="44.99%" headers="mcps1.2.3.1.1 "><p id="p49111335143920"><a name="p49111335143920"></a><a name="p49111335143920"></a>Negative value</p>
</td>
<td class="cellrowborder" valign="top" width="55.010000000000005%" headers="mcps1.2.3.1.2 "><p id="p1891216356391"><a name="p1891216356391"></a><a name="p1891216356391"></a>Failed to feed the watchdog.</p>
</td>
</tr>
</tbody>
</table>

```
int32_t ret;
/* Feed the watchdog. */
ret = WatchdogFeed(handle);
if (ret != 0) {
    HDF_LOGE("WatchdogFeed: failed, ret %d\n", ret);
    return;
}
```

## Stopping a Watchdog<a name="section15282123192816"></a>

int32\_t WatchdogStop\(struct DevHandle \*handle\);

**Table  7**  Description of WatchdogStop

<a name="table1286810515254"></a>
<table><thead align="left"><tr id="row28687517259"><th class="cellrowborder" valign="top" width="44.99%" id="mcps1.2.3.1.1"><p id="p6868185120254"><a name="p6868185120254"></a><a name="p6868185120254"></a><strong>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="55.010000000000005%" id="mcps1.2.3.1.2"><p id="p15868185114252"><a name="p15868185114252"></a><a name="p15868185114252"></a><strong>Description</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row1868165114256"><td class="cellrowborder" valign="top" width="44.99%" headers="mcps1.2.3.1.1 "><p id="p6869105115256"><a name="p6869105115256"></a><a name="p6869105115256"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="55.010000000000005%" headers="mcps1.2.3.1.2 "><p id="p19869951202513"><a name="p19869951202513"></a><a name="p19869951202513"></a>Watchdog handle.</p>
</td>
</tr>
<tr id="row68696510259"><td class="cellrowborder" valign="top" width="44.99%" headers="mcps1.2.3.1.1 "><p id="p2869165114256"><a name="p2869165114256"></a><a name="p2869165114256"></a><strong>Return Value</strong></p>
</td>
<td class="cellrowborder" valign="top" width="55.010000000000005%" headers="mcps1.2.3.1.2 "><p id="p158691551142517"><a name="p158691551142517"></a><a name="p158691551142517"></a><strong>Description</strong></p>
</td>
</tr>
<tr id="row9869851192516"><td class="cellrowborder" valign="top" width="44.99%" headers="mcps1.2.3.1.1 "><p id="p686916516252"><a name="p686916516252"></a><a name="p686916516252"></a>0</p>
</td>
<td class="cellrowborder" valign="top" width="55.010000000000005%" headers="mcps1.2.3.1.2 "><p id="p7869115192510"><a name="p7869115192510"></a><a name="p7869115192510"></a>The watchdog is stopped.</p>
</td>
</tr>
<tr id="row15869951122519"><td class="cellrowborder" valign="top" width="44.99%" headers="mcps1.2.3.1.1 "><p id="p486925112518"><a name="p486925112518"></a><a name="p486925112518"></a>Negative value</p>
</td>
<td class="cellrowborder" valign="top" width="55.010000000000005%" headers="mcps1.2.3.1.2 "><p id="p086945172518"><a name="p086945172518"></a><a name="p086945172518"></a>Stopping the watchdog failed.</p>
</td>
</tr>
</tbody>
</table>

```
int32_t ret;
/* Stop the watchdog. */
ret = WatchdogStop(handle);
if (ret != 0) {
    HDF_LOGE("WatchdogStop: failed, ret %d\n", ret);
    return;
}
```

## Closing a Watchdog<a name="section7857850173411"></a>

If the watchdog is no longer required, call  **WatchdogClose**  to close the watchdog handle.

void WatchdogClose\(struct DevHandle \*handle\);

**Table  8**  Description of WatchdogClose

<a name="table1017315185320"></a>
<table><thead align="left"><tr id="row417314182327"><th class="cellrowborder" valign="top" width="44.99%" id="mcps1.2.3.1.1"><p id="p117310184320"><a name="p117310184320"></a><a name="p117310184320"></a><strong>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="55.010000000000005%" id="mcps1.2.3.1.2"><p id="p7173191812324"><a name="p7173191812324"></a><a name="p7173191812324"></a><strong>Description</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row1617331823211"><td class="cellrowborder" valign="top" width="44.99%" headers="mcps1.2.3.1.1 "><p id="p17173191811326"><a name="p17173191811326"></a><a name="p17173191811326"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="55.010000000000005%" headers="mcps1.2.3.1.2 "><p id="p538814308323"><a name="p538814308323"></a><a name="p538814308323"></a>Watchdog handle.</p>
</td>
</tr>
</tbody>
</table>

```
/* Close the watchdog. */
ret = WatchdogClose(handle);
```

