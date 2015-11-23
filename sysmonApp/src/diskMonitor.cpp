/* 
 * diskMonitor.cpp
 *
 * Asyn Port Driver to monitor disk usage
 *
 */

#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <math.h>

#include <epicsTypes.h>
#include <epicsTime.h>
#include <epicsThread.h>
#include <epicsString.h>
#include <epicsTimer.h>
#include <epicsMutex.h>
#include <epicsExport.h>
#include <epicsEvent.h>
#include <iocsh.h>

#include "diskMonitor.h"

static const char *driverName = "diskMonitorDriver";

/** Constructor for the diskMonitorDriver class.
  * Calls constructor for the asynPortDriver base class.
  * \param[in] portName The name of the asyn port driver to be created.
  * \param[in] maxPoints The maximum  number of points in the volt and time arrays */

diskMonitorDriver::diskMonitorDriver(const char *portName, const char *path) 
   : asynPortDriver(portName, 
                    1, /* maxAddr */ 
                    0, //(int)NUM_SCOPE_PARAMS,
                    asynInt32Mask | asynFloat64Mask | asynFloat64ArrayMask | asynEnumMask | asynDrvUserMask, /* Interface mask */
                    asynInt32Mask | asynFloat64Mask | asynFloat64ArrayMask | asynEnumMask,  /* Interrupt mask */
                    0, /* asynFlags.  This driver does not block and it is not multi-device, so flag is 0 */
                    1, /* Autoconnect */
                    0, /* Default priority */
                    0) /* Default stack size*/    
{
  asynStatus status;
  const char *functionName = "diskMonitorDriver";

  eventId_ = epicsEventCreate(epicsEventEmpty);
  /* Create the thread that computes the waveforms in the background */
  status = (asynStatus)(epicsThreadCreate("diskMonitorTask",
                        epicsThreadPriorityMedium,
                        epicsThreadGetStackSize(epicsThreadStackMedium),
                        (EPICSTHREADFUNC)::monitorTask,
                        this) == NULL);
  if (status) {
    printf("%s:%s: epicsThreadCreate failure\n", driverName, functionName);
    return;
  }
}

void diskMonitorDriver::monitorTask(void){

  double pollTime = 10.0;

  lock();

  while(1){
    unlock();
    epicsEventWaitWithTimeout(eventId_, pollTime);
    lock(); 

    fprintf(stderr, "Ping ....\n");
  }

  unlock(); // We should never get here
}

void monitorTask(void *drvPvt){
  diskMonitorDriver *pPvt = (diskMonitorDriver *)drvPvt;
  pPvt->monitorTask();
}

/* C Parts for registering with iocsh etc.... */

extern "C" {

/** EPICS iocsh callable function to call constructor for the diskMonitorDriver class.
  * \param[in] portName The name of the asyn port driver to be created.
  * \param[in] path The path of the partition to monitor 
  */

int diskMonitorDriverConfigure(const char *portName, const char *path)
{
    new diskMonitorDriver(portName, path);
    return(asynSuccess);
}


/* EPICS iocsh shell commands */

static const iocshArg initArg0 = { "portName",iocshArgString};
static const iocshArg initArg1 = { "path",iocshArgString};
static const iocshArg * const initArgs[] = {&initArg0,
                                            &initArg1};
static const iocshFuncDef initFuncDef = {"diskMonitorDriverConfigure",2,initArgs};
static void initCallFunc(const iocshArgBuf *args)
{
    diskMonitorDriverConfigure(args[0].sval, args[1].sval);
}

void diskMonitorDriverRegister(void)
{
    iocshRegister(&initFuncDef,initCallFunc);
}

epicsExportRegistrar(diskMonitorDriverRegister);

} /* extern "C" */

