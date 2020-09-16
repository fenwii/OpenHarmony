# Development Guidelines on Photographing<a name="EN-US_TOPIC_0000001052170554"></a>

## When to Use<a name="section1963312376119"></a>

Use the camera module APIs to capture frames \(photographing\).

## Available APIs<a name="section56549532016"></a>

**Table  1**  APIs for photographing

<a name="table2069447114914"></a>
<table><thead align="left"><tr id="row4903852104914"><th class="cellrowborder" valign="top" width="18.811881188118814%" id="mcps1.2.4.1.1"><p id="p2903252174918"><a name="p2903252174918"></a><a name="p2903252174918"></a>Class</p>
</th>
<th class="cellrowborder" valign="top" width="46.534653465346544%" id="mcps1.2.4.1.2"><p id="p1595113912507"><a name="p1595113912507"></a><a name="p1595113912507"></a>Function</p>
</th>
<th class="cellrowborder" valign="top" width="34.65346534653466%" id="mcps1.2.4.1.3"><p id="p15951597508"><a name="p15951597508"></a><a name="p15951597508"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row492815717494"><td class="cellrowborder" valign="top" width="18.811881188118814%" headers="mcps1.2.4.1.1 "><p id="p1592812716495"><a name="p1592812716495"></a><a name="p1592812716495"></a>CameraKit</p>
</td>
<td class="cellrowborder" valign="top" width="46.534653465346544%" headers="mcps1.2.4.1.2 "><p id="p1492837144919"><a name="p1492837144919"></a><a name="p1492837144919"></a>int32_t GetCameraIds(std::list&lt;string&gt; cameraList)</p>
</td>
<td class="cellrowborder" valign="top" width="34.65346534653466%" headers="mcps1.2.4.1.3 "><p id="p2092807134919"><a name="p2092807134919"></a><a name="p2092807134919"></a>Obtains IDs of cameras that are currently available.</p>
</td>
</tr>
<tr id="row11928157114912"><td class="cellrowborder" valign="top" width="18.811881188118814%" headers="mcps1.2.4.1.1 "><p id="p139287774911"><a name="p139287774911"></a><a name="p139287774911"></a>CameraKit</p>
</td>
<td class="cellrowborder" valign="top" width="46.534653465346544%" headers="mcps1.2.4.1.2 "><p id="p9928107174915"><a name="p9928107174915"></a><a name="p9928107174915"></a>CameraAbility&amp; GetCameraAbility(string cameraId)</p>
</td>
<td class="cellrowborder" valign="top" width="34.65346534653466%" headers="mcps1.2.4.1.3 "><p id="p139281171494"><a name="p139281171494"></a><a name="p139281171494"></a>Obtains the camera capability</p>
</td>
</tr>
<tr id="row119282719496"><td class="cellrowborder" valign="top" width="18.811881188118814%" headers="mcps1.2.4.1.1 "><p id="p159288734914"><a name="p159288734914"></a><a name="p159288734914"></a>CameraKit</p>
</td>
<td class="cellrowborder" valign="top" width="46.534653465346544%" headers="mcps1.2.4.1.2 "><p id="p99280794913"><a name="p99280794913"></a><a name="p99280794913"></a>void RegisterCameraDeviceCallback(CameraDeviceCallback* callback, EventHandler* handler)</p>
</td>
<td class="cellrowborder" valign="top" width="34.65346534653466%" headers="mcps1.2.4.1.3 "><p id="p8928197134910"><a name="p8928197134910"></a><a name="p8928197134910"></a>Registers a camera callback for camera status changes.</p>
</td>
</tr>
<tr id="row4928673496"><td class="cellrowborder" valign="top" width="18.811881188118814%" headers="mcps1.2.4.1.1 "><p id="p14928770497"><a name="p14928770497"></a><a name="p14928770497"></a>CameraKit</p>
</td>
<td class="cellrowborder" valign="top" width="46.534653465346544%" headers="mcps1.2.4.1.2 "><p id="p14928197194915"><a name="p14928197194915"></a><a name="p14928197194915"></a>void UnregisterCameraDeviceCallback(CameraDeviceCallback* callback)</p>
</td>
<td class="cellrowborder" valign="top" width="34.65346534653466%" headers="mcps1.2.4.1.3 "><p id="p17929197134913"><a name="p17929197134913"></a><a name="p17929197134913"></a>Unregisters a camera callback.</p>
</td>
</tr>
<tr id="row16929187104912"><td class="cellrowborder" valign="top" width="18.811881188118814%" headers="mcps1.2.4.1.1 "><p id="p6929157184911"><a name="p6929157184911"></a><a name="p6929157184911"></a>CameraKit</p>
</td>
<td class="cellrowborder" valign="top" width="46.534653465346544%" headers="mcps1.2.4.1.2 "><p id="p1192910704914"><a name="p1192910704914"></a><a name="p1192910704914"></a>void CreateCamera(string cameraId, CameraStateCallback* callback, EventHandler* handler)</p>
</td>
<td class="cellrowborder" valign="top" width="34.65346534653466%" headers="mcps1.2.4.1.3 "><p id="p12929167154912"><a name="p12929167154912"></a><a name="p12929167154912"></a>Creates a <strong id="b1512582132318"><a name="b1512582132318"></a><a name="b1512582132318"></a>Camera</strong> instance.</p>
</td>
</tr>
<tr id="row592967184912"><td class="cellrowborder" valign="top" width="18.811881188118814%" headers="mcps1.2.4.1.1 "><p id="p9929127134915"><a name="p9929127134915"></a><a name="p9929127134915"></a>Camera</p>
</td>
<td class="cellrowborder" valign="top" width="46.534653465346544%" headers="mcps1.2.4.1.2 "><p id="p0929107204913"><a name="p0929107204913"></a><a name="p0929107204913"></a>string GetCameraId()</p>
</td>
<td class="cellrowborder" valign="top" width="34.65346534653466%" headers="mcps1.2.4.1.3 "><p id="p1592914710490"><a name="p1592914710490"></a><a name="p1592914710490"></a>Obtains the camera ID.</p>
</td>
</tr>
<tr id="row13929197104913"><td class="cellrowborder" valign="top" width="18.811881188118814%" headers="mcps1.2.4.1.1 "><p id="p16929167134913"><a name="p16929167134913"></a><a name="p16929167134913"></a>Camera</p>
</td>
<td class="cellrowborder" valign="top" width="46.534653465346544%" headers="mcps1.2.4.1.2 "><p id="p15929175491"><a name="p15929175491"></a><a name="p15929175491"></a>CameraConfig&amp; GetCameraConfig()</p>
</td>
<td class="cellrowborder" valign="top" width="34.65346534653466%" headers="mcps1.2.4.1.3 "><p id="p19298714917"><a name="p19298714917"></a><a name="p19298714917"></a>Obtains the camera configuration.</p>
</td>
</tr>
<tr id="row1892918764915"><td class="cellrowborder" valign="top" width="18.811881188118814%" headers="mcps1.2.4.1.1 "><p id="p69291072495"><a name="p69291072495"></a><a name="p69291072495"></a>Camera</p>
</td>
<td class="cellrowborder" valign="top" width="46.534653465346544%" headers="mcps1.2.4.1.2 "><p id="p5930172494"><a name="p5930172494"></a><a name="p5930172494"></a>FrameConfig&amp; GetFrameConfig(int32_t type)</p>
</td>
<td class="cellrowborder" valign="top" width="34.65346534653466%" headers="mcps1.2.4.1.3 "><p id="p19301176495"><a name="p19301176495"></a><a name="p19301176495"></a>Obtains the frame configuration.</p>
</td>
</tr>
<tr id="row893019794915"><td class="cellrowborder" valign="top" width="18.811881188118814%" headers="mcps1.2.4.1.1 "><p id="p893016714919"><a name="p893016714919"></a><a name="p893016714919"></a>Camera</p>
</td>
<td class="cellrowborder" valign="top" width="46.534653465346544%" headers="mcps1.2.4.1.2 "><p id="p1093067134915"><a name="p1093067134915"></a><a name="p1093067134915"></a>void Configure(CameraConfig&amp; config)</p>
</td>
<td class="cellrowborder" valign="top" width="34.65346534653466%" headers="mcps1.2.4.1.3 "><p id="p1493037114912"><a name="p1493037114912"></a><a name="p1493037114912"></a>Configures the camera using the <strong id="b1158653521815"><a name="b1158653521815"></a><a name="b1158653521815"></a>CameraConfig</strong> object.</p>
</td>
</tr>
<tr id="row11930197174917"><td class="cellrowborder" valign="top" width="18.811881188118814%" headers="mcps1.2.4.1.1 "><p id="p4930197184914"><a name="p4930197184914"></a><a name="p4930197184914"></a>Camera</p>
</td>
<td class="cellrowborder" valign="top" width="46.534653465346544%" headers="mcps1.2.4.1.2 "><p id="p19304717492"><a name="p19304717492"></a><a name="p19304717492"></a>void Release()</p>
</td>
<td class="cellrowborder" valign="top" width="34.65346534653466%" headers="mcps1.2.4.1.3 "><p id="p189301479494"><a name="p189301479494"></a><a name="p189301479494"></a>Releases the <strong id="b12391143101812"><a name="b12391143101812"></a><a name="b12391143101812"></a>Camera</strong> object and associated resources.</p>
</td>
</tr>
<tr id="row109304717499"><td class="cellrowborder" valign="top" width="18.811881188118814%" headers="mcps1.2.4.1.1 "><p id="p4930873496"><a name="p4930873496"></a><a name="p4930873496"></a>Camera</p>
</td>
<td class="cellrowborder" valign="top" width="46.534653465346544%" headers="mcps1.2.4.1.2 "><p id="p1893017720490"><a name="p1893017720490"></a><a name="p1893017720490"></a>int TriggerLoopingCapture(FrameConfig&amp; frameConfig)</p>
</td>
<td class="cellrowborder" valign="top" width="34.65346534653466%" headers="mcps1.2.4.1.3 "><p id="p149307754918"><a name="p149307754918"></a><a name="p149307754918"></a>Starts looping-frame capture.</p>
</td>
</tr>
<tr id="row19306794915"><td class="cellrowborder" valign="top" width="18.811881188118814%" headers="mcps1.2.4.1.1 "><p id="p6930167194910"><a name="p6930167194910"></a><a name="p6930167194910"></a>Camera</p>
</td>
<td class="cellrowborder" valign="top" width="46.534653465346544%" headers="mcps1.2.4.1.2 "><p id="p139311577499"><a name="p139311577499"></a><a name="p139311577499"></a>void StopLoopingCapture()</p>
</td>
<td class="cellrowborder" valign="top" width="34.65346534653466%" headers="mcps1.2.4.1.3 "><p id="p693115764914"><a name="p693115764914"></a><a name="p693115764914"></a>Stops looping-frame capture.</p>
</td>
</tr>
<tr id="row593116713492"><td class="cellrowborder" valign="top" width="18.811881188118814%" headers="mcps1.2.4.1.1 "><p id="p1193187174913"><a name="p1193187174913"></a><a name="p1193187174913"></a>Camera</p>
</td>
<td class="cellrowborder" valign="top" width="46.534653465346544%" headers="mcps1.2.4.1.2 "><p id="p1493111713496"><a name="p1493111713496"></a><a name="p1493111713496"></a>int32_t TriggerSingleCapture(FrameConfig&amp; frameConfig)</p>
</td>
<td class="cellrowborder" valign="top" width="34.65346534653466%" headers="mcps1.2.4.1.3 "><p id="p1193137104919"><a name="p1193137104919"></a><a name="p1193137104919"></a>Starts single-frame capture.</p>
</td>
</tr>
<tr id="row1693112711491"><td class="cellrowborder" valign="top" width="18.811881188118814%" headers="mcps1.2.4.1.1 "><p id="p89312716494"><a name="p89312716494"></a><a name="p89312716494"></a>CameraConfig</p>
</td>
<td class="cellrowborder" valign="top" width="46.534653465346544%" headers="mcps1.2.4.1.2 "><p id="p199312784912"><a name="p199312784912"></a><a name="p199312784912"></a>void SetFrameStateCallback(FrameStateCallback* callback, EventHandler* handler);</p>
</td>
<td class="cellrowborder" valign="top" width="34.65346534653466%" headers="mcps1.2.4.1.3 "><p id="p49312714495"><a name="p49312714495"></a><a name="p49312714495"></a>Sets a frame state callback to respond to state changes.</p>
</td>
</tr>
<tr id="row9931076492"><td class="cellrowborder" valign="top" width="18.811881188118814%" headers="mcps1.2.4.1.1 "><p id="p59317784917"><a name="p59317784917"></a><a name="p59317784917"></a>CameraConfig</p>
</td>
<td class="cellrowborder" valign="top" width="46.534653465346544%" headers="mcps1.2.4.1.2 "><p id="p17931197124912"><a name="p17931197124912"></a><a name="p17931197124912"></a>static CameraConfig* CreateCameraConfig()</p>
</td>
<td class="cellrowborder" valign="top" width="34.65346534653466%" headers="mcps1.2.4.1.3 "><p id="p5931177164912"><a name="p5931177164912"></a><a name="p5931177164912"></a>Creates a <strong id="b101608165182"><a name="b101608165182"></a><a name="b101608165182"></a>CameraConfig</strong> instance.</p>
</td>
</tr>
<tr id="row29321744917"><td class="cellrowborder" valign="top" width="18.811881188118814%" headers="mcps1.2.4.1.1 "><p id="p1093219716492"><a name="p1093219716492"></a><a name="p1093219716492"></a>CameraAbility</p>
</td>
<td class="cellrowborder" valign="top" width="46.534653465346544%" headers="mcps1.2.4.1.2 "><p id="p12932979493"><a name="p12932979493"></a><a name="p12932979493"></a>std::list&lt;Size&gt; GetSupportedSizes(int format)</p>
</td>
<td class="cellrowborder" valign="top" width="34.65346534653466%" headers="mcps1.2.4.1.3 "><p id="p1493210764918"><a name="p1493210764918"></a><a name="p1493210764918"></a>Obtains the supported image sizes for a specified image format.</p>
</td>
</tr>
<tr id="row1193267184910"><td class="cellrowborder" valign="top" width="18.811881188118814%" headers="mcps1.2.4.1.1 "><p id="p1393214717492"><a name="p1393214717492"></a><a name="p1393214717492"></a>CameraAbility</p>
</td>
<td class="cellrowborder" valign="top" width="46.534653465346544%" headers="mcps1.2.4.1.2 "><p id="p119321477495"><a name="p119321477495"></a><a name="p119321477495"></a>std::list&lt;T&gt; GetParameterRange(uint32_t key)</p>
</td>
<td class="cellrowborder" valign="top" width="34.65346534653466%" headers="mcps1.2.4.1.3 "><p id="p139331079491"><a name="p139331079491"></a><a name="p139331079491"></a>Obtains the parameter value range based on a specified parameter key.</p>
</td>
</tr>
<tr id="row0933197134920"><td class="cellrowborder" valign="top" width="18.811881188118814%" headers="mcps1.2.4.1.1 "><p id="p1493310764917"><a name="p1493310764917"></a><a name="p1493310764917"></a>CameraDevice</p>
</td>
<td class="cellrowborder" valign="top" width="46.534653465346544%" headers="mcps1.2.4.1.2 "><p id="p493313724915"><a name="p493313724915"></a><a name="p493313724915"></a>CameraDeviceCallback()</p>
</td>
<td class="cellrowborder" valign="top" width="34.65346534653466%" headers="mcps1.2.4.1.3 "><p id="p993416724915"><a name="p993416724915"></a><a name="p993416724915"></a>A constructor used to create a <strong id="b99481043111719"><a name="b99481043111719"></a><a name="b99481043111719"></a>CameraDeviceCallback</strong> instance.</p>
</td>
</tr>
<tr id="row093418712498"><td class="cellrowborder" valign="top" width="18.811881188118814%" headers="mcps1.2.4.1.1 "><p id="p159341779492"><a name="p159341779492"></a><a name="p159341779492"></a>CameraDevice</p>
</td>
<td class="cellrowborder" valign="top" width="46.534653465346544%" headers="mcps1.2.4.1.2 "><p id="p1493411774912"><a name="p1493411774912"></a><a name="p1493411774912"></a>void OnCameraStatus​(std::string cameraId, int32_t status)</p>
</td>
<td class="cellrowborder" valign="top" width="34.65346534653466%" headers="mcps1.2.4.1.3 "><p id="p1393419715491"><a name="p1393419715491"></a><a name="p1393419715491"></a>Called when the camera device status changes.</p>
</td>
</tr>
<tr id="row109348711497"><td class="cellrowborder" valign="top" width="18.811881188118814%" headers="mcps1.2.4.1.1 "><p id="p993419724914"><a name="p993419724914"></a><a name="p993419724914"></a>CameraStateCallback</p>
</td>
<td class="cellrowborder" valign="top" width="46.534653465346544%" headers="mcps1.2.4.1.2 "><p id="p993418720497"><a name="p993418720497"></a><a name="p993418720497"></a>CameraStateCallback​()</p>
</td>
<td class="cellrowborder" valign="top" width="34.65346534653466%" headers="mcps1.2.4.1.3 "><p id="p693511794919"><a name="p693511794919"></a><a name="p693511794919"></a>A constructor used to create a <strong id="b10634201491717"><a name="b10634201491717"></a><a name="b10634201491717"></a>CameraStateCallback</strong> instance.</p>
</td>
</tr>
<tr id="row159358717497"><td class="cellrowborder" valign="top" width="18.811881188118814%" headers="mcps1.2.4.1.1 "><p id="p1992012253527"><a name="p1992012253527"></a><a name="p1992012253527"></a>CameraStateCallback</p>
</td>
<td class="cellrowborder" valign="top" width="46.534653465346544%" headers="mcps1.2.4.1.2 "><p id="p29351077497"><a name="p29351077497"></a><a name="p29351077497"></a>void OnConfigured​(Camera&amp; camera)</p>
</td>
<td class="cellrowborder" valign="top" width="34.65346534653466%" headers="mcps1.2.4.1.3 "><p id="p093515774914"><a name="p093515774914"></a><a name="p093515774914"></a>Called when the camera is configured.</p>
</td>
</tr>
<tr id="row9935147184918"><td class="cellrowborder" valign="top" width="18.811881188118814%" headers="mcps1.2.4.1.1 "><p id="p117291328135211"><a name="p117291328135211"></a><a name="p117291328135211"></a>CameraStateCallback</p>
</td>
<td class="cellrowborder" valign="top" width="46.534653465346544%" headers="mcps1.2.4.1.2 "><p id="p19935174496"><a name="p19935174496"></a><a name="p19935174496"></a>void OnConfigureFailed​(Camera&amp; camera,int32_t errorCode)</p>
</td>
<td class="cellrowborder" valign="top" width="34.65346534653466%" headers="mcps1.2.4.1.3 "><p id="p159352077495"><a name="p159352077495"></a><a name="p159352077495"></a>Called when the camera fails to be configured.</p>
</td>
</tr>
<tr id="row1935279498"><td class="cellrowborder" valign="top" width="18.811881188118814%" headers="mcps1.2.4.1.1 "><p id="p1514619311525"><a name="p1514619311525"></a><a name="p1514619311525"></a>CameraStateCallback</p>
</td>
<td class="cellrowborder" valign="top" width="46.534653465346544%" headers="mcps1.2.4.1.2 "><p id="p493512744915"><a name="p493512744915"></a><a name="p493512744915"></a>void OnCreated​(Camera&amp; camera)</p>
</td>
<td class="cellrowborder" valign="top" width="34.65346534653466%" headers="mcps1.2.4.1.3 "><p id="p1493511784914"><a name="p1493511784914"></a><a name="p1493511784914"></a>Called when the camera is successfully created.</p>
</td>
</tr>
<tr id="row189351877493"><td class="cellrowborder" valign="top" width="18.811881188118814%" headers="mcps1.2.4.1.1 "><p id="p172071933175218"><a name="p172071933175218"></a><a name="p172071933175218"></a>CameraStateCallback</p>
</td>
<td class="cellrowborder" valign="top" width="46.534653465346544%" headers="mcps1.2.4.1.2 "><p id="p129361977498"><a name="p129361977498"></a><a name="p129361977498"></a>void OnCreateFailed​(std::string cameraId,int32_t errorCode)</p>
</td>
<td class="cellrowborder" valign="top" width="34.65346534653466%" headers="mcps1.2.4.1.3 "><p id="p2936197114919"><a name="p2936197114919"></a><a name="p2936197114919"></a>Called when the camera fails to be created.</p>
</td>
</tr>
<tr id="row20936472491"><td class="cellrowborder" valign="top" width="18.811881188118814%" headers="mcps1.2.4.1.1 "><p id="p61213391523"><a name="p61213391523"></a><a name="p61213391523"></a>CameraStateCallback</p>
</td>
<td class="cellrowborder" valign="top" width="46.534653465346544%" headers="mcps1.2.4.1.2 "><p id="p793697174919"><a name="p793697174919"></a><a name="p793697174919"></a>void OnReleased​(Camera&amp; camera)</p>
</td>
<td class="cellrowborder" valign="top" width="34.65346534653466%" headers="mcps1.2.4.1.3 "><p id="p49361719495"><a name="p49361719495"></a><a name="p49361719495"></a>Called when the camera is released.</p>
</td>
</tr>
<tr id="row159361179493"><td class="cellrowborder" valign="top" width="18.811881188118814%" headers="mcps1.2.4.1.1 "><p id="p10936147194918"><a name="p10936147194918"></a><a name="p10936147194918"></a>FrameStateCallback</p>
</td>
<td class="cellrowborder" valign="top" width="46.534653465346544%" headers="mcps1.2.4.1.2 "><p id="p9936279496"><a name="p9936279496"></a><a name="p9936279496"></a>FrameStateCallback​()</p>
</td>
<td class="cellrowborder" valign="top" width="34.65346534653466%" headers="mcps1.2.4.1.3 "><p id="p49367718499"><a name="p49367718499"></a><a name="p49367718499"></a>A constructor used to create a <strong id="b225612012172"><a name="b225612012172"></a><a name="b225612012172"></a>FrameStateCallback</strong> instance.</p>
</td>
</tr>
<tr id="row1893617744916"><td class="cellrowborder" valign="top" width="18.811881188118814%" headers="mcps1.2.4.1.1 "><p id="p136968511524"><a name="p136968511524"></a><a name="p136968511524"></a>FrameStateCallback</p>
</td>
<td class="cellrowborder" valign="top" width="46.534653465346544%" headers="mcps1.2.4.1.2 "><p id="p209379744911"><a name="p209379744911"></a><a name="p209379744911"></a>void OnFrameFinished(Camera&amp; camera, FrameConfig&amp; frameConfig, FrameResult&amp; frameResult)</p>
</td>
<td class="cellrowborder" valign="top" width="34.65346534653466%" headers="mcps1.2.4.1.3 "><p id="p19374724913"><a name="p19374724913"></a><a name="p19374724913"></a>Called when the frame capture is completed.</p>
</td>
</tr>
<tr id="row093719718495"><td class="cellrowborder" valign="top" width="18.811881188118814%" headers="mcps1.2.4.1.1 "><p id="p772975317527"><a name="p772975317527"></a><a name="p772975317527"></a>FrameStateCallback</p>
</td>
<td class="cellrowborder" valign="top" width="46.534653465346544%" headers="mcps1.2.4.1.2 "><p id="p189371471498"><a name="p189371471498"></a><a name="p189371471498"></a>void OnFrameError​(Camera&amp; camera, FrameConfig&amp; frameConfig, int32_t errorCode, FrameResult&amp; frameResult)</p>
</td>
<td class="cellrowborder" valign="top" width="34.65346534653466%" headers="mcps1.2.4.1.3 "><p id="p109371778497"><a name="p109371778497"></a><a name="p109371778497"></a>Called when the frame capture fails.</p>
</td>
</tr>
<tr id="row179381979499"><td class="cellrowborder" valign="top" width="18.811881188118814%" headers="mcps1.2.4.1.1 "><p id="p169381975499"><a name="p169381975499"></a><a name="p169381975499"></a>FrameConfig</p>
</td>
<td class="cellrowborder" valign="top" width="46.534653465346544%" headers="mcps1.2.4.1.2 "><p id="p1793867124910"><a name="p1793867124910"></a><a name="p1793867124910"></a>int32_t GetFrameConfigType()</p>
</td>
<td class="cellrowborder" valign="top" width="34.65346534653466%" headers="mcps1.2.4.1.3 "><p id="p1993817744915"><a name="p1993817744915"></a><a name="p1993817744915"></a>Obtains the frame configuration type.</p>
</td>
</tr>
<tr id="row793817784912"><td class="cellrowborder" valign="top" width="18.811881188118814%" headers="mcps1.2.4.1.1 "><p id="p69381724914"><a name="p69381724914"></a><a name="p69381724914"></a>FrameConfig</p>
</td>
<td class="cellrowborder" valign="top" width="46.534653465346544%" headers="mcps1.2.4.1.2 "><p id="p149382077496"><a name="p149382077496"></a><a name="p149382077496"></a>std::list&lt;OHOS::Surface&gt; GetSurfaces()</p>
</td>
<td class="cellrowborder" valign="top" width="34.65346534653466%" headers="mcps1.2.4.1.3 "><p id="p893867114919"><a name="p893867114919"></a><a name="p893867114919"></a>Obtains a list of surface objects (shared memories).</p>
</td>
</tr>
<tr id="row109401570498"><td class="cellrowborder" valign="top" width="18.811881188118814%" headers="mcps1.2.4.1.1 "><p id="p294019712492"><a name="p294019712492"></a><a name="p294019712492"></a>FrameConfig</p>
</td>
<td class="cellrowborder" valign="top" width="46.534653465346544%" headers="mcps1.2.4.1.2 "><p id="p19940170499"><a name="p19940170499"></a><a name="p19940170499"></a>void AddSurface(OHOS::AGP::UISurface&amp; surface);</p>
</td>
<td class="cellrowborder" valign="top" width="34.65346534653466%" headers="mcps1.2.4.1.3 "><p id="p11940197144915"><a name="p11940197144915"></a><a name="p11940197144915"></a>Adds a surface.</p>
</td>
</tr>
<tr id="row994018711492"><td class="cellrowborder" valign="top" width="18.811881188118814%" headers="mcps1.2.4.1.1 "><p id="p1094016718493"><a name="p1094016718493"></a><a name="p1094016718493"></a>FrameConfig</p>
</td>
<td class="cellrowborder" valign="top" width="46.534653465346544%" headers="mcps1.2.4.1.2 "><p id="p139411279498"><a name="p139411279498"></a><a name="p139411279498"></a>void RemoveSurface(OHOS::AGP::UISurface&amp; surface);</p>
</td>
<td class="cellrowborder" valign="top" width="34.65346534653466%" headers="mcps1.2.4.1.3 "><p id="p39415717494"><a name="p39415717494"></a><a name="p39415717494"></a>Removes a surface.</p>
</td>
</tr>
</tbody>
</table>

