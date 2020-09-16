# ping6<a name="ZH-CN_TOPIC_0000001052451611"></a>

## 命令功能<a name="section1057291313393"></a>

ping6用于测试IPv6网络连接是否正常。

## 命令格式<a name="section199901315123919"></a>

ping6  _\[-c count\] \[-I interface / sourceAddress\] destination_

## 参数说明<a name="section4679319113919"></a>

**表 1**  参数说明

<a name="table2742mcpsimp"></a>
<table><thead align="left"><tr id="row2748mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p2750mcpsimp"><a name="p2750mcpsimp"></a><a name="p2750mcpsimp"></a>参数</p>
</th>
<th class="cellrowborder" valign="top" width="52%" id="mcps1.2.4.1.2"><p id="p2752mcpsimp"><a name="p2752mcpsimp"></a><a name="p2752mcpsimp"></a>参数说明</p>
</th>
<th class="cellrowborder" valign="top" width="27%" id="mcps1.2.4.1.3"><p id="p2754mcpsimp"><a name="p2754mcpsimp"></a><a name="p2754mcpsimp"></a>取值范围</p>
</th>
</tr>
</thead>
<tbody><tr id="row2755mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p2757mcpsimp"><a name="p2757mcpsimp"></a><a name="p2757mcpsimp"></a>-c count</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p2759mcpsimp"><a name="p2759mcpsimp"></a><a name="p2759mcpsimp"></a>执行的次数，不带本参数则默认为4次。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p2761mcpsimp"><a name="p2761mcpsimp"></a><a name="p2761mcpsimp"></a>1~65535</p>
</td>
</tr>
<tr id="row2762mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p2764mcpsimp"><a name="p2764mcpsimp"></a><a name="p2764mcpsimp"></a>-I interface</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p2766mcpsimp"><a name="p2766mcpsimp"></a><a name="p2766mcpsimp"></a>指定网卡执行IPv6 ping操作。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p2768mcpsimp"><a name="p2768mcpsimp"></a><a name="p2768mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row2769mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p2771mcpsimp"><a name="p2771mcpsimp"></a><a name="p2771mcpsimp"></a>-I sourceAddress</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p2773mcpsimp"><a name="p2773mcpsimp"></a><a name="p2773mcpsimp"></a>指定源IPv6地址执行ping操作。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p2775mcpsimp"><a name="p2775mcpsimp"></a><a name="p2775mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row84173618410"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p141163619410"><a name="p141163619410"></a><a name="p141163619410"></a>destination</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p134111362417"><a name="p134111362417"></a><a name="p134111362417"></a>目标主机地址。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p134173611412"><a name="p134173611412"></a><a name="p134173611412"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

## 使用指南<a name="section1127917226399"></a>

-   如果目的IPv6地址不可达，会显示请求超时。
-   如果显示发送错误，说明没有到目的IPV6的路由。
-   命令需要启动TCP/IP协议栈后才能使用。

## 使用实例<a name="section7211192553917"></a>

-   ping6 2001:a:b:c:d:e:f:b
-   ping6 -c 3 2001:a:b:c:d:e:f:b
-   ping6 -I eth0 2001:a:b:c:d:e:f:b
-   ping6 -I 2001:a:b:c:d:e:f:d 2001:a:b:c:d:e:f:b

## 输出说明<a name="section4846145221215"></a>

1.  输入ping6 2001:a:b:c:d:e:f:b

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

2.  输入 ping6 -c 3 2001:a:b:c:d:e:f:b   指定3次进行网络测试

    ```
    OHOS # ping6 -c 3 2001:a:b:c:d:e:f:b    PING 2001:A:B:C:D:E:F:B with 56 bytes of data.
    56 bytes from 2001:A:B:C:D:E:F:B : icmp_seq=1 time<1 ms
    56 bytes from 2001:A:B:C:D:E:F:B : icmp_seq=2 time<1 ms
    56 bytes from 2001:A:B:C:D:E:F:B : icmp_seq=3 time<1 ms
    --- 2001:a:b:c:d:e:f:b/64 ping statistics ---
    3 packets transmitted, 3 received, 0.00% packet loss, time 20ms
    rtt min/avg/max = 0/0.00/0 ms
    ```

3.  输入 ping6 -I eth0 2001:a:b:c:d:e:f:b  使用指定网卡接口eth0测试IPv6。

    ```
    OHOS # ping6 -I eth0 2001:a:b:c:d:e:f:b PING 2001:A:B:C:D:E:F:B with 56 bytes of data.
    56 bytes from 2001:A:B:C:D:E:F:B : icmp_seq=1 time=10 ms
    56 bytes from 2001:A:B:C:D:E:F:B : icmp_seq=2 time<1 ms
    56 bytes from 2001:A:B:C:D:E:F:B : icmp_seq=3 time<1 ms
    56 bytes from 2001:A:B:C:D:E:F:B : icmp_seq=4 time<1 ms
    --- 2001:a:b:c:d:e:f:b/64 ping statistics ---
    4 packets transmitted, 4 received, 0.00% packet loss, time 30msrtt min/avg/max = 0/2.50/10 ms
    ```

4.  输入 ping6 -I 2001:a:b:c:d:e:f:d 2001:a:b:c:d:e:f:b   使用指定的源IPv6地址2001:a:b:c:d:e:f:d进行测试。

    ```
    OHOS # ping6 -I 2001:a:b:c:d:e:f:d 2001:a:b:c:d:e:f:b PING 2001:A:B:C:D:E:F:B with 56 bytes of data.
    56 bytes from 2001:A:B:C:D:E:F:B : icmp_seq=1 time<1 ms
    56 bytes from 2001:A:B:C:D:E:F:B : icmp_seq=2 time<1 ms
    56 bytes from 2001:A:B:C:D:E:F:B : icmp_seq=3 time<1 ms
    56 bytes from 2001:A:B:C:D:E:F:B : icmp_seq=4 time<1 ms
    --- 2001:a:b:c:d:e:f:b/64 ping statistics ---
    4 packets transmitted, 4 received, 0.00% packet loss, time 20msrtt min/avg/max = 0/0.00/0 ms
    ```


