#!/bin/sh

#Set Key Index 1
himm 0x10240008 0x01

#set key~key3 and CRC16
himm 0x1024000C 0x00000001
himm 0x10240010 0x00000002
himm 0x10240014 0x00000003
himm 0x10240018 0x00000004
himm 0x1024001C 0x0000B533

#Set mode, write key
himm 0x10240000 0x02

#start write key to OTP 1
himm 0x10240004 0x1acce551

sleep 1
himd.l 0x1024004C
#should be 0x00001202, Bit2 should be 1.


