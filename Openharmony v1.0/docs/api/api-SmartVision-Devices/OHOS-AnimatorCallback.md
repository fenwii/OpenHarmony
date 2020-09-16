# OHOS::AnimatorCallback<a name="ZH-CN_TOPIC_0000001055678110"></a>

## **Overview**<a name="section438119024093532"></a>

**Related Modules:**

[Graphic](Graphic.md)

**Description:**

Represents the animator callback. 

You need to implement the callback function to produce specific animator effects.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section898056720093532"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table940507070093532"></a>
<table><thead align="left"><tr id="row1717127482093532"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p644460536093532"><a name="p644460536093532"></a><a name="p644460536093532"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p977272090093532"><a name="p977272090093532"></a><a name="p977272090093532"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row424244302093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p423762370093532"><a name="p423762370093532"></a><a name="p423762370093532"></a><a href="Graphic.md#gace3debcfa4200de1951a8eae6421e5aa">Callback</a> (<a href="OHOS-UIView.md">UIView</a> *view)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p43335681093532"><a name="p43335681093532"></a><a name="p43335681093532"></a>virtual void&nbsp;</p>
<p id="p168735969093532"><a name="p168735969093532"></a><a name="p168735969093532"></a>Called when each frame starts. This is a pure virtual function, which needs your inheritance and implementation. </p>
</td>
</tr>
<tr id="row139458647093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1410742062093532"><a name="p1410742062093532"></a><a name="p1410742062093532"></a><a href="Graphic.md#ga33875ecdc72e4d8076be696a35667a8f">OnStop</a> (<a href="OHOS-UIView.md">UIView</a> &amp;view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1216484739093532"><a name="p1216484739093532"></a><a name="p1216484739093532"></a>virtual void&nbsp;</p>
<p id="p1449821094093532"><a name="p1449821094093532"></a><a name="p1449821094093532"></a>Called when an animator stops. This is a pure virtual function, which needs your inheritance and implementation. </p>
</td>
</tr>
<tr id="row649992067093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p708032414093532"><a name="p708032414093532"></a><a name="p708032414093532"></a><a href="Graphic.md#ga783aca5777750141552a5aba974ffdff">~AnimatorCallback</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p800660226093532"><a name="p800660226093532"></a><a name="p800660226093532"></a>virtual&nbsp;</p>
<p id="p2015585517093532"><a name="p2015585517093532"></a><a name="p2015585517093532"></a>A default destructor used to delete an <strong id="b261444588093532"><a name="b261444588093532"></a><a name="b261444588093532"></a><a href="OHOS-AnimatorCallback.md">AnimatorCallback</a></strong> instance. </p>
</td>
</tr>
<tr id="row4847595093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1535484984093532"><a name="p1535484984093532"></a><a name="p1535484984093532"></a><a href="Graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1573370026093532"><a name="p1573370026093532"></a><a name="p1573370026093532"></a>void *&nbsp;</p>
<p id="p1850683016093532"><a name="p1850683016093532"></a><a name="p1850683016093532"></a>Overrides the <strong id="b815669746093532"><a name="b815669746093532"></a><a name="b815669746093532"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row1572524674093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1856087689093532"><a name="p1856087689093532"></a><a name="p1856087689093532"></a><a href="Graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p583454056093532"><a name="p583454056093532"></a><a name="p583454056093532"></a>void&nbsp;</p>
<p id="p1041453521093532"><a name="p1041453521093532"></a><a name="p1041453521093532"></a>Overrides the <strong id="b708717663093532"><a name="b708717663093532"></a><a name="b708717663093532"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

