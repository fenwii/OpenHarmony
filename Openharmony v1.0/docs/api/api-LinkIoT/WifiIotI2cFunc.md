# WifiIotI2cFunc<a name="ZH-CN_TOPIC_0000001054595105"></a>

## **Overview**<a name="section1966963801191904"></a>

**Related Modules:**

[Wifiiot](Wifiiot.md)

**Description:**

Defines I2C callbacks. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1588723698191904"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table803818132191904"></a>
<table><thead align="left"><tr id="row859032302191904"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1617706074191904"><a name="p1617706074191904"></a><a name="p1617706074191904"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p405715202191904"><a name="p405715202191904"></a><a name="p405715202191904"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2056659251191904"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p15652808191904"><a name="p15652808191904"></a><a name="p15652808191904"></a><a href="WifiIotI2cFunc.md#a9feb0d5af81f7aba205c276b9f3c9d62">resetFunc</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1578824082191904"><a name="p1578824082191904"></a><a name="p1578824082191904"></a><a href="Wifiiot.md#ga1176c2c06eca906f3e662027df156109">I2CResetFunc</a>&nbsp;</p>
</td>
</tr>
<tr id="row1962659888191904"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p173329721191904"><a name="p173329721191904"></a><a name="p173329721191904"></a><a href="WifiIotI2cFunc.md#a9f3d568d7e3c3c3e69cbb33b93bfe946">prepareFunc</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1653220426191904"><a name="p1653220426191904"></a><a name="p1653220426191904"></a><a href="Wifiiot.md#ga1f0c8fe1deb1cf1fc8b19d69c2fca729">I2cPrepareFunc</a>&nbsp;</p>
</td>
</tr>
<tr id="row1817164142191904"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1259874849191904"><a name="p1259874849191904"></a><a name="p1259874849191904"></a><a href="WifiIotI2cFunc.md#adc1d6da360168022a6ef3472760fbf1e">restoreFunc</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1011946177191904"><a name="p1011946177191904"></a><a name="p1011946177191904"></a><a href="Wifiiot.md#ga16779c755404f2ec8543452268a9fb3b">I2cRestoreFunc</a>&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section379138535191904"></a>

## **Field Documentation**<a name="section1932889132191904"></a>

## prepareFunc<a name="a9f3d568d7e3c3c3e69cbb33b93bfe946"></a>

```
[I2cPrepareFunc](Wifiiot.md#ga1f0c8fe1deb1cf1fc8b19d69c2fca729) WifiIotI2cFunc::prepareFunc
```

 **Description:**

Callback invoked for data preparation 

## resetFunc<a name="a9feb0d5af81f7aba205c276b9f3c9d62"></a>

```
[I2CResetFunc](Wifiiot.md#ga1176c2c06eca906f3e662027df156109) WifiIotI2cFunc::resetFunc
```

 **Description:**

Callback invoked upon an I2C device exception 

## restoreFunc<a name="adc1d6da360168022a6ef3472760fbf1e"></a>

```
[I2cRestoreFunc](Wifiiot.md#ga16779c755404f2ec8543452268a9fb3b) WifiIotI2cFunc::restoreFunc
```

 **Description:**

Callback invoked for data recovery 

