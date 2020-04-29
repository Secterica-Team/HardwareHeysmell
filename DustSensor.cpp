//
// Created by Max on 17-Mar-20.
//

#include "DustSensor.h"

DustSensor::DustSensor(){
  pinMode(DUST_PIN, INPUT);
  starttime = millis(); 
  Serial.begin(9600);
}

double DustSensor::dustConcentration(){
  pinMode(DUST_PIN, INPUT);
  starttime = millis();
//  starttime = millis(); 
//  float ratio = 0;
//  float concentration = 0;
//  duration = pulseIn(DUST_PIN, LOW);
//  lowpulseoccupancy = lowpulseoccupancy+duration;
//  int timespend = millis() - starttime;
//  Serial.println("Some time dust");
//  ratio = lowpulseoccupancy/(timespend*10.0);  
//  concentration = 1.1 * pow(ratio, 3) - 3.8 * pow(ratio, 2) + 520 * ratio + 0.62; 
//  lowpulseoccupancy = 0;
//  return concentration;
    duration = pulseIn(DUST_PIN, LOW);
    lowpulseoccupancy = lowpulseoccupancy+duration;
    while (true){
    lowpulseoccupancy = lowpulseoccupancy+duration;
    duration = pulseIn(DUST_PIN, LOW);
    if ((millis()-starttime) > sampletime_ms)//if the sampel time == 30s
    {
        float ratio = lowpulseoccupancy/(sampletime_ms*10.0);  // Integer percentage 0=>100
        float concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
        Serial.print(lowpulseoccupancy);
        Serial.print(",");
        Serial.print(ratio);
        Serial.print(",");
        Serial.println(concentration);
        lowpulseoccupancy = 0;
        starttime = millis();
        return concentration;
    }
    else continue;
    }
    return 0;
}
