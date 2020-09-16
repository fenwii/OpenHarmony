# SPI Usage Guidelines<a name="EN-US_TOPIC_0000001052857954"></a>

## How to Use<a name="section691514116412"></a>

[Figure 1](#fig23885455594)  shows the process of using an SPI device.

**Figure  1**  Process of using an SPI device<a name="fig23885455594"></a>  


![](figures/en-us_image_0000001054726248.png)

## Obtaining an SPI Device Handle<a name="section12372204616215"></a>

Before performing SPI communication, obtain an SPI device handle by calling  **SpiOpen**. This function returns an SPI device handle with a specified bus number and CS number.

struct DevHandle \*SpiOpen\(const struct SpiDevInfo \*info\);

**Table  1**  Description of  **SpiOpen**

<a name="table7603619123820"></a>
<table><tbody><tr id="row1060351914386"><td class="cellrowborder" valign="top" width="50%"><p id="p14603181917382"><a name="p14603181917382"></a><a name="p14603181917382"></a><strong id="b743851872411"><a name="b743851872411"></a><a name="b743851872411"></a>Parameter</strong></p>
</td>
<td class="cellrowborder" valign="top" width="50%"><p id="p36031519183819"><a name="p36031519183819"></a><a name="p36031519183819"></a><strong id="b96951957101511"><a name="b96951957101511"></a><a name="b96951957101511"></a>Description</strong></p>
</td>
</tr>
<tr id="row1960431983813"><td class="cellrowborder" valign="top" width="50%"><p id="p3604719123817"><a name="p3604719123817"></a><a name="p3604719123817"></a>info</p>
</td>
<td class="cellrowborder" valign="top" width="50%"><p id="p1560441923818"><a name="p1560441923818"></a><a name="p1560441923818"></a>Pointer to the SPI device descriptor.</p>
</td>
</tr>
<tr id="row380484160"><td class="cellrowborder" valign="top" width="50%"><p id="p460381915385"><a name="p460381915385"></a><a name="p460381915385"></a><strong id="b209091422131617"><a name="b209091422131617"></a><a name="b209091422131617"></a>Return Value</strong></p>
</td>
<td class="cellrowborder" valign="top" width="50%"><p id="p96031619153812"><a name="p96031619153812"></a><a name="p96031619153812"></a><strong id="b126401632121619"><a name="b126401632121619"></a><a name="b126401632121619"></a>Description</strong></p>
</td>
</tr>
<tr id="row5793818161"><td class="cellrowborder" valign="top" width="50%"><p id="p1060418195389"><a name="p1060418195389"></a><a name="p1060418195389"></a>NULL</p>
</td>
<td class="cellrowborder" valign="top" width="50%"><p id="p760471912388"><a name="p760471912388"></a><a name="p760471912388"></a>Failed to obtain an SPI device handle.</p>
</td>
</tr>
<tr id="row187914871618"><td class="cellrowborder" valign="top" width="50%"><p id="p5604719133811"><a name="p5604719133811"></a><a name="p5604719133811"></a>Device handle</p>
</td>
<td class="cellrowborder" valign="top" width="50%"><p id="p3604181933818"><a name="p3604181933818"></a><a name="p3604181933818"></a>Returns the pointer to the SPI device handle.</p>
</td>
</tr>
</tbody>
</table>

The following example shows how to obtain an SPI device handle based on the assumption that both the bus number and CS number of the SPI device are  **0**.

```
struct SpiDevInfo spiDevinfo;       /* SPI device descriptor */
struct DevHandle *spiHandle = NULL; /* SPI device handle */
spiDevinfo.busNum = 0;              /* SPI device bus number */
spiDevinfo.csNum = 0;               /* SPI device CS number */

/* Obtain an SPI device handle. */
spiHandle = SpiOpen(&spiDevinfo);
if (spiHandle == NULL) {
    HDF_LOGE("SpiOpen: failed\n");
    return;
}
```

## Obtaining SPI Device Configuration Parameters<a name="section17121446171311"></a>

After obtaining the SPI device handle, obtain the SPI device configuration parameters by calling the following function:

int32\_t SpiGetCfg\(struct DevHandle \*handle, struct SpiCfg \*cfg\);

**Table  2**  Description of  **SpiGetCfg**

<a name="table14209152141313"></a>
<table><tbody><tr id="row1420918529133"><td class="cellrowborder" valign="top" width="50%"><p id="p42091852141314"><a name="p42091852141314"></a><a name="p42091852141314"></a><strong id="b2209135217139"><a name="b2209135217139"></a><a name="b2209135217139"></a>Parameter</strong></p>
</td>
<td class="cellrowborder" valign="top" width="50%"><p id="p202099523137"><a name="p202099523137"></a><a name="p202099523137"></a><strong id="b61647247617"><a name="b61647247617"></a><a name="b61647247617"></a>Description</strong></p>
</td>
</tr>
<tr id="row142091352171310"><td class="cellrowborder" valign="top" width="50%"><p id="p1520915529131"><a name="p1520915529131"></a><a name="p1520915529131"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="50%"><p id="p720995291310"><a name="p720995291310"></a><a name="p720995291310"></a>Pointer to the SPI device handle.</p>
</td>
</tr>
<tr id="row6209152161314"><td class="cellrowborder" valign="top" width="50%"><p id="p720916522139"><a name="p720916522139"></a><a name="p720916522139"></a>cfg</p>
</td>
<td class="cellrowborder" valign="top" width="50%"><p id="p172091452131319"><a name="p172091452131319"></a><a name="p172091452131319"></a>Pointer to SPI device configuration parameters.</p>
</td>
</tr>
<tr id="row12092522139"><td class="cellrowborder" valign="top" width="50%"><p id="p18209125211134"><a name="p18209125211134"></a><a name="p18209125211134"></a><strong id="b2209155219132"><a name="b2209155219132"></a><a name="b2209155219132"></a>Return Value</strong></p>
</td>
<td class="cellrowborder" valign="top" width="50%"><p id="p420975231318"><a name="p420975231318"></a><a name="p420975231318"></a><strong id="b4209165210132"><a name="b4209165210132"></a><a name="b4209165210132"></a>Description</strong></p>
</td>
</tr>
<tr id="row8209155251310"><td class="cellrowborder" valign="top" width="50%"><p id="p13210145291312"><a name="p13210145291312"></a><a name="p13210145291312"></a>0</p>
</td>
<td class="cellrowborder" valign="top" width="50%"><p id="p152101952141315"><a name="p152101952141315"></a><a name="p152101952141315"></a>Succeeded in obtaining SPI device configuration parameters.</p>
</td>
</tr>
<tr id="row102101452121320"><td class="cellrowborder" valign="top" width="50%"><p id="p10210175219134"><a name="p10210175219134"></a><a name="p10210175219134"></a>Negative value</p>
</td>
<td class="cellrowborder" valign="top" width="50%"><p id="p72101252101312"><a name="p72101252101312"></a><a name="p72101252101312"></a>Failed to obtain SPI device configuration parameters.</p>
</td>
</tr>
</tbody>
</table>

```
int32_t ret;
struct SpiCfg cfg = {0};                /* SPI configuration information */
ret = PalSpiSetCfg(spiHandle, &cfg);       /* Set SPI device configuration parameters. */
if (ret != 0) {
    HDF_LOGE("SpiGetCfg: failed, ret %d\n", ret);
}
```

## Setting SPI Device Configuration Parameters<a name="section97691946634"></a>

After obtaining the SPI device handle, set SPI device configuration parameters by calling the following function:

int32\_t SpiSetCfg\(struct DevHandle \*handle, struct SpiCfg \*cfg\);

**Table  3**  Description of  **SpiSetCfg**

<a name="table219052945210"></a>
<table><tbody><tr id="row14191192918522"><td class="cellrowborder" valign="top" width="50%"><p id="p17424155016529"><a name="p17424155016529"></a><a name="p17424155016529"></a><strong id="b13808393249"><a name="b13808393249"></a><a name="b13808393249"></a>Parameter</strong></p>
</td>
<td class="cellrowborder" valign="top" width="50%"><p id="p942512508520"><a name="p942512508520"></a><a name="p942512508520"></a><strong id="b78202962416"><a name="b78202962416"></a><a name="b78202962416"></a>Description</strong></p>
</td>
</tr>
<tr id="row219152915524"><td class="cellrowborder" valign="top" width="50%"><p id="p2191122985218"><a name="p2191122985218"></a><a name="p2191122985218"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="50%"><p id="p1519162913524"><a name="p1519162913524"></a><a name="p1519162913524"></a>Pointer to the SPI device handle.</p>
</td>
</tr>
<tr id="row1719110297526"><td class="cellrowborder" valign="top" width="50%"><p id="p181911292523"><a name="p181911292523"></a><a name="p181911292523"></a>cfg</p>
</td>
<td class="cellrowborder" valign="top" width="50%"><p id="p91911729155216"><a name="p91911729155216"></a><a name="p91911729155216"></a>Pointer to SPI device configuration parameters.</p>
</td>
</tr>
<tr id="row036524131716"><td class="cellrowborder" valign="top" width="50%"><p id="p6425165035214"><a name="p6425165035214"></a><a name="p6425165035214"></a><strong id="b61219451173"><a name="b61219451173"></a><a name="b61219451173"></a>Return Value</strong></p>
</td>
<td class="cellrowborder" valign="top" width="50%"><p id="p18425650165215"><a name="p18425650165215"></a><a name="p18425650165215"></a><strong id="b826124514172"><a name="b826124514172"></a><a name="b826124514172"></a>Description</strong></p>
</td>
</tr>
<tr id="row43653411178"><td class="cellrowborder" valign="top" width="50%"><p id="p1319132918520"><a name="p1319132918520"></a><a name="p1319132918520"></a>0</p>
</td>
<td class="cellrowborder" valign="top" width="50%"><p id="p1719117292522"><a name="p1719117292522"></a><a name="p1719117292522"></a>Succeeded in setting SPI device configuration parameters.</p>
</td>
</tr>
<tr id="row536594171715"><td class="cellrowborder" valign="top" width="50%"><p id="p719119296522"><a name="p719119296522"></a><a name="p719119296522"></a>Negative value</p>
</td>
<td class="cellrowborder" valign="top" width="50%"><p id="p20191192925212"><a name="p20191192925212"></a><a name="p20191192925212"></a>Failed to set SPI device configuration parameters.</p>
</td>
</tr>
</tbody>
</table>

```
int32_t ret;
struct SpiCfg cfg = {0};                     /* SPI configuration information */
cfg.mode = SPI_MODE_LOOP;                    /* Communicate in loopback mode. */
cfg.comMode = PAL_SPI_POLLING_TRANSFER; /* Communicate in polling mode. */
cfg.maxSpeedHz = 115200;                     /* Maximum transmission frequency */
cfg.bitsPerWord = 8;                         /* The width of per word to be read or written is 8 bits. */
ret = SpiSetCfg(spiHandle, &cfg);            /* Set SPI device configuration parameters. */
if (ret != 0) {
    HDF_LOGE("SpiSetCfg: failed, ret %d\n", ret);
}
```

## Performing SPI Communication<a name="section197116254416"></a>

-   Writing data of a specified length into an SPI device

To write data into an SPI device only once, call the following function:

int32\_t SpiWrite\(struct DevHandle \*handle, uint8\_t \*buf, uint32\_t len\);

**Table  4**  Description of  **SpiWrite**

<a name="table1018490043"></a>
<table><tbody><tr id="row31848013417"><td class="cellrowborder" valign="top" width="50%"><p id="p1415816132411"><a name="p1415816132411"></a><a name="p1415816132411"></a><strong id="b011110449230"><a name="b011110449230"></a><a name="b011110449230"></a>Parameter</strong></p>
</td>
<td class="cellrowborder" valign="top" width="50%"><p id="p11158111316410"><a name="p11158111316410"></a><a name="p11158111316410"></a><strong id="b157362419310"><a name="b157362419310"></a><a name="b157362419310"></a>Description</strong></p>
</td>
</tr>
<tr id="row10184701945"><td class="cellrowborder" valign="top" width="50%"><p id="p104891871157"><a name="p104891871157"></a><a name="p104891871157"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="50%"><p id="p204891671156"><a name="p204891671156"></a><a name="p204891671156"></a>Pointer to the SPI device handle.</p>
</td>
</tr>
<tr id="row928111518418"><td class="cellrowborder" valign="top" width="50%"><p id="p4282955412"><a name="p4282955412"></a><a name="p4282955412"></a>buf</p>
</td>
<td class="cellrowborder" valign="top" width="50%"><p id="p7282752412"><a name="p7282752412"></a><a name="p7282752412"></a>Pointer to the data to write.</p>
</td>
</tr>
<tr id="row149041113651"><td class="cellrowborder" valign="top" width="50%"><p id="p139051213357"><a name="p139051213357"></a><a name="p139051213357"></a>len</p>
</td>
<td class="cellrowborder" valign="top" width="50%"><p id="p16905313854"><a name="p16905313854"></a><a name="p16905313854"></a>Length of the data to write.</p>
</td>
</tr>
<tr id="row1148818622017"><td class="cellrowborder" valign="top" width="50%"><p id="p8158313248"><a name="p8158313248"></a><a name="p8158313248"></a><strong id="b1197324122018"><a name="b1197324122018"></a><a name="b1197324122018"></a>Return Value</strong></p>
</td>
<td class="cellrowborder" valign="top" width="50%"><p id="p161591413741"><a name="p161591413741"></a><a name="p161591413741"></a><strong id="b15219182419209"><a name="b15219182419209"></a><a name="b15219182419209"></a>Description</strong></p>
</td>
</tr>
<tr id="row14488762202"><td class="cellrowborder" valign="top" width="50%"><p id="p103191916578"><a name="p103191916578"></a><a name="p103191916578"></a>0</p>
</td>
<td class="cellrowborder" valign="top" width="50%"><p id="p1231981611712"><a name="p1231981611712"></a><a name="p1231981611712"></a>Succeeded in writing data into an SPI device.</p>
</td>
</tr>
<tr id="row164881464201"><td class="cellrowborder" valign="top" width="50%"><p id="p531916166716"><a name="p531916166716"></a><a name="p531916166716"></a>Negative value</p>
</td>
<td class="cellrowborder" valign="top" width="50%"><p id="p93191161174"><a name="p93191161174"></a><a name="p93191161174"></a>Failed to write data into an SPI device.</p>
</td>
</tr>
</tbody>
</table>

```
int32_t ret;
uint8_t wbuff[4] = {0x12, 0x34, 0x56, 0x78};
/* Write data of a specified length into an SPI device. */
ret = SpiWrite(spiHandle, wbuff, 4);
if (ret != 0) {
    HDF_LOGE("SpiWrite: failed, ret %d\n", ret);
}
```

-   Reading data of a specified length from an SPI device

To read data from an SPI device only once, call the following function:

int32\_t SpiRead\(struct DevHandle \*handle, uint8\_t \*buf, uint32\_t len\);

**Table  5**  Description of  **SpiRead**

<a name="table0265191412124"></a>
<table><tbody><tr id="row42651914141213"><td class="cellrowborder" valign="top" width="50%"><p id="p1483184123"><a name="p1483184123"></a><a name="p1483184123"></a><strong id="b81201431172318"><a name="b81201431172318"></a><a name="b81201431172318"></a>Parameter</strong></p>
</td>
<td class="cellrowborder" valign="top" width="50%"><p id="p9831871216"><a name="p9831871216"></a><a name="p9831871216"></a><strong id="b31321731122316"><a name="b31321731122316"></a><a name="b31321731122316"></a>Description</strong></p>
</td>
</tr>
<tr id="row1926651415123"><td class="cellrowborder" valign="top" width="50%"><p id="p389183129"><a name="p389183129"></a><a name="p389183129"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="50%"><p id="p168151817124"><a name="p168151817124"></a><a name="p168151817124"></a>Pointer to the SPI device handle. </p>
</td>
</tr>
<tr id="row202661414201220"><td class="cellrowborder" valign="top" width="50%"><p id="p158161821210"><a name="p158161821210"></a><a name="p158161821210"></a>buf</p>
</td>
<td class="cellrowborder" valign="top" width="50%"><p id="p98131811126"><a name="p98131811126"></a><a name="p98131811126"></a>Pointer to the data to read.</p>
</td>
</tr>
<tr id="row1926621451212"><td class="cellrowborder" valign="top" width="50%"><p id="p2918182124"><a name="p2918182124"></a><a name="p2918182124"></a>len</p>
</td>
<td class="cellrowborder" valign="top" width="50%"><p id="p169718191220"><a name="p169718191220"></a><a name="p169718191220"></a>Length of the data to read.</p>
</td>
</tr>
<tr id="row05841310206"><td class="cellrowborder" valign="top" width="50%"><p id="p38171818128"><a name="p38171818128"></a><a name="p38171818128"></a><strong id="b33485467201"><a name="b33485467201"></a><a name="b33485467201"></a>Return Value</strong></p>
</td>
<td class="cellrowborder" valign="top" width="50%"><p id="p881918161220"><a name="p881918161220"></a><a name="p881918161220"></a><strong id="b202091232184813"><a name="b202091232184813"></a><a name="b202091232184813"></a>Description</strong></p>
</td>
</tr>
<tr id="row15584173192016"><td class="cellrowborder" valign="top" width="50%"><p id="p14871820128"><a name="p14871820128"></a><a name="p14871820128"></a>0</p>
</td>
<td class="cellrowborder" valign="top" width="50%"><p id="p88118101211"><a name="p88118101211"></a><a name="p88118101211"></a>Succeeded in reading data from an SPI device.</p>
</td>
</tr>
<tr id="row1058418317204"><td class="cellrowborder" valign="top" width="50%"><p id="p10841817125"><a name="p10841817125"></a><a name="p10841817125"></a>Negative value</p>
</td>
<td class="cellrowborder" valign="top" width="50%"><p id="p986183127"><a name="p986183127"></a><a name="p986183127"></a>Failed to read data from an SPI device.</p>
</td>
</tr>
</tbody>
</table>

```
int32_t ret;
uint8_t rbuff[4] = {0};
/* Read data of a specified length from an SPI device. */
ret = SpiRead(spiHandle, rbuff, 4);
if (ret != 0) {
    HDF_LOGE("SpiRead: failed, ret %d\n", ret);
}
```

-   Launching a custom transfer

To launch a custom transfer, call the following function:

int32\_t SpiTransfer\(struct DevHandle \*handle, struct SpiMsg \*msgs, uint32\_t count\);

**Table  6**  Description of  **SpiTransfer**

<a name="table1934414174212"></a>
<table><tbody><tr id="row1134415176216"><td class="cellrowborder" valign="top" width="50%"><p id="p13295152320217"><a name="p13295152320217"></a><a name="p13295152320217"></a><strong id="b14726194114224"><a name="b14726194114224"></a><a name="b14726194114224"></a>Parameter</strong></p>
</td>
<td class="cellrowborder" valign="top" width="50%"><p id="p1295112352115"><a name="p1295112352115"></a><a name="p1295112352115"></a><strong id="b6744541162218"><a name="b6744541162218"></a><a name="b6744541162218"></a>Description</strong></p>
</td>
</tr>
<tr id="row5344101702113"><td class="cellrowborder" valign="top" width="50%"><p id="p19295132382111"><a name="p19295132382111"></a><a name="p19295132382111"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="50%"><p id="p829510232213"><a name="p829510232213"></a><a name="p829510232213"></a>Pointer to the SPI device handle.</p>
</td>
</tr>
<tr id="row17344171722117"><td class="cellrowborder" valign="top" width="50%"><p id="p9295122332113"><a name="p9295122332113"></a><a name="p9295122332113"></a>msgs</p>
</td>
<td class="cellrowborder" valign="top" width="50%"><p id="p202951238218"><a name="p202951238218"></a><a name="p202951238218"></a>Pointer to the message array to be transferred.</p>
</td>
</tr>
<tr id="row45812466213"><td class="cellrowborder" valign="top" width="50%"><p id="p1659246112117"><a name="p1659246112117"></a><a name="p1659246112117"></a>count</p>
</td>
<td class="cellrowborder" valign="top" width="50%"><p id="p259124622119"><a name="p259124622119"></a><a name="p259124622119"></a>Length of the message array.</p>
</td>
</tr>
<tr id="row45187318214"><td class="cellrowborder" valign="top" width="50%"><p id="p17295142322113"><a name="p17295142322113"></a><a name="p17295142322113"></a><strong id="b6754144472117"><a name="b6754144472117"></a><a name="b6754144472117"></a>Return Value</strong></p>
</td>
<td class="cellrowborder" valign="top" width="50%"><p id="p142959232211"><a name="p142959232211"></a><a name="p142959232211"></a><strong id="b107682446216"><a name="b107682446216"></a><a name="b107682446216"></a>Description</strong></p>
</td>
</tr>
<tr id="row175186313217"><td class="cellrowborder" valign="top" width="50%"><p id="p929532313211"><a name="p929532313211"></a><a name="p929532313211"></a>0</p>
</td>
<td class="cellrowborder" valign="top" width="50%"><p id="p829512237217"><a name="p829512237217"></a><a name="p829512237217"></a>Succeeded in launching the custom transfer.</p>
</td>
</tr>
<tr id="row1451803152114"><td class="cellrowborder" valign="top" width="50%"><p id="p12958234217"><a name="p12958234217"></a><a name="p12958234217"></a>Negative value</p>
</td>
<td class="cellrowborder" valign="top" width="50%"><p id="p1295192312112"><a name="p1295192312112"></a><a name="p1295192312112"></a>Failed to launch the custom transfer.</p>
</td>
</tr>
</tbody>
</table>

```
int32_t ret;
uint8_t wbuff[1] = {0x12};
uint8_t rbuff[1] = {0};
struct SpiMsg msg;        /* Custom message to be transferred */
msg.wbuf = wbuff;         /* Pointer to the data to read */
msg.rbuf = rbuff;         /* Pointer to the data to read */
msg.len = 1;              /* The length of the data to be read or written is 1 bit. */
msg.csChange = 1;         /* Disable the CS before the next transfer. */
msg.delayUs = 0;          /* No delay before the next transfer */
msg.speed = 115200;       /* Speed of this transfer */
/* Launch a custom transfer. The number of messages to be transferred is 1. */
ret = SpiTransfer(spiHandle, &msg, 1);
if (ret != 0) {
    HDF_LOGE("SpiTransfer: failed, ret %d\n", ret);
}
```

## Destroying the SPI Device Handle<a name="section117661819108"></a>

After the SPI communication, destroy the SPI device handle by calling the following function:

void SpiClose\(struct DevHandle \*handle\);

This function will release the resources previously obtained.

**Table  7**  Description of  **SpiClose**

<a name="table72517953115"></a>
<table><tbody><tr id="row1525793312"><td class="cellrowborder" valign="top" width="50%"><p id="p115402031153111"><a name="p115402031153111"></a><a name="p115402031153111"></a><strong id="b691142582513"><a name="b691142582513"></a><a name="b691142582513"></a>Parameter</strong></p>
</td>
<td class="cellrowborder" valign="top" width="50%"><p id="p65406313319"><a name="p65406313319"></a><a name="p65406313319"></a><strong id="b1934710353319"><a name="b1934710353319"></a><a name="b1934710353319"></a>Description</strong></p>
</td>
</tr>
<tr id="row1926109193116"><td class="cellrowborder" valign="top" width="50%"><p id="p105419317318"><a name="p105419317318"></a><a name="p105419317318"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="50%"><p id="p16541153110317"><a name="p16541153110317"></a><a name="p16541153110317"></a>Pointer to the SPI device handle</p>
</td>
</tr>
</tbody>
</table>

```
PalHandleDestroy(spiHandle); /* Destroy the SPI device handle. */
```

