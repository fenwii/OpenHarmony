# Overview<a name="EN-US_TOPIC_0000001051690589"></a>

## Basic Concepts<a name="section175012297491"></a>

Camera is one of the services provided by the OpenHarmony media subsystem. The camera module provides recording, preview, and photographing features and supports concurrent stream reading by multiple users.

It is considered good practice that you understand the following concepts before starting development:

-   Video frame

    A video frame is formed by the stream data of a video image. Video data streams are formed by a series of image data arranged at a fixed time interval.

-   Frame per second \(FPS\)

    FPS is used to represent the frame rate at which images are refreshed during video playback, or the number of frames per second during video playback. A higher frame rate means smoother video playback.

-   Resolution

    Information about each image frame consists of pixels. The number of pixels in an image is presented by the resolution. For example, 1080p \(1920 x 1080\) indicates that the image width is 1920 pixels and the image height is 1080 pixels.


## Working Principles<a name="section193961322175011"></a>

-   Media services

    Media services are started by the  **Init**  process upon system startup, and media hardware resources \(such as memory, display hardware, image sensors, and codecs\) are initialized and allocated. During the initialization, the configuration file is parsed, which determines the upper limit of capabilities and resources of each service. Generally, the upper limit is configured by original equipment manufacturers \(OEMs\) in the configuration file. The following configuration items are available for the camera service during media service initialization:

    -   Memory pool: Memory blocks in the memory pool are accessed and released continuously by all media services.
    -   Image sensor: sensor type, resolution, ISP, and more
    -   Image processor: resolution, bit rate, image inversion, and more
    -   Image encoder: encoding format, bit rate, resolution, and more


-   Major classes

    You can use the  **Camera**  class and its asynchronous callback classes to configure and access the camera functionalities. The three callback classes correspond to different asynchronous processing scenarios, as described in  [Table 1](#table486418149411).

    **Table  1**  Class description

    <a name="table486418149411"></a>
    <table><thead align="left"><tr id="row19864414104115"><th class="cellrowborder" valign="top" width="22.322232223222326%" id="mcps1.2.4.1.1"><p id="p128641914114112"><a name="p128641914114112"></a><a name="p128641914114112"></a>Class</p>
    </th>
    <th class="cellrowborder" valign="top" width="44.34443444344435%" id="mcps1.2.4.1.2"><p id="p1386471410411"><a name="p1386471410411"></a><a name="p1386471410411"></a>Description</p>
    </th>
    <th class="cellrowborder" valign="top" width="33.33333333333333%" id="mcps1.2.4.1.3"><p id="p1486541484116"><a name="p1486541484116"></a><a name="p1486541484116"></a>Examples</p>
    </th>
    </tr>
    </thead>
    <tbody><tr id="row138651914104113"><td class="cellrowborder" valign="top" width="22.322232223222326%" headers="mcps1.2.4.1.1 "><p id="p1886515147416"><a name="p1886515147416"></a><a name="p1886515147416"></a>Camera</p>
    </td>
    <td class="cellrowborder" valign="top" width="44.34443444344435%" headers="mcps1.2.4.1.2 "><p id="p48653148414"><a name="p48653148414"></a><a name="p48653148414"></a>Configures the static camera capability through the configuration class to use basic camera functionalities.</p>
    </td>
    <td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p986510145416"><a name="p986510145416"></a><a name="p986510145416"></a>Photographing, video recording, and previewing</p>
    </td>
    </tr>
    <tr id="row98656144413"><td class="cellrowborder" valign="top" width="22.322232223222326%" headers="mcps1.2.4.1.1 "><p id="p13865161412412"><a name="p13865161412412"></a><a name="p13865161412412"></a>CameraDeviceCallback</p>
    </td>
    <td class="cellrowborder" valign="top" width="44.34443444344435%" headers="mcps1.2.4.1.2 "><p id="p1986517141413"><a name="p1986517141413"></a><a name="p1986517141413"></a>Handles camera hardware state changes.</p>
    </td>
    <td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p286531413419"><a name="p286531413419"></a><a name="p286531413419"></a>Available or unavailable</p>
    </td>
    </tr>
    <tr id="row167872310411"><td class="cellrowborder" valign="top" width="22.322232223222326%" headers="mcps1.2.4.1.1 "><p id="p196793230419"><a name="p196793230419"></a><a name="p196793230419"></a>CameraStateCallback</p>
    </td>
    <td class="cellrowborder" valign="top" width="44.34443444344435%" headers="mcps1.2.4.1.2 "><p id="p14679823144110"><a name="p14679823144110"></a><a name="p14679823144110"></a>Handles camera instance state changes.</p>
    </td>
    <td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p6679102354112"><a name="p6679102354112"></a><a name="p6679102354112"></a>Created or released</p>
    </td>
    </tr>
    <tr id="row886581414118"><td class="cellrowborder" valign="top" width="22.322232223222326%" headers="mcps1.2.4.1.1 "><p id="p1865614194116"><a name="p1865614194116"></a><a name="p1865614194116"></a>FrameStateCallback</p>
    </td>
    <td class="cellrowborder" valign="top" width="44.34443444344435%" headers="mcps1.2.4.1.2 "><p id="p1865171420410"><a name="p1865171420410"></a><a name="p1865171420410"></a>Handles frame status changes.</p>
    </td>
    <td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p486541444119"><a name="p486541444119"></a><a name="p486541444119"></a>Start and end of photographing, and frame rate changes</p>
    </td>
    </tr>
    </tbody>
    </table>

-   Stream transfer

    A surface is the basic data structure for transferring audio and video data. A camera is generally used as the data producer of a surface and has specific consumers in different scenarios.

    Camera preview and recording outputs are video streams, and photographing outputs are image frames. The outputs are transferred through the  **Surface**  class. A surface can transmit media information streams within and cross processes.

    Take video recording as an example. You create a  **Recorder**  instance, obtain the surface of the  **Recorder**  instance, and then transfer the surface to the  **Camera**  instance. In this case, the  **Camera**  instance works as a producer to inject video streams to the surface, and the  **Recorder**  instance act as the consumer to obtain video streams from the surface for storage. In this case, you connect the recorder and camera through the surface.

    Similarly, you can create a surface, implement consumer logic for it, and transfer it to the  **Camera**  instance. For example, transmit video streams over the network or save captured frame data as an image file.

    The graphics module also obtains stream resources from the camera module through surfaces. For details, see development guidelines on  [Graphic](graphics.md).

-   Camera running process
    1.  Creating a camera

        This process creates a  **Camera**  instance by  **CameraManager**, binds the camera device to the server, and asynchronously notifies you of the successful creation. The following figure shows the time sequence between classes.

        **Figure  1**  Sequence diagram for creating a camera<a name="fig9882125184416"></a>  
        

        ![](figures/en-us_image_0000001054101094.png)


    1.  Taking a video/Previewing

        This process creates a  **Camera**  instance via  **CameraKit**, and configures frame attributes via  **FrameConfig**  for recording or previewing. The following figure shows the time sequence.

        **Figure  2**  Sequence diagram for recording/previewing<a name="fig642695404512"></a>  
        

        ![](figures/en-us_image_0000001054421113.png)



