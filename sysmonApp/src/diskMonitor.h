
#include "asynPortDriver.h"

#define P_DISK_FREE                "DISK_FREE"
#define P_DISK_USED                "DISK_USED"
#define P_DISK_TOTAL               "DISK_TOTAL"
#define P_DISK_UPDATE              "DISK_UPDATE"

void monitorTask(void *drvPvt);

class diskMonitorDriver : public asynPortDriver {
public:
  diskMonitorDriver(const char *portName, const char* path);
               
  /* These are the methods that we override from asynPortDriver */
  //virtual asynStatus writeInt32(asynUser *pasynUser, epicsInt32 value);
  //virtual asynStatus writeFloat64(asynUser *pasynUser, epicsFloat64 value);
  //virtual asynStatus readFloat64Array(asynUser *pasynUser, epicsFloat64 *value,
  //                                    size_t nElements, size_t *nIn);
  //virtual asynStatus readEnum(asynUser *pasynUser, char *strings[], int values[], int severities[],
  //                            size_t nElements, size_t *nIn);

  /* These are the methods that are new to this class */
  void monitorTask(void);

protected:
  int P_Disk_Free;
#define FIRST_DISK_COMMAND P_Disk_Free
  int P_Disk_Used;
  int P_Disk_Total;
  int P_Disk_Update;
#define LAST_DISK_COMMAND P_Disk_Update

private:
  epicsEventId eventId_;
  char fileSystemPath[256];
};

#define NUM_DISK_PARAMS (&LAST_DISK_COMMAND - &FIRST_DISK_COMMAND + 1)
