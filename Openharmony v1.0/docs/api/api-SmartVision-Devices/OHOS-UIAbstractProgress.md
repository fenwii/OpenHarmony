# OHOS::UIAbstractProgress<a name="ZH-CN_TOPIC_0000001055078159"></a>

## **Overview**<a name="section1813171099093533"></a>

**Related Modules:**

[Graphic](Graphic.md)

**Description:**

Represents the abstract base class which provides functions related to the progress bar. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section974249811093533"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table1516680720093533"></a>
<table><thead align="left"><tr id="row160151793093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1584867240093533"><a name="p1584867240093533"></a><a name="p1584867240093533"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p276778022093533"><a name="p276778022093533"></a><a name="p276778022093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1614099319093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1860719302093533"><a name="p1860719302093533"></a><a name="p1860719302093533"></a><a href="Graphic.md#ga8f9bfb4f42ee0e094501ff776e3336da">UIAbstractProgress</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1077350327093533"><a name="p1077350327093533"></a><a name="p1077350327093533"></a>&nbsp;</p>
<p id="p93252867093533"><a name="p93252867093533"></a><a name="p93252867093533"></a>A constructor used to create a <strong id="b628181953093533"><a name="b628181953093533"></a><a name="b628181953093533"></a><a href="OHOS-UIAbstractProgress.md">UIAbstractProgress</a></strong> instance. </p>
</td>
</tr>
<tr id="row1995653215093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p608273514093533"><a name="p608273514093533"></a><a name="p608273514093533"></a><a href="Graphic.md#ga5c1cf7239bf0c0f7d331e63df805b518">~UIAbstractProgress</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2078559817093533"><a name="p2078559817093533"></a><a name="p2078559817093533"></a>virtual&nbsp;</p>
<p id="p123576035093533"><a name="p123576035093533"></a><a name="p123576035093533"></a>A destructor used to delete the <strong id="b1444807889093533"><a name="b1444807889093533"></a><a name="b1444807889093533"></a><a href="OHOS-UIAbstractProgress.md">UIAbstractProgress</a></strong> instance. </p>
</td>
</tr>
<tr id="row379059804093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1947148590093533"><a name="p1947148590093533"></a><a name="p1947148590093533"></a><a href="Graphic.md#ga79885b87d1935947f6980ae56f139083">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p188251962093533"><a name="p188251962093533"></a><a name="p188251962093533"></a>UIViewType&nbsp;</p>
<p id="p1342583535093533"><a name="p1342583535093533"></a><a name="p1342583535093533"></a>Obtains the component type. </p>
</td>
</tr>
<tr id="row810376676093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p550087825093533"><a name="p550087825093533"></a><a name="p550087825093533"></a><a href="Graphic.md#gacb680c1ddc9135371676df504dc6c8f2">EnableBackground</a> (bool enable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p49099116093533"><a name="p49099116093533"></a><a name="p49099116093533"></a>void&nbsp;</p>
<p id="p1374006114093533"><a name="p1374006114093533"></a><a name="p1374006114093533"></a>Sets whether the background of the progress bar is visible. </p>
</td>
</tr>
<tr id="row1525020777093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1354222938093533"><a name="p1354222938093533"></a><a name="p1354222938093533"></a><a href="Graphic.md#ga5f65014431a6489ffa1d4949f9c4449b">SetValue</a> (int16_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p49156895093533"><a name="p49156895093533"></a><a name="p49156895093533"></a>void&nbsp;</p>
<p id="p2031736584093533"><a name="p2031736584093533"></a><a name="p2031736584093533"></a>Sets the current value for this progress bar. </p>
</td>
</tr>
<tr id="row1428314081093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p183130697093533"><a name="p183130697093533"></a><a name="p183130697093533"></a><a href="Graphic.md#ga6face76aa7972efeb6cbb8f525f23135">GetValue</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p392931468093533"><a name="p392931468093533"></a><a name="p392931468093533"></a>int16_t&nbsp;</p>
<p id="p25071599093533"><a name="p25071599093533"></a><a name="p25071599093533"></a>Obtains the current value of this progress bar. </p>
</td>
</tr>
<tr id="row1478543986093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p20066158093533"><a name="p20066158093533"></a><a name="p20066158093533"></a><a href="Graphic.md#ga089e3875453011499ad33ed89a44a699">SetRange</a> (int16_t rangeMax, int16_t rangeMin)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p918085768093533"><a name="p918085768093533"></a><a name="p918085768093533"></a>void&nbsp;</p>
<p id="p780750245093533"><a name="p780750245093533"></a><a name="p780750245093533"></a>Sets the range for this progress bar. </p>
</td>
</tr>
<tr id="row684381860093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1079506903093533"><a name="p1079506903093533"></a><a name="p1079506903093533"></a><a href="Graphic.md#ga68ab733afcf4224a799ccad2092d1d23">GetRangeMin</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1285089851093533"><a name="p1285089851093533"></a><a name="p1285089851093533"></a>int16_t&nbsp;</p>
<p id="p833152423093533"><a name="p833152423093533"></a><a name="p833152423093533"></a>Obtains the minimum value of this progress bar. </p>
</td>
</tr>
<tr id="row168029215093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1220202194093533"><a name="p1220202194093533"></a><a name="p1220202194093533"></a><a href="Graphic.md#ga1840199f22d5d3e4ef58e41ac8f4febc">GetRangeMax</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p592430131093533"><a name="p592430131093533"></a><a name="p592430131093533"></a>int16_t&nbsp;</p>
<p id="p1392820562093533"><a name="p1392820562093533"></a><a name="p1392820562093533"></a>Obtains the maximum value of this progress bar. </p>
</td>
</tr>
<tr id="row1236251730093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p378608289093533"><a name="p378608289093533"></a><a name="p378608289093533"></a><a href="Graphic.md#ga5b3ec363e391f601e12bf937b9cf77db">SetImage</a> (const char *foregroundImage, const char *backgroundImage=nullptr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1576747642093533"><a name="p1576747642093533"></a><a name="p1576747642093533"></a>void&nbsp;</p>
<p id="p1141779184093533"><a name="p1141779184093533"></a><a name="p1141779184093533"></a>Sets the image for this progress bar. </p>
</td>
</tr>
<tr id="row1273511311093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1169992403093533"><a name="p1169992403093533"></a><a name="p1169992403093533"></a><a href="Graphic.md#ga10723293ab9e384907dd9dacbc9ad448">SetImage</a> (const <a href="OHOS-ImageInfo.md">ImageInfo</a> *foregroundImage, const <a href="OHOS-ImageInfo.md">ImageInfo</a> *backgroundImage=nullptr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2077303685093533"><a name="p2077303685093533"></a><a name="p2077303685093533"></a>void&nbsp;</p>
<p id="p1910824913093533"><a name="p1910824913093533"></a><a name="p1910824913093533"></a>Sets the image as a pixel map for this progress bar. </p>
</td>
</tr>
<tr id="row1683686613093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1330497914093533"><a name="p1330497914093533"></a><a name="p1330497914093533"></a><a href="Graphic.md#ga747a29652b441a06d09a97a297aae9bb">SetStep</a> (uint16_t step)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1871953797093533"><a name="p1871953797093533"></a><a name="p1871953797093533"></a>void&nbsp;</p>
<p id="p1773232092093533"><a name="p1773232092093533"></a><a name="p1773232092093533"></a>Sets the step for this progress bar. </p>
</td>
</tr>
<tr id="row660110024093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2009188665093533"><a name="p2009188665093533"></a><a name="p2009188665093533"></a><a href="Graphic.md#ga9c1678604605a54c2e338d283c46866d">GetStep</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p375697724093533"><a name="p375697724093533"></a><a name="p375697724093533"></a>uint16_t&nbsp;</p>
<p id="p449725264093533"><a name="p449725264093533"></a><a name="p449725264093533"></a>Obtains the current step of this progress bar. </p>
</td>
</tr>
<tr id="row429737717093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1727008373093533"><a name="p1727008373093533"></a><a name="p1727008373093533"></a><a href="Graphic.md#ga6817b5178e93e5f16f2b420cf5a171c1">SetBackgroundStyle</a> (const <a href="OHOS-Style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p43402093533"><a name="p43402093533"></a><a name="p43402093533"></a>void&nbsp;</p>
<p id="p1406946769093533"><a name="p1406946769093533"></a><a name="p1406946769093533"></a>Sets the background style for this progress bar. </p>
</td>
</tr>
<tr id="row758599869093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1853711197093533"><a name="p1853711197093533"></a><a name="p1853711197093533"></a><a href="Graphic.md#ga23acea0a42587746e35ec5f3a74af59f">SetBackgroundStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1862053796093533"><a name="p1862053796093533"></a><a name="p1862053796093533"></a>void&nbsp;</p>
<p id="p542660316093533"><a name="p542660316093533"></a><a name="p542660316093533"></a>Sets a background style for this progress bar. </p>
</td>
</tr>
<tr id="row719264550093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p736313133093533"><a name="p736313133093533"></a><a name="p736313133093533"></a><a href="Graphic.md#gac2ca1212c23c11405b12ae0a46c7eff1">GetBackgroundStyle</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1614313995093533"><a name="p1614313995093533"></a><a name="p1614313995093533"></a>const <a href="OHOS-Style.md">Style</a> &amp;&nbsp;</p>
<p id="p862441066093533"><a name="p862441066093533"></a><a name="p862441066093533"></a>Obtains the background style of this progress bar. </p>
</td>
</tr>
<tr id="row1667131798093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p139880865093533"><a name="p139880865093533"></a><a name="p139880865093533"></a><a href="Graphic.md#ga946d3f2c39a79d45149118536b2557a9">GetBackgroundStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1554276470093533"><a name="p1554276470093533"></a><a name="p1554276470093533"></a>int64_t&nbsp;</p>
<p id="p1880787486093533"><a name="p1880787486093533"></a><a name="p1880787486093533"></a>Obtains the value of a background style of this progress bar. </p>
</td>
</tr>
<tr id="row670795849093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1701262463093533"><a name="p1701262463093533"></a><a name="p1701262463093533"></a><a href="Graphic.md#gaccebcfa35f98f9bc6be4bb8cc53eb11c">SetForegroundStyle</a> (const <a href="OHOS-Style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p121019423093533"><a name="p121019423093533"></a><a name="p121019423093533"></a>void&nbsp;</p>
<p id="p322429243093533"><a name="p322429243093533"></a><a name="p322429243093533"></a>Sets the foreground style for this progress bar. </p>
</td>
</tr>
<tr id="row1613282602093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p344234537093533"><a name="p344234537093533"></a><a name="p344234537093533"></a><a href="Graphic.md#gae6386ca25603e42f06087f6b2ef65bae">SetForegroundStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1148586494093533"><a name="p1148586494093533"></a><a name="p1148586494093533"></a>void&nbsp;</p>
<p id="p340303231093533"><a name="p340303231093533"></a><a name="p340303231093533"></a>Sets a foreground style for this progress bar. </p>
</td>
</tr>
<tr id="row1521867604093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2068137999093533"><a name="p2068137999093533"></a><a name="p2068137999093533"></a><a href="Graphic.md#gac77f945f375f333f80bd70254b5c1f96">GetForegroundStyle</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p129887316093533"><a name="p129887316093533"></a><a name="p129887316093533"></a>const <a href="OHOS-Style.md">Style</a> &amp;&nbsp;</p>
<p id="p1382544523093533"><a name="p1382544523093533"></a><a name="p1382544523093533"></a>Obtains the foreground style of this progress bar. </p>
</td>
</tr>
<tr id="row1897560656093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2053054412093533"><a name="p2053054412093533"></a><a name="p2053054412093533"></a><a href="Graphic.md#ga74cd121dd1794d7e8d905b233bd98217">GetForegroundStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p727345073093533"><a name="p727345073093533"></a><a name="p727345073093533"></a>int64_t&nbsp;</p>
<p id="p1587879504093533"><a name="p1587879504093533"></a><a name="p1587879504093533"></a>Obtains the value of a foreground style of this progress bar. </p>
</td>
</tr>
<tr id="row605096971093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p963818105093533"><a name="p963818105093533"></a><a name="p963818105093533"></a><a href="Graphic.md#gabdc0eb4d279212ea7c3ea7a1f9a85e13">SetCapType</a> (<a href="Graphic.md#ga2db3928cdf793f4950245a6841dd43d6">CapType</a> cap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1085313833093533"><a name="p1085313833093533"></a><a name="p1085313833093533"></a>void&nbsp;</p>
<p id="p343454146093533"><a name="p343454146093533"></a><a name="p343454146093533"></a>Sets the type of caps on the background and foreground of the progress bar. </p>
</td>
</tr>
<tr id="row1573025911093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1748882574093533"><a name="p1748882574093533"></a><a name="p1748882574093533"></a><a href="Graphic.md#ga7aad5b50d945efe5f9304bc978b2001c">UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1959264911093533"><a name="p1959264911093533"></a><a name="p1959264911093533"></a>&nbsp;</p>
<p id="p393751738093533"><a name="p393751738093533"></a><a name="p393751738093533"></a>A default constructor used to create an <strong id="b1393239452093533"><a name="b1393239452093533"></a><a name="b1393239452093533"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1275300518093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1159753859093533"><a name="p1159753859093533"></a><a name="p1159753859093533"></a><a href="Graphic.md#ga57d429bb1cd71782f3b825f1bc6b9362">UIView</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p734382427093533"><a name="p734382427093533"></a><a name="p734382427093533"></a>&nbsp;</p>
<p id="p1030465913093533"><a name="p1030465913093533"></a><a name="p1030465913093533"></a>A constructor used to create an <strong id="b973159794093533"><a name="b973159794093533"></a><a name="b973159794093533"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1676595734093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p18246060093533"><a name="p18246060093533"></a><a name="p18246060093533"></a><a href="Graphic.md#ga17f0ffc1090bdcce0f88288da5962012">~UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p357398458093533"><a name="p357398458093533"></a><a name="p357398458093533"></a>virtual&nbsp;</p>
<p id="p294585911093533"><a name="p294585911093533"></a><a name="p294585911093533"></a>A destructor used to delete the <strong id="b759346721093533"><a name="b759346721093533"></a><a name="b759346721093533"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row13150550093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1362047322093533"><a name="p1362047322093533"></a><a name="p1362047322093533"></a><a href="Graphic.md#gac295fe4851eed72f48e9a63771416d71">OnPreDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1963680800093533"><a name="p1963680800093533"></a><a name="p1963680800093533"></a>virtual bool&nbsp;</p>
<p id="p1558725424093533"><a name="p1558725424093533"></a><a name="p1558725424093533"></a>Called before a view is drawn. This function is used to check whether the parent view of this view needs to be redrawn so as to optimize the drawing process. </p>
</td>
</tr>
<tr id="row246446538093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p661569683093533"><a name="p661569683093533"></a><a name="p661569683093533"></a><a href="Graphic.md#ga9a5f43bdc03cde30323b570bfb7ae425">OnDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p503251723093533"><a name="p503251723093533"></a><a name="p503251723093533"></a>virtual void&nbsp;</p>
<p id="p1013904208093533"><a name="p1013904208093533"></a><a name="p1013904208093533"></a>Called when a view is drawn. </p>
</td>
</tr>
<tr id="row1886870549093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p176360815093533"><a name="p176360815093533"></a><a name="p176360815093533"></a><a href="Graphic.md#gab70473cd0d8fe7c9d4bb817caeee9153">OnPostDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1844928193093533"><a name="p1844928193093533"></a><a name="p1844928193093533"></a>virtual void&nbsp;</p>
<p id="p1067990960093533"><a name="p1067990960093533"></a><a name="p1067990960093533"></a>Called after a view is drawn. </p>
</td>
</tr>
<tr id="row859840305093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p717116674093533"><a name="p717116674093533"></a><a name="p717116674093533"></a><a href="Graphic.md#ga81726238adeda1efa989be6ed4f4fe5b">ReMeasure</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1847389168093533"><a name="p1847389168093533"></a><a name="p1847389168093533"></a>virtual void&nbsp;</p>
<p id="p340779825093533"><a name="p340779825093533"></a><a name="p340779825093533"></a>Remeasures the view size. </p>
</td>
</tr>
<tr id="row800612554093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p518185917093533"><a name="p518185917093533"></a><a name="p518185917093533"></a><a href="Graphic.md#ga2a9a38b8450fbb196277238a51fbbf99">Invalidate</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1749850390093533"><a name="p1749850390093533"></a><a name="p1749850390093533"></a>void&nbsp;</p>
<p id="p1418688828093533"><a name="p1418688828093533"></a><a name="p1418688828093533"></a>Refreshes the invalidated area of the view. </p>
</td>
</tr>
<tr id="row250442631093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p936397878093533"><a name="p936397878093533"></a><a name="p936397878093533"></a><a href="Graphic.md#gaf0e6b65ced8b931642f2a80c195962d2">InvalidateRect</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1061295572093533"><a name="p1061295572093533"></a><a name="p1061295572093533"></a>void&nbsp;</p>
<p id="p1284579337093533"><a name="p1284579337093533"></a><a name="p1284579337093533"></a>Refreshes a view in a specified invalidated area. </p>
</td>
</tr>
<tr id="row1465817272093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p76931287093533"><a name="p76931287093533"></a><a name="p76931287093533"></a><a href="Graphic.md#gac311aa47301d727c35fc31f8630d016e">OnLongPressEvent</a> (const <a href="OHOS-LongPressEvent.md">LongPressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1585965882093533"><a name="p1585965882093533"></a><a name="p1585965882093533"></a>virtual bool&nbsp;</p>
<p id="p118990646093533"><a name="p118990646093533"></a><a name="p118990646093533"></a>Called when the view is long pressed. </p>
</td>
</tr>
<tr id="row93892287093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1055407259093533"><a name="p1055407259093533"></a><a name="p1055407259093533"></a><a href="Graphic.md#gac0e10556ff99b8a92bfb11df6456d605">OnDragStartEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1448220472093533"><a name="p1448220472093533"></a><a name="p1448220472093533"></a>virtual bool&nbsp;</p>
<p id="p687663594093533"><a name="p687663594093533"></a><a name="p687663594093533"></a>Called when the view starts to drag. </p>
</td>
</tr>
<tr id="row2328766093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1959016724093533"><a name="p1959016724093533"></a><a name="p1959016724093533"></a><a href="Graphic.md#ga46249c8caf06b81590d9450e30a31147">OnDragEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p963529021093533"><a name="p963529021093533"></a><a name="p963529021093533"></a>virtual bool&nbsp;</p>
<p id="p198836853093533"><a name="p198836853093533"></a><a name="p198836853093533"></a>Called when the view is being dragged. </p>
</td>
</tr>
<tr id="row1857727629093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2115042402093533"><a name="p2115042402093533"></a><a name="p2115042402093533"></a><a href="Graphic.md#ga1799d33be73f64ed2066f50d7e65468d">OnDragEndEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p215498876093533"><a name="p215498876093533"></a><a name="p215498876093533"></a>virtual bool&nbsp;</p>
<p id="p1930454424093533"><a name="p1930454424093533"></a><a name="p1930454424093533"></a>Called when the view stops dragging. </p>
</td>
</tr>
<tr id="row225407568093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1438443668093533"><a name="p1438443668093533"></a><a name="p1438443668093533"></a><a href="Graphic.md#gad08697a29aae4c58267f494b66b9a547">OnClickEvent</a> (const <a href="OHOS-ClickEvent.md">ClickEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1432713672093533"><a name="p1432713672093533"></a><a name="p1432713672093533"></a>virtual void&nbsp;</p>
<p id="p113864072093533"><a name="p113864072093533"></a><a name="p113864072093533"></a>Called when the view is clicked. </p>
</td>
</tr>
<tr id="row1278575474093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2132800977093533"><a name="p2132800977093533"></a><a name="p2132800977093533"></a><a href="Graphic.md#gafa544ff2d27785a9410a80689f1ad3b1">OnPressEvent</a> (const <a href="OHOS-PressEvent.md">PressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1997599771093533"><a name="p1997599771093533"></a><a name="p1997599771093533"></a>virtual void&nbsp;</p>
<p id="p1857128159093533"><a name="p1857128159093533"></a><a name="p1857128159093533"></a>Called when the view is pressed. </p>
</td>
</tr>
<tr id="row423466490093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p520810338093533"><a name="p520810338093533"></a><a name="p520810338093533"></a><a href="Graphic.md#ga7bd1a74563b059b03fbf66f9add53ee3">OnReleaseEvent</a> (const <a href="OHOS-ReleaseEvent.md">ReleaseEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1189458623093533"><a name="p1189458623093533"></a><a name="p1189458623093533"></a>virtual void&nbsp;</p>
<p id="p399345408093533"><a name="p399345408093533"></a><a name="p399345408093533"></a>Called when the view is released. </p>
</td>
</tr>
<tr id="row126186527093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1349564823093533"><a name="p1349564823093533"></a><a name="p1349564823093533"></a><a href="Graphic.md#ga8f01ff25a33b20df0758f564148e579d">OnCancelEvent</a> (const <a href="OHOS-CancelEvent.md">CancelEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p743982633093533"><a name="p743982633093533"></a><a name="p743982633093533"></a>virtual void&nbsp;</p>
<p id="p1150307153093533"><a name="p1150307153093533"></a><a name="p1150307153093533"></a>Called when a click event on the view is canceled. </p>
</td>
</tr>
<tr id="row721645338093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1559363820093533"><a name="p1559363820093533"></a><a name="p1559363820093533"></a><a href="Graphic.md#gad8e3cf5f0dd003a6aa932ef04e7b59f2">SetOnDragListener</a> (<a href="OHOS-UIView-OnDragListener.md">OnDragListener</a> *onDragListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1106197310093533"><a name="p1106197310093533"></a><a name="p1106197310093533"></a>void&nbsp;</p>
<p id="p182196743093533"><a name="p182196743093533"></a><a name="p182196743093533"></a>Sets a drag event listener for the view. </p>
</td>
</tr>
<tr id="row539681644093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1364676302093533"><a name="p1364676302093533"></a><a name="p1364676302093533"></a><a href="Graphic.md#ga45a02cba4887c5c0b8e243941bcdc5cb">GetOnDragListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p330281861093533"><a name="p330281861093533"></a><a name="p330281861093533"></a><a href="OHOS-UIView-OnDragListener.md">OnDragListener</a> *&amp;&nbsp;</p>
<p id="p2112424855093533"><a name="p2112424855093533"></a><a name="p2112424855093533"></a>Obtains the drag event listener for the view. </p>
</td>
</tr>
<tr id="row2118891213093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p450474729093533"><a name="p450474729093533"></a><a name="p450474729093533"></a><a href="Graphic.md#ga4564bf8d8c7184e9c02bf33c9e171fa3">SetOnClickListener</a> (<a href="OHOS-UIView-OnClickListener.md">OnClickListener</a> *onClickListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p821816163093533"><a name="p821816163093533"></a><a name="p821816163093533"></a>void&nbsp;</p>
<p id="p1660063565093533"><a name="p1660063565093533"></a><a name="p1660063565093533"></a>Sets a click event listener for the view. </p>
</td>
</tr>
<tr id="row183701142093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1907684818093533"><a name="p1907684818093533"></a><a name="p1907684818093533"></a><a href="Graphic.md#ga35e885cb380c37245fa4305bba10cd4a">GetOnClickListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p124660980093533"><a name="p124660980093533"></a><a name="p124660980093533"></a><a href="OHOS-UIView-OnClickListener.md">OnClickListener</a> *&amp;&nbsp;</p>
<p id="p70796094093533"><a name="p70796094093533"></a><a name="p70796094093533"></a>Obtains the click event listener for the view. </p>
</td>
</tr>
<tr id="row243865912093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1511419651093533"><a name="p1511419651093533"></a><a name="p1511419651093533"></a><a href="Graphic.md#gabcbe7a0adce600424f7f0d5a7396eb5b">SetOnLongPressListener</a> (<a href="OHOS-UIView-OnLongPressListener.md">OnLongPressListener</a> *onLongPressListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1773926790093533"><a name="p1773926790093533"></a><a name="p1773926790093533"></a>void&nbsp;</p>
<p id="p1839150692093533"><a name="p1839150692093533"></a><a name="p1839150692093533"></a>Sets a long-press event listener for the view. </p>
</td>
</tr>
<tr id="row545729390093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p661053870093533"><a name="p661053870093533"></a><a name="p661053870093533"></a><a href="Graphic.md#gaafd4d354f5f111e758d046109fd7f656">GetOnLongPressListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p641510556093533"><a name="p641510556093533"></a><a name="p641510556093533"></a><a href="OHOS-UIView-OnLongPressListener.md">OnLongPressListener</a> *&amp;&nbsp;</p>
<p id="p258250825093533"><a name="p258250825093533"></a><a name="p258250825093533"></a>Obtains the long-press event listener for the view. </p>
</td>
</tr>
<tr id="row351373308093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p930836407093533"><a name="p930836407093533"></a><a name="p930836407093533"></a><a href="Graphic.md#gadd697fbf481f98d9d6ca8b67390071af">SetOnTouchListener</a> (<a href="OHOS-UIView-OnTouchListener.md">OnTouchListener</a> *onTouchListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p422730211093533"><a name="p422730211093533"></a><a name="p422730211093533"></a>void&nbsp;</p>
<p id="p1232757302093533"><a name="p1232757302093533"></a><a name="p1232757302093533"></a>Sets a touch event listener for the view. </p>
</td>
</tr>
<tr id="row1396310112093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1348281962093533"><a name="p1348281962093533"></a><a name="p1348281962093533"></a><a href="Graphic.md#gae7c65c68653103dae85acdcef78777a6">GetTouchListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p19649213093533"><a name="p19649213093533"></a><a name="p19649213093533"></a><a href="OHOS-UIView-OnTouchListener.md">OnTouchListener</a> *&amp;&nbsp;</p>
<p id="p399922328093533"><a name="p399922328093533"></a><a name="p399922328093533"></a>Obtains the touch event listener for the view. </p>
</td>
</tr>
<tr id="row1147847712093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1125164361093533"><a name="p1125164361093533"></a><a name="p1125164361093533"></a><a href="Graphic.md#gaea9f334f2481e1c03a2cd8f3078d7c72">GetTargetView</a> (const <a href="OHOS-Point.md">Point</a> &amp;point, <a href="OHOS-UIView.md">UIView</a> **last)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2094243479093533"><a name="p2094243479093533"></a><a name="p2094243479093533"></a>virtual void&nbsp;</p>
<p id="p2082067498093533"><a name="p2082067498093533"></a><a name="p2082067498093533"></a>Obtains the top-level view based on specified coordinates. </p>
</td>
</tr>
<tr id="row1191649595093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2120632665093533"><a name="p2120632665093533"></a><a name="p2120632665093533"></a><a href="Graphic.md#gaeea67a3a84b4ffe9bfeda418b82184cc">SetParent</a> (<a href="OHOS-UIView.md">UIView</a> *parent)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1966259572093533"><a name="p1966259572093533"></a><a name="p1966259572093533"></a>void&nbsp;</p>
<p id="p2077053026093533"><a name="p2077053026093533"></a><a name="p2077053026093533"></a>Sets the parent view for the view. </p>
</td>
</tr>
<tr id="row1355022455093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p408178840093533"><a name="p408178840093533"></a><a name="p408178840093533"></a><a href="Graphic.md#ga706530e4a38108615d5e0c918685ec96">GetParent</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p572934972093533"><a name="p572934972093533"></a><a name="p572934972093533"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1817376504093533"><a name="p1817376504093533"></a><a name="p1817376504093533"></a>Obtains the parent view of the view. </p>
</td>
</tr>
<tr id="row2024063984093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p377306371093533"><a name="p377306371093533"></a><a name="p377306371093533"></a><a href="Graphic.md#ga02bec5de07d93cabc45affba79eba4ad">SetNextSibling</a> (<a href="OHOS-UIView.md">UIView</a> *sibling)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2124090201093533"><a name="p2124090201093533"></a><a name="p2124090201093533"></a>void&nbsp;</p>
<p id="p1420654457093533"><a name="p1420654457093533"></a><a name="p1420654457093533"></a>Sets the next sibling view for the view. </p>
</td>
</tr>
<tr id="row1280963909093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1505821146093533"><a name="p1505821146093533"></a><a name="p1505821146093533"></a><a href="Graphic.md#gab0030977b30ddc9f2e15dbc2f58937e6">GetNextSibling</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1126410345093533"><a name="p1126410345093533"></a><a name="p1126410345093533"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1214439925093533"><a name="p1214439925093533"></a><a name="p1214439925093533"></a>Obtains the next sibling view of the view. </p>
</td>
</tr>
<tr id="row2053010272093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1347965718093533"><a name="p1347965718093533"></a><a name="p1347965718093533"></a><a href="Graphic.md#ga07e7e1f268bd6ce975f4f0f8487af5d0">SetVisible</a> (bool visible)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p135289690093533"><a name="p135289690093533"></a><a name="p135289690093533"></a>virtual void&nbsp;</p>
<p id="p1889947222093533"><a name="p1889947222093533"></a><a name="p1889947222093533"></a>Sets whether the view is visible. </p>
</td>
</tr>
<tr id="row1427684168093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1801768035093533"><a name="p1801768035093533"></a><a name="p1801768035093533"></a><a href="Graphic.md#gaee178fc0a86ac03a6bdf2ade0c1914c8">IsVisible</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p408917146093533"><a name="p408917146093533"></a><a name="p408917146093533"></a>bool&nbsp;</p>
<p id="p998090451093533"><a name="p998090451093533"></a><a name="p998090451093533"></a>Checks whether the view is visible. </p>
</td>
</tr>
<tr id="row1845962054093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1730838710093533"><a name="p1730838710093533"></a><a name="p1730838710093533"></a><a href="Graphic.md#gaf9fb55fd9aa397f7158f1515e90bce02">SetTouchable</a> (bool touch)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2050469118093533"><a name="p2050469118093533"></a><a name="p2050469118093533"></a>void&nbsp;</p>
<p id="p1699716347093533"><a name="p1699716347093533"></a><a name="p1699716347093533"></a>Sets whether the view is touchable. </p>
</td>
</tr>
<tr id="row1361403235093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p31335723093533"><a name="p31335723093533"></a><a name="p31335723093533"></a><a href="Graphic.md#ga502a53fb77b260fa36b5b3adf82e2340">IsTouchable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1783532057093533"><a name="p1783532057093533"></a><a name="p1783532057093533"></a>bool&nbsp;</p>
<p id="p1630459209093533"><a name="p1630459209093533"></a><a name="p1630459209093533"></a>Checks whether the view is touchable. </p>
</td>
</tr>
<tr id="row1830864865093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1320240228093533"><a name="p1320240228093533"></a><a name="p1320240228093533"></a><a href="Graphic.md#gab06abe0fe824c048f3b72974f9a8f0d0">SetDraggable</a> (bool draggable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p632551238093533"><a name="p632551238093533"></a><a name="p632551238093533"></a>void&nbsp;</p>
<p id="p85699345093533"><a name="p85699345093533"></a><a name="p85699345093533"></a>Sets whether the view is draggable. </p>
</td>
</tr>
<tr id="row1493788693093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p655463218093533"><a name="p655463218093533"></a><a name="p655463218093533"></a><a href="Graphic.md#ga25bb796ff400c767d622cbed280fc500">IsDraggable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1195252254093533"><a name="p1195252254093533"></a><a name="p1195252254093533"></a>bool&nbsp;</p>
<p id="p1135883368093533"><a name="p1135883368093533"></a><a name="p1135883368093533"></a>Checks whether the view is draggable. </p>
</td>
</tr>
<tr id="row1317158476093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p259012164093533"><a name="p259012164093533"></a><a name="p259012164093533"></a><a href="Graphic.md#ga6c08e49bf7a82a7ebaef0f251e7a6f85">SetDragParentInstead</a> (bool dragParentInstead)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p765085009093533"><a name="p765085009093533"></a><a name="p765085009093533"></a>void&nbsp;</p>
<p id="p1087453501093533"><a name="p1087453501093533"></a><a name="p1087453501093533"></a>Sets whether to transfer the drag event to the parent view for processing when the view is being dragged. </p>
</td>
</tr>
<tr id="row141148847093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1674005443093533"><a name="p1674005443093533"></a><a name="p1674005443093533"></a><a href="Graphic.md#gaf0c462bc31e779b1898ad4cdfdad6faf">IsDragParentInstead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1781558070093533"><a name="p1781558070093533"></a><a name="p1781558070093533"></a>bool&nbsp;</p>
<p id="p1853124293093533"><a name="p1853124293093533"></a><a name="p1853124293093533"></a>Obtains whether the view transfers a drag event to the parent view for processing. </p>
</td>
</tr>
<tr id="row116253485093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p97389517093533"><a name="p97389517093533"></a><a name="p97389517093533"></a><a href="Graphic.md#ga86cb8d364f18494d67636c55babced5c">GetRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1672425124093533"><a name="p1672425124093533"></a><a name="p1672425124093533"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p476442098093533"><a name="p476442098093533"></a><a name="p476442098093533"></a>Obtains the absolute rectangle area of the view. When the view has deformation such as rotation, the rectangle area is the intersection set of the absolute rectangle area and deformation matrix. </p>
</td>
</tr>
<tr id="row532343335093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p54863877093533"><a name="p54863877093533"></a><a name="p54863877093533"></a><a href="Graphic.md#ga06e79704a19f2a238982076cac3d059b">GetVisibleRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1276278860093533"><a name="p1276278860093533"></a><a name="p1276278860093533"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1644963010093533"><a name="p1644963010093533"></a><a name="p1644963010093533"></a>Obtains the visible absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row1562892975093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2096546299093533"><a name="p2096546299093533"></a><a name="p2096546299093533"></a><a href="Graphic.md#gab3f8993b3953f27bfc61d53429916cba">GetMaskedRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p620548000093533"><a name="p620548000093533"></a><a name="p620548000093533"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1992429267093533"><a name="p1992429267093533"></a><a name="p1992429267093533"></a>Obtains the valid absolute rectangle area of the view. The valid area refers to the area where the view can be displayed. Generally, the valid area is the same as the visible view area, but they may be different in the grid layout. </p>
</td>
</tr>
<tr id="row530619161093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1199319047093533"><a name="p1199319047093533"></a><a name="p1199319047093533"></a><a href="Graphic.md#ga64cf308a09999def1192f9c4e0f17f0a">GetOrigRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1428769666093533"><a name="p1428769666093533"></a><a name="p1428769666093533"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p739566512093533"><a name="p739566512093533"></a><a name="p739566512093533"></a>Obtains the absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row1936894794093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1033077832093533"><a name="p1033077832093533"></a><a name="p1033077832093533"></a><a href="Graphic.md#ga9db88eae712676359d02a92be14fa316">GetContentRect</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p115036650093533"><a name="p115036650093533"></a><a name="p115036650093533"></a>virtual <a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1520256378093533"><a name="p1520256378093533"></a><a name="p1520256378093533"></a>Obtains the content of the absolute rectangle area of the view. This area excludes padding. </p>
</td>
</tr>
<tr id="row501095592093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1333237613093533"><a name="p1333237613093533"></a><a name="p1333237613093533"></a><a href="Graphic.md#gae9b96837fa1d45648a2a6fbbfcc5eb4a">GetRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p846543890093533"><a name="p846543890093533"></a><a name="p846543890093533"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1217752087093533"><a name="p1217752087093533"></a><a name="p1217752087093533"></a>Obtains the rectangular area of the view relative to the parent view, that is, the rectangular area relative to the coordinates of the parent view. </p>
</td>
</tr>
<tr id="row953757943093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1386474076093533"><a name="p1386474076093533"></a><a name="p1386474076093533"></a><a href="Graphic.md#gae6c5f3bcf99dc837bcecd60c38d3df5a">ResizeVisibleArea</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p348677630093533"><a name="p348677630093533"></a><a name="p348677630093533"></a>void&nbsp;</p>
<p id="p831620461093533"><a name="p831620461093533"></a><a name="p831620461093533"></a>Adjusts the size of the visible area. This operation may affect the final display size. </p>
</td>
</tr>
<tr id="row1992520050093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1889581923093533"><a name="p1889581923093533"></a><a name="p1889581923093533"></a><a href="Graphic.md#ga3375ec5ef059fd88c657af4552d2fa4f">SetWidth</a> (int16_t width)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1954815604093533"><a name="p1954815604093533"></a><a name="p1954815604093533"></a>virtual void&nbsp;</p>
<p id="p2019010424093533"><a name="p2019010424093533"></a><a name="p2019010424093533"></a>Sets the width for the view. </p>
</td>
</tr>
<tr id="row886646410093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p795530752093533"><a name="p795530752093533"></a><a name="p795530752093533"></a><a href="Graphic.md#ga90cf8cffb98d71c30d6fc1d118442dbd">GetWidth</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p422715107093533"><a name="p422715107093533"></a><a name="p422715107093533"></a>virtual int16_t&nbsp;</p>
<p id="p1081275144093533"><a name="p1081275144093533"></a><a name="p1081275144093533"></a>Obtains the width for the view. </p>
</td>
</tr>
<tr id="row2045519801093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p401101736093533"><a name="p401101736093533"></a><a name="p401101736093533"></a><a href="Graphic.md#ga9c7110620d5dc3a7bd3efe1fc2edd125">SetHeight</a> (int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1300321826093533"><a name="p1300321826093533"></a><a name="p1300321826093533"></a>virtual void&nbsp;</p>
<p id="p1227771641093533"><a name="p1227771641093533"></a><a name="p1227771641093533"></a>Sets the height for the view. </p>
</td>
</tr>
<tr id="row92777264093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p901048519093533"><a name="p901048519093533"></a><a name="p901048519093533"></a><a href="Graphic.md#ga9b35f4603a561c7a9a29b023a022ac97">GetHeight</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1358382667093533"><a name="p1358382667093533"></a><a name="p1358382667093533"></a>virtual int16_t&nbsp;</p>
<p id="p1033367138093533"><a name="p1033367138093533"></a><a name="p1033367138093533"></a>Obtains the height for the view. </p>
</td>
</tr>
<tr id="row310268057093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1542787537093533"><a name="p1542787537093533"></a><a name="p1542787537093533"></a><a href="Graphic.md#gae985b607d2f0701911778bf20d640ccd">Resize</a> (int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1687435917093533"><a name="p1687435917093533"></a><a name="p1687435917093533"></a>virtual void&nbsp;</p>
<p id="p704693264093533"><a name="p704693264093533"></a><a name="p704693264093533"></a>Adjusts the size of the view. </p>
</td>
</tr>
<tr id="row1065786252093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1104405405093533"><a name="p1104405405093533"></a><a name="p1104405405093533"></a><a href="Graphic.md#gaded403626558d28e62bf5632ccbb24b5">SetX</a> (int16_t x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1928956471093533"><a name="p1928956471093533"></a><a name="p1928956471093533"></a>virtual void&nbsp;</p>
<p id="p260218301093533"><a name="p260218301093533"></a><a name="p260218301093533"></a>Sets the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row200205092093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1934851690093533"><a name="p1934851690093533"></a><a name="p1934851690093533"></a><a href="Graphic.md#ga89dc5f8fb1cb4b2259dc0439185359f1">GetX</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1210612391093533"><a name="p1210612391093533"></a><a name="p1210612391093533"></a>int16_t&nbsp;</p>
<p id="p1382927598093533"><a name="p1382927598093533"></a><a name="p1382927598093533"></a>Obtains the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row1075672893093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p608532681093533"><a name="p608532681093533"></a><a name="p608532681093533"></a><a href="Graphic.md#gaaa8edc224cf1c7deb2724fb225960877">SetY</a> (int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p360980656093533"><a name="p360980656093533"></a><a name="p360980656093533"></a>virtual void&nbsp;</p>
<p id="p1478077253093533"><a name="p1478077253093533"></a><a name="p1478077253093533"></a>Sets the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row533567861093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p618666226093533"><a name="p618666226093533"></a><a name="p618666226093533"></a><a href="Graphic.md#ga193619d649204b0e9bb854d3b30275c3">GetY</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p654492853093533"><a name="p654492853093533"></a><a name="p654492853093533"></a>int16_t&nbsp;</p>
<p id="p682877245093533"><a name="p682877245093533"></a><a name="p682877245093533"></a>Obtains the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row1210037115093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p217109403093533"><a name="p217109403093533"></a><a name="p217109403093533"></a><a href="Graphic.md#gab34233f6aeae330b025969137d03e67a">SetPosition</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1939948429093533"><a name="p1939948429093533"></a><a name="p1939948429093533"></a>virtual void&nbsp;</p>
<p id="p987078660093533"><a name="p987078660093533"></a><a name="p987078660093533"></a>Sets the position for the view. </p>
</td>
</tr>
<tr id="row788949259093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p554928085093533"><a name="p554928085093533"></a><a name="p554928085093533"></a><a href="Graphic.md#gaf8ce4c009f23b7175b2b34bac4a74262">SetPosition</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1074587936093533"><a name="p1074587936093533"></a><a name="p1074587936093533"></a>virtual void&nbsp;</p>
<p id="p388116547093533"><a name="p388116547093533"></a><a name="p388116547093533"></a>Adjusts the position and size of the view. </p>
</td>
</tr>
<tr id="row1819049873093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p456602261093533"><a name="p456602261093533"></a><a name="p456602261093533"></a><a href="Graphic.md#gab2ce8c11abbd55f40687f38a52511b11">IsViewGroup</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p314453731093533"><a name="p314453731093533"></a><a name="p314453731093533"></a>bool&nbsp;</p>
<p id="p1577332865093533"><a name="p1577332865093533"></a><a name="p1577332865093533"></a>Checks whether the view is a container view. </p>
</td>
</tr>
<tr id="row663216488093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p107466163093533"><a name="p107466163093533"></a><a name="p107466163093533"></a><a href="Graphic.md#ga980fc6824c64cfae6af8657aee17af88">SetIntercept</a> (bool isIntercept)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p654011055093533"><a name="p654011055093533"></a><a name="p654011055093533"></a>void&nbsp;</p>
<p id="p130253691093533"><a name="p130253691093533"></a><a name="p130253691093533"></a>Sets whether to intercept the drag event. If intercepted, the view does not transfer the drag event to the parent view after local processing. </p>
</td>
</tr>
<tr id="row1591172347093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p324754121093533"><a name="p324754121093533"></a><a name="p324754121093533"></a><a href="Graphic.md#ga8623abbbeff458c0cb2d7dc0d1f21e4a">SetTransformMap</a> (const <a href="OHOS-TransformMap.md">TransformMap</a> &amp;transMap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1630726810093533"><a name="p1630726810093533"></a><a name="p1630726810093533"></a>void&nbsp;</p>
<p id="p1269542198093533"><a name="p1269542198093533"></a><a name="p1269542198093533"></a>Sets the affine transformation matrix. </p>
</td>
</tr>
<tr id="row1142623704093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p801344883093533"><a name="p801344883093533"></a><a name="p801344883093533"></a><a href="Graphic.md#gab8cee5a7052a88722768c8ed1324abc1">GetTransformMap</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1701470639093533"><a name="p1701470639093533"></a><a name="p1701470639093533"></a><a href="OHOS-TransformMap.md">TransformMap</a> &amp;&nbsp;</p>
<p id="p1134959350093533"><a name="p1134959350093533"></a><a name="p1134959350093533"></a>Obtains an affine transformation matrix. </p>
</td>
</tr>
<tr id="row2120974647093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1003498220093533"><a name="p1003498220093533"></a><a name="p1003498220093533"></a><a href="Graphic.md#ga0573aa25307c22319db4629781b5cad2">GetChildById</a> (const char *id) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p355131399093533"><a name="p355131399093533"></a><a name="p355131399093533"></a>virtual <a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1125838342093533"><a name="p1125838342093533"></a><a name="p1125838342093533"></a>Obtains the child view of a specified ID. </p>
</td>
</tr>
<tr id="row689180211093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p577262348093533"><a name="p577262348093533"></a><a name="p577262348093533"></a><a href="Graphic.md#ga0caaa15c9b304673331e778a266be77f">SetViewId</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p602693443093533"><a name="p602693443093533"></a><a name="p602693443093533"></a>void&nbsp;</p>
<p id="p1492618685093533"><a name="p1492618685093533"></a><a name="p1492618685093533"></a>Sets the view ID. </p>
</td>
</tr>
<tr id="row694499540093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p797347903093533"><a name="p797347903093533"></a><a name="p797347903093533"></a><a href="Graphic.md#gad6c7644bd2abfa3c92d80776b0bd1936">GetViewId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1565234799093533"><a name="p1565234799093533"></a><a name="p1565234799093533"></a>const char *&nbsp;</p>
<p id="p1982139245093533"><a name="p1982139245093533"></a><a name="p1982139245093533"></a>Obtains the view ID. </p>
</td>
</tr>
<tr id="row664637057093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p340563320093533"><a name="p340563320093533"></a><a name="p340563320093533"></a><a href="Graphic.md#ga77a961aa53567c5214508b4569801c16">SetViewIndex</a> (int16_t <a href="zh-cn_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p371120645093533"><a name="p371120645093533"></a><a name="p371120645093533"></a>void&nbsp;</p>
<p id="p571217765093533"><a name="p571217765093533"></a><a name="p571217765093533"></a>Sets the view index. </p>
</td>
</tr>
<tr id="row2111905622093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1994466732093533"><a name="p1994466732093533"></a><a name="p1994466732093533"></a><a href="Graphic.md#ga62f51715b6d420a296ebe0296717b906">GetViewIndex</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1340461664093533"><a name="p1340461664093533"></a><a name="p1340461664093533"></a>int16_t&nbsp;</p>
<p id="p739792037093533"><a name="p739792037093533"></a><a name="p739792037093533"></a>Obtains the view index. </p>
</td>
</tr>
<tr id="row191629451093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2096509445093533"><a name="p2096509445093533"></a><a name="p2096509445093533"></a><a href="Graphic.md#gaca871fa2f8219e7ea9388e212d1f1e69">LayoutChildren</a> (bool neeInvalidate=false)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p291416732093533"><a name="p291416732093533"></a><a name="p291416732093533"></a>virtual void&nbsp;</p>
<p id="p146172346093533"><a name="p146172346093533"></a><a name="p146172346093533"></a>Lays out all child views according to the preset arrangement mode. </p>
</td>
</tr>
<tr id="row1390244767093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1373427422093533"><a name="p1373427422093533"></a><a name="p1373427422093533"></a><a href="Graphic.md#ga443b86ee9275b0421b37a47bad3264dc">LayoutCenterOfParent</a> (int16_t xOffSet=0, int16_t yOffset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1679040505093533"><a name="p1679040505093533"></a><a name="p1679040505093533"></a>void&nbsp;</p>
<p id="p532498496093533"><a name="p532498496093533"></a><a name="p532498496093533"></a>Lays out the view in the center of the parent view. </p>
</td>
</tr>
<tr id="row415198542093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p532955297093533"><a name="p532955297093533"></a><a name="p532955297093533"></a><a href="Graphic.md#ga94999b271f27cd5d6bfaf303f7d5c708">LayoutLeftOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p756423487093533"><a name="p756423487093533"></a><a name="p756423487093533"></a>void&nbsp;</p>
<p id="p328660331093533"><a name="p328660331093533"></a><a name="p328660331093533"></a>Lays out the view on the left of the parent view. </p>
</td>
</tr>
<tr id="row326418684093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2129249167093533"><a name="p2129249167093533"></a><a name="p2129249167093533"></a><a href="Graphic.md#ga479528ed259b5539e423955f2b60517d">LayoutRightOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p329338815093533"><a name="p329338815093533"></a><a name="p329338815093533"></a>void&nbsp;</p>
<p id="p161671652093533"><a name="p161671652093533"></a><a name="p161671652093533"></a>Lays out the view on the right of the parent view. </p>
</td>
</tr>
<tr id="row514529273093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1286062764093533"><a name="p1286062764093533"></a><a name="p1286062764093533"></a><a href="Graphic.md#ga859288ea61ad23ba7e381bbc07769e83">LayoutTopOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p734665692093533"><a name="p734665692093533"></a><a name="p734665692093533"></a>void&nbsp;</p>
<p id="p1653172431093533"><a name="p1653172431093533"></a><a name="p1653172431093533"></a>Lays out the view on the top of the parent view. </p>
</td>
</tr>
<tr id="row549294050093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2093046123093533"><a name="p2093046123093533"></a><a name="p2093046123093533"></a><a href="Graphic.md#ga809aeee4792ae58218a0bcfcb94d5cdc">LayoutBottomOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1695295095093533"><a name="p1695295095093533"></a><a name="p1695295095093533"></a>void&nbsp;</p>
<p id="p2048725825093533"><a name="p2048725825093533"></a><a name="p2048725825093533"></a>Lays out the view on the bottom of the parent view. </p>
</td>
</tr>
<tr id="row1269718444093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p764218131093533"><a name="p764218131093533"></a><a name="p764218131093533"></a><a href="Graphic.md#gac7f5f2584c716a56fee3783f8dea6246">AlignLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p674279773093533"><a name="p674279773093533"></a><a name="p674279773093533"></a>void&nbsp;</p>
<p id="p1627678225093533"><a name="p1627678225093533"></a><a name="p1627678225093533"></a>Aligns the view with the left of a sibling view. </p>
</td>
</tr>
<tr id="row1242245891093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p795859002093533"><a name="p795859002093533"></a><a name="p795859002093533"></a><a href="Graphic.md#gabb1ac454cdf95593c1e387d5e272433c">AlignRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1340927014093533"><a name="p1340927014093533"></a><a name="p1340927014093533"></a>void&nbsp;</p>
<p id="p1416101016093533"><a name="p1416101016093533"></a><a name="p1416101016093533"></a>Aligns the view with the right of a sibling view. </p>
</td>
</tr>
<tr id="row1561149389093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2045761131093533"><a name="p2045761131093533"></a><a name="p2045761131093533"></a><a href="Graphic.md#ga903d7cbc59bac06d728b7f6435c9a504">AlignTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p908087461093533"><a name="p908087461093533"></a><a name="p908087461093533"></a>void&nbsp;</p>
<p id="p156403611093533"><a name="p156403611093533"></a><a name="p156403611093533"></a>Aligns the view with the top of a sibling view. </p>
</td>
</tr>
<tr id="row837317451093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p14516188093533"><a name="p14516188093533"></a><a name="p14516188093533"></a><a href="Graphic.md#ga7607c3f9661932c495d080e9d92fb1a3">AlignBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p508088771093533"><a name="p508088771093533"></a><a name="p508088771093533"></a>void&nbsp;</p>
<p id="p316851369093533"><a name="p316851369093533"></a><a name="p316851369093533"></a>Aligns the view with the bottom of a sibling view. </p>
</td>
</tr>
<tr id="row944054415093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p610214096093533"><a name="p610214096093533"></a><a name="p610214096093533"></a><a href="Graphic.md#gac23776dbc2fce7ff30d57438abfa5230">AlignHorCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p107233428093533"><a name="p107233428093533"></a><a name="p107233428093533"></a>void&nbsp;</p>
<p id="p1080794114093533"><a name="p1080794114093533"></a><a name="p1080794114093533"></a>Aligns the view with the center of a sibling view in the x-axis. </p>
</td>
</tr>
<tr id="row1576649523093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2100313349093533"><a name="p2100313349093533"></a><a name="p2100313349093533"></a><a href="Graphic.md#gad3caa27aa0cb73ec4656e7d23aa222de">AlignVerCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1511663275093533"><a name="p1511663275093533"></a><a name="p1511663275093533"></a>void&nbsp;</p>
<p id="p1413521422093533"><a name="p1413521422093533"></a><a name="p1413521422093533"></a>Aligns the view with the center of a sibling view in the y-axis. </p>
</td>
</tr>
<tr id="row104850604093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1186172451093533"><a name="p1186172451093533"></a><a name="p1186172451093533"></a><a href="Graphic.md#ga58f1a34a943c4492970f901d63bbc3d8">LayoutLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1378100280093533"><a name="p1378100280093533"></a><a name="p1378100280093533"></a>void&nbsp;</p>
<p id="p2031317885093533"><a name="p2031317885093533"></a><a name="p2031317885093533"></a>Lays out the view on the left of a sibling view. </p>
</td>
</tr>
<tr id="row1010445331093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p31518449093533"><a name="p31518449093533"></a><a name="p31518449093533"></a><a href="Graphic.md#gac4cd64de5291759add164825a323a0d6">LayoutRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2082775804093533"><a name="p2082775804093533"></a><a name="p2082775804093533"></a>void&nbsp;</p>
<p id="p1657781308093533"><a name="p1657781308093533"></a><a name="p1657781308093533"></a>Lays out the view on the right of a sibling view. </p>
</td>
</tr>
<tr id="row1971344551093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p855329925093533"><a name="p855329925093533"></a><a name="p855329925093533"></a><a href="Graphic.md#gaaa8385807e3a9bea46f8dcc326252a70">LayoutTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p576799773093533"><a name="p576799773093533"></a><a name="p576799773093533"></a>void&nbsp;</p>
<p id="p955718079093533"><a name="p955718079093533"></a><a name="p955718079093533"></a>Lays out the view on the above of a sibling view. </p>
</td>
</tr>
<tr id="row918932997093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1087557890093533"><a name="p1087557890093533"></a><a name="p1087557890093533"></a><a href="Graphic.md#gaa23a68e8ef0fb13b362218e71cf67ace">LayoutBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1543817705093533"><a name="p1543817705093533"></a><a name="p1543817705093533"></a>void&nbsp;</p>
<p id="p193469879093533"><a name="p193469879093533"></a><a name="p193469879093533"></a>Lays out the view on the below of a sibling view. </p>
</td>
</tr>
<tr id="row1263553166093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p910375495093533"><a name="p910375495093533"></a><a name="p910375495093533"></a><a href="Graphic.md#ga9c1a3db000fdcd200fec8d2c49f5a0a8">SetStyle</a> (<a href="OHOS-Style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1098706219093533"><a name="p1098706219093533"></a><a name="p1098706219093533"></a>virtual void&nbsp;</p>
<p id="p1598029513093533"><a name="p1598029513093533"></a><a name="p1598029513093533"></a>Sets the view style. </p>
</td>
</tr>
<tr id="row735424528093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1256799644093533"><a name="p1256799644093533"></a><a name="p1256799644093533"></a><a href="Graphic.md#ga0945c2f05815dc2e466ef9ceaca2f700">SetStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p859728885093533"><a name="p859728885093533"></a><a name="p859728885093533"></a>virtual void&nbsp;</p>
<p id="p1926017626093533"><a name="p1926017626093533"></a><a name="p1926017626093533"></a>Sets a style. </p>
</td>
</tr>
<tr id="row1914886457093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p980830649093533"><a name="p980830649093533"></a><a name="p980830649093533"></a><a href="Graphic.md#ga4ea19bc9f4b487946c9e29e63b54a0e6">GetStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p191101115093533"><a name="p191101115093533"></a><a name="p191101115093533"></a>virtual int64_t&nbsp;</p>
<p id="p438205288093533"><a name="p438205288093533"></a><a name="p438205288093533"></a>Obtains the value of a style. </p>
</td>
</tr>
<tr id="row869285816093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1316436457093533"><a name="p1316436457093533"></a><a name="p1316436457093533"></a><a href="Graphic.md#ga1b28213d4c2cd0f8324bce3fe56eb7bb">GetStyleConst</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1930584558093533"><a name="p1930584558093533"></a><a name="p1930584558093533"></a>const <a href="OHOS-Style.md">Style</a> &amp;&nbsp;</p>
<p id="p571152641093533"><a name="p571152641093533"></a><a name="p571152641093533"></a>Obtains the view style. This function applies to scenarios where the style does not need to be modified, which saves memory. </p>
</td>
</tr>
<tr id="row1929019573093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1080086591093533"><a name="p1080086591093533"></a><a name="p1080086591093533"></a><a href="Graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p876814560093533"><a name="p876814560093533"></a><a name="p876814560093533"></a>void *&nbsp;</p>
<p id="p1075128335093533"><a name="p1075128335093533"></a><a name="p1075128335093533"></a>Overrides the <strong id="b367867440093533"><a name="b367867440093533"></a><a name="b367867440093533"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row1219949115093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1399434235093533"><a name="p1399434235093533"></a><a name="p1399434235093533"></a><a href="Graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1985270087093533"><a name="p1985270087093533"></a><a name="p1985270087093533"></a>void&nbsp;</p>
<p id="p140520301093533"><a name="p140520301093533"></a><a name="p140520301093533"></a>Overrides the <strong id="b1811929022093533"><a name="b1811929022093533"></a><a name="b1811929022093533"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

