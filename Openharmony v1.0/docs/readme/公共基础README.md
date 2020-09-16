# 公共基础<a name="ZH-CN_TOPIC_0000001052623010"></a>

## 简介<a name="section11660541593"></a>

公共基础库存放OpenHarmony通用的基础组件。这些基础组件可被OpenHarmony各业务子系统及上层应用所使用。

公共基础库在不同平台上提供的能力：

-   LiteOS-M平台：KV存储、文件操作、定时器、IoT外设控制
-   LiteOS-A平台：KV存储、定时器、ACE JS API

## 目录<a name="section1464106163817"></a>

```
utils/native/lite/          # 公共基础库根目录
├── file            # 文件接口实现
├── hals            # HAL目录
│   └── file       # 文件操作硬件抽象层头文件
├── include         # 公共基础库对外接口文件
├── js                          # ACE JS API目录                 
│   └── builtin					
│       ├── common
│       ├── deviceinfokit       # 设备信息Kit
│       ├── filekit             # 文件Kit
│       └── kvstorekit          # KV存储Kit
├── kal             # KAL目录
│   └── timer      # Timer的KAL实现
├── kv_store	       # KV存储实现
│   ├── innerkits   # KV存储内部接口
│   └── src	        # KV存储源文件
└── timer_task       # Timer实现

base/iot_hardware          #IoT外设控制
├── frameworks          
│   └── wifiiot_lite   #IoT外设控制模块实现
├── hals
│   └── wifiiot_lite   #HAL适配层接口
└── interfaces
    └── kits            #IoT外设控制模块接口

vendor/hisi/hi3861/hi3861_adapter/hals/iot_hardware  #IoT外设控制HAL层
└── wifiiot_lite       #HAL适配层接口实现
```

## 约束<a name="section1718733212019"></a>

公共基础库使用C语言开发。

**表 1**  公共基础库功能及约束

