# ping6<a name="EN-US_TOPIC_0000001052451611"></a>

## Command Function<a name="section1057291313393"></a>

This command is used to test whether the IPv6 network connection is normal.

## Syntax<a name="section199901315123919"></a>

ping6  _\[-c count\] \[-I interface / sourceAddress\] destination_

## Parameter Description<a name="section4679319113919"></a>

**Table  1**  Parameters

<a name="table2742mcpsimp"></a>
<table><thead align="left"><tr id="row2748mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p2750mcpsimp"><a name="p2750mcpsimp"></a><a name="p2750mcpsimp"></a><strong id="b9059409211170"><a name="b9059409211170"></a><a name="b9059409211170"></a>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="52%" id="mcps1.2.4.1.2"><p id="p2752mcpsimp"><a name="p2752mcpsimp"></a><a name="p2752mcpsimp"></a><strong id="b189621522143614"><a name="b189621522143614"></a><a name="b189621522143614"></a>Description</strong></p>
</th>
<th class="cellrowborder" valign="top" width="27%" id="mcps1.2.4.1.3"><p id="p2754mcpsimp"><a name="p2754mcpsimp"></a><a name="p2754mcpsimp"></a><strong id="b1322365521170"><a name="b1322365521170"></a><a name="b1322365521170"></a>Value Range</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row2755mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p2757mcpsimp"><a name="p2757mcpsimp"></a><a name="p2757mcpsimp"></a>-c count</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p2759mcpsimp"><a name="p2759mcpsimp"></a><a name="p2759mcpsimp"></a>Indicates the number of execution times. If this parameter is not specified, the default value is <strong id="b1769545815488"><a name="b1769545815488"></a><a name="b1769545815488"></a>4</strong>.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p2761mcpsimp"><a name="p2761mcpsimp"></a><a name="p2761mcpsimp"></a>1~65535</p>
</td>
</tr>
<tr id="row2762mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p2764mcpsimp"><a name="p2764mcpsimp"></a><a name="p2764mcpsimp"></a>-I interface</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p2766mcpsimp"><a name="p2766mcpsimp"></a><a name="p2766mcpsimp"></a>Performs an IPv6 ping operation for a specified NIC.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p2768mcpsimp"><a name="p2768mcpsimp"></a><a name="p2768mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row2769mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p2771mcpsimp"><a name="p2771mcpsimp"></a><a name="p2771mcpsimp"></a>-I sourceAddress</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p2773mcpsimp"><a name="p2773mcpsimp"></a><a name="p2773mcpsimp"></a>Indicates the source IPv6 address to be pinged.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p2775mcpsimp"><a name="p2775mcpsimp"></a><a name="p2775mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row84173618410"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p141163619410"><a name="p141163619410"></a><a name="p141163619410"></a>destination</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p134111362417"><a name="p134111362417"></a><a name="p134111362417"></a>Indicates the IP address of the destination host.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p134173611412"><a name="p134173611412"></a><a name="p134173611412"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

## Usage<a name="section1127917226399"></a>

-   If the destination IPv6 address is unreachable, the system displays a message indicating that the request times out.
-   If no route is available to the destination IPv6 address, an error message is displayed.
-   This command can be used only after the TCP/IP protocol stack is enabled.

## Example<a name="section7211192553917"></a>

-   ping6 2001:a:b:c:d:e:f:b
-   ping6 -c 3 2001:a:b:c:d:e:f:b
-   ping6 -I eth0 2001:a:b:c:d:e:f:b
-   ping6 -I 2001:a:b:c:d:e:f:d 2001:a:b:c:d:e:f:b

## Output<a name="section4846145221215"></a>

1.  Output of  **ping6 2001:a:b:c:d:e:f:b**:

    ```
    OHOS # ping6 2001:a:b:c:d:e:f:b PING 2001:A:B:C:D:E:F:B with 56 bytes of data.
    56 bytes from 2001:A:B:C:D:E:F:B : icmp_seq=1 time<1 ms
    56 bytes from 2001:A:B:C:D:E:F:B : icmp_seq=2 time<1 ms
    56 bytes from 2001:A:B:C:D:E:F:B : icmp_seq=3 time<1 ms
    56 bytes from 2001:A:B:C:D:E:F:B : icmp_seq=4 time<1 ms
    --- 2001:a:b:c:d:e:f:b/64 ping statistics ---
    4 packets transmitted, 4 received, 0.00% packet loss, time 20ms
    rtt min/avg/max = 0/0.00/0 ms
    ```

2.  Output of  **ping6 -c 3 2001:a:b:c:d:e:f:b**:

    ```
    OHOS # ping6 -c 3 2001:a:b:c:d:e:f:b    PING 2001:A:B:C:D:E:F:B with 56 bytes of data.
    56 bytes from 2001:A:B:C:D:E:F:B : icmp_seq=1 time<1 ms
    56 bytes from 2001:A:B:C:D:E:F:B : icmp_seq=2 time<1 ms
    56 bytes from 2001:A:B:C:D:E:F:B : icmp_seq=3 time<1 ms
    --- 2001:a:b:c:d:e:f:b/64 ping statistics ---
    3 packets transmitted, 3 received, 0.00% packet loss, time 20ms
    rtt min/avg/max = 0/0.00/0 ms
    ```

3.  Output of  **ping6 -I eth0 2001:a:b:c:d:e:f:b**:

    ```
    OHOS # ping6 -I eth0 2001:a:b:c:d:e:f:b PING 2001:A:B:C:D:E:F:B with 56 bytes of data.
    56 bytes from 2001:A:B:C:D:E:F:B : icmp_seq=1 time=10 ms
    56 bytes from 2001:A:B:C:D:E:F:B : icmp_seq=2 time<1 ms
    56 bytes from 2001:A:B:C:D:E:F:B : icmp_seq=3 time<1 ms
    56 bytes from 2001:A:B:C:D:E:F:B : icmp_seq=4 time<1 ms
    --- 2001:a:b:c:d:e:f:b/64 ping statistics ---
    4 packets transmitted, 4 received, 0.00% packet loss, time 30msrtt min/avg/max = 0/2.50/10 ms
    ```

4.  Output of  **ping6 -I 2001:a:b:c:d:e:f:d 2001:a:b:c:d:e:f:b**:

    ```
    OHOS # ping6 -I 2001:a:b:c:d:e:f:d 2001:a:b:c:d:e:f:b PING 2001:A:B:C:D:E:F:B with 56 bytes of data.
    56 bytes from 2001:A:B:C:D:E:F:B : icmp_seq=1 time<1 ms
    56 bytes from 2001:A:B:C:D:E:F:B : icmp_seq=2 time<1 ms
    56 bytes from 2001:A:B:C:D:E:F:B : icmp_seq=3 time<1 ms
    56 bytes from 2001:A:B:C:D:E:F:B : icmp_seq=4 time<1 ms
    --- 2001:a:b:c:d:e:f:b/64 ping statistics ---
    4 packets transmitted, 4 received, 0.00% packet loss, time 20msrtt min/avg/max = 0/0.00/0 ms
    ```