## Limitations and Constraints<a name="section1165911177314"></a>

None

## How to Develop<a name="section138543918214"></a>

1.  <a name="li378084192111"></a>Extend the  **CameraDeviceCallback**  class and call  **OnCameraStatus**  to customize operations when the camera device changes, for example, when a camera becomes available or unavailable.

    ```
    class SampleCameraDeviceCallback : public CameraDeviceCallback {
        void OnCameraStatus(std::string cameraId, int32_t status) override
        {
            // Do something when camera is available or unavailable.
        }
    };
    ```

2.  <a name="li8716104682913"></a>Extend the  **FrameStateCallback**  class. After obtaining the frame data, save the data as a file.

    ```
    static void SampleSaveCapture(const char *p, uint32_t size)
    {
        cout << "Start saving picture" << endl;
        struct timeval tv;
        gettimeofday(&tv, NULL);
        struct tm *ltm = localtime(&tv.tv_sec);
        if (ltm != nullptr) {
            ostringstream ss("Capture_");
            ss << "Capture" << ltm->tm_hour << "-" << ltm->tm_min << "-" << ltm->tm_sec << ".jpg";
    
            ofstream pic("/tmp/" + ss.str(), ofstream::out | ofstream::trunc);
            cout << "write " << size << " bytes" << endl;
            pic.write(p, size);
            cout << "Saving picture end" << endl;
        }
    }
    
    class TestFrameStateCallback : public FrameStateCallback {
        void OnFrameFinished(Camera &camera, FrameConfig &fc, FrameResult &result) override
        {
            cout << "Receive frame complete inform." << endl;
            if (fc.GetFrameConfigType() == FRAME_CONFIG_CAPTURE) {
                cout << "Capture frame received." << endl;
                list<Surface *> surfaceList = fc.GetSurfaces();
                for (Surface *surface : surfaceList) {
                    SurfaceBuffer *buffer = surface->AcquireBuffer();
                    if (buffer != nullptr) {
                        char *virtAddr = static_cast<char *>(buffer->GetVirAddr());
                        if (virtAddr != nullptr) {
                            SampleSaveCapture(virtAddr, buffer->GetSize());
                        }
                        surface->ReleaseBuffer(buffer);
                    }
                    delete surface;
                }
                delete &fc;
            }
        }
    };
    ```

