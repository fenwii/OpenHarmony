# Graphics<a name="EN-US_TOPIC_0000001051770388"></a>

The OpenHarmony graphics subsystem provides you with basic UI and container components, including buttons, images, labels, lists, animators, scroll views, swipe views, fonts, clock, charts, canvas, sliders, and layouts. In addition, this subsystem provides the Design for X \(DFX\) capability to capture screenshots and export the component tree. It also implements features such as component rendering, animation, and input event distribution.

## UI Components<a name="section1987017145112"></a>

Contain a variety of basic components \(such as buttons, text, and progress bars\) and complex components \(such as page switching and image sequence frames\).

## Layouts<a name="section662016231612"></a>

Implement grid layout and flexible layout \(such as centered, left-aligned, and right-aligned\).

As each layout is a one-off, the positions of components in a specific layout are calculated each time related functions are called on the layout. However, if the position of a component changes with an operation \(dragging for example\), the positions of other associated components do not automatically change. To change them, you need to call the layout functions again.

## Animators<a name="section73736284117"></a>

Each time the Tick event is received, the Task Manager module periodically invokes callbacks upon attribute changes and then triggers redrawing to produce the desired animation effect.

You can call related functions to start, stop, pause, resume, create, and destroy an animator.

## Input Events<a name="section672194012114"></a>

Include touchscreen and physical key input events. Each time the GUI engine runs, the Input Manager module reads the input of all registered hardware devices and converts the input into various events for UI components to use.

## Rendering<a name="section14338859916"></a>

-   2D graphics rendering

    Draws lines, rectangles, triangles, and arcs.


-   Image rendering

    Draws images of various types, such as RGB565, RGB888, ARGB8888, PNG, and JPG.


-   Font rendering

    Draws vector fonts in real time.