<a name="table1361018216112"></a>
<table><thead align="left"><tr id="row1661115214112"><th class="cellrowborder" valign="top" width="12.659999999999998%" id="mcps1.2.5.1.1"><p id="p1261115231118"><a name="p1261115231118"></a><a name="p1261115231118"></a>组件</p>
</th>
<th class="cellrowborder" valign="top" width="14.78%" id="mcps1.2.5.1.2"><p id="p11611825118"><a name="p11611825118"></a><a name="p11611825118"></a>平台支持</p>
</th>
<th class="cellrowborder" valign="top" width="32.22%" id="mcps1.2.5.1.3"><p id="p1336312010465"><a name="p1336312010465"></a><a name="p1336312010465"></a>说明</p>
</th>
<th class="cellrowborder" valign="top" width="40.339999999999996%" id="mcps1.2.5.1.4"><p id="p1833742934815"><a name="p1833742934815"></a><a name="p1833742934815"></a>约束</p>
</th>
</tr>
</thead>
<tbody><tr id="row10455841151112"><td class="cellrowborder" valign="top" width="12.659999999999998%" headers="mcps1.2.5.1.1 "><p id="p1945511415113"><a name="p1945511415113"></a><a name="p1945511415113"></a>KV存储</p>
</td>
<td class="cellrowborder" valign="top" width="14.78%" headers="mcps1.2.5.1.2 "><p id="p668274310317"><a name="p668274310317"></a><a name="p668274310317"></a>LiteOS-M平台、LiteOS-A平台</p>
</td>
<td class="cellrowborder" valign="top" width="32.22%" headers="mcps1.2.5.1.3 "><p id="p193638017460"><a name="p193638017460"></a><a name="p193638017460"></a>为应用程序提供KV存储机制。</p>
</td>
<td class="cellrowborder" valign="top" width="40.339999999999996%" headers="mcps1.2.5.1.4 "><p id="p1733717294484"><a name="p1733717294484"></a><a name="p1733717294484"></a>-</p>
</td>
</tr>
<tr id="row540314384111"><td class="cellrowborder" valign="top" width="12.659999999999998%" headers="mcps1.2.5.1.1 "><p id="p134041038141112"><a name="p134041038141112"></a><a name="p134041038141112"></a>文件操作</p>
</td>
<td class="cellrowborder" valign="top" width="14.78%" headers="mcps1.2.5.1.2 "><p id="p19404193811110"><a name="p19404193811110"></a><a name="p19404193811110"></a>LiteOS-M平台</p>
</td>
<td class="cellrowborder" valign="top" width="32.22%" headers="mcps1.2.5.1.3 "><p id="p113646084618"><a name="p113646084618"></a><a name="p113646084618"></a>提供统一的文件操作接口，屏蔽对底层不同芯片组件的差异。</p>
</td>
<td class="cellrowborder" valign="top" width="40.339999999999996%" headers="mcps1.2.5.1.4 "><p id="p83372029154819"><a name="p83372029154819"></a><a name="p83372029154819"></a>-</p>
</td>
</tr>
<tr id="row175322121218"><td class="cellrowborder" valign="top" width="12.659999999999998%" headers="mcps1.2.5.1.1 "><p id="p1053219131219"><a name="p1053219131219"></a><a name="p1053219131219"></a>定时器</p>
</td>
<td class="cellrowborder" valign="top" width="14.78%" headers="mcps1.2.5.1.2 "><p id="p1912957139"><a name="p1912957139"></a><a name="p1912957139"></a>LiteOS-M平台、LiteOS-A平台</p>
</td>
<td class="cellrowborder" valign="top" width="32.22%" headers="mcps1.2.5.1.3 "><p id="p15364170194610"><a name="p15364170194610"></a><a name="p15364170194610"></a>提供统一的定时器操作接口，屏蔽对底层不同芯片组件的差异。</p>
</td>
<td class="cellrowborder" valign="top" width="40.339999999999996%" headers="mcps1.2.5.1.4 "><p id="p633742915481"><a name="p633742915481"></a><a name="p633742915481"></a>-</p>
</td>
</tr>
<tr id="row1821629675"><td class="cellrowborder" valign="top" width="12.659999999999998%" headers="mcps1.2.5.1.1 "><p id="p198212291879"><a name="p198212291879"></a><a name="p198212291879"></a>IoT外设控制</p>
</td>
<td class="cellrowborder" valign="top" width="14.78%" headers="mcps1.2.5.1.2 "><p id="p13827290715"><a name="p13827290715"></a><a name="p13827290715"></a>LiteOS-M平台</p>
</td>
<td class="cellrowborder" valign="top" width="32.22%" headers="mcps1.2.5.1.3 "><p id="p4822295710"><a name="p4822295710"></a><a name="p4822295710"></a>IoT外设控制模块提供对外围设备的操作能力。</p>
</td>
<td class="cellrowborder" valign="top" width="40.339999999999996%" headers="mcps1.2.5.1.4 ">&nbsp;&nbsp;</td>
</tr>
</tbody>
</table>

## 使用<a name="section83091355151312"></a>

-   **KV存储**

    获取接口

    ```
    char key1[] = "rw.sys.version";
    char value1[32] = {0};
    int ret = UtilsGetValue(key1, value1, 32);
    设置接口
    char key14[] = "key_14";
    ret = UtilsSetValue(key14, defValue);
    ```

-   **文件操作**

    ```
    // open && write
    char fileName[] = "testfile";
    int fd = UtilsFileOpen(fileName, O_RDWR_FS | O_CREAT_FS | O_TRUNC_FS, 0);
    printf("file handle = %d\n", fd);
    int ret = UtilsFileWrite(fd, def, strlen(def));
    printf("write ret = %d\n", ret);
    // stat
    int fileLen = 0;
    ret = UtilsFileStat(fileName, &fileLen);
    printf("file size = %d\n", fileLen);
    // seek
    int fd1 = UtilsFileOpen(fileName, O_RDWR_FS, 0);
    ret = UtilsFileSeek(fd1, 5, SEEK_SET_FS);
    printf("lseek ret = %d\n", ret);
    char buf[32] = {0};
    int readLen = UtilsFileRead(fd1, buf, 32);
    ret = UtilsFileClose(fd1);
    printf("read len = %d : buf = %s\n", readLen, buf);
    // delete
    ret = UtilsFileDelete(fileName);
    printf("delete ret = %d\n", ret);
    ```


## 涉及仓<a name="section6250105871917"></a>

iothardware\_frameworks\_wifiiot\_lite

iothardware\_hals\_wifiiot\_lite

iothardware\_interfaces\_kits\_wifiiot\_lite

utils\_native\_lite

