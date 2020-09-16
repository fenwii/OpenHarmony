# Overview<a name="EN-US_TOPIC_0000001051452100"></a>

This document describes how to develop OpenHarmony bundles and distributions, and how to create, develop, and build code, as well as burn and debug devices by using a command line tool.

-   A bundle usually maps onto a code repository, which is a code archive with the  **bundle.json**,  **README**, and  **LICENSE**  files.
-   A distribution consists of multiple bundles. Each distribution integrates various bundles of a comprehensive system, such as the driver, kernel, framework, and applications. These bundles can be used for device burning.

**Table  1**  Differences between a bundle and a distribution

<a name="table6287133615412"></a>
<table><thead align="left"><tr id="row17288183614415"><th class="cellrowborder" valign="top" width="16.24162416241624%" id="mcps1.2.4.1.1"><p id="p528818361545"><a name="p528818361545"></a><a name="p528818361545"></a>Aspect</p>
</th>
<th class="cellrowborder" valign="top" width="33.31333133313331%" id="mcps1.2.4.1.2"><p id="p1288836247"><a name="p1288836247"></a><a name="p1288836247"></a>Bundle</p>
</th>
<th class="cellrowborder" valign="top" width="50.44504450445044%" id="mcps1.2.4.1.3"><p id="p112885362418"><a name="p112885362418"></a><a name="p112885362418"></a>Distribution</p>
</th>
</tr>
</thead>
<tbody><tr id="row1728813361848"><td class="cellrowborder" valign="top" width="16.24162416241624%" headers="mcps1.2.4.1.1 "><p id="p2010613564815"><a name="p2010613564815"></a><a name="p2010613564815"></a>Application scenario</p>
</td>
<td class="cellrowborder" valign="top" width="33.31333133313331%" headers="mcps1.2.4.1.2 "><p id="p1910555184818"><a name="p1910555184818"></a><a name="p1910555184818"></a>Feature-oriented</p>
</td>
<td class="cellrowborder" valign="top" width="50.44504450445044%" headers="mcps1.2.4.1.3 "><p id="p13871955484"><a name="p13871955484"></a><a name="p13871955484"></a>System-oriented</p>
</td>
</tr>
<tr id="row676745614472"><td class="cellrowborder" valign="top" width="16.24162416241624%" headers="mcps1.2.4.1.1 "><p id="p1028816365414"><a name="p1028816365414"></a><a name="p1028816365414"></a>Content</p>
</td>
<td class="cellrowborder" valign="top" width="33.31333133313331%" headers="mcps1.2.4.1.2 "><p id="p428812361042"><a name="p428812361042"></a><a name="p428812361042"></a>Codes or a binary library for implementing features</p>
</td>
<td class="cellrowborder" valign="top" width="50.44504450445044%" headers="mcps1.2.4.1.3 "><p id="p328817366417"><a name="p328817366417"></a><a name="p328817366417"></a>List of dependent bundles as well as their compiling and building scripts</p>
</td>
</tr>
<tr id="row95114356"><td class="cellrowborder" valign="top" width="16.24162416241624%" headers="mcps1.2.4.1.1 "><p id="p184894513517"><a name="p184894513517"></a><a name="p184894513517"></a>Integrity</p>
</td>
<td class="cellrowborder" valign="top" width="33.31333133313331%" headers="mcps1.2.4.1.2 "><p id="p1951741155"><a name="p1951741155"></a><a name="p1951741155"></a>A part of the operating system</p>
</td>
<td class="cellrowborder" valign="top" width="50.44504450445044%" headers="mcps1.2.4.1.3 "><p id="p20521542512"><a name="p20521542512"></a><a name="p20521542512"></a>An entire operating system</p>
</td>
</tr>
<tr id="row13581419518"><td class="cellrowborder" valign="top" width="16.24162416241624%" headers="mcps1.2.4.1.1 "><p id="p859171059"><a name="p859171059"></a><a name="p859171059"></a>Compilation result</p>
</td>
<td class="cellrowborder" valign="top" width="33.31333133313331%" headers="mcps1.2.4.1.2 "><p id="p259201355"><a name="p259201355"></a><a name="p259201355"></a>Bundles</p>
</td>
<td class="cellrowborder" valign="top" width="50.44504450445044%" headers="mcps1.2.4.1.3 "><p id="p459414519"><a name="p459414519"></a><a name="p459414519"></a>System image</p>
</td>
</tr>
</tbody>
</table>

**Figure  1**  Composition of bundles and distributions<a name="fig85033524124"></a>  


![](figures/en-us_image_0000001054663940.png)

