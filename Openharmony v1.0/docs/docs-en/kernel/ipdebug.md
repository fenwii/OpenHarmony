# ipdebug<a name="EN-US_TOPIC_0000001051690317"></a>

## Command Function<a name="section10191115553720"></a>

**ipdebug**  is a console command and is used for IPv6 information debugging. It can display IPv6 address prefixes, neighbor entries, destination cache entries, and default routing entries.

## Syntax<a name="section124061758123713"></a>

ipdebug

## Usage<a name="section171837113810"></a>

Enter the  **ipdebug**  command.

## Output<a name="section561416467104"></a>

The  **ipdebug**  output is as follows:

```
OHOS # ipdebug
=================
|| Prefix List ||
=================
Prefix validLifetime Flags
==============================================================================================
2001:: 86384 1
----------------------------------------------------------------------------------------------
============================
|| Neighbor Cache Entries ||
============================
2001::1 dev eth0 lladr 44:39:C4:94:5D:44 STALE Router
FE80::4639:C4FF:FE94:5D44 dev eth0 lladr 44:39:C4:94:5D:44 REACHABLE Router
--------------------------------------------------------------------
===============================
|| Destination Cache Entries ||
===============================
2001::1 2001::1 pmtu 1500 age 152
FE80::4639:C4FF:FE94:5D44 FE80::4639:C4FF:FE94:5D44 pmtu 1500 age 6
2002::1 FE80::4639:C4FF:FE94:5D44 pmtu 1500 age 17
:: :: pmtu 0 age 219
:: :: pmtu 0 age 219
:: :: pmtu 0 age 219
:: :: pmtu 0 age 219
:: :: pmtu 0 age 219
:: :: pmtu 0 age 219
:: :: pmtu 0 age 219
--------------------------------------------------------------------
============================
|| Default Router Entries ||
============================
FE80::4639:C4FF:FE94:5D44 invalidation_timer 1784 flags 0
--------------------------------------------------------------------
```

