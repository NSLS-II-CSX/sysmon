#!../../bin/linux-x86_64/sysmon

## You may have to change sysmon to something else
## everywhere it appears in this file

< envPaths

epicsEnvSet("BASENAME", "TEST")

## Register all support components
dbLoadDatabase("../../dbd/sysmon.dbd",0,0)
sysmon_registerRecordDeviceDriver(pdbbase) 

diskMonitorDriverConfigure("PATH1", "/GPFS/xf23id")

## Load record instances

dbLoadRecords("$(TOP)/db/iocAdminSoft.db", "IOC=$(BASENAME)")
dbLoadRecords("$(TOP)/db/iocAdminSoftAdd.db", "IOC=$(BASENAME)")

dbLoadRecords("$(TOP)/db/diskMonitor.db", "Sys=XF:23ID1-CT,Dev={IOC:SRV1-Vol:GPFS},PORT=PATH1,TIMEOUT=0,ADDR=0")

system("install -m 777 -d $(TOP)/as/save") 
system("install -m 777 -d $(TOP)/as/req")

## autosave/restore machinery
save_restoreSet_Debug(0)
save_restoreSet_IncompleteSetsOk(1)
save_restoreSet_DatedBackupFiles(1)

set_savefile_path("${TOP}/as","/save")
set_requestfile_path("${TOP}/as","/req")

set_pass0_restoreFile("info_positions.sav")
set_pass0_restoreFile("info_settings.sav")
set_pass1_restoreFile("info_settings.sav")

asSetFilename("/epics/xf/23id/xf23id.acf")

iocInit()

cd ${TOP}/as/req
makeAutosaveFiles()
create_monitor_set("info_positions.req", 5 , "")
create_monitor_set("info_settings.req", 15 , "")
