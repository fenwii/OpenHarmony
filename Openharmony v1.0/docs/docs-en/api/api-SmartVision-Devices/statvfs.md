# statvfs<a name="EN-US_TOPIC_0000001055678142"></a>

## **Overview**<a name="section467434898084843"></a>

**Related Modules:**

[FS](fs.md)

**Description:**

Describes file system information. 

## **Summary**<a name="section487801491084843"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1744310502084843"></a>
<table><thead align="left"><tr id="row880538930084843"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1828887717084843"><a name="p1828887717084843"></a><a name="p1828887717084843"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p813384273084843"><a name="p813384273084843"></a><a name="p813384273084843"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1867407824084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1685286715084843"><a name="p1685286715084843"></a><a name="p1685286715084843"></a><a href="statvfs.md#a3400d89a2627d6313da0cb39ff6209ec">f_bsize</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p163402655084843"><a name="p163402655084843"></a><a name="p163402655084843"></a>unsigned long </p>
</td>
</tr>
<tr id="row1880123757084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p573414300084843"><a name="p573414300084843"></a><a name="p573414300084843"></a><a href="statvfs.md#af01dafa58ce2f665bc8b6ba1741f1896">f_frsize</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1176601408084843"><a name="p1176601408084843"></a><a name="p1176601408084843"></a>unsigned long </p>
</td>
</tr>
<tr id="row2007606524084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1165750455084843"><a name="p1165750455084843"></a><a name="p1165750455084843"></a><a href="statvfs.md#a83b2d1725a43fef463597eda75b7af1b">f_blocks</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p879585598084843"><a name="p879585598084843"></a><a name="p879585598084843"></a>fsblkcnt_t </p>
</td>
</tr>
<tr id="row685370762084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p387702768084843"><a name="p387702768084843"></a><a name="p387702768084843"></a><a href="statvfs.md#ab004873a74b951610b969a222116dccb">f_bfree</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p655968883084843"><a name="p655968883084843"></a><a name="p655968883084843"></a>fsblkcnt_t </p>
</td>
</tr>
<tr id="row1346350082084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1946539446084843"><a name="p1946539446084843"></a><a name="p1946539446084843"></a><a href="statvfs.md#a38e0b0109797e233de83ff9e8c4d0520">f_bavail</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p549627033084843"><a name="p549627033084843"></a><a name="p549627033084843"></a>fsblkcnt_t </p>
</td>
</tr>
<tr id="row441124531084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1449235955084843"><a name="p1449235955084843"></a><a name="p1449235955084843"></a><a href="statvfs.md#a38f6a9335cabe3bff82c2d96cc538e6f">f_files</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1870353056084843"><a name="p1870353056084843"></a><a name="p1870353056084843"></a>fsfilcnt_t </p>
</td>
</tr>
<tr id="row1256710737084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p916818028084843"><a name="p916818028084843"></a><a name="p916818028084843"></a><a href="statvfs.md#a601437cadd9c607cba0c653706af3d22">f_ffree</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p899579738084843"><a name="p899579738084843"></a><a name="p899579738084843"></a>fsfilcnt_t </p>
</td>
</tr>
<tr id="row1144957159084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1046692827084843"><a name="p1046692827084843"></a><a name="p1046692827084843"></a><a href="statvfs.md#a6f336f60b6cba33b9380181ef413022f">f_favail</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p245821717084843"><a name="p245821717084843"></a><a name="p245821717084843"></a>fsfilcnt_t </p>
</td>
</tr>
<tr id="row2017259314084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p328642401084843"><a name="p328642401084843"></a><a name="p328642401084843"></a><a href="statvfs.md#a1a180e536ad58f06b0c05d913d0ae9cf">f_fsid</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1545222216084843"><a name="p1545222216084843"></a><a name="p1545222216084843"></a>unsigned long </p>
</td>
</tr>
<tr id="row312305177084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1854323337084843"><a name="p1854323337084843"></a><a name="p1854323337084843"></a><a href="statvfs.md#adb8f52b3e1b3a90358ec3e97e56aafcd">f_flag</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2034309669084843"><a name="p2034309669084843"></a><a name="p2034309669084843"></a>unsigned long </p>
</td>
</tr>
<tr id="row552716914084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p911170207084843"><a name="p911170207084843"></a><a name="p911170207084843"></a><a href="statvfs.md#a138cd6cae031d89d7ae90649fb667696">f_namemax</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1925551226084843"><a name="p1925551226084843"></a><a name="p1925551226084843"></a>unsigned long </p>
</td>
</tr>
<tr id="row996262555084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1312076239084843"><a name="p1312076239084843"></a><a name="p1312076239084843"></a><a href="statvfs.md#a57b706767c1a69cdb86c33e7196fe647">__reserved</a> [6]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p11791822084843"><a name="p11791822084843"></a><a name="p11791822084843"></a>int </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1212205440084843"></a>

## **Field Documentation**<a name="section683045177084843"></a>

## \_\_reserved<a name="a57b706767c1a69cdb86c33e7196fe647"></a>

```
int statvfs::__reserved[6]
```

 **Description:**

Reserved 

## f\_bavail<a name="a38e0b0109797e233de83ff9e8c4d0520"></a>

```
fsblkcnt_t statvfs::f_bavail
```

 **Description:**

Free blocks for unprivileged users 

## f\_bfree<a name="ab004873a74b951610b969a222116dccb"></a>

```
fsblkcnt_t statvfs::f_bfree
```

 **Description:**

Free blocks 

## f\_blocks<a name="a83b2d1725a43fef463597eda75b7af1b"></a>

```
fsblkcnt_t statvfs::f_blocks
```

 **Description:**

Size of  **fs**, in units of  **f\_frsize** 

## f\_bsize<a name="a3400d89a2627d6313da0cb39ff6209ec"></a>

```
unsigned long statvfs::f_bsize
```

 **Description:**

File system block size 

## f\_favail<a name="a6f336f60b6cba33b9380181ef413022f"></a>

```
fsfilcnt_t statvfs::f_favail
```

 **Description:**

Free inodes for unprivileged users 

## f\_ffree<a name="a601437cadd9c607cba0c653706af3d22"></a>

```
fsfilcnt_t statvfs::f_ffree
```

 **Description:**

Free inodes 

## f\_files<a name="a38f6a9335cabe3bff82c2d96cc538e6f"></a>

```
fsfilcnt_t statvfs::f_files
```

 **Description:**

File nodes \(inodes\) 

## f\_flag<a name="adb8f52b3e1b3a90358ec3e97e56aafcd"></a>

```
unsigned long statvfs::f_flag
```

 **Description:**

Mount flags 

## f\_frsize<a name="af01dafa58ce2f665bc8b6ba1741f1896"></a>

```
unsigned long statvfs::f_frsize
```

 **Description:**

Fragment size 

## f\_fsid<a name="a1a180e536ad58f06b0c05d913d0ae9cf"></a>

```
unsigned long statvfs::f_fsid
```

 **Description:**

File system ID 

## f\_namemax<a name="a138cd6cae031d89d7ae90649fb667696"></a>

```
unsigned long statvfs::f_namemax
```

 **Description:**

Maximum file name length 

