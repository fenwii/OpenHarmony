# OHOS::SysInfo::OnFPSChangedListener<a name="EN-US_TOPIC_0000001055039550"></a>

## **Overview**<a name="section692633069093535"></a>

**Related Modules:**

[Graphic](graphic.md)

**Description:**

Called when the FPS changes. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1145127675093535"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table1886914788093535"></a>
<table><thead align="left"><tr id="row845036221093535"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p158451976093535"><a name="p158451976093535"></a><a name="p158451976093535"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p901548037093535"><a name="p901548037093535"></a><a name="p901548037093535"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row858208674093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1096460983093535"><a name="p1096460983093535"></a><a name="p1096460983093535"></a><a href="graphic.md#ga3e24fe52ec7c4bf9fc9f5703982b3568">OnFPSChangedListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1092367368093535"><a name="p1092367368093535"></a><a name="p1092367368093535"></a> </p>
<p id="p2012714601093535"><a name="p2012714601093535"></a><a name="p2012714601093535"></a>A constructor used to create an <strong id="b1745615143093535"><a name="b1745615143093535"></a><a name="b1745615143093535"></a><a href="ohos-sysinfo-onfpschangedlistener.md">OnFPSChangedListener</a></strong> instance with the default sampling type <strong id="b1837024129093535"><a name="b1837024129093535"></a><a name="b1837024129093535"></a>FPS_CT_FIXED_TIME</strong>. </p>
</td>
</tr>
<tr id="row1579502026093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1922183064093535"><a name="p1922183064093535"></a><a name="p1922183064093535"></a><a href="graphic.md#ga4e103243c2fd1e2e5206262280f1b80c">~OnFPSChangedListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1619856370093535"><a name="p1619856370093535"></a><a name="p1619856370093535"></a>virtual </p>
<p id="p1678132466093535"><a name="p1678132466093535"></a><a name="p1678132466093535"></a>A destructor used to delete the <strong id="b181102574093535"><a name="b181102574093535"></a><a name="b181102574093535"></a><a href="ohos-sysinfo-onfpschangedlistener.md">OnFPSChangedListener</a></strong> instance. </p>
</td>
</tr>
<tr id="row1114008424093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p723517007093535"><a name="p723517007093535"></a><a name="p723517007093535"></a><a href="graphic.md#ga82a8426a18e30ff3e9d4d388c53b4af5">OnFPSChanged</a> (float newFPS)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1553563098093535"><a name="p1553563098093535"></a><a name="p1553563098093535"></a>virtual void </p>
<p id="p714626626093535"><a name="p714626626093535"></a><a name="p714626626093535"></a>Called when the FPS data changes. </p>
</td>
</tr>
<tr id="row1076500290093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p507105733093535"><a name="p507105733093535"></a><a name="p507105733093535"></a><a href="graphic.md#gaf7c8d9a4d44cee2001ad0cd40c827c47">GetFPSCalculateType</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p257649393093535"><a name="p257649393093535"></a><a name="p257649393093535"></a><a href="graphic.md#ga75d850e3abff6c2f617b689a0cb9a3d1">FPSCalculateType</a> </p>
<p id="p1582454546093535"><a name="p1582454546093535"></a><a name="p1582454546093535"></a>Obtains the FPS sampling type. </p>
</td>
</tr>
<tr id="row1870625374093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2085530641093535"><a name="p2085530641093535"></a><a name="p2085530641093535"></a><a href="graphic.md#ga5eb3d62fce38f8d2fcf2a0a4560a3640">SetFPSCalculateType</a> (<a href="graphic.md#ga75d850e3abff6c2f617b689a0cb9a3d1">FPSCalculateType</a> type)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1133508010093535"><a name="p1133508010093535"></a><a name="p1133508010093535"></a>void </p>
<p id="p209885880093535"><a name="p209885880093535"></a><a name="p209885880093535"></a>Sets the FPS sampling type. </p>
</td>
</tr>
<tr id="row1478581587093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p14682191093535"><a name="p14682191093535"></a><a name="p14682191093535"></a><a href="graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p775889343093535"><a name="p775889343093535"></a><a name="p775889343093535"></a>void * </p>
<p id="p484228765093535"><a name="p484228765093535"></a><a name="p484228765093535"></a>Overrides the <strong id="b1933010170093535"><a name="b1933010170093535"></a><a name="b1933010170093535"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row1905962254093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p250537572093535"><a name="p250537572093535"></a><a name="p250537572093535"></a><a href="graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p250579708093535"><a name="p250579708093535"></a><a name="p250579708093535"></a>void </p>
<p id="p550106398093535"><a name="p550106398093535"></a><a name="p550106398093535"></a>Overrides the <strong id="b30911395093535"><a name="b30911395093535"></a><a name="b30911395093535"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

