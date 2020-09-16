# OHOS::UIImageAnimatorView<a name="ZH-CN_TOPIC_0000001054918179"></a>

## **Overview**<a name="section795674215093534"></a>

**Related Modules:**

[Graphic](Graphic.md)

**Description:**

Represents an image animator. 

Images are switched at a specified interval to form an animator.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section557267028093534"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table160816006093534"></a>
<table><thead align="left"><tr id="row1189680894093534"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p228695819093534"><a name="p228695819093534"></a><a name="p228695819093534"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1398785427093534"><a name="p1398785427093534"></a><a name="p1398785427093534"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1497716305093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p486347489093534"><a name="p486347489093534"></a><a name="p486347489093534"></a><a href="OHOS-UIImageAnimatorView-AnimatorStopListener.md">AnimatorStopListener</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p773141131093534"><a name="p773141131093534"></a><a name="p773141131093534"></a>Represents a listener that contains a callback to be invoked when this animator stops. </p>
</td>
</tr>
</tbody>
</table>

## Public Member Functions<a name="pub-methods"></a>

<a name="table468669294093534"></a>
<table><thead align="left"><tr id="row781775010093534"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1319427928093534"><a name="p1319427928093534"></a><a name="p1319427928093534"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1903980896093534"><a name="p1903980896093534"></a><a name="p1903980896093534"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1467563367093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p225340748093534"><a name="p225340748093534"></a><a name="p225340748093534"></a><a href="Graphic.md#ga0506b7e6730f07b6e78371b479326b54">UIImageAnimatorView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1356241931093534"><a name="p1356241931093534"></a><a name="p1356241931093534"></a>&nbsp;</p>
<p id="p1998927763093534"><a name="p1998927763093534"></a><a name="p1998927763093534"></a>A constructor used to create a <strong id="b1165729497093534"><a name="b1165729497093534"></a><a name="b1165729497093534"></a><a href="OHOS-UIImageAnimatorView.md">UIImageAnimatorView</a></strong> instance. </p>
</td>
</tr>
<tr id="row14672589093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1734568366093534"><a name="p1734568366093534"></a><a name="p1734568366093534"></a><a href="Graphic.md#ga72c8450b3c27dd0429691667a6d66dd1">~UIImageAnimatorView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p892506607093534"><a name="p892506607093534"></a><a name="p892506607093534"></a>virtual&nbsp;</p>
<p id="p1611510346093534"><a name="p1611510346093534"></a><a name="p1611510346093534"></a>A destructor used to delete the <strong id="b1331860654093534"><a name="b1331860654093534"></a><a name="b1331860654093534"></a><a href="OHOS-UIImageAnimatorView.md">UIImageAnimatorView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1949780362093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1793856856093534"><a name="p1793856856093534"></a><a name="p1793856856093534"></a><a href="Graphic.md#ga831167c9f5000af808638eac56d6ec19">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1644460859093534"><a name="p1644460859093534"></a><a name="p1644460859093534"></a>UIViewType&nbsp;</p>
<p id="p1357036380093534"><a name="p1357036380093534"></a><a name="p1357036380093534"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row1723182483093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1708519528093534"><a name="p1708519528093534"></a><a name="p1708519528093534"></a><a href="Graphic.md#ga6d585adbcbd0d236df848b48ff1b7ece">SetImageAnimatorSrc</a> (const char *imageSrc, uint8_t imageNum, uint16_t timeOfUpdate)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p868996327093534"><a name="p868996327093534"></a><a name="p868996327093534"></a>void&nbsp;</p>
<p id="p1761659238093534"><a name="p1761659238093534"></a><a name="p1761659238093534"></a>Sets the images and speed for this animator. </p>
</td>
</tr>
<tr id="row1976692738093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p256787799093534"><a name="p256787799093534"></a><a name="p256787799093534"></a><a href="Graphic.md#ga4b2c4bc9d0ab881439d5ec728adc0b1a">SetImageAnimatorSrc</a> (const char *imageSrc, uint8_t imageNum)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1601457263093534"><a name="p1601457263093534"></a><a name="p1601457263093534"></a>void&nbsp;</p>
<p id="p2005761244093534"><a name="p2005761244093534"></a><a name="p2005761244093534"></a>Sets the images for this animator. </p>
</td>
</tr>
<tr id="row1340996665093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p230266271093534"><a name="p230266271093534"></a><a name="p230266271093534"></a><a href="Graphic.md#ga0ee52a2ca252957199034c1234dc4f64">SetTimeOfUpdate</a> (uint16_t timeOfUpdate)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1536469101093534"><a name="p1536469101093534"></a><a name="p1536469101093534"></a>void&nbsp;</p>
<p id="p1642960270093534"><a name="p1642960270093534"></a><a name="p1642960270093534"></a>Sets the speed for this animator. </p>
</td>
</tr>
<tr id="row1595918238093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p838224316093534"><a name="p838224316093534"></a><a name="p838224316093534"></a><a href="Graphic.md#ga24411b0b4d9f619532aa879ee6ee7af1">GetTimeOfUpdate</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1879938108093534"><a name="p1879938108093534"></a><a name="p1879938108093534"></a>uint16_t&nbsp;</p>
<p id="p66040452093534"><a name="p66040452093534"></a><a name="p66040452093534"></a>Obtains the speed of this animator. </p>
</td>
</tr>
<tr id="row30003565093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1426813541093534"><a name="p1426813541093534"></a><a name="p1426813541093534"></a><a href="Graphic.md#gad4bd7aaf1100aac86a2cde8728ae8ee0">SetTimeOfPause</a> (uint16_t timeOfPause)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p115277563093534"><a name="p115277563093534"></a><a name="p115277563093534"></a>void&nbsp;</p>
<p id="p1457546997093534"><a name="p1457546997093534"></a><a name="p1457546997093534"></a>Sets the interval between two playbacks of an infinitely repeated animator. </p>
</td>
</tr>
<tr id="row2001589050093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1302964449093534"><a name="p1302964449093534"></a><a name="p1302964449093534"></a><a href="Graphic.md#ga8bd6ba744209193fd1f3e630e6cf1c5a">GetTimeOfPause</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1906026688093534"><a name="p1906026688093534"></a><a name="p1906026688093534"></a>uint16_t&nbsp;</p>
<p id="p2007367488093534"><a name="p2007367488093534"></a><a name="p2007367488093534"></a>Obtains the interval between two playbacks of an infinitely repeated animator. </p>
</td>
</tr>
<tr id="row275673397093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1126854657093534"><a name="p1126854657093534"></a><a name="p1126854657093534"></a><a href="Graphic.md#gadc1064a27f9b95a2797c33793b2110ee">GetImageAnimatorSrc</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2119544816093534"><a name="p2119544816093534"></a><a name="p2119544816093534"></a>const <a href="OHOS-ImageAnimatorInfo.md">ImageAnimatorInfo</a> *&nbsp;</p>
<p id="p421552587093534"><a name="p421552587093534"></a><a name="p421552587093534"></a>Obtains the image array of this frame animator. </p>
</td>
</tr>
<tr id="row1452370942093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p706515136093534"><a name="p706515136093534"></a><a name="p706515136093534"></a><a href="Graphic.md#ga1da191cab1e6b4ffb3a87b50fbe4f7ed">GetImageAnimatorImageNum</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1597983040093534"><a name="p1597983040093534"></a><a name="p1597983040093534"></a>uint8_t&nbsp;</p>
<p id="p119665637093534"><a name="p119665637093534"></a><a name="p119665637093534"></a>Obtains the number of images. </p>
</td>
</tr>
<tr id="row1709955549093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1738219081093534"><a name="p1738219081093534"></a><a name="p1738219081093534"></a><a href="Graphic.md#ga0e41547fd9d55ff85d6b800e59957370">SetSizeFixed</a> (bool fixed)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p221275596093534"><a name="p221275596093534"></a><a name="p221275596093534"></a>void&nbsp;</p>
<p id="p1719584921093534"><a name="p1719584921093534"></a><a name="p1719584921093534"></a>Sets whether the image size is fixed to the view size. </p>
</td>
</tr>
<tr id="row872021337093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1626734488093534"><a name="p1626734488093534"></a><a name="p1626734488093534"></a><a href="Graphic.md#gabf4bad201ee9ef8aa484677b1daa3ba4">IsSizeFixed</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p22784037093534"><a name="p22784037093534"></a><a name="p22784037093534"></a>bool&nbsp;</p>
<p id="p1125826462093534"><a name="p1125826462093534"></a><a name="p1125826462093534"></a>Checks whether the image size is fixed to the view size. </p>
</td>
</tr>
<tr id="row136799900093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1472422183093534"><a name="p1472422183093534"></a><a name="p1472422183093534"></a><a href="Graphic.md#ga0368d596c01e1a6093d7476fce548a38">SetRepeat</a> (bool repeat)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1194199505093534"><a name="p1194199505093534"></a><a name="p1194199505093534"></a>void&nbsp;</p>
<p id="p1272931765093534"><a name="p1272931765093534"></a><a name="p1272931765093534"></a>Sets whether to play this animator for infinite times. </p>
</td>
</tr>
<tr id="row1415706852093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1677322196093534"><a name="p1677322196093534"></a><a name="p1677322196093534"></a><a href="Graphic.md#ga5e3700fe3d572ed6329237480bd4b5d2">IsRepeat</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1831215626093534"><a name="p1831215626093534"></a><a name="p1831215626093534"></a>bool&nbsp;</p>
<p id="p1633401789093534"><a name="p1633401789093534"></a><a name="p1633401789093534"></a>Checks whether this animator is played for infinite times. </p>
</td>
</tr>
<tr id="row1444645688093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1431571318093534"><a name="p1431571318093534"></a><a name="p1431571318093534"></a><a href="Graphic.md#ga8d0a02c46af6bea17323c715620b6212">SetRepeatTimes</a> (uint32_t <a href="zh-cn_topic_0000001054879478.md#gad8751576e987b576f4e6e42f9b42fec9">times</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1538240780093534"><a name="p1538240780093534"></a><a name="p1538240780093534"></a>void&nbsp;</p>
<p id="p2055743424093534"><a name="p2055743424093534"></a><a name="p2055743424093534"></a>Sets the playback times for this animator. </p>
</td>
</tr>
<tr id="row354018585093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1670104745093534"><a name="p1670104745093534"></a><a name="p1670104745093534"></a><a href="Graphic.md#gae900ab627983fb255dc0d1672c1f3a03">GetRepeatTimes</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1737402318093534"><a name="p1737402318093534"></a><a name="p1737402318093534"></a>uint32_t&nbsp;</p>
<p id="p2064734750093534"><a name="p2064734750093534"></a><a name="p2064734750093534"></a>Obtains the playback times. </p>
</td>
</tr>
<tr id="row697802777093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1497548191093534"><a name="p1497548191093534"></a><a name="p1497548191093534"></a><a href="Graphic.md#gaad46659a26146d0edccad42f45f85d6c">GetState</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1857103633093534"><a name="p1857103633093534"></a><a name="p1857103633093534"></a>uint8_t&nbsp;</p>
<p id="p1722963491093534"><a name="p1722963491093534"></a><a name="p1722963491093534"></a>Obtains the current state of this animator. </p>
</td>
</tr>
<tr id="row60318829093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p124895646093534"><a name="p124895646093534"></a><a name="p124895646093534"></a><a href="Graphic.md#ga38a53936c930f4d75ccd9d9c6a5b9afa">SetReverse</a> (bool reverse)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p285740381093534"><a name="p285740381093534"></a><a name="p285740381093534"></a>void&nbsp;</p>
<p id="p2053315994093534"><a name="p2053315994093534"></a><a name="p2053315994093534"></a>Sets the playback sequence for this animator. </p>
</td>
</tr>
<tr id="row942338909093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p807721637093534"><a name="p807721637093534"></a><a name="p807721637093534"></a><a href="Graphic.md#ga35b508048046b7adf938de5cc4004724">IsReverse</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1836549493093534"><a name="p1836549493093534"></a><a name="p1836549493093534"></a>bool&nbsp;</p>
<p id="p1668384231093534"><a name="p1668384231093534"></a><a name="p1668384231093534"></a>Obtains the playback sequence of this animator. </p>
</td>
</tr>
<tr id="row403941811093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1629405724093534"><a name="p1629405724093534"></a><a name="p1629405724093534"></a><a href="Graphic.md#ga99fb1b9b27ee65f812085f93e05330a6">Start</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1873913888093534"><a name="p1873913888093534"></a><a name="p1873913888093534"></a>void&nbsp;</p>
<p id="p2025332505093534"><a name="p2025332505093534"></a><a name="p2025332505093534"></a>Starts this animator. </p>
</td>
</tr>
<tr id="row1494240448093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1093331084093534"><a name="p1093331084093534"></a><a name="p1093331084093534"></a><a href="Graphic.md#ga1887f1afd8e85c0a9c781e182fe5afc3">Stop</a> (bool needReset=true)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1913908434093534"><a name="p1913908434093534"></a><a name="p1913908434093534"></a>void&nbsp;</p>
<p id="p1126628867093534"><a name="p1126628867093534"></a><a name="p1126628867093534"></a>Stops this animator. </p>
</td>
</tr>
<tr id="row1133482936093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1658753287093534"><a name="p1658753287093534"></a><a name="p1658753287093534"></a><a href="Graphic.md#gab8af32245cdf31fcc0a9d0a5d681774c">Pause</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1895317997093534"><a name="p1895317997093534"></a><a name="p1895317997093534"></a>void&nbsp;</p>
<p id="p915468673093534"><a name="p915468673093534"></a><a name="p915468673093534"></a>Pauses this animator at the current image. </p>
</td>
</tr>
<tr id="row1544318567093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1608596220093534"><a name="p1608596220093534"></a><a name="p1608596220093534"></a><a href="Graphic.md#ga051f03136d8c00295162f53acbe6da97">Resume</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1660780674093534"><a name="p1660780674093534"></a><a name="p1660780674093534"></a>void&nbsp;</p>
<p id="p1567645265093534"><a name="p1567645265093534"></a><a name="p1567645265093534"></a>Resumes this animator from the current image. </p>
</td>
</tr>
<tr id="row2083643933093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1800590575093534"><a name="p1800590575093534"></a><a name="p1800590575093534"></a><a href="Graphic.md#ga80b4b917c30226c1b1f7169e3eb8ed8d">SetAnimatorStopListener</a> (<a href="OHOS-UIImageAnimatorView-AnimatorStopListener.md">AnimatorStopListener</a> *listener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p914096986093534"><a name="p914096986093534"></a><a name="p914096986093534"></a>void&nbsp;</p>
<p id="p21514767093534"><a name="p21514767093534"></a><a name="p21514767093534"></a>Sets the listener for the stop of this animator. </p>
</td>
</tr>
<tr id="row525141672093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1001462227093534"><a name="p1001462227093534"></a><a name="p1001462227093534"></a><a href="Graphic.md#ga3db47186dbc7a0cb996c23abcdaf2c38">UIImageView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p720669330093534"><a name="p720669330093534"></a><a name="p720669330093534"></a>&nbsp;</p>
<p id="p645578295093534"><a name="p645578295093534"></a><a name="p645578295093534"></a>A default constructor used to create a <strong id="b640889460093534"><a name="b640889460093534"></a><a name="b640889460093534"></a><a href="OHOS-UIImageView.md">UIImageView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1717951360093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1361905126093534"><a name="p1361905126093534"></a><a name="p1361905126093534"></a><a href="Graphic.md#ga8be6fe17af73ab21f97effa26dbacaca">~UIImageView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1712172674093534"><a name="p1712172674093534"></a><a name="p1712172674093534"></a>virtual&nbsp;</p>
<p id="p1897474141093534"><a name="p1897474141093534"></a><a name="p1897474141093534"></a>A destructor used to delete the <strong id="b1259906632093534"><a name="b1259906632093534"></a><a name="b1259906632093534"></a><a href="OHOS-UIImageView.md">UIImageView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1652020371093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1177279846093534"><a name="p1177279846093534"></a><a name="p1177279846093534"></a><a href="Graphic.md#ga5dc99855271c582e960e0952cca8227c">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p304701810093534"><a name="p304701810093534"></a><a name="p304701810093534"></a>UIViewType&nbsp;</p>
<p id="p1625019562093534"><a name="p1625019562093534"></a><a name="p1625019562093534"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row147244162093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p991386859093534"><a name="p991386859093534"></a><a name="p991386859093534"></a><a href="Graphic.md#ga20ea7dd2d8ddb16cf9750ccdcc2a2803">GetWidth</a> () override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1454772559093534"><a name="p1454772559093534"></a><a name="p1454772559093534"></a>int16_t&nbsp;</p>
<p id="p257597550093534"><a name="p257597550093534"></a><a name="p257597550093534"></a>Obtains the width of this image view. </p>
</td>
</tr>
<tr id="row851355340093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1957923592093534"><a name="p1957923592093534"></a><a name="p1957923592093534"></a><a href="Graphic.md#gaddc6e68c67782eaad40977c6c2256cdd">GetHeight</a> () override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2055773500093534"><a name="p2055773500093534"></a><a name="p2055773500093534"></a>int16_t&nbsp;</p>
<p id="p2022181874093534"><a name="p2022181874093534"></a><a name="p2022181874093534"></a>Obtains the height of this image view. </p>
</td>
</tr>
<tr id="row1950746355093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1764102520093534"><a name="p1764102520093534"></a><a name="p1764102520093534"></a><a href="Graphic.md#ga5d79816831f61406c1c8bd300da9973e">OnPreDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p419233352093534"><a name="p419233352093534"></a><a name="p419233352093534"></a>bool&nbsp;</p>
<p id="p1928633562093534"><a name="p1928633562093534"></a><a name="p1928633562093534"></a>Checks whether this image view needs to be covered to optimize the drawing process. </p>
</td>
</tr>
<tr id="row997456012093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2043405425093534"><a name="p2043405425093534"></a><a name="p2043405425093534"></a><a href="Graphic.md#ga565cecb8ac66f2009dc4783da9bdc699">OnDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p51187313093534"><a name="p51187313093534"></a><a name="p51187313093534"></a>void&nbsp;</p>
<p id="p244612861093534"><a name="p244612861093534"></a><a name="p244612861093534"></a>Draws this image view. </p>
</td>
</tr>
<tr id="row1582121701093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1785535118093534"><a name="p1785535118093534"></a><a name="p1785535118093534"></a><a href="Graphic.md#ga4e2dac4fd52a54a828f13db5ab51d110">SetSrc</a> (const char *src)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1819981169093534"><a name="p1819981169093534"></a><a name="p1819981169093534"></a>void&nbsp;</p>
<p id="p796077472093534"><a name="p796077472093534"></a><a name="p796077472093534"></a>Sets the image path. </p>
</td>
</tr>
<tr id="row1415912461093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1227770667093534"><a name="p1227770667093534"></a><a name="p1227770667093534"></a><a href="Graphic.md#ga18a9eed434132ac60c127ca1fc03e663">SetSrc</a> (const <a href="OHOS-ImageInfo.md">ImageInfo</a> *src)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p726630652093534"><a name="p726630652093534"></a><a name="p726630652093534"></a>void&nbsp;</p>
<p id="p750104520093534"><a name="p750104520093534"></a><a name="p750104520093534"></a>Sets the image information. </p>
</td>
</tr>
<tr id="row1296090769093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p607128369093534"><a name="p607128369093534"></a><a name="p607128369093534"></a><a href="Graphic.md#gab3f60d7eff9b467c64edc90293dbb21d">SetAutoEnable</a> (bool enable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p484319326093534"><a name="p484319326093534"></a><a name="p484319326093534"></a>void&nbsp;</p>
<p id="p1925912594093534"><a name="p1925912594093534"></a><a name="p1925912594093534"></a>Sets whether the image view size needs to be adaptive to the image size. </p>
</td>
</tr>
<tr id="row1313304331093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1475578771093534"><a name="p1475578771093534"></a><a name="p1475578771093534"></a><a href="Graphic.md#ga339c80c2f8f05ff0d79638dc61c71d5a">SetBlurLevel</a> (BlurLevel level)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p67471594093534"><a name="p67471594093534"></a><a name="p67471594093534"></a>void&nbsp;</p>
<p id="p2060077521093534"><a name="p2060077521093534"></a><a name="p2060077521093534"></a>Sets the blur level for this image when it is rotated or scaled. </p>
</td>
</tr>
<tr id="row1999937771093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p322488522093534"><a name="p322488522093534"></a><a name="p322488522093534"></a><a href="Graphic.md#ga8c891ce7719b97f6d49b0554caa371cb">GetBlurLevel</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p365291014093534"><a name="p365291014093534"></a><a name="p365291014093534"></a>BlurLevel&nbsp;</p>
<p id="p2118165423093534"><a name="p2118165423093534"></a><a name="p2118165423093534"></a>Obtains the blur level of this image when it is rotated or scaled. </p>
</td>
</tr>
<tr id="row1235340410093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p593008326093534"><a name="p593008326093534"></a><a name="p593008326093534"></a><a href="Graphic.md#gacd3bafd7cd7dfb83d46d4fae36eae612">SetTransformAlgorithm</a> (TransformAlgorithm algorithm)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1830333290093534"><a name="p1830333290093534"></a><a name="p1830333290093534"></a>void&nbsp;</p>
<p id="p461625156093534"><a name="p461625156093534"></a><a name="p461625156093534"></a>Sets the algorithm used for image rotation and scaling. </p>
</td>
</tr>
<tr id="row1137125977093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p454682619093534"><a name="p454682619093534"></a><a name="p454682619093534"></a><a href="Graphic.md#gac7b75c6fa653d3ac0c8bc9062939d293">GetTransformAlgorithm</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p593954216093534"><a name="p593954216093534"></a><a name="p593954216093534"></a>TransformAlgorithm&nbsp;</p>
<p id="p555175010093534"><a name="p555175010093534"></a><a name="p555175010093534"></a>Obtains the algorithm used for image rotation and scaling. </p>
</td>
</tr>
<tr id="row1403720034093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p488795543093534"><a name="p488795543093534"></a><a name="p488795543093534"></a><a href="Graphic.md#ga3824befafd4f4dda003195ca2bbef399">GetPath</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p150513846093534"><a name="p150513846093534"></a><a name="p150513846093534"></a>const char *&nbsp;</p>
<p id="p903642561093534"><a name="p903642561093534"></a><a name="p903642561093534"></a>获取图片路径 </p>
</td>
</tr>
<tr id="row2045265426093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1133659537093534"><a name="p1133659537093534"></a><a name="p1133659537093534"></a><a href="Graphic.md#gaa9fbde27be3e3ea2fc6b4dabbf588af8">GetImageInfo</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1223067875093534"><a name="p1223067875093534"></a><a name="p1223067875093534"></a>const <a href="OHOS-ImageInfo.md">ImageInfo</a> *&nbsp;</p>
<p id="p1029762166093534"><a name="p1029762166093534"></a><a name="p1029762166093534"></a>获取图片信息 </p>
</td>
</tr>
<tr id="row2108341489093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1179840283093534"><a name="p1179840283093534"></a><a name="p1179840283093534"></a><a href="Graphic.md#ga07da08c8507a3dbee5c21ea0de170a16">GetSrcType</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1943399832093534"><a name="p1943399832093534"></a><a name="p1943399832093534"></a>uint8_t&nbsp;</p>
<p id="p1825034697093534"><a name="p1825034697093534"></a><a name="p1825034697093534"></a>获取图片类型 </p>
</td>
</tr>
<tr id="row1400047667093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1282785447093534"><a name="p1282785447093534"></a><a name="p1282785447093534"></a><a href="Graphic.md#ga7aad5b50d945efe5f9304bc978b2001c">UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1607922609093534"><a name="p1607922609093534"></a><a name="p1607922609093534"></a>&nbsp;</p>
<p id="p2096619459093534"><a name="p2096619459093534"></a><a name="p2096619459093534"></a>A default constructor used to create an <strong id="b671813446093534"><a name="b671813446093534"></a><a name="b671813446093534"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1298766805093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1370494710093534"><a name="p1370494710093534"></a><a name="p1370494710093534"></a><a href="Graphic.md#ga57d429bb1cd71782f3b825f1bc6b9362">UIView</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p916509243093534"><a name="p916509243093534"></a><a name="p916509243093534"></a>&nbsp;</p>
<p id="p1994110636093534"><a name="p1994110636093534"></a><a name="p1994110636093534"></a>A constructor used to create an <strong id="b1689765295093534"><a name="b1689765295093534"></a><a name="b1689765295093534"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row277223481093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p377786980093534"><a name="p377786980093534"></a><a name="p377786980093534"></a><a href="Graphic.md#ga17f0ffc1090bdcce0f88288da5962012">~UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p744153626093534"><a name="p744153626093534"></a><a name="p744153626093534"></a>virtual&nbsp;</p>
<p id="p580548351093534"><a name="p580548351093534"></a><a name="p580548351093534"></a>A destructor used to delete the <strong id="b1872600593093534"><a name="b1872600593093534"></a><a name="b1872600593093534"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row190755182093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p528961881093534"><a name="p528961881093534"></a><a name="p528961881093534"></a><a href="Graphic.md#gab70473cd0d8fe7c9d4bb817caeee9153">OnPostDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1065326047093534"><a name="p1065326047093534"></a><a name="p1065326047093534"></a>virtual void&nbsp;</p>
<p id="p604808176093534"><a name="p604808176093534"></a><a name="p604808176093534"></a>Called after a view is drawn. </p>
</td>
</tr>
<tr id="row41314311093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1746249298093534"><a name="p1746249298093534"></a><a name="p1746249298093534"></a><a href="Graphic.md#ga2a9a38b8450fbb196277238a51fbbf99">Invalidate</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1959697418093534"><a name="p1959697418093534"></a><a name="p1959697418093534"></a>void&nbsp;</p>
<p id="p425300564093534"><a name="p425300564093534"></a><a name="p425300564093534"></a>Refreshes the invalidated area of the view. </p>
</td>
</tr>
<tr id="row835840463093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1189423175093534"><a name="p1189423175093534"></a><a name="p1189423175093534"></a><a href="Graphic.md#gaf0e6b65ced8b931642f2a80c195962d2">InvalidateRect</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1506802414093534"><a name="p1506802414093534"></a><a name="p1506802414093534"></a>void&nbsp;</p>
<p id="p110501333093534"><a name="p110501333093534"></a><a name="p110501333093534"></a>Refreshes a view in a specified invalidated area. </p>
</td>
</tr>
<tr id="row2118523123093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1535028242093534"><a name="p1535028242093534"></a><a name="p1535028242093534"></a><a href="Graphic.md#gac311aa47301d727c35fc31f8630d016e">OnLongPressEvent</a> (const <a href="OHOS-LongPressEvent.md">LongPressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p413569665093534"><a name="p413569665093534"></a><a name="p413569665093534"></a>virtual bool&nbsp;</p>
<p id="p1640404028093534"><a name="p1640404028093534"></a><a name="p1640404028093534"></a>Called when the view is long pressed. </p>
</td>
</tr>
<tr id="row1729597739093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p726980092093534"><a name="p726980092093534"></a><a name="p726980092093534"></a><a href="Graphic.md#gac0e10556ff99b8a92bfb11df6456d605">OnDragStartEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1584990001093534"><a name="p1584990001093534"></a><a name="p1584990001093534"></a>virtual bool&nbsp;</p>
<p id="p631944427093534"><a name="p631944427093534"></a><a name="p631944427093534"></a>Called when the view starts to drag. </p>
</td>
</tr>
<tr id="row1919321070093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2083247895093534"><a name="p2083247895093534"></a><a name="p2083247895093534"></a><a href="Graphic.md#ga46249c8caf06b81590d9450e30a31147">OnDragEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p309428019093534"><a name="p309428019093534"></a><a name="p309428019093534"></a>virtual bool&nbsp;</p>
<p id="p639020621093534"><a name="p639020621093534"></a><a name="p639020621093534"></a>Called when the view is being dragged. </p>
</td>
</tr>
<tr id="row666276519093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1896493949093534"><a name="p1896493949093534"></a><a name="p1896493949093534"></a><a href="Graphic.md#ga1799d33be73f64ed2066f50d7e65468d">OnDragEndEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1708849551093534"><a name="p1708849551093534"></a><a name="p1708849551093534"></a>virtual bool&nbsp;</p>
<p id="p1862221908093534"><a name="p1862221908093534"></a><a name="p1862221908093534"></a>Called when the view stops dragging. </p>
</td>
</tr>
<tr id="row216111145093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1784443317093534"><a name="p1784443317093534"></a><a name="p1784443317093534"></a><a href="Graphic.md#gad08697a29aae4c58267f494b66b9a547">OnClickEvent</a> (const <a href="OHOS-ClickEvent.md">ClickEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p765885443093534"><a name="p765885443093534"></a><a name="p765885443093534"></a>virtual void&nbsp;</p>
<p id="p1492181448093534"><a name="p1492181448093534"></a><a name="p1492181448093534"></a>Called when the view is clicked. </p>
</td>
</tr>
<tr id="row2140003074093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p173372223093534"><a name="p173372223093534"></a><a name="p173372223093534"></a><a href="Graphic.md#gafa544ff2d27785a9410a80689f1ad3b1">OnPressEvent</a> (const <a href="OHOS-PressEvent.md">PressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p460021977093534"><a name="p460021977093534"></a><a name="p460021977093534"></a>virtual void&nbsp;</p>
<p id="p287688423093534"><a name="p287688423093534"></a><a name="p287688423093534"></a>Called when the view is pressed. </p>
</td>
</tr>
<tr id="row1264444919093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1488393475093534"><a name="p1488393475093534"></a><a name="p1488393475093534"></a><a href="Graphic.md#ga7bd1a74563b059b03fbf66f9add53ee3">OnReleaseEvent</a> (const <a href="OHOS-ReleaseEvent.md">ReleaseEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1004145165093534"><a name="p1004145165093534"></a><a name="p1004145165093534"></a>virtual void&nbsp;</p>
<p id="p1777722035093534"><a name="p1777722035093534"></a><a name="p1777722035093534"></a>Called when the view is released. </p>
</td>
</tr>
<tr id="row286219101093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1897079633093534"><a name="p1897079633093534"></a><a name="p1897079633093534"></a><a href="Graphic.md#ga8f01ff25a33b20df0758f564148e579d">OnCancelEvent</a> (const <a href="OHOS-CancelEvent.md">CancelEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1008600343093534"><a name="p1008600343093534"></a><a name="p1008600343093534"></a>virtual void&nbsp;</p>
<p id="p905948017093534"><a name="p905948017093534"></a><a name="p905948017093534"></a>Called when a click event on the view is canceled. </p>
</td>
</tr>
<tr id="row415980645093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1603973991093534"><a name="p1603973991093534"></a><a name="p1603973991093534"></a><a href="Graphic.md#gad8e3cf5f0dd003a6aa932ef04e7b59f2">SetOnDragListener</a> (<a href="OHOS-UIView-OnDragListener.md">OnDragListener</a> *onDragListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p761791186093534"><a name="p761791186093534"></a><a name="p761791186093534"></a>void&nbsp;</p>
<p id="p100504801093534"><a name="p100504801093534"></a><a name="p100504801093534"></a>Sets a drag event listener for the view. </p>
</td>
</tr>
<tr id="row257543090093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1330778854093534"><a name="p1330778854093534"></a><a name="p1330778854093534"></a><a href="Graphic.md#ga45a02cba4887c5c0b8e243941bcdc5cb">GetOnDragListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p19242006093534"><a name="p19242006093534"></a><a name="p19242006093534"></a><a href="OHOS-UIView-OnDragListener.md">OnDragListener</a> *&amp;&nbsp;</p>
<p id="p1558197459093534"><a name="p1558197459093534"></a><a name="p1558197459093534"></a>Obtains the drag event listener for the view. </p>
</td>
</tr>
<tr id="row914547537093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p630585937093534"><a name="p630585937093534"></a><a name="p630585937093534"></a><a href="Graphic.md#ga4564bf8d8c7184e9c02bf33c9e171fa3">SetOnClickListener</a> (<a href="OHOS-UIView-OnClickListener.md">OnClickListener</a> *onClickListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1891499630093534"><a name="p1891499630093534"></a><a name="p1891499630093534"></a>void&nbsp;</p>
<p id="p1080149204093534"><a name="p1080149204093534"></a><a name="p1080149204093534"></a>Sets a click event listener for the view. </p>
</td>
</tr>
<tr id="row1936150748093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p712596234093534"><a name="p712596234093534"></a><a name="p712596234093534"></a><a href="Graphic.md#ga35e885cb380c37245fa4305bba10cd4a">GetOnClickListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p406503656093534"><a name="p406503656093534"></a><a name="p406503656093534"></a><a href="OHOS-UIView-OnClickListener.md">OnClickListener</a> *&amp;&nbsp;</p>
<p id="p1224295478093534"><a name="p1224295478093534"></a><a name="p1224295478093534"></a>Obtains the click event listener for the view. </p>
</td>
</tr>
<tr id="row459848921093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p275480149093534"><a name="p275480149093534"></a><a name="p275480149093534"></a><a href="Graphic.md#gabcbe7a0adce600424f7f0d5a7396eb5b">SetOnLongPressListener</a> (<a href="OHOS-UIView-OnLongPressListener.md">OnLongPressListener</a> *onLongPressListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p809231050093534"><a name="p809231050093534"></a><a name="p809231050093534"></a>void&nbsp;</p>
<p id="p956046092093534"><a name="p956046092093534"></a><a name="p956046092093534"></a>Sets a long-press event listener for the view. </p>
</td>
</tr>
<tr id="row1471300083093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p329227824093534"><a name="p329227824093534"></a><a name="p329227824093534"></a><a href="Graphic.md#gaafd4d354f5f111e758d046109fd7f656">GetOnLongPressListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p364945305093534"><a name="p364945305093534"></a><a name="p364945305093534"></a><a href="OHOS-UIView-OnLongPressListener.md">OnLongPressListener</a> *&amp;&nbsp;</p>
<p id="p291024490093534"><a name="p291024490093534"></a><a name="p291024490093534"></a>Obtains the long-press event listener for the view. </p>
</td>
</tr>
<tr id="row1801541261093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2125474156093534"><a name="p2125474156093534"></a><a name="p2125474156093534"></a><a href="Graphic.md#gadd697fbf481f98d9d6ca8b67390071af">SetOnTouchListener</a> (<a href="OHOS-UIView-OnTouchListener.md">OnTouchListener</a> *onTouchListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1945432084093534"><a name="p1945432084093534"></a><a name="p1945432084093534"></a>void&nbsp;</p>
<p id="p937503027093534"><a name="p937503027093534"></a><a name="p937503027093534"></a>Sets a touch event listener for the view. </p>
</td>
</tr>
<tr id="row237858008093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1530752066093534"><a name="p1530752066093534"></a><a name="p1530752066093534"></a><a href="Graphic.md#gae7c65c68653103dae85acdcef78777a6">GetTouchListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p494408449093534"><a name="p494408449093534"></a><a name="p494408449093534"></a><a href="OHOS-UIView-OnTouchListener.md">OnTouchListener</a> *&amp;&nbsp;</p>
<p id="p2032210436093534"><a name="p2032210436093534"></a><a name="p2032210436093534"></a>Obtains the touch event listener for the view. </p>
</td>
</tr>
<tr id="row1269654971093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1576258147093534"><a name="p1576258147093534"></a><a name="p1576258147093534"></a><a href="Graphic.md#gaea9f334f2481e1c03a2cd8f3078d7c72">GetTargetView</a> (const <a href="OHOS-Point.md">Point</a> &amp;point, <a href="OHOS-UIView.md">UIView</a> **last)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2061615006093534"><a name="p2061615006093534"></a><a name="p2061615006093534"></a>virtual void&nbsp;</p>
<p id="p1970278948093534"><a name="p1970278948093534"></a><a name="p1970278948093534"></a>Obtains the top-level view based on specified coordinates. </p>
</td>
</tr>
<tr id="row739503764093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p631616923093534"><a name="p631616923093534"></a><a name="p631616923093534"></a><a href="Graphic.md#gaeea67a3a84b4ffe9bfeda418b82184cc">SetParent</a> (<a href="OHOS-UIView.md">UIView</a> *parent)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1114442979093534"><a name="p1114442979093534"></a><a name="p1114442979093534"></a>void&nbsp;</p>
<p id="p1484606856093534"><a name="p1484606856093534"></a><a name="p1484606856093534"></a>Sets the parent view for the view. </p>
</td>
</tr>
<tr id="row1678861583093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1122904156093534"><a name="p1122904156093534"></a><a name="p1122904156093534"></a><a href="Graphic.md#ga706530e4a38108615d5e0c918685ec96">GetParent</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p419498143093534"><a name="p419498143093534"></a><a name="p419498143093534"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1169801416093534"><a name="p1169801416093534"></a><a name="p1169801416093534"></a>Obtains the parent view of the view. </p>
</td>
</tr>
<tr id="row2012630592093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1139396088093534"><a name="p1139396088093534"></a><a name="p1139396088093534"></a><a href="Graphic.md#ga02bec5de07d93cabc45affba79eba4ad">SetNextSibling</a> (<a href="OHOS-UIView.md">UIView</a> *sibling)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p107818346093534"><a name="p107818346093534"></a><a name="p107818346093534"></a>void&nbsp;</p>
<p id="p1882403168093534"><a name="p1882403168093534"></a><a name="p1882403168093534"></a>Sets the next sibling view for the view. </p>
</td>
</tr>
<tr id="row1952547914093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2118783468093534"><a name="p2118783468093534"></a><a name="p2118783468093534"></a><a href="Graphic.md#gab0030977b30ddc9f2e15dbc2f58937e6">GetNextSibling</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1725109678093534"><a name="p1725109678093534"></a><a name="p1725109678093534"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p369168868093534"><a name="p369168868093534"></a><a name="p369168868093534"></a>Obtains the next sibling view of the view. </p>
</td>
</tr>
<tr id="row937878588093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1236177058093534"><a name="p1236177058093534"></a><a name="p1236177058093534"></a><a href="Graphic.md#ga07e7e1f268bd6ce975f4f0f8487af5d0">SetVisible</a> (bool visible)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2009769374093534"><a name="p2009769374093534"></a><a name="p2009769374093534"></a>virtual void&nbsp;</p>
<p id="p1889491533093534"><a name="p1889491533093534"></a><a name="p1889491533093534"></a>Sets whether the view is visible. </p>
</td>
</tr>
<tr id="row1414369976093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1037870215093534"><a name="p1037870215093534"></a><a name="p1037870215093534"></a><a href="Graphic.md#gaee178fc0a86ac03a6bdf2ade0c1914c8">IsVisible</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p849763847093534"><a name="p849763847093534"></a><a name="p849763847093534"></a>bool&nbsp;</p>
<p id="p210512650093534"><a name="p210512650093534"></a><a name="p210512650093534"></a>Checks whether the view is visible. </p>
</td>
</tr>
<tr id="row1813652185093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p383770914093534"><a name="p383770914093534"></a><a name="p383770914093534"></a><a href="Graphic.md#gaf9fb55fd9aa397f7158f1515e90bce02">SetTouchable</a> (bool touch)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p797842894093534"><a name="p797842894093534"></a><a name="p797842894093534"></a>void&nbsp;</p>
<p id="p1346407773093534"><a name="p1346407773093534"></a><a name="p1346407773093534"></a>Sets whether the view is touchable. </p>
</td>
</tr>
<tr id="row2057725504093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p701246503093534"><a name="p701246503093534"></a><a name="p701246503093534"></a><a href="Graphic.md#ga502a53fb77b260fa36b5b3adf82e2340">IsTouchable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1718016146093534"><a name="p1718016146093534"></a><a name="p1718016146093534"></a>bool&nbsp;</p>
<p id="p1206413407093534"><a name="p1206413407093534"></a><a name="p1206413407093534"></a>Checks whether the view is touchable. </p>
</td>
</tr>
<tr id="row993411006093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1561579654093534"><a name="p1561579654093534"></a><a name="p1561579654093534"></a><a href="Graphic.md#gab06abe0fe824c048f3b72974f9a8f0d0">SetDraggable</a> (bool draggable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p678312893093534"><a name="p678312893093534"></a><a name="p678312893093534"></a>void&nbsp;</p>
<p id="p469254911093534"><a name="p469254911093534"></a><a name="p469254911093534"></a>Sets whether the view is draggable. </p>
</td>
</tr>
<tr id="row1417080145093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p414289154093534"><a name="p414289154093534"></a><a name="p414289154093534"></a><a href="Graphic.md#ga25bb796ff400c767d622cbed280fc500">IsDraggable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p149658856093534"><a name="p149658856093534"></a><a name="p149658856093534"></a>bool&nbsp;</p>
<p id="p750961353093534"><a name="p750961353093534"></a><a name="p750961353093534"></a>Checks whether the view is draggable. </p>
</td>
</tr>
<tr id="row1259649813093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p658271174093534"><a name="p658271174093534"></a><a name="p658271174093534"></a><a href="Graphic.md#ga6c08e49bf7a82a7ebaef0f251e7a6f85">SetDragParentInstead</a> (bool dragParentInstead)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1888249599093534"><a name="p1888249599093534"></a><a name="p1888249599093534"></a>void&nbsp;</p>
<p id="p88868562093534"><a name="p88868562093534"></a><a name="p88868562093534"></a>Sets whether to transfer the drag event to the parent view for processing when the view is being dragged. </p>
</td>
</tr>
<tr id="row1666588206093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1188055848093534"><a name="p1188055848093534"></a><a name="p1188055848093534"></a><a href="Graphic.md#gaf0c462bc31e779b1898ad4cdfdad6faf">IsDragParentInstead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1691270272093534"><a name="p1691270272093534"></a><a name="p1691270272093534"></a>bool&nbsp;</p>
<p id="p1948747952093534"><a name="p1948747952093534"></a><a name="p1948747952093534"></a>Obtains whether the view transfers a drag event to the parent view for processing. </p>
</td>
</tr>
<tr id="row1111258061093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1023902409093534"><a name="p1023902409093534"></a><a name="p1023902409093534"></a><a href="Graphic.md#ga86cb8d364f18494d67636c55babced5c">GetRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p974069556093534"><a name="p974069556093534"></a><a name="p974069556093534"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p313727692093534"><a name="p313727692093534"></a><a name="p313727692093534"></a>Obtains the absolute rectangle area of the view. When the view has deformation such as rotation, the rectangle area is the intersection set of the absolute rectangle area and deformation matrix. </p>
</td>
</tr>
<tr id="row1282970034093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p741355510093534"><a name="p741355510093534"></a><a name="p741355510093534"></a><a href="Graphic.md#ga06e79704a19f2a238982076cac3d059b">GetVisibleRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p958759810093534"><a name="p958759810093534"></a><a name="p958759810093534"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1256008091093534"><a name="p1256008091093534"></a><a name="p1256008091093534"></a>Obtains the visible absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row1158431651093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p903816041093534"><a name="p903816041093534"></a><a name="p903816041093534"></a><a href="Graphic.md#gab3f8993b3953f27bfc61d53429916cba">GetMaskedRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2105941903093534"><a name="p2105941903093534"></a><a name="p2105941903093534"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1673373670093534"><a name="p1673373670093534"></a><a name="p1673373670093534"></a>Obtains the valid absolute rectangle area of the view. The valid area refers to the area where the view can be displayed. Generally, the valid area is the same as the visible view area, but they may be different in the grid layout. </p>
</td>
</tr>
<tr id="row113796211093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1934347755093534"><a name="p1934347755093534"></a><a name="p1934347755093534"></a><a href="Graphic.md#ga64cf308a09999def1192f9c4e0f17f0a">GetOrigRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p806959342093534"><a name="p806959342093534"></a><a name="p806959342093534"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p788349765093534"><a name="p788349765093534"></a><a name="p788349765093534"></a>Obtains the absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row1989321848093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p856851957093534"><a name="p856851957093534"></a><a name="p856851957093534"></a><a href="Graphic.md#ga9db88eae712676359d02a92be14fa316">GetContentRect</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1510191773093534"><a name="p1510191773093534"></a><a name="p1510191773093534"></a>virtual <a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p426184620093534"><a name="p426184620093534"></a><a name="p426184620093534"></a>Obtains the content of the absolute rectangle area of the view. This area excludes padding. </p>
</td>
</tr>
<tr id="row676028686093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1640660036093534"><a name="p1640660036093534"></a><a name="p1640660036093534"></a><a href="Graphic.md#gae9b96837fa1d45648a2a6fbbfcc5eb4a">GetRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1276073418093534"><a name="p1276073418093534"></a><a name="p1276073418093534"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1026670143093534"><a name="p1026670143093534"></a><a name="p1026670143093534"></a>Obtains the rectangular area of the view relative to the parent view, that is, the rectangular area relative to the coordinates of the parent view. </p>
</td>
</tr>
<tr id="row506387848093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p354360742093534"><a name="p354360742093534"></a><a name="p354360742093534"></a><a href="Graphic.md#gae6c5f3bcf99dc837bcecd60c38d3df5a">ResizeVisibleArea</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p210181813093534"><a name="p210181813093534"></a><a name="p210181813093534"></a>void&nbsp;</p>
<p id="p1034186721093534"><a name="p1034186721093534"></a><a name="p1034186721093534"></a>Adjusts the size of the visible area. This operation may affect the final display size. </p>
</td>
</tr>
<tr id="row699258316093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p778096939093534"><a name="p778096939093534"></a><a name="p778096939093534"></a><a href="Graphic.md#ga3375ec5ef059fd88c657af4552d2fa4f">SetWidth</a> (int16_t width)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p487588151093534"><a name="p487588151093534"></a><a name="p487588151093534"></a>virtual void&nbsp;</p>
<p id="p478551090093534"><a name="p478551090093534"></a><a name="p478551090093534"></a>Sets the width for the view. </p>
</td>
</tr>
<tr id="row1125203994093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p983520211093534"><a name="p983520211093534"></a><a name="p983520211093534"></a><a href="Graphic.md#ga9c7110620d5dc3a7bd3efe1fc2edd125">SetHeight</a> (int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p812257452093534"><a name="p812257452093534"></a><a name="p812257452093534"></a>virtual void&nbsp;</p>
<p id="p400582539093534"><a name="p400582539093534"></a><a name="p400582539093534"></a>Sets the height for the view. </p>
</td>
</tr>
<tr id="row1383663642093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2111228072093534"><a name="p2111228072093534"></a><a name="p2111228072093534"></a><a href="Graphic.md#gae985b607d2f0701911778bf20d640ccd">Resize</a> (int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p444732808093534"><a name="p444732808093534"></a><a name="p444732808093534"></a>virtual void&nbsp;</p>
<p id="p964435987093534"><a name="p964435987093534"></a><a name="p964435987093534"></a>Adjusts the size of the view. </p>
</td>
</tr>
<tr id="row912443361093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1922898393093534"><a name="p1922898393093534"></a><a name="p1922898393093534"></a><a href="Graphic.md#gaded403626558d28e62bf5632ccbb24b5">SetX</a> (int16_t x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p647398682093534"><a name="p647398682093534"></a><a name="p647398682093534"></a>virtual void&nbsp;</p>
<p id="p647217815093534"><a name="p647217815093534"></a><a name="p647217815093534"></a>Sets the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row769671403093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p525995264093534"><a name="p525995264093534"></a><a name="p525995264093534"></a><a href="Graphic.md#ga89dc5f8fb1cb4b2259dc0439185359f1">GetX</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p535427185093534"><a name="p535427185093534"></a><a name="p535427185093534"></a>int16_t&nbsp;</p>
<p id="p2061546424093534"><a name="p2061546424093534"></a><a name="p2061546424093534"></a>Obtains the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row871854645093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1755673344093534"><a name="p1755673344093534"></a><a name="p1755673344093534"></a><a href="Graphic.md#gaaa8edc224cf1c7deb2724fb225960877">SetY</a> (int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1701590259093534"><a name="p1701590259093534"></a><a name="p1701590259093534"></a>virtual void&nbsp;</p>
<p id="p1594072793093534"><a name="p1594072793093534"></a><a name="p1594072793093534"></a>Sets the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row1304504119093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1356572020093534"><a name="p1356572020093534"></a><a name="p1356572020093534"></a><a href="Graphic.md#ga193619d649204b0e9bb854d3b30275c3">GetY</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p367701905093534"><a name="p367701905093534"></a><a name="p367701905093534"></a>int16_t&nbsp;</p>
<p id="p2113283806093534"><a name="p2113283806093534"></a><a name="p2113283806093534"></a>Obtains the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row1554809328093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p971206217093534"><a name="p971206217093534"></a><a name="p971206217093534"></a><a href="Graphic.md#gab34233f6aeae330b025969137d03e67a">SetPosition</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1139477631093534"><a name="p1139477631093534"></a><a name="p1139477631093534"></a>virtual void&nbsp;</p>
<p id="p2067446400093534"><a name="p2067446400093534"></a><a name="p2067446400093534"></a>Sets the position for the view. </p>
</td>
</tr>
<tr id="row567237477093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1140777364093534"><a name="p1140777364093534"></a><a name="p1140777364093534"></a><a href="Graphic.md#gaf8ce4c009f23b7175b2b34bac4a74262">SetPosition</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p315936067093534"><a name="p315936067093534"></a><a name="p315936067093534"></a>virtual void&nbsp;</p>
<p id="p1051651715093534"><a name="p1051651715093534"></a><a name="p1051651715093534"></a>Adjusts the position and size of the view. </p>
</td>
</tr>
<tr id="row2060751358093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p432418071093534"><a name="p432418071093534"></a><a name="p432418071093534"></a><a href="Graphic.md#gab2ce8c11abbd55f40687f38a52511b11">IsViewGroup</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1778543952093534"><a name="p1778543952093534"></a><a name="p1778543952093534"></a>bool&nbsp;</p>
<p id="p552449079093534"><a name="p552449079093534"></a><a name="p552449079093534"></a>Checks whether the view is a container view. </p>
</td>
</tr>
<tr id="row958096271093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1392978910093534"><a name="p1392978910093534"></a><a name="p1392978910093534"></a><a href="Graphic.md#ga980fc6824c64cfae6af8657aee17af88">SetIntercept</a> (bool isIntercept)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2084755482093534"><a name="p2084755482093534"></a><a name="p2084755482093534"></a>void&nbsp;</p>
<p id="p21791486093534"><a name="p21791486093534"></a><a name="p21791486093534"></a>Sets whether to intercept the drag event. If intercepted, the view does not transfer the drag event to the parent view after local processing. </p>
</td>
</tr>
<tr id="row938395034093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1013996904093534"><a name="p1013996904093534"></a><a name="p1013996904093534"></a><a href="Graphic.md#ga8623abbbeff458c0cb2d7dc0d1f21e4a">SetTransformMap</a> (const <a href="OHOS-TransformMap.md">TransformMap</a> &amp;transMap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p224045421093534"><a name="p224045421093534"></a><a name="p224045421093534"></a>void&nbsp;</p>
<p id="p740807759093534"><a name="p740807759093534"></a><a name="p740807759093534"></a>Sets the affine transformation matrix. </p>
</td>
</tr>
<tr id="row227429237093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1561618719093534"><a name="p1561618719093534"></a><a name="p1561618719093534"></a><a href="Graphic.md#gab8cee5a7052a88722768c8ed1324abc1">GetTransformMap</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1569794563093534"><a name="p1569794563093534"></a><a name="p1569794563093534"></a><a href="OHOS-TransformMap.md">TransformMap</a> &amp;&nbsp;</p>
<p id="p1663703845093534"><a name="p1663703845093534"></a><a name="p1663703845093534"></a>Obtains an affine transformation matrix. </p>
</td>
</tr>
<tr id="row419121451093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p715020771093534"><a name="p715020771093534"></a><a name="p715020771093534"></a><a href="Graphic.md#ga0573aa25307c22319db4629781b5cad2">GetChildById</a> (const char *id) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1833510945093534"><a name="p1833510945093534"></a><a name="p1833510945093534"></a>virtual <a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1237587481093534"><a name="p1237587481093534"></a><a name="p1237587481093534"></a>Obtains the child view of a specified ID. </p>
</td>
</tr>
<tr id="row1899534362093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1920020286093534"><a name="p1920020286093534"></a><a name="p1920020286093534"></a><a href="Graphic.md#ga0caaa15c9b304673331e778a266be77f">SetViewId</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1811853519093534"><a name="p1811853519093534"></a><a name="p1811853519093534"></a>void&nbsp;</p>
<p id="p791390466093534"><a name="p791390466093534"></a><a name="p791390466093534"></a>Sets the view ID. </p>
</td>
</tr>
<tr id="row1680910945093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p373032672093534"><a name="p373032672093534"></a><a name="p373032672093534"></a><a href="Graphic.md#gad6c7644bd2abfa3c92d80776b0bd1936">GetViewId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1438501834093534"><a name="p1438501834093534"></a><a name="p1438501834093534"></a>const char *&nbsp;</p>
<p id="p1467801752093534"><a name="p1467801752093534"></a><a name="p1467801752093534"></a>Obtains the view ID. </p>
</td>
</tr>
<tr id="row320048268093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p323000993093534"><a name="p323000993093534"></a><a name="p323000993093534"></a><a href="Graphic.md#ga77a961aa53567c5214508b4569801c16">SetViewIndex</a> (int16_t <a href="zh-cn_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1441299842093534"><a name="p1441299842093534"></a><a name="p1441299842093534"></a>void&nbsp;</p>
<p id="p148189147093534"><a name="p148189147093534"></a><a name="p148189147093534"></a>Sets the view index. </p>
</td>
</tr>
<tr id="row630969816093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p825879403093534"><a name="p825879403093534"></a><a name="p825879403093534"></a><a href="Graphic.md#ga62f51715b6d420a296ebe0296717b906">GetViewIndex</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1770794479093534"><a name="p1770794479093534"></a><a name="p1770794479093534"></a>int16_t&nbsp;</p>
<p id="p1168353296093534"><a name="p1168353296093534"></a><a name="p1168353296093534"></a>Obtains the view index. </p>
</td>
</tr>
<tr id="row1561328315093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1900526234093534"><a name="p1900526234093534"></a><a name="p1900526234093534"></a><a href="Graphic.md#gaca871fa2f8219e7ea9388e212d1f1e69">LayoutChildren</a> (bool neeInvalidate=false)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p710966399093534"><a name="p710966399093534"></a><a name="p710966399093534"></a>virtual void&nbsp;</p>
<p id="p1915631488093534"><a name="p1915631488093534"></a><a name="p1915631488093534"></a>Lays out all child views according to the preset arrangement mode. </p>
</td>
</tr>
<tr id="row1575772638093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1183344239093534"><a name="p1183344239093534"></a><a name="p1183344239093534"></a><a href="Graphic.md#ga443b86ee9275b0421b37a47bad3264dc">LayoutCenterOfParent</a> (int16_t xOffSet=0, int16_t yOffset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1461827663093534"><a name="p1461827663093534"></a><a name="p1461827663093534"></a>void&nbsp;</p>
<p id="p312067112093534"><a name="p312067112093534"></a><a name="p312067112093534"></a>Lays out the view in the center of the parent view. </p>
</td>
</tr>
<tr id="row1184210487093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p429156156093534"><a name="p429156156093534"></a><a name="p429156156093534"></a><a href="Graphic.md#ga94999b271f27cd5d6bfaf303f7d5c708">LayoutLeftOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p279928691093534"><a name="p279928691093534"></a><a name="p279928691093534"></a>void&nbsp;</p>
<p id="p627714891093534"><a name="p627714891093534"></a><a name="p627714891093534"></a>Lays out the view on the left of the parent view. </p>
</td>
</tr>
<tr id="row114536127093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p326797562093534"><a name="p326797562093534"></a><a name="p326797562093534"></a><a href="Graphic.md#ga479528ed259b5539e423955f2b60517d">LayoutRightOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2129424610093534"><a name="p2129424610093534"></a><a name="p2129424610093534"></a>void&nbsp;</p>
<p id="p1553147426093534"><a name="p1553147426093534"></a><a name="p1553147426093534"></a>Lays out the view on the right of the parent view. </p>
</td>
</tr>
<tr id="row641080246093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p889176253093534"><a name="p889176253093534"></a><a name="p889176253093534"></a><a href="Graphic.md#ga859288ea61ad23ba7e381bbc07769e83">LayoutTopOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p488104210093534"><a name="p488104210093534"></a><a name="p488104210093534"></a>void&nbsp;</p>
<p id="p1418207885093534"><a name="p1418207885093534"></a><a name="p1418207885093534"></a>Lays out the view on the top of the parent view. </p>
</td>
</tr>
<tr id="row1920848062093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1750813617093534"><a name="p1750813617093534"></a><a name="p1750813617093534"></a><a href="Graphic.md#ga809aeee4792ae58218a0bcfcb94d5cdc">LayoutBottomOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p107097388093534"><a name="p107097388093534"></a><a name="p107097388093534"></a>void&nbsp;</p>
<p id="p39572147093534"><a name="p39572147093534"></a><a name="p39572147093534"></a>Lays out the view on the bottom of the parent view. </p>
</td>
</tr>
<tr id="row1131259755093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1238997461093534"><a name="p1238997461093534"></a><a name="p1238997461093534"></a><a href="Graphic.md#gac7f5f2584c716a56fee3783f8dea6246">AlignLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p424188113093534"><a name="p424188113093534"></a><a name="p424188113093534"></a>void&nbsp;</p>
<p id="p68558073093534"><a name="p68558073093534"></a><a name="p68558073093534"></a>Aligns the view with the left of a sibling view. </p>
</td>
</tr>
<tr id="row1457586927093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1854718032093534"><a name="p1854718032093534"></a><a name="p1854718032093534"></a><a href="Graphic.md#gabb1ac454cdf95593c1e387d5e272433c">AlignRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p502040002093534"><a name="p502040002093534"></a><a name="p502040002093534"></a>void&nbsp;</p>
<p id="p1671951671093534"><a name="p1671951671093534"></a><a name="p1671951671093534"></a>Aligns the view with the right of a sibling view. </p>
</td>
</tr>
<tr id="row1873161064093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1713151408093534"><a name="p1713151408093534"></a><a name="p1713151408093534"></a><a href="Graphic.md#ga903d7cbc59bac06d728b7f6435c9a504">AlignTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1333136667093534"><a name="p1333136667093534"></a><a name="p1333136667093534"></a>void&nbsp;</p>
<p id="p1910369242093534"><a name="p1910369242093534"></a><a name="p1910369242093534"></a>Aligns the view with the top of a sibling view. </p>
</td>
</tr>
<tr id="row733802335093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p114471565093534"><a name="p114471565093534"></a><a name="p114471565093534"></a><a href="Graphic.md#ga7607c3f9661932c495d080e9d92fb1a3">AlignBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p681484505093534"><a name="p681484505093534"></a><a name="p681484505093534"></a>void&nbsp;</p>
<p id="p1776737535093534"><a name="p1776737535093534"></a><a name="p1776737535093534"></a>Aligns the view with the bottom of a sibling view. </p>
</td>
</tr>
<tr id="row2080521764093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2055886185093534"><a name="p2055886185093534"></a><a name="p2055886185093534"></a><a href="Graphic.md#gac23776dbc2fce7ff30d57438abfa5230">AlignHorCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2087647122093534"><a name="p2087647122093534"></a><a name="p2087647122093534"></a>void&nbsp;</p>
<p id="p1812019476093534"><a name="p1812019476093534"></a><a name="p1812019476093534"></a>Aligns the view with the center of a sibling view in the x-axis. </p>
</td>
</tr>
<tr id="row1446439496093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1566859292093534"><a name="p1566859292093534"></a><a name="p1566859292093534"></a><a href="Graphic.md#gad3caa27aa0cb73ec4656e7d23aa222de">AlignVerCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p84444578093534"><a name="p84444578093534"></a><a name="p84444578093534"></a>void&nbsp;</p>
<p id="p278193814093534"><a name="p278193814093534"></a><a name="p278193814093534"></a>Aligns the view with the center of a sibling view in the y-axis. </p>
</td>
</tr>
<tr id="row994637842093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p390589839093534"><a name="p390589839093534"></a><a name="p390589839093534"></a><a href="Graphic.md#ga58f1a34a943c4492970f901d63bbc3d8">LayoutLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p902392755093534"><a name="p902392755093534"></a><a name="p902392755093534"></a>void&nbsp;</p>
<p id="p1169146918093534"><a name="p1169146918093534"></a><a name="p1169146918093534"></a>Lays out the view on the left of a sibling view. </p>
</td>
</tr>
<tr id="row1810463984093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1137775429093534"><a name="p1137775429093534"></a><a name="p1137775429093534"></a><a href="Graphic.md#gac4cd64de5291759add164825a323a0d6">LayoutRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p244878299093534"><a name="p244878299093534"></a><a name="p244878299093534"></a>void&nbsp;</p>
<p id="p176748715093534"><a name="p176748715093534"></a><a name="p176748715093534"></a>Lays out the view on the right of a sibling view. </p>
</td>
</tr>
<tr id="row728194858093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1634071953093534"><a name="p1634071953093534"></a><a name="p1634071953093534"></a><a href="Graphic.md#gaaa8385807e3a9bea46f8dcc326252a70">LayoutTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2008230907093534"><a name="p2008230907093534"></a><a name="p2008230907093534"></a>void&nbsp;</p>
<p id="p976819752093534"><a name="p976819752093534"></a><a name="p976819752093534"></a>Lays out the view on the above of a sibling view. </p>
</td>
</tr>
<tr id="row1965773523093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1678910073093534"><a name="p1678910073093534"></a><a name="p1678910073093534"></a><a href="Graphic.md#gaa23a68e8ef0fb13b362218e71cf67ace">LayoutBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1971689398093534"><a name="p1971689398093534"></a><a name="p1971689398093534"></a>void&nbsp;</p>
<p id="p1501545594093534"><a name="p1501545594093534"></a><a name="p1501545594093534"></a>Lays out the view on the below of a sibling view. </p>
</td>
</tr>
<tr id="row155556939093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p47726608093534"><a name="p47726608093534"></a><a name="p47726608093534"></a><a href="Graphic.md#ga9c1a3db000fdcd200fec8d2c49f5a0a8">SetStyle</a> (<a href="OHOS-Style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1343326338093534"><a name="p1343326338093534"></a><a name="p1343326338093534"></a>virtual void&nbsp;</p>
<p id="p897431580093534"><a name="p897431580093534"></a><a name="p897431580093534"></a>Sets the view style. </p>
</td>
</tr>
<tr id="row488605348093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p600458731093534"><a name="p600458731093534"></a><a name="p600458731093534"></a><a href="Graphic.md#ga0945c2f05815dc2e466ef9ceaca2f700">SetStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p151180874093534"><a name="p151180874093534"></a><a name="p151180874093534"></a>virtual void&nbsp;</p>
<p id="p850274279093534"><a name="p850274279093534"></a><a name="p850274279093534"></a>Sets a style. </p>
</td>
</tr>
<tr id="row853562463093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1698432647093534"><a name="p1698432647093534"></a><a name="p1698432647093534"></a><a href="Graphic.md#ga4ea19bc9f4b487946c9e29e63b54a0e6">GetStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p28205304093534"><a name="p28205304093534"></a><a name="p28205304093534"></a>virtual int64_t&nbsp;</p>
<p id="p458425972093534"><a name="p458425972093534"></a><a name="p458425972093534"></a>Obtains the value of a style. </p>
</td>
</tr>
<tr id="row1836414658093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1139927955093534"><a name="p1139927955093534"></a><a name="p1139927955093534"></a><a href="Graphic.md#ga1b28213d4c2cd0f8324bce3fe56eb7bb">GetStyleConst</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1593266028093534"><a name="p1593266028093534"></a><a name="p1593266028093534"></a>const <a href="OHOS-Style.md">Style</a> &amp;&nbsp;</p>
<p id="p1349833699093534"><a name="p1349833699093534"></a><a name="p1349833699093534"></a>Obtains the view style. This function applies to scenarios where the style does not need to be modified, which saves memory. </p>
</td>
</tr>
<tr id="row952307747093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p910195474093534"><a name="p910195474093534"></a><a name="p910195474093534"></a><a href="Graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2089868260093534"><a name="p2089868260093534"></a><a name="p2089868260093534"></a>void *&nbsp;</p>
<p id="p652630551093534"><a name="p652630551093534"></a><a name="p652630551093534"></a>Overrides the <strong id="b880494301093534"><a name="b880494301093534"></a><a name="b880494301093534"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row586376339093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p862915897093534"><a name="p862915897093534"></a><a name="p862915897093534"></a><a href="Graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2058533545093534"><a name="p2058533545093534"></a><a name="p2058533545093534"></a>void&nbsp;</p>
<p id="p533978789093534"><a name="p533978789093534"></a><a name="p533978789093534"></a>Overrides the <strong id="b1980585530093534"><a name="b1980585530093534"></a><a name="b1980585530093534"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

## Additional Inherited Members<a name="inherited"></a>

<a name="table730587520093534"></a>
<table><thead align="left"><tr id="row366578559093534"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1004995679093534"><a name="p1004995679093534"></a><a name="p1004995679093534"></a>Additional Inherited Member Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1575577282093534"><a name="p1575577282093534"></a><a name="p1575577282093534"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1478863836093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1782660569093534"><a name="p1782660569093534"></a><a name="p1782660569093534"></a><a href="Graphic.md#ga3e530646bd55e49f0e5b0052e121f040">imageWidth_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p989529324093534"><a name="p989529324093534"></a><a name="p989529324093534"></a>Represents the width of this image. </p>
</td>
</tr>
<tr id="row1056416870093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1060273554093534"><a name="p1060273554093534"></a><a name="p1060273554093534"></a><a href="Graphic.md#ga5a7112d86d7b11b904b57c853817621d">imageHeight_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p574184132093534"><a name="p574184132093534"></a><a name="p574184132093534"></a>Represents the height of this image. </p>
</td>
</tr>
<tr id="row459713255093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p641484136093534"><a name="p641484136093534"></a><a name="p641484136093534"></a><a href="Graphic.md#gac13c0b542f4d7f789754bacf572894b2">autoEnable_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1420815517093534"><a name="p1420815517093534"></a><a name="p1420815517093534"></a>Specifies whether automatic adaptation is enabled. </p>
</td>
</tr>
<tr id="row131517723093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1532625668093534"><a name="p1532625668093534"></a><a name="p1532625668093534"></a><a href="Graphic.md#ga687a71ca22c04a7e761969f1fab1b06f">needRefresh_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p237934060093534"><a name="p237934060093534"></a><a name="p237934060093534"></a>Specifies whether a refresh is needed. </p>
</td>
</tr>
<tr id="row1118268204093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p44175425093534"><a name="p44175425093534"></a><a name="p44175425093534"></a><a href="Graphic.md#gacbbee3e74893c43864b116779d97ad09">colorFormat_</a>: 4</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p854175566093534"><a name="p854175566093534"></a><a name="p854175566093534"></a>Represents the color format of this image. </p>
</td>
</tr>
<tr id="row44380601093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1445280955093534"><a name="p1445280955093534"></a><a name="p1445280955093534"></a><a href="Graphic.md#ga1c57bd4af56c49a11060e32b6e33066c">blurLevel_</a>: 2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p332029511093534"><a name="p332029511093534"></a><a name="p332029511093534"></a>Represents the blur level of this image when it is rotated or scaled. </p>
</td>
</tr>
<tr id="row1772520345093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p487377474093534"><a name="p487377474093534"></a><a name="p487377474093534"></a><a href="Graphic.md#ga5a8f8683c377c59c6a3c193f18468e60">algorithm_</a>: 1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p643671964093534"><a name="p643671964093534"></a><a name="p643671964093534"></a>Represents the algorithm used for image rotation and scaling. </p>
</td>
</tr>
</tbody>
</table>

