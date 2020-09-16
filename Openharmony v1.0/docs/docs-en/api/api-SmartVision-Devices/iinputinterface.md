# IInputInterface<a name="EN-US_TOPIC_0000001055039518"></a>

## **Overview**<a name="section981537337093530"></a>

**Related Modules:**

[Input](input.md)

**Description:**

Defines interfaces for providing driver capabilities of input devices. 

## **Summary**<a name="section1102677348093530"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1505262157093530"></a>
<table><thead align="left"><tr id="row1745860111093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1525786542093530"><a name="p1525786542093530"></a><a name="p1525786542093530"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2133440484093530"><a name="p2133440484093530"></a><a name="p2133440484093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1849185095093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1636343419093530"><a name="p1636343419093530"></a><a name="p1636343419093530"></a><a href="iinputinterface.md#a539baf2f3554b901abd4820e521ac0ea">iInputManager</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p316021506093530"><a name="p316021506093530"></a><a name="p316021506093530"></a><a href="inputmanager.md">InputManager</a> * </p>
</td>
</tr>
<tr id="row473614036093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1252648199093530"><a name="p1252648199093530"></a><a name="p1252648199093530"></a><a href="iinputinterface.md#a0da92e255529827b823c19071f50fa27">iInputController</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1082826122093530"><a name="p1082826122093530"></a><a name="p1082826122093530"></a><a href="inputcontroller.md">InputController</a> * </p>
</td>
</tr>
<tr id="row513940522093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p355326634093530"><a name="p355326634093530"></a><a name="p355326634093530"></a><a href="iinputinterface.md#a592d65e0a8ad8e9bc0241a0be50669d0">iInputReporter</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p11826621093530"><a name="p11826621093530"></a><a name="p11826621093530"></a><a href="inputreporter.md">InputReporter</a> * </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section108468589093530"></a>

## **Field Documentation**<a name="section163183902093530"></a>

## iInputController<a name="a0da92e255529827b823c19071f50fa27"></a>

```
[InputController](inputcontroller.md)* IInputInterface::iInputController
```

 **Description:**

[Service](service.md)  control interface for input devices 

## iInputManager<a name="a539baf2f3554b901abd4820e521ac0ea"></a>

```
[InputManager](inputmanager.md)* IInputInterface::iInputManager
```

 **Description:**

Device management interface for input devices 

## iInputReporter<a name="a592d65e0a8ad8e9bc0241a0be50669d0"></a>

```
[InputReporter](inputreporter.md)* IInputInterface::iInputReporter
```

 **Description:**

Data reporting interface for input devices 

