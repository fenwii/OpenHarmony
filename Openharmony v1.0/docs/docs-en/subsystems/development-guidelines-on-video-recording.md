# Development Guidelines on Video Recording<a name="EN-US_TOPIC_0000001051451869"></a>

## When to Use<a name="section186634310418"></a>

Use the camera module APIs to capture video streams.

## Available APIs<a name="section125479541744"></a>

For details, see  [Available APIs](development-guidelines-on-photographing.md#section56549532016).

## Limitations and Constraints<a name="section1165911177314"></a>

None

## How to Develop<a name="section1196016315516"></a>

1.  Perform step 1 through step 4 provided in  [Development Guidelines on Photographing](development-guidelines-on-photographing.md).
2.  Obtain the  **FrameConfig**  instance for audio recording.

    ```
    /* Obtain the surface from the recorder. */
    Surface *surface = recorder_->GetSurface(0);
    surface->SetWidthAndHeight(1920, 1080);
    surface->SetQueueSize(3);
    surface->SetSize(1024 * 1024);
    /* Add the surface to the FrameConfig instance. */
    FrameConfig *fc = new FrameConfig(FRAME_CONFIG_RECORD);
    fc->AddSurface(*surface);
    ```

3.  Start and stop video recording.

    ```
    stateCallback->camera_->TriggerLoopingCapture(*fc); // Start recording.
    stateCallback->camera_->StopLoopingCapture(); // Stop recording.
    ```