3.  <a name="li6671035102514"></a>Extend the  **CameraStateCallback**  class and customize operations when the camera state changes \(configuration successful or failed, and creation successful or failed\).

    ```
    class SampleCameraStateMng : public CameraStateCallback {
    public:
        SampleCameraStateMng() = delete;
        SampleCameraStateMng(EventHandler &eventHdlr) : eventHdlr_(eventHdlr) {}
        ~SampleCameraStateMng()
        {
            if (recordFd_ != -1) {
                close(recordFd_);
            }
        }
        void OnCreated(Camera &c) override
        {
            cout << "Sample recv OnCreate camera." << endl;
            auto config = CameraConfig::CreateCameraConfig();
            config->SetFrameStateCallback(&fsCb_, &eventHdlr_);
            c.Configure(*config);
            cam_ = &c;
        }
        void OnCreateFailed(const std::string cameraId, int32_t errorCode) override {}
        void OnReleased(Camera &c) override {}
    };
    ```

4.  Create a  **CameraKit**  instance to set and obtain camera information.

    ```
    CameraKit *camKit = CameraKit::GetInstance();
    list<string> camList = camKit->GetCameraIds();
    string camId;
    for (auto &cam : camList) {
        cout << "camera name:" << cam << endl;
        const CameraAbility *ability = camKit->GetCameraAbility(cam);
        /* Find the camera that fits your ability. */
        list<CameraPicSize> sizeList = ability->GetSupportedSizes(0);
        if (find(sizeList.begin(), sizeList.end(), CAM_PIC_1080P) != sizeList.end()) {
            camId = cam;
            break;
        }
    }
    ```

