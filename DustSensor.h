#include <ArduinoOTA.h>

//
// Created by Max on 17-Mar-20.
//

#ifndef AIRQUALITY_DUSTSENSOR_H
#define AIRQUALITY_DUSTSENSOR_H

#define DUST_PIN 12


class DustSensor {
  private:
  unsigned long duration;
  unsigned long starttime;
  unsigned long sampletime_ms = 10000; 
  unsigned long lowpulseoccupancy = 0;
 
  public:
  DustSensor();
  double dustConcentration();
  int get_aqi(double val);

};


#endif //AIRQUALITY_DUSTSENSOR_H
