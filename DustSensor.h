#include <ArduinoOTA.h>

//
// Created by Max on 17-Mar-20.
//

#ifndef AIRQUALITY_DUSTSENSOR_H
#define AIRQUALITY_DUSTSENSOR_H

#include "constants.h"


class DustSensor {
  private:
  unsigned long duration;
  unsigned long starttime;
  unsigned long sampletime_ms = 2000; 
  unsigned long lowpulseoccupancy = 0;
 
  public:
  DustSensor();
  double dustConcentration();

};


#endif //AIRQUALITY_DUSTSENSOR_H
