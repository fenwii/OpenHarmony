# OHOS<a name="ZH-CN_TOPIC_0000001054492904"></a>

## **Overview**<a name="section1756991423113035"></a>

**Related Modules:**

[AbilityKit](AbilityKit.md)  |  [Graphic](Graphic.md)  |  [MultiMedia\_AudioCapturer](MultiMedia_AudioCapturer.md)  |  [MultiMedia\_Camera](MultiMedia_Camera.md)  |  [MultiMedia\_CameraAbility](MultiMedia_CameraAbility.md)  |  [MultiMedia\_CameraConfig](MultiMedia_CameraConfig.md)  |  [MuiltiMedia\_CameraDeviceCallback](MuiltiMedia_CameraDeviceCallback.md)  |  [MultiMedia\_CameraKit](MultiMedia_CameraKit.md)  |  [MultiMedia\_CameraStateCallback](MultiMedia_CameraStateCallback.md)  |  [MultiMedia\_MediaCommon](MultiMedia_MediaCommon.md)  |  [MultiMedia\_FrameConfig](MultiMedia_FrameConfig.md)  |  [MultiMedia\_FrameStateCallback](MultiMedia_FrameStateCallback.md)  |  [Surface](Surface.md)  |  [MultiMedia\_Player](MultiMedia_Player.md)  |  [MultiMedia\_Recorder](MultiMedia_Recorder.md)  |  [Window](Window.md)

**Description:**

Declares functions in the  **CameraConfig**  class. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1555327383113035"></a>

