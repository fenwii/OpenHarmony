# OHOS::Animator<a name="ZH-CN_TOPIC_0000001055518106"></a>

## **Overview**<a name="section1405122097093533"></a>

**Related Modules:**

[Graphic](Graphic.md)

**Description:**

Represents an animator. 

This class is used to set the animator attributes, such as the duration, whether an animator is repeated, start and stop of an animator.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section301920878093533"></a>

## Public Types<a name="pub-types"></a>

<a name="table1197783799093533"></a>
<table><thead align="left"><tr id="row478211553093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1191823996093533"><a name="p1191823996093533"></a><a name="p1191823996093533"></a>Public Type Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1438013700093533"><a name="p1438013700093533"></a><a name="p1438013700093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1732930242093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1977387179093533"><a name="p1977387179093533"></a><a name="p1977387179093533"></a>: uint8_t { <a href="Graphic.md#gga7b892afa4e88ab11bf96dbd67653f134a6618a5c1c0e9e4be3acba1aaee15cb8d">STOP</a>, <a href="Graphic.md#gga7b892afa4e88ab11bf96dbd67653f134a49f9e652157f467df5de3be9e8758f91">START</a>, <a href="Graphic.md#gga7b892afa4e88ab11bf96dbd67653f134ae5db6c9a921eec21a2990d73400ff507">PAUSE</a>, <a href="Graphic.md#gga7b892afa4e88ab11bf96dbd67653f134a6ef6036766e105b2cd6bf2fb94e92e1b">RUNNING</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p174012373093533"><a name="p174012373093533"></a><a name="p174012373093533"></a>Enumerates the states of this animator. </p>
</td>
</tr>
</tbody>
</table>

## Public Member Functions<a name="pub-methods"></a>

