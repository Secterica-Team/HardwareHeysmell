//
// Created by Max on 17-Mar-20.
//

#include "DustSensor.h"

DustSensor::DustSensor(){
  pinMode(DUST_PIN, INPUT);
  starttime = millis(); 
}

double DustSensor::dustConcentration(){
  float ratio = 0;
  float concentration = 0;
  duration = pulseIn(DUST_PIN, LOW);
  lowpulseoccupancy = lowpulseoccupancy+duration;
  while((millis()-starttime) <= sampletime_ms)
  {
     delay(1);
  }
  ratio = lowpulseoccupancy/(sampletime_ms*10.0);  
  concentration = 1.1 * pow(ratio, 3) - 3.8 * pow(ratio, 2) + 520 * ratio + 0.62; 
  lowpulseoccupancy = 0;
  starttime = millis();
  return concentration;
}