## Data Structures<a name="nested-classes"></a>

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-Ability.md">Ability</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Declares ability-related functions, including ability lifecycle callbacks and functions for connecting to or disconnecting from AAs. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-AbilityContext.md">AbilityContext</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Provides functions for starting and stopping an ability. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-AbilityEventHandler.md">AbilityEventHandler</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Declares functions for performing operations during inter-thread communication, including running and quitting the event loop of the current thread and posting tasks to an asynchronous thread. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-AbilityLoader.md">AbilityLoader</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Declares functions for registering the class names of <a href="OHOS-Ability.md">Ability</a> and <a href="AbilitySlice.md">AbilitySlice</a> with the ability management framework. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="AbilitySlice.md">AbilitySlice</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Provides ability slice-related functions, including ability slice lifecycle callbacks and functions for connecting to or disconnecting from ability slices. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-AbstractAdapter.md">AbstractAdapter</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines the base class for adapters. You can derive <strong><a href="OHOS-AbstractAdapter.md">AbstractAdapter</a></strong> based on actual requirements and use the <strong><a href="Graphic.md#gab155b2f4a6d8fd97755dcd1e6d3d8361">GetView()</a></strong> and <strong><a href="Graphic.md#ga67021b360d4097c475d5e24519b5276d">GetCount()</a></strong> functions to implement adapters of different data types. For details, see <a href="TextAdapter.md">TextAdapter</a>. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-Animator.md">Animator</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Represents an animator. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-AnimatorCallback.md">AnimatorCallback</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Represents the animator callback. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-AnimatorManager.md">AnimatorManager</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Represents the animator manager. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-BinHeader.md">BinHeader</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>struct <a href="OHOS-BinHeader.md">BinHeader</a> for font refer to ui_font.h </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-ButtonStyle.md">ButtonStyle</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Stores styles of a button in its different states. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-CancelEvent.md">CancelEvent</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines a cancel event, which usually occurs when the target view changes due to user sliding. For example, this event is triggered if you, after pressing a button, does not release the button but slides. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-ClickEvent.md">ClickEvent</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines a click event, which indicates that a finger is pressed on the screen and then lifted within 1 second. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-Color.md">Color</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Converts colors in different formats and defines common colors. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-Color16.md">Color16</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines the color attribute when the color depth is <strong>16</strong>. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-Color24.md">Color24</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines the color attribute when the color depth is <strong>24</strong>. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-Color32.md">Color32</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines the color attribute when the color depth is <strong>32</strong>. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-DragEvent.md">DragEvent</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines a drag event, which indicates a certain movement (more than 10 pixels) after a view is pressed. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-EasingEquation.md">EasingEquation</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines functions for specifying the velocity of an animation. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-Event.md">Event</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines the base class of a user input event and provides functions to record information such as the event position and timestamp. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-FlexLayout.md">FlexLayout</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines a flexible layout container. You can perform simple adaptive layout on child views that the container holds, for example, to evenly arrange all child views in the same row or column. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-FontHeader.md">FontHeader</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>struct <a href="OHOS-FontHeader.md">FontHeader</a> refer to ui_font.h </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-GlyphHeader.md">GlyphHeader</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>struct <a href="OHOS-GlyphHeader.md">GlyphHeader</a> for font, font tool using, not for bin file refer to ui_font.h </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-GlyphNode.md">GlyphNode</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>struct <a href="OHOS-GlyphNode.md">GlyphNode</a> for font refer to ui_font.h </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-GridLayout.md">GridLayout</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines a grid layout container. You can perform simple grid layout on child views that the container holds. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-IBufferConsumerListener.md">IBufferConsumerListener</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines the consumer listener used to notify consumers when the surface status is updated. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-Image.md">Image</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Represents basic image attributes, including the image type and path. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-ImageAnimatorInfo.md">ImageAnimatorInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Provides information about the images. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-ImageHeader.md">ImageHeader</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines image head node information. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-ImageInfo.md">ImageInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines image information. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-Interpolation.md">Interpolation</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Calculates the Bezier interpolation. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-KernNode.md">KernNode</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>struct <a href="OHOS-KernNode.md">KernNode</a> for kerning of font refer to ui_font.h </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-KeyEvent.md">KeyEvent</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines a key event, which indicates that a physical button is pressed or released. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-LangBinHeader.md">LangBinHeader</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>struct <a href="OHOS-LangBinHeader.md">LangBinHeader</a> for font refer to ui_font.h </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-LangFontBinHeader.md">LangFontBinHeader</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>struct <a href="OHOS-LangFontBinHeader.md">LangFontBinHeader</a> for font refer to ui_font.h </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-LangTexsTableHeader.md">LangTexsTableHeader</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>struct <a href="OHOS-LangTexsTableHeader.md">LangTexsTableHeader</a> for font refer to ui_font.h </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-LangTexsUtf8Param.md">LangTexsUtf8Param</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>struct <a href="OHOS-LangTexsUtf8Param.md">LangTexsUtf8Param</a> for font refer to ui_font.h </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-Layout.md">Layout</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines the base class of the layout, which indicates the basic data types and operations that may be used in the layout. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-Line.md">Line</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines a line, which consists of the start and end points. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-List-T.md">List</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines a linked list template class, which implements the data structure of bidirectional linked list and provides basic functions such as adding, deleting, inserting, clearing, popping up, and obtaining the size of the linked list. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-ListNode-T.md">ListNode</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Stores linked list data and contains pointers to the previous node and the next node. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-ListScrollListener.md">ListScrollListener</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Represents a listener that contains a callback to be invoked when the scroll state changes or when a new child view is selected at the preset position as this list scrolls. The scroll state can be <strong>SCROLL_STATE_STOP</strong> or <strong>SCROLL_STATE_MOVE</strong>. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-LongPressEvent.md">LongPressEvent</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines a long-press event, which indicates that the finger is not raised or moved within 1 second after a view is pressed. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-Matrix3-T.md">Matrix3</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines a 3 x 3 matrix. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-Paint.md">Paint</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines the basic styles of graphs drawn on canvases. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-Point.md">Point</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines a point. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-Polygon.md">Polygon</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines a polygon, including vertex coordinates and the maximum number of vertices (defined by <a href="Graphic.md#gafff78acb69e2b147b6f33d68e570ef54">MAX_VERTEX_NUM</a>). </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-PressEvent.md">PressEvent</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines a touch event, which indicates that the touchscreen or mouse is pressed. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-RawEvent.md">RawEvent</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>struct of raw event </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Rect.md">Rect</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines a rectangle, including the position data of the four boundaries of the rectangle, and provides functions for rectangle inclusion, intersection, and aggregation. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-ReleaseEvent.md">ReleaseEvent</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines a release event, which indicates that the touchscreen or mouse is released. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="RootView.md">RootView</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines the functions related to a root view which contains its child views and represents the root node in a tree structure. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-StyleDefault.md">StyleDefault</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Define some default style for <a href="OHOS-UIView.md">UIView</a>. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-Surface.md">Surface</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines the consumer listener used to notify consumers when the surface status is updated. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-SurfaceBuffer.md">SurfaceBuffer</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Provides functions such as setting the virtual address, size, and additional attributes of shared memory. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-SysInfo.md">SysInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Obtains the system information. Currently, the FPS information can be obtained. To enable the FPS feature, enable the <strong>ENABLE_FPS_SUPPORT</strong> macro. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-Text.md">Text</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Represents the base class of <strong><a href="OHOS-Text.md">Text</a></strong>, providing the text attribute setting and text drawing capabilities for components that require font display. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="TextAdapter.md">TextAdapter</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines a text adapter, which implements <a href="UILabel.md">UILabel</a> instance construction and supports text data and continuous integer data. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-TextFormatter.md">TextFormatter</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines a text formatter. You can inherit this class and implement the <strong><a href="Graphic.md#ga183cac282667493fa2a008f9a7f4f9d2">Format()</a></strong> function. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-ThemeManager.md">ThemeManager</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Declares the singleton class used to manage the current screen theme of an application. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-TransformMap.md">TransformMap</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Transforms a rectangle, including rotation and scaling. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-TtfHeader.md">TtfHeader</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>struct <a href="OHOS-TtfHeader.md">TtfHeader</a> for header of ttftab.bin refer to ui_font.h </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-UIAbstractClock.md">UIAbstractClock</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>An abstract class that contains functions for converting units of time (hour, minute, and second), setting and obtaining the time. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-UIAbstractProgress.md">UIAbstractProgress</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Represents the abstract base class which provides functions related to the progress bar. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-UIAbstractScroll.md">UIAbstractScroll</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines the attributes of a scroll, including the scroll direction, blank size of a scroll view, velocity and effects of a scroll animation. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-UIAnalogClock.md">UIAnalogClock</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Provides the functions related to an analog clock. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-UIArcLabel.md">UIArcLabel</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines functions related to an arc label. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-UIAxis.md">UIAxis</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Represents the coordinate axis base class, which defines the basic attributes of coordinate axis, sets whether a coordinate axis is visible, and sets the number of scales on a coordinate axis. This class is used in <a href="UIChart.md">UIChart</a>. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-UIBoxProgress.md">UIBoxProgress</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Represents a linear progress bar. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-UIButton.md">UIButton</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Represents a button. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-UICanvas.md">UICanvas</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines a canvas, which is used to draw multiple types of 2D graphs. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="UIChart.md">UIChart</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines the chart class and provides functions such as adding and deleting data sets to display a chart. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-UIChartDataSerial.md">UIChartDataSerial</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines a data set and provides functions such as adding and deleting data points. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-UIChartPillar.md">UIChartPillar</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Provides special functions for implementing a bar chart. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-UIChartPolyline.md">UIChartPolyline</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Provides special functions for implementing a polyline. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-UICheckBox.md">UICheckBox</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Represents a check box. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-UICircleProgress.md">UICircleProgress</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Represents a circular progress bar. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-UIDialog.md">UIDialog</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Represents a dialog box. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-UIDigitalClock.md">UIDigitalClock</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Displays time digitally. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-UIDumpDomTree.md">UIDumpDomTree</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Provides functions for exporting information about a specified DOM node or information about the DOM tree starting from a specified DOM node. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-UIImageAnimatorView.md">UIImageAnimatorView</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Represents an image animator. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-UIImageView.md">UIImageView</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines the functions related to an image view. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="UILabel.md">UILabel</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines the functions for presenting a label in a specified area, setting the style and background color of a label, and setting the display mode of a long label text. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-UILabelButton.md">UILabelButton</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Provides the functions related to a label button. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-UIList.md">UIList</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Represents a scrollable list which is used with the adapter <a href="OHOS-AbstractAdapter.md">AbstractAdapter</a> to implement scrolling, inertial scrolling, automatic alignment, and invoking of a callback when a child view is selected at the preset position as this list scrolls. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-UIPicker.md">UIPicker</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines a picker. Multiple texts or numbers can be put into a sliding list for selection. The selected text or numbers are highlighted. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-UIRadioButton.md">UIRadioButton</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Represents a radio button. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-UIRepeatButton.md">UIRepeatButton</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Represents a repeat button. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-UIScrollView.md">UIScrollView</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Supports horizontal or vertical scroll of child views. This class is inherited from <a href="OHOS-UIAbstractScroll.md">UIAbstractScroll</a>. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-UISlider.md">UISlider</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Represents a slider. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-UISnapShot.md">UISnapShot</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Represents the <strong><a href="OHOS-UISnapShot.md">UISnapShot</a></strong> class. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-UISwipeView.md">UISwipeView</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Represents a swipe view. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-UITextureMapper.md">UITextureMapper</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Rotates and scales images. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-UITimePicker.md">UITimePicker</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines the time picker. The time is in the format of "hour:minute" or "hour:minute:second". The selected time is highlighted. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-UIToggleButton.md">UIToggleButton</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Represents a toggle button. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-UIView.md">UIView</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines the base class of a view, providing basic view attributes and operations. All views are derived from this class. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-UIViewGroup.md">UIViewGroup</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Represents a view group that consists of its child views. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-UIXAxis.md">UIXAxis</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines the unique attributes and functions for the x-axis. This class is used in <a href="UIChart.md">UIChart</a>. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-UIYAxis.md">UIYAxis</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines the unique attributes and functions for the y-axis. This class is used in <a href="UIChart.md">UIChart</a>. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-Vector2-T.md">Vector2</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines the two-dimensional vector, and provides basic mathematical operations such as vector assignment, scalar product, cross product, addition, and subtraction. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-Vector3-T.md">Vector3</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines the 3-dimensional vector, and provides basic operators such as [] and ==. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-VirtualDeviceEvent.md">VirtualDeviceEvent</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines a virtual device event, which is used to receive a customized input event and call back the listening function registered. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-Window.md">Window</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Provides a drawing canvas for the <strong><a href="RootView.md">RootView</a></strong>, which represents the root node of a view tree. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS-WindowConfig.md">WindowConfig</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Sets the attributes for this window. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Graphic.md#gaf04c41bb7b151a6e8be2012cc9e6475b">EasingFunc</a>) (int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>typedef int16_t(*&nbsp;</p>
<p>Calculates the value for the current time of an animation. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p>{ <a href="Graphic.md#ggab33bf9b3f667764c47dc1a69326424f1ad4bd10bef3f1df05fd29e023050b9cca">OPA_TRANSPARENT</a> = 0, <a href="Graphic.md#ggab33bf9b3f667764c47dc1a69326424f1aebcfc69c18e2c29c89f800d95f32754f">OPA_OPAQUE</a> = 255 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Enumerates opacity values. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Graphic.md#ga3f99b58f731a37cacde72d5e0c934593">UITextLanguageAlignment</a> : uint8_t { &nbsp;&nbsp;<a href="Graphic.md#gga3f99b58f731a37cacde72d5e0c934593a37453e521c390e6157ac2efff1197a43">TEXT_ALIGNMENT_LEFT</a> = 0, <a href="Graphic.md#gga3f99b58f731a37cacde72d5e0c934593af6fdcea7d95056a0bab016ba7bee66bd">TEXT_ALIGNMENT_RIGHT</a>, <a href="Graphic.md#gga3f99b58f731a37cacde72d5e0c934593a1dd445f9b6987a84a7022885ea13c81c">TEXT_ALIGNMENT_CENTER</a>, <a href="Graphic.md#gga3f99b58f731a37cacde72d5e0c934593a33dfd4e235bcc2f6f42f4efc8c8264a2">TEXT_ALIGNMENT_TOP</a>, &nbsp;&nbsp;<a href="Graphic.md#gga3f99b58f731a37cacde72d5e0c934593aa7798629aa2199c86cb668e94115186c">TEXT_ALIGNMENT_BOTTOM</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Enumerates text alignment modes. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Graphic.md#ga0c108f97781843f67c101b47b6c00cf0">UITextLanguageDirect</a> : uint8_t { <a href="Graphic.md#gga0c108f97781843f67c101b47b6c00cf0a387cedfce95a736f28a1c2748086b1a9">TEXT_DIRECT_LTR</a> = 0, <a href="Graphic.md#gga0c108f97781843f67c101b47b6c00cf0a76658b82f45d4136910ded0c22afe7f8">TEXT_DIRECT_RTL</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Enumerates text directions. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Graphic.md#ga3a3fb04ed2cda4017e6771c66b692141">ColorMode</a> : uint8_t { &nbsp;&nbsp;<a href="Graphic.md#gga3a3fb04ed2cda4017e6771c66b692141a2f9573d43aecf2449480f8574b907683">ARGB8888</a> = 0, <a href="Graphic.md#gga3a3fb04ed2cda4017e6771c66b692141a5a962b82aadba3263c4f0de98262e30e">RGB888</a>, <a href="Graphic.md#gga3a3fb04ed2cda4017e6771c66b692141aecb2d8fad7e9b4cfcf53e5490c80651f">RGB565</a>, <a href="Graphic.md#gga3a3fb04ed2cda4017e6771c66b692141add58b331447c6b0e8963fc0f21b78033">ARGB1555</a>, &nbsp;&nbsp;<a href="Graphic.md#gga3a3fb04ed2cda4017e6771c66b692141a21266607b0e5987609d37b52e63f5277">ARGB4444</a>, <a href="Graphic.md#gga3a3fb04ed2cda4017e6771c66b692141a6fbe6b11f436174cc18a931ae9fb85d3">AL44</a>, <a href="Graphic.md#gga3a3fb04ed2cda4017e6771c66b692141a7cc06e38b82b0bda251bfc8f0fc953b6">AL88</a>, <a href="Graphic.md#gga3a3fb04ed2cda4017e6771c66b692141a734f6e329eed35e1fe3f2f6d753665ac">L1</a>, &nbsp;&nbsp;<a href="Graphic.md#gga3a3fb04ed2cda4017e6771c66b692141abe9263055f6c06124c0c8b513e1d87df">L2</a>, <a href="Graphic.md#gga3a3fb04ed2cda4017e6771c66b692141a493a9a5cd759369b982ad7e6ac0de13f">L4</a>, <a href="Graphic.md#gga3a3fb04ed2cda4017e6771c66b692141a8417494b1a72ed840b16752f32e7554c">L8</a>, <a href="Graphic.md#gga3a3fb04ed2cda4017e6771c66b692141a106ce1ddec51f2cb302686252d3c9560">A1</a>, &nbsp;&nbsp;<a href="Graphic.md#gga3a3fb04ed2cda4017e6771c66b692141a365d0df177aa6e1b73fe0cddf72e88c7">A2</a>, <a href="Graphic.md#gga3a3fb04ed2cda4017e6771c66b692141ae49cb0538532ad895017e6f0d236d9da">A4</a>, <a href="Graphic.md#gga3a3fb04ed2cda4017e6771c66b692141a3b6524df7a87ae2800f8ac5b7417d5bc">A8</a>, <a href="Graphic.md#gga3a3fb04ed2cda4017e6771c66b692141a892afdfffaf015240b16b563599b0244">UNKNOW</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>colormode of image and font. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS.md#ac4e2abaf935793b876fbe5905d560e92">InputDevType</a> { , &nbsp;&nbsp;<a href="OHOS.md#ac4e2abaf935793b876fbe5905d560e92a15a665fc432ea0808773802b796861c7">InputDevType::INDEV_TYPE_KEY</a>, <a href="OHOS.md#ac4e2abaf935793b876fbe5905d560e92a6e03d0fde54ba9c1b339984a8729070f">InputDevType::INDEV_TYPE_KEYBOARD</a>, <a href="OHOS.md#ac4e2abaf935793b876fbe5905d560e92ae8d50d9f58cc3bd0dd327192a0ac0b7d">InputDevType::INDEV_TYPE_MOUSE</a>, <a href="OHOS.md#ac4e2abaf935793b876fbe5905d560e92a9eea2481807e5f4a6e7fefa8f1575c79">InputDevType::INDEV_TYPE_BUTTON</a>, &nbsp;&nbsp;<a href="OHOS.md#ac4e2abaf935793b876fbe5905d560e92a4f8759aa8d44ef162a7bed84a4099da5">InputDevType::INDEV_TYPE_CROWN</a>, <a href="OHOS.md#ac4e2abaf935793b876fbe5905d560e92a5f2c187e15e6b416e5edd138c54282ea">InputDevType::INDEV_TYPE_ENCODER</a>, <a href="OHOS.md#ac4e2abaf935793b876fbe5905d560e92a3f0daa63c46624034a1b5f315c89317d">InputDevType::INDEV_TYPE_UNKNOWN</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">&nbsp;</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p>: uint8_t { &nbsp;&nbsp;<a href="Graphic.md#ggaa79136fc449e3dbd54564d59d948e0c0a81f161546d7e1853d1c273e3810fe08b">STYLE_BACKGROUND_COLOR</a>, <a href="Graphic.md#ggaa79136fc449e3dbd54564d59d948e0c0a639cb87312225b97bde6e4d2be950b7f">STYLE_BACKGROUND_OPA</a>, <a href="Graphic.md#ggaa79136fc449e3dbd54564d59d948e0c0a4e61810ea3d5f385908eb8a4139027a5">STYLE_BORDER_RADIUS</a>, <a href="Graphic.md#ggaa79136fc449e3dbd54564d59d948e0c0a8fc5a572665a64ad6d27f70480de3b9a">STYLE_BORDER_COLOR</a>, &nbsp;&nbsp;<a href="Graphic.md#ggaa79136fc449e3dbd54564d59d948e0c0a13df567903c15b369bf612bd97a9b886">STYLE_BORDER_OPA</a>, <a href="Graphic.md#ggaa79136fc449e3dbd54564d59d948e0c0ae9bd454f8703c13e8385668b3ac19e41">STYLE_BORDER_WIDTH</a>, <a href="Graphic.md#ggaa79136fc449e3dbd54564d59d948e0c0a3231d33e8bb12cd0cf6911076c877892">STYLE_PADDING_LEFT</a>, <a href="Graphic.md#ggaa79136fc449e3dbd54564d59d948e0c0a8cc34b7c9774ce7dc940b7deeb64de1f">STYLE_PADDING_RIGHT</a>, &nbsp;&nbsp;<a href="Graphic.md#ggaa79136fc449e3dbd54564d59d948e0c0a5225ed05b95d4a95a2c48250518c7c7f">STYLE_PADDING_TOP</a>, <a href="Graphic.md#ggaa79136fc449e3dbd54564d59d948e0c0a65e4dd92a76dc374b487cd24fa37199b">STYLE_PADDING_BOTTOM</a>, <a href="Graphic.md#ggaa79136fc449e3dbd54564d59d948e0c0a251e2a6ea777b9b6af8f6ccf79d060cc">STYLE_MARGIN_LEFT</a>, <a href="Graphic.md#ggaa79136fc449e3dbd54564d59d948e0c0a59ab9a49b6fe3f1fd42a79bf70398c70">STYLE_MARGIN_RIGHT</a>, &nbsp;&nbsp;<a href="Graphic.md#ggaa79136fc449e3dbd54564d59d948e0c0ad5dbc07ebf86daf81e30fcbf9051c3b6">STYLE_MARGIN_TOP</a>, <a href="Graphic.md#ggaa79136fc449e3dbd54564d59d948e0c0a05fa788c60b80429efd0e42fc5d3d4af">STYLE_MARGIN_BOTTOM</a>, <a href="Graphic.md#ggaa79136fc449e3dbd54564d59d948e0c0ae63c7c001e11994f2ec952559c3a0d5f">STYLE_IMAGE_OPA</a>, <a href="Graphic.md#ggaa79136fc449e3dbd54564d59d948e0c0a21142f37831ece4dc6fe12a3474029a5">STYLE_TEXT_COLOR</a>, &nbsp;&nbsp;<a href="Graphic.md#ggaa79136fc449e3dbd54564d59d948e0c0a7288938187d2b5c74d0d1789d73784a3">STYLE_TEXT_FONT</a>, <a href="Graphic.md#ggaa79136fc449e3dbd54564d59d948e0c0af705c0b077d93c8e5ee3cb4583c8ea87">STYLE_LETTER_SPACE</a>, <a href="Graphic.md#ggaa79136fc449e3dbd54564d59d948e0c0a06ab7c8b467da98902fe19f2b21595ba">STYLE_LINE_SPACE</a>, <a href="Graphic.md#ggaa79136fc449e3dbd54564d59d948e0c0a8889542f8ea0fc454895c6e245d9cfdf">STYLE_TEXT_OPA</a>, &nbsp;&nbsp;<a href="Graphic.md#ggaa79136fc449e3dbd54564d59d948e0c0a59ce09cf70ef205a7ff081f10d6c1380">STYLE_LINE_COLOR</a>, <a href="Graphic.md#ggaa79136fc449e3dbd54564d59d948e0c0adb7984bac1deeffafc3f04169480937e">STYLE_LINE_WIDTH</a>, <a href="Graphic.md#ggaa79136fc449e3dbd54564d59d948e0c0a7aa7e8dfa8b88cc3ef77c4c3b23a5ea2">STYLE_LINE_OPA</a>, <a href="Graphic.md#ggaa79136fc449e3dbd54564d59d948e0c0a420aa5184ddfd2e95632095c92dfbee5">STYLE_LINE_CAP</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Enumerates keys of styles. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Surface.md#ga16d4d4f73d748455e45924ffbdd1e891">BufferConsumerUsage</a> { &nbsp;&nbsp;<a href="Surface.md#gga16d4d4f73d748455e45924ffbdd1e891a59c0ac95bd7994b6eda43b34f59c237b">BUFFER_CONSUMER_USAGE_SORTWARE</a> = 0, <a href="Surface.md#gga16d4d4f73d748455e45924ffbdd1e891abe0bc63ca1799ca0b2182e908780da7b">BUFFER_CONSUMER_USAGE_HARDWARE</a>, <a href="Surface.md#gga16d4d4f73d748455e45924ffbdd1e891a93eebf8af6f264494a57771865c90b08">BUFFER_CONSUMER_USAGE_HARDWARE_CONSUMER_CACHE</a>, <a href="Surface.md#gga16d4d4f73d748455e45924ffbdd1e891a7a31f6403b7aa4ba989e7cd5b3eb7a06">BUFFER_CONSUMER_USAGE_HARDWARE_PRODUCER_CACHE</a>, &nbsp;&nbsp;<a href="Surface.md#gga16d4d4f73d748455e45924ffbdd1e891a56aa1994f77d06504c40421f6555f1cf">BUFFER_CONSUMER_USAGE_MAX</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Enumerates shared memory usage scenarios, including physically contiguous memory and virtual memory. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Surface.md#gaa191d6e3b92a0f527744d43e056ae025">ImagePixelFormat</a> { &nbsp;&nbsp;<a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025a9690a1d8cf1d21fcad76876f122a12ab">IMAGE_PIXEL_FORMAT_NONE</a> = 0, <a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025aff11848c6a38afb3afdcbeaec2400055">IMAGE_PIXEL_FORMAT_RGB565</a> = 101, <a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025a9cf3bfb5153d8cf23f4c0d3bb9cc4f43">IMAGE_PIXEL_FORMAT_ARGB1555</a>, <a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025ad4774f5ba15cf25a3d0951f5986ab0d5">IMAGE_PIXEL_FORMAT_RGB888</a>, &nbsp;&nbsp;<a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025a1a18541878a09cbca269918a7ef4796f">IMAGE_PIXEL_FORMAT_ARGB8888</a>, <a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025affcb2a4b4832e3c33789f9e8efffe7b0">IMAGE_PIXEL_FORMAT_YUYV</a> = 201, <a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025a4ec5bc985a5f49f26178ab18c074cfa6">IMAGE_PIXEL_FORMAT_YVYU</a>, <a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025a098b93504ac8e11c4d5d488930187f37">IMAGE_PIXEL_FORMAT_UYVY</a>, &nbsp;&nbsp;<a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025a0e242cad6dae11690013c6771b80fc9b">IMAGE_PIXEL_FORMAT_VYUY</a>, <a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025ab690ca190de1686041f0d0c320427b1c">IMAGE_PIXEL_FORMAT_AYUV</a>, <a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025aa4e3c6974a86c29cf707f371ad1b0b49">IMAGE_PIXEL_FORMAT_YUV410</a>, <a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025a3c4c9612392a81fa2d1d305d08064146">IMAGE_PIXEL_FORMAT_YVU410</a>, &nbsp;&nbsp;<a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025acc77b028562f155f1099de249b7bffae">IMAGE_PIXEL_FORMAT_YUV411</a>, <a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025a99cb00970d669d9ba2ac1049d19c60e4">IMAGE_PIXEL_FORMAT_YVU411</a>, <a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025acf60892315d8aee3d421f75d70db796f">IMAGE_PIXEL_FORMAT_YUV420</a>, <a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025ac3dfd6c2f350194d2a525a14d9e72b71">IMAGE_PIXEL_FORMAT_YVU420</a>, &nbsp;&nbsp;<a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025ae87be6ce296c907d99381d1db48c288f">IMAGE_PIXEL_FORMAT_YUV422</a>, <a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025ab33d1df10479e267ca7c3cb6102d8dbb">IMAGE_PIXEL_FORMAT_YVU422</a>, <a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025a7f2a90344e786071a49db0da82b201e4">IMAGE_PIXEL_FORMAT_YUV444</a>, <a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025a4e18880bae5fa08cbd510f23f549087d">IMAGE_PIXEL_FORMAT_YVU444</a>, &nbsp;&nbsp;<a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025a93a54b97b83f6e042c993d045be27a33">IMAGE_PIXEL_FORMAT_NV12</a> = 301, <a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025ab7d0f6b75189a47fdf613bbbeaa3b628">IMAGE_PIXEL_FORMAT_NV21</a>, <a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025a5fd084cc32d1fdbe8017fd210a7e3ffa">IMAGE_PIXEL_FORMAT_NV16</a>, <a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025a77a0063a555db3ca68a304e494f094cf">IMAGE_PIXEL_FORMAT_NV61</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Enumerates a pixel format. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Window.md#gade9f6a70c1e8547785d266aab3ca5725">WindowPixelFormat</a> { <a href="Window.md#ggade9f6a70c1e8547785d266aab3ca5725a23fea82a04292ba974dad96468ae610c">WINDOW_PIXEL_FORMAT_RGB565</a> = 101, <a href="Window.md#ggade9f6a70c1e8547785d266aab3ca5725a4f397aa8d8480b22b8a65594e09fbc9a">WINDOW_PIXEL_FORMAT_ARGB1555</a>, <a href="Window.md#ggade9f6a70c1e8547785d266aab3ca5725a083e4a4abba5810d7bedb8a65bea23f1">WINDOW_PIXEL_FORMAT_RGB888</a>, <a href="Window.md#ggade9f6a70c1e8547785d266aab3ca5725a94212b4cc96d2cb46cec7de114437d26">WINDOW_PIXEL_FORMAT_ARGB8888</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Enumerates the pixel formats of this window. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS.md#a189e509f80b46d63b866c9a68e7589d7">GetTextLangFontsTable</a> (uint8_t langFontId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>UITextLanguageFontParam *&nbsp;</p>
<p>Get the <a href="OHOS-Text.md">Text</a> Lang Fonts Table. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS.md#a84240be6768f30e8a13cde6e9804f6dd">GetTotalLangId</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>uint8_t&nbsp;</p>
<p>Get the Total Lang Id. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS.md#a9c427c15128c695c001f27bd2351577b">GetTotalFontId</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>uint8_t&nbsp;</p>
<p>Get the Total Font Id. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS.md#ae5129a740fdb9f12118c7b2334f17cc4">GetTotalTextId</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>uint16_t&nbsp;</p>
<p>Get the Total <a href="OHOS-Text.md">Text</a> Id. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OHOS.md#a6f489752e6e7578ce0bdc8c5bff62b4c">GetLangTextDefaultParamTable</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>LangTextParam *&nbsp;</p>
<p>Get the Lang <a href="OHOS-Text.md">Text</a> default param table. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Graphic.md#ga1779d4dd0671282d297f1693252ca9d9">Intersect</a> (const <a href="OHOS-Line.md">Line</a> &amp;a, const <a href="OHOS-Line.md">Line</a> &amp;b, <a href="OHOS-Vector2-T.md">Vector2</a>&lt; int16_t &gt; &amp;out)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>bool&nbsp;</p>
<p>Checks whether line segment a and line segment b intersect, and returns the intersection point (if available). </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Graphic.md#gace8a8524c6f91aa2f0f9be73a628da20">IsIntersect</a> (const <a href="OHOS-Line.md">Line</a> &amp;a, const <a href="OHOS-Line.md">Line</a> &amp;b)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>bool&nbsp;</p>
<p>Chekcs whether line segment a and line segment b intersect. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Graphic.md#ga0001387a136a87fb2c2e2b5eb3363c72">Clip</a> (<a href="OHOS-Polygon.md">Polygon</a> &amp;poly, const <a href="OHOS-Line.md">Line</a> &amp;line)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>void&nbsp;</p>
<p>Clips a polygon by using a line segment. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Graphic.md#ga9fd2882e4813fbf4dbe77baa50d97b5c">SuthHodgClip</a> (const <a href="Rect.md">Rect</a> &amp;clipRect, const <a href="OHOS-Polygon.md">Polygon</a> &amp;polygon)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p><a href="OHOS-Polygon.md">Polygon</a>&nbsp;</p>
<p>Implements Sutherland-Hodgman, an algorithm used for clipping polygons. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Graphic.md#ga22219a4351530d5a6914bdc5dcf406d0">Clip</a> (const <a href="OHOS-Line.md">Line</a> &amp;line, const <a href="OHOS-Polygon.md">Polygon</a> &amp;poly, <a href="OHOS-Vector2-T.md">Vector2</a>&lt; int16_t &gt; *pOut, uint8_t *pNum)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>void&nbsp;</p>
<p>Clips a polygon by using a line segment and obtains the intersections. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Graphic.md#gaabb0ea584d8faebbdcb45fcc11447b8b">ImageCacheMalloc</a> (<a href="OHOS-ImageInfo.md">ImageInfo</a> &amp;info)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>void *&nbsp;</p>
<p>Applies for the image cache memory. You can customize the memory area when loading image resources. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Graphic.md#ga71fe0f3eb82083006b51fec59ad11088">ImageCacheFree</a> (<a href="OHOS-ImageInfo.md">ImageInfo</a> &amp;info)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>void&nbsp;</p>
<p>Releases the image cache memory. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Graphic.md#gafc7b2c7d0b427079d8b04b11cc4db009">UIMalloc</a> (uint32_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>void *&nbsp;</p>
<p>Applies for memory for the graphics module. You can implement this function to override the <strong>malloc</strong> and <strong>new</strong> functions. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Graphic.md#ga77914ea7bc96f6cb30f65ae2014746e8">UIFree</a> (void *buffer)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>void&nbsp;</p>
<p>Releases memory for the graphics module. You can implement this function to override the <strong>free</strong> and <strong>delete</strong> functions. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Graphic.md#ga9bb4f3256ad01b5abdd347de1fea09ee">Rotate</a> (const <a href="OHOS-Vector2-T.md">Vector2</a>&lt; int16_t &gt; &amp;point, int16_t angle, const <a href="OHOS-Vector2-T.md">Vector2</a>&lt; int16_t &gt; &amp;pivot, <a href="OHOS-Vector2-T.md">Vector2</a>&lt; int16_t &gt; &amp;out)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>void&nbsp;</p>
<p>Rotates a point around the pivot by a certain angle. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Graphic.md#gac57d591450b239f8e375f4c7b287f0d8">Rotate</a> (const <a href="OHOS-Line.md">Line</a> &amp;origLine, int16_t angle, const <a href="OHOS-Vector2-T.md">Vector2</a>&lt; int16_t &gt; &amp;pivot, <a href="OHOS-Line.md">Line</a> &amp;out)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>void&nbsp;</p>
<p>Rotates a line around the pivot by a certain angle. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Graphic.md#ga77d0dea6024cd2bb980f27f789db77c3">Rotate</a> (const <a href="Rect.md">Rect</a> &amp;origRect, int16_t angle, const <a href="OHOS-Vector2-T.md">Vector2</a>&lt; int16_t &gt; &amp;pivot, <a href="OHOS-Polygon.md">Polygon</a> &amp;out)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>void&nbsp;</p>
<p>Rotates a rectangle around the pivot by a certain angle. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Graphic.md#ga45704f59419f34aa75868387bf74b160">GetVersion</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>std::string&nbsp;</p>
<p>Obtains the version number of the graphics module. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Graphic.md#ga29d7531162c23d230c617280c5c4acf2">GetLibDsc</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>std::string&nbsp;</p>
<p>Obtains the library description of the graphics module. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1024883881113035"></a>

## **Enumeration Type Documentation**<a name="section1589645135113035"></a>

## InputDevType<a name="ac4e2abaf935793b876fbe5905d560e92"></a>

```
enum [OHOS::InputDevType](OHOS.md#ac4e2abaf935793b876fbe5905d560e92)
```

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ac4e2abaf935793b876fbe5905d560e92a15a665fc432ea0808773802b796861c7"><a name="ac4e2abaf935793b876fbe5905d560e92a15a665fc432ea0808773802b796861c7"></a><a name="ac4e2abaf935793b876fbe5905d560e92a15a665fc432ea0808773802b796861c7"></a></strong>INDEV_TYPE_KEY&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Touchscreen </p>
 </td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ac4e2abaf935793b876fbe5905d560e92a6e03d0fde54ba9c1b339984a8729070f"><a name="ac4e2abaf935793b876fbe5905d560e92a6e03d0fde54ba9c1b339984a8729070f"></a><a name="ac4e2abaf935793b876fbe5905d560e92a6e03d0fde54ba9c1b339984a8729070f"></a></strong>INDEV_TYPE_KEYBOARD&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Physical key </p>
 </td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ac4e2abaf935793b876fbe5905d560e92ae8d50d9f58cc3bd0dd327192a0ac0b7d"><a name="ac4e2abaf935793b876fbe5905d560e92ae8d50d9f58cc3bd0dd327192a0ac0b7d"></a><a name="ac4e2abaf935793b876fbe5905d560e92ae8d50d9f58cc3bd0dd327192a0ac0b7d"></a></strong>INDEV_TYPE_MOUSE&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Keyboard </p>
 </td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ac4e2abaf935793b876fbe5905d560e92a9eea2481807e5f4a6e7fefa8f1575c79"><a name="ac4e2abaf935793b876fbe5905d560e92a9eea2481807e5f4a6e7fefa8f1575c79"></a><a name="ac4e2abaf935793b876fbe5905d560e92a9eea2481807e5f4a6e7fefa8f1575c79"></a></strong>INDEV_TYPE_BUTTON&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Mouse </p>
 </td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ac4e2abaf935793b876fbe5905d560e92a4f8759aa8d44ef162a7bed84a4099da5"><a name="ac4e2abaf935793b876fbe5905d560e92a4f8759aa8d44ef162a7bed84a4099da5"></a><a name="ac4e2abaf935793b876fbe5905d560e92a4f8759aa8d44ef162a7bed84a4099da5"></a></strong>INDEV_TYPE_CROWN&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Virtual button </p>
 </td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ac4e2abaf935793b876fbe5905d560e92a5f2c187e15e6b416e5edd138c54282ea"><a name="ac4e2abaf935793b876fbe5905d560e92a5f2c187e15e6b416e5edd138c54282ea"></a><a name="ac4e2abaf935793b876fbe5905d560e92a5f2c187e15e6b416e5edd138c54282ea"></a></strong>INDEV_TYPE_ENCODER&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Watch crown </p>
 </td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ac4e2abaf935793b876fbe5905d560e92a3f0daa63c46624034a1b5f315c89317d"><a name="ac4e2abaf935793b876fbe5905d560e92a3f0daa63c46624034a1b5f315c89317d"></a><a name="ac4e2abaf935793b876fbe5905d560e92a3f0daa63c46624034a1b5f315c89317d"></a></strong>INDEV_TYPE_UNKNOWN&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Customized type of a specific function or event </p>
 </td>
</tr>
</tbody>
</table>

## **Function Documentation**<a name="section877802197113035"></a>

## GetLangTextDefaultParamTable\(\)<a name="a6f489752e6e7578ce0bdc8c5bff62b4c"></a>

```
LangTextParam* OHOS::GetLangTextDefaultParamTable ()
```

 **Description:**

Get the Lang  [Text](OHOS-Text.md)  default param table. 

**Returns:**

LangTextParam\* the param table, definition is in font tool 



## GetTextLangFontsTable\(\)<a name="a189e509f80b46d63b866c9a68e7589d7"></a>

```
UITextLanguageFontParam* OHOS::GetTextLangFontsTable (uint8_t langFontId)
```

 **Description:**

Get the  [Text](OHOS-Text.md)  Lang Fonts Table. 

**Parameters:**

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">uint8_t</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">langFontId [in] the font id </td>
</tr>
</tbody>
</table>

**Returns:**

UITextLanguageFontParam\* the font table, definition is in font tool 



## GetTotalFontId\(\)<a name="a9c427c15128c695c001f27bd2351577b"></a>

```
uint8_t OHOS::GetTotalFontId ()
```

 **Description:**

Get the Total Font Id. 

**Returns:**

uint8\_t the total font id, definition is in font tool 



## GetTotalLangId\(\)<a name="a84240be6768f30e8a13cde6e9804f6dd"></a>

```
uint8_t OHOS::GetTotalLangId ()
```

 **Description:**

Get the Total Lang Id. 

**Returns:**

uint8\_t the total Lang id, definition is in font tool 



## GetTotalTextId\(\)<a name="ae5129a740fdb9f12118c7b2334f17cc4"></a>

```
uint16_t OHOS::GetTotalTextId ()
```

 **Description:**

Get the Total  [Text](OHOS-Text.md)  Id. 

**Returns:**

uint8\_t the total text id, definition is in font tool 