<a name="table377169577093533"></a>
<table><thead align="left"><tr id="row326902421093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p39807169093533"><a name="p39807169093533"></a><a name="p39807169093533"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1542920049093533"><a name="p1542920049093533"></a><a name="p1542920049093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row121144328093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2100618280093533"><a name="p2100618280093533"></a><a name="p2100618280093533"></a><a href="Graphic.md#gabcc3afbe99010e70e3e6dbd780cb5974">Animator</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1002899832093533"><a name="p1002899832093533"></a><a name="p1002899832093533"></a>&nbsp;</p>
<p id="p1855746949093533"><a name="p1855746949093533"></a><a name="p1855746949093533"></a>A default constructor used to create an <strong id="b1074560116093533"><a name="b1074560116093533"></a><a name="b1074560116093533"></a><a href="OHOS-Animator.md">Animator</a></strong> instance. </p>
</td>
</tr>
<tr id="row1958171417093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p327387641093533"><a name="p327387641093533"></a><a name="p327387641093533"></a><a href="Graphic.md#ga79be500c40ba8743dd58dc633a732b53">Animator</a> (<a href="OHOS-AnimatorCallback.md">AnimatorCallback</a> *callback, <a href="OHOS-UIView.md">UIView</a> *view, uint32_t <a href="zh-cn_topic_0000001054879478.md#gae7841e681c8c9d59818568d39553642c">time</a>, bool repeat)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2126294840093533"><a name="p2126294840093533"></a><a name="p2126294840093533"></a>&nbsp;</p>
<p id="p699443264093533"><a name="p699443264093533"></a><a name="p699443264093533"></a>A constructor used to create an <strong id="b971944344093533"><a name="b971944344093533"></a><a name="b971944344093533"></a><a href="OHOS-Animator.md">Animator</a></strong> instance. </p>
</td>
</tr>
<tr id="row1413442860093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p176081222093533"><a name="p176081222093533"></a><a name="p176081222093533"></a><a href="Graphic.md#gaee2a71f97b102654ca3b7ded4b5ce350">~Animator</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2094573898093533"><a name="p2094573898093533"></a><a name="p2094573898093533"></a>virtual&nbsp;</p>
<p id="p2143714336093533"><a name="p2143714336093533"></a><a name="p2143714336093533"></a>A destructor used to delete the <strong id="b271975274093533"><a name="b271975274093533"></a><a name="b271975274093533"></a><a href="OHOS-Animator.md">Animator</a></strong> instance. </p>
</td>
</tr>
<tr id="row1789202766093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2085010465093533"><a name="p2085010465093533"></a><a name="p2085010465093533"></a><a href="Graphic.md#gad56477fe4b6d0158082e841e327c1bf6">Start</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p799989706093533"><a name="p799989706093533"></a><a name="p799989706093533"></a>void&nbsp;</p>
<p id="p2008632751093533"><a name="p2008632751093533"></a><a name="p2008632751093533"></a>Starts this animator. </p>
</td>
</tr>
<tr id="row553533624093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p871428087093533"><a name="p871428087093533"></a><a name="p871428087093533"></a><a href="Graphic.md#gad670cee429a5535149db0f8b3828e951">Stop</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p14706315093533"><a name="p14706315093533"></a><a name="p14706315093533"></a>void&nbsp;</p>
<p id="p1450100953093533"><a name="p1450100953093533"></a><a name="p1450100953093533"></a>Stops this animator. </p>
</td>
</tr>
<tr id="row642427523093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p319166181093533"><a name="p319166181093533"></a><a name="p319166181093533"></a><a href="Graphic.md#ga4dd9d23ebff1359bd1145fd2f26e1be2">Pause</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p278932057093533"><a name="p278932057093533"></a><a name="p278932057093533"></a>void&nbsp;</p>
<p id="p643010259093533"><a name="p643010259093533"></a><a name="p643010259093533"></a>Pauses this animator. </p>
</td>
</tr>
<tr id="row1989845060093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1672118125093533"><a name="p1672118125093533"></a><a name="p1672118125093533"></a><a href="Graphic.md#ga645bbd33356bd708636a94c3d95c282d">Resume</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p706113178093533"><a name="p706113178093533"></a><a name="p706113178093533"></a>void&nbsp;</p>
<p id="p215338912093533"><a name="p215338912093533"></a><a name="p215338912093533"></a>Resumes this animator from where it was paused. </p>
</td>
</tr>
<tr id="row1903976632093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p805405681093533"><a name="p805405681093533"></a><a name="p805405681093533"></a><a href="Graphic.md#gafd0166df63bed582022ed93175dd3179">GetState</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p492779589093533"><a name="p492779589093533"></a><a name="p492779589093533"></a>uint8_t&nbsp;</p>
<p id="p1359915537093533"><a name="p1359915537093533"></a><a name="p1359915537093533"></a>Obtains the current state of this animator. </p>
</td>
</tr>
<tr id="row42863172093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p165369380093533"><a name="p165369380093533"></a><a name="p165369380093533"></a><a href="Graphic.md#gab8ec3815f5e42605a51a328c1b0857dd">SetState</a> (uint8_t state)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1100045327093533"><a name="p1100045327093533"></a><a name="p1100045327093533"></a>void&nbsp;</p>
<p id="p645333159093533"><a name="p645333159093533"></a><a name="p645333159093533"></a>Sets the current state for this animator. </p>
</td>
</tr>
<tr id="row66261680093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p762501580093533"><a name="p762501580093533"></a><a name="p762501580093533"></a><a href="Graphic.md#gac05ba70bafa9887dc23ea4ba69da632d">GetTime</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p238359474093533"><a name="p238359474093533"></a><a name="p238359474093533"></a>uint32_t&nbsp;</p>
<p id="p1218607331093533"><a name="p1218607331093533"></a><a name="p1218607331093533"></a>Obtains the total duration of this animator. </p>
</td>
</tr>
<tr id="row429043015093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2068737940093533"><a name="p2068737940093533"></a><a name="p2068737940093533"></a><a href="Graphic.md#ga5a2bfa5fb257b2116d08ad5ae254327c">SetTime</a> (uint32_t <a href="zh-cn_topic_0000001054879478.md#gae7841e681c8c9d59818568d39553642c">time</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2004686175093533"><a name="p2004686175093533"></a><a name="p2004686175093533"></a>void&nbsp;</p>
<p id="p1951273265093533"><a name="p1951273265093533"></a><a name="p1951273265093533"></a>Sets the total duration for this animator. </p>
</td>
</tr>
<tr id="row393555927093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1806779748093533"><a name="p1806779748093533"></a><a name="p1806779748093533"></a><a href="Graphic.md#ga18a8b8b9ceb344e6660a5c0de5a9ce1f">GetRunTime</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1511277934093533"><a name="p1511277934093533"></a><a name="p1511277934093533"></a>uint32_t&nbsp;</p>
<p id="p1127080466093533"><a name="p1127080466093533"></a><a name="p1127080466093533"></a>Obtains the running time of this animator. </p>
</td>
</tr>
<tr id="row2143494097093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1969816685093533"><a name="p1969816685093533"></a><a name="p1969816685093533"></a><a href="Graphic.md#ga4d5ff5057df28da1bc99d08070312f24">SetRunTime</a> (uint32_t runTime)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1251029240093533"><a name="p1251029240093533"></a><a name="p1251029240093533"></a>void&nbsp;</p>
<p id="p1074214480093533"><a name="p1074214480093533"></a><a name="p1074214480093533"></a>Sets the running time for this animator. </p>
</td>
</tr>
<tr id="row1727961483093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p218851016093533"><a name="p218851016093533"></a><a name="p218851016093533"></a><a href="Graphic.md#gacd3c360c8a3f6b5aeffcf10c1a1588da">IsRepeat</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p891806270093533"><a name="p891806270093533"></a><a name="p891806270093533"></a>bool&nbsp;</p>
<p id="p1417233406093533"><a name="p1417233406093533"></a><a name="p1417233406093533"></a>Checks whether this animator is repeated. </p>
</td>
</tr>
<tr id="row1768761016093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p922674202093533"><a name="p922674202093533"></a><a name="p922674202093533"></a><a href="Graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1097645457093533"><a name="p1097645457093533"></a><a name="p1097645457093533"></a>void *&nbsp;</p>
<p id="p834571350093533"><a name="p834571350093533"></a><a name="p834571350093533"></a>Overrides the <strong id="b1525364805093533"><a name="b1525364805093533"></a><a name="b1525364805093533"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row132967225093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p203147356093533"><a name="p203147356093533"></a><a name="p203147356093533"></a><a href="Graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p810224735093533"><a name="p810224735093533"></a><a name="p810224735093533"></a>void&nbsp;</p>
<p id="p36787977093533"><a name="p36787977093533"></a><a name="p36787977093533"></a>Overrides the <strong id="b597373008093533"><a name="b597373008093533"></a><a name="b597373008093533"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

