TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

PROD_IOC = sysmon
# sysmon.dbd will be created and installed
DBD += sysmon.dbd

# sysmon.dbd will be made up from these files:
sysmon_DBD += base.dbd
sysmon_DBD += diskMonitor.dbd

# Include dbd files from all support applications:
sysmon_DBD += devIocStats.dbd
sysmon_DBD += asSupport.dbd
sysmon_DBD += system.dbd
sysmon_DBD += asyn.dbd

# Add all the support libraries needed by this IOC
sysmon_LIBS += devIocStats
sysmon_LIBS += autosave
sysmon_LIBS += asyn

# sysmon_registerRecordDeviceDriver.cpp derives from sysmon.dbd
sysmon_SRCS += diskMonitor.cpp
sysmon_SRCS += sysmon_registerRecordDeviceDriver.cpp

# Build the main IOC entry point on workstation OSs.
sysmon_SRCS_DEFAULT += sysmonMain.cpp
sysmon_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#sysmon_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Finally link to the EPICS Base libraries
sysmon_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

