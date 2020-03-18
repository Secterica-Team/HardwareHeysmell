//
// Created by Max on 18-Feb-20.
//

#include "HumiditySensor.h"
#include <DHT.h>
#include <DHT_U.h>

//
// Created by Max on 18-Feb-20.
//

#include "constants.h"


HumiditySensor::HumiditySensor(){
   dht = new DHT(DHTPIN, DHTTYPE);
   dht -> begin();
}

float HumiditySensor::getTemperature(){
   float humidity = dht -> readHumidity();
   float temperatureAbstract = dht -> readTemperature();
   float realTemperature;

   if (!isnan(humidity) && !isnan(temperatureAbstract))
   {
      realTemperature = dht -> computeHeatIndex(temperatureAbstract, humidity, false);
   }
   return temperatureAbstract;
}

float HumiditySensor::getHumidity(){
    float humidity = dht -> readHumidity();
     if (!isnan(humidity))
        {
           return humidity;
        }
     return 0;
}
