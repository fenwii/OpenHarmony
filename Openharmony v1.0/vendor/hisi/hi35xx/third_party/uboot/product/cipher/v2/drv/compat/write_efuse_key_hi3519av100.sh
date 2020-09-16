#!/bin/sh

#Set Key Index 1
himm 0x040A0008 0x01

#set key~key3 and CRC16
himm 0x040A000C 0x00000001
himm 0x040A0010 0x00000002
himm 0x040A0014 0x00000003
himm 0x040A0018 0x00000004
#himm 0x040A001C 0x0000B533

#Set mode, write key
himm 0x040A0000 0x02

#start write key to OTP 1
himm 0x040A0004 0x1acce551

sleep 1
himd.l 0x040A004C
#should be 0x00001202, Bit2 should be 1.


