# getopt.h<a name="ZH-CN_TOPIC_0000001054948033"></a>

## **Overview**<a name="section612995814084830"></a>

**Related Modules:**

[UTILS](UTILS.md)

**Description:**

Provides functions and data structures, such as command-line argument parsing. 

You can use the functions provided in this file to perform operations related to wide character types during development, such as, command-line argument parsing. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section126641778084830"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table609168848084830"></a>
<table><thead align="left"><tr id="row607172921084830"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p309260806084830"><a name="p309260806084830"></a><a name="p309260806084830"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p899976928084830"><a name="p899976928084830"></a><a name="p899976928084830"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row896408380084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p152759246084830"><a name="p152759246084830"></a><a name="p152759246084830"></a><a href="option.md">option</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p42147506084830"><a name="p42147506084830"></a><a name="p42147506084830"></a>Defines the command parsing option. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1120322762084830"></a>
<table><thead align="left"><tr id="row24163162084830"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p952921814084830"><a name="p952921814084830"></a><a name="p952921814084830"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p357027820084830"><a name="p357027820084830"></a><a name="p357027820084830"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1056414457084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1861463389084830"><a name="p1861463389084830"></a><a name="p1861463389084830"></a><a href="UTILS.md#ga3d26a6a51c3a1576b36c66798a64a3cf">getopt_long</a> (int argc, char *const *argv, const char *optstring, const struct <a href="option.md">option</a> *longopts, int *longindex)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p76868988084830"><a name="p76868988084830"></a><a name="p76868988084830"></a>int&nbsp;</p>
<p id="p2106559145084830"><a name="p2106559145084830"></a><a name="p2106559145084830"></a>Parses the command-line arguments. </p>
</td>
</tr>
<tr id="row427491539084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p787325178084830"><a name="p787325178084830"></a><a name="p787325178084830"></a><a href="UTILS.md#ga6606cd658b7339db0fab03d3454bd29c">getopt_long_only</a> (int argc, char *const *argv, const char *optstring, const struct <a href="option.md">option</a> *longopts, int *longindex)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p439057763084830"><a name="p439057763084830"></a><a name="p439057763084830"></a>int&nbsp;</p>
<p id="p142118720084830"><a name="p142118720084830"></a><a name="p142118720084830"></a>Parses the command-line arguments. </p>
</td>
</tr>
</tbody>
</table>

