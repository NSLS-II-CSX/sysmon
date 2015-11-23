
#include "asynPortDriver.h"

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

private:
  epicsEventId eventId_;
};


