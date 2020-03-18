#include <Adafruit_Sensor.h>
#pragma once
#include <DHT.h>
#include <DHT_U.h>

//
// Created by Max on 18-Feb-20.
//

#ifndef AIRQUALITY_HUMIDITYSENSOR_H
#define AIRQUALITY_HUMIDITYSENSOR_H

#include "constants.c"


class HumiditySensor{
        private:
          DHT* dht;

        public:
          HumiditySensor();

          /*
           * This one gives temperature in degrees celcius
           */
          float getTemperature();

          /*
           * This one gives pressure in atmospheres
           */
          float getHumidity();
};


#endif //AIRQUALITY_HUMIDITYSENSOR_H
