#!../../bin/linux-x86_64/sysmon

## You may have to change sysmon to something else
## everywhere it appears in this file

< envPaths

## Register all support components
dbLoadDatabase("../../dbd/sysmon.dbd",0,0)
sysmon_registerRecordDeviceDriver(pdbbase) 

## Load record instances

dbLoadRecords("$(TOP)/db/iocAdminSoft.db", "IOC=XF:23ID1-CT{IOC:SRV1}")
dbLoadRecords("$(TOP)/db/iocAdminSoftAdd.db", "IOC=XF:23ID1-CT{IOC:SRV1}")

iocInit()

