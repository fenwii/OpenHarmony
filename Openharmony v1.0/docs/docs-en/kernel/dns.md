# dns<a name="EN-US_TOPIC_0000001051930305"></a>

## Command Function<a name="section997513673713"></a>

This command is used to query and set the IP address of a DNS server on a board.

## Syntax<a name="section146015943711"></a>

dns <_1-2_\> <_IP_\>

dns  _-a_

## Parameter Description<a name="section5732111163716"></a>

**Table  1**  Parameters

<a name="table1942mcpsimp"></a>
<table><thead align="left"><tr id="row1948mcpsimp"><th class="cellrowborder" valign="top" width="20.79%" id="mcps1.2.4.1.1"><p id="p1950mcpsimp"><a name="p1950mcpsimp"></a><a name="p1950mcpsimp"></a><strong id="b95550757711755"><a name="b95550757711755"></a><a name="b95550757711755"></a>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="52.480000000000004%" id="mcps1.2.4.1.2"><p id="p1952mcpsimp"><a name="p1952mcpsimp"></a><a name="p1952mcpsimp"></a><strong id="b19814795720"><a name="b19814795720"></a><a name="b19814795720"></a>Description</strong></p>
</th>
<th class="cellrowborder" valign="top" width="26.729999999999997%" id="mcps1.2.4.1.3"><p id="p1954mcpsimp"><a name="p1954mcpsimp"></a><a name="p1954mcpsimp"></a><strong id="b167665273911755"><a name="b167665273911755"></a><a name="b167665273911755"></a>Value Range</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row1955mcpsimp"><td class="cellrowborder" valign="top" width="20.79%" headers="mcps1.2.4.1.1 "><p id="p1957mcpsimp"><a name="p1957mcpsimp"></a><a name="p1957mcpsimp"></a>&lt;1-2&gt;</p>
</td>
<td class="cellrowborder" valign="top" width="52.480000000000004%" headers="mcps1.2.4.1.2 "><p id="p1959mcpsimp"><a name="p1959mcpsimp"></a><a name="p1959mcpsimp"></a>Indicates the DNS server to set the IP address.</p>
</td>
<td class="cellrowborder" valign="top" width="26.729999999999997%" headers="mcps1.2.4.1.3 "><p id="p1961mcpsimp"><a name="p1961mcpsimp"></a><a name="p1961mcpsimp"></a><strong id="b1954822719815"><a name="b1954822719815"></a><a name="b1954822719815"></a>1</strong> or <strong id="b88294281386"><a name="b88294281386"></a><a name="b88294281386"></a>2</strong></p>
</td>
</tr>
<tr id="row1962mcpsimp"><td class="cellrowborder" valign="top" width="20.79%" headers="mcps1.2.4.1.1 "><p id="p1964mcpsimp"><a name="p1964mcpsimp"></a><a name="p1964mcpsimp"></a>&lt;IP&gt;</p>
</td>
<td class="cellrowborder" valign="top" width="52.480000000000004%" headers="mcps1.2.4.1.2 "><p id="p1966mcpsimp"><a name="p1966mcpsimp"></a><a name="p1966mcpsimp"></a>Indicates the IP address of the server.</p>
</td>
<td class="cellrowborder" valign="top" width="26.729999999999997%" headers="mcps1.2.4.1.3 "><p id="entry1967mcpsimpp0"><a name="entry1967mcpsimpp0"></a><a name="entry1967mcpsimpp0"></a>N/A</p>
</td>
</tr>
<tr id="row1968mcpsimp"><td class="cellrowborder" valign="top" width="20.79%" headers="mcps1.2.4.1.1 "><p id="p1970mcpsimp"><a name="p1970mcpsimp"></a><a name="p1970mcpsimp"></a>-a</p>
</td>
<td class="cellrowborder" valign="top" width="52.480000000000004%" headers="mcps1.2.4.1.2 "><p id="p1972mcpsimp"><a name="p1972mcpsimp"></a><a name="p1972mcpsimp"></a>Displays the current settings.</p>
</td>
<td class="cellrowborder" valign="top" width="26.729999999999997%" headers="mcps1.2.4.1.3 "><p id="entry1973mcpsimpp0"><a name="entry1973mcpsimpp0"></a><a name="entry1973mcpsimpp0"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

## Usage<a name="section15642141417371"></a>

None

## Example<a name="section1995841617370"></a>

Example:

1.  Check the current DNS settings.
2.  Set the IP address of the second DNS server.
3.  Verify the setting.

## Output<a name="section1114210258917"></a>

1.  Checking the current DNS settings:

    ```
    OHOS # dns -a
    dns1: 208.61.222.222
    dns2: 0.0.0.0
    ```

2.  Setting the IP address of the second DNS server:

    ```
    OHOS # dns 2 192.168.1.2
    ```

3.  Verifying the setting:

    ```
    OHOS # dns -a
    dns1: 208.61.222.222
    dns2: 192.168.1.2
    ```