5.  Create a  **Camera**  instance.

    ```
    EventHandler eventHdlr; // Create a thread to handle callback events.
    SampleCameraStateMng CamStateMng(eventHdlr);
    
    camKit->CreateCamera(camId, CamStateMng, eventHdlr);
    ```

6.  In the main process, synchronize configurations set by callback functions implemented in  [step 1](#li378084192111),  [step 2](#li8716104682913), and  [step 3](#li6671035102514).

    ```
    void OnCreated(Camera &c) override
    {
        cout << "Sample recv OnCreate camera." << endl;
        auto config = CameraConfig::CreateCameraConfig();
        config->SetFrameStateCallback(&fsCb_, &eventHdlr_);
        c.Configure(*config);
        cam_ = &c;
    }
    
    void Capture()
    {
        if (cam_ == nullptr) {
            cout << "Camera is not ready." << endl;
            return;
        }
        FrameConfig *fc = new FrameConfig(FRAME_CONFIG_CAPTURE);
        Surface *surface = Surface::CreateSurface();
        if (surface == nullptr) {
            delete fc;
        }
        surface->SetWidthAndHeight(1920, 1080); /* 1920:width,1080:height */
        fc->AddSurface(*surface);
        cam_->TriggerSingleCapture(*fc);
    }
    ```


