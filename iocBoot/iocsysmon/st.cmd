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