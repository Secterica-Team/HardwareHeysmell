//
// Created by Max on 17-Mar-20.
//

#include "DustSensor.h"

DustSensor::DustSensor(){
  pinMode(DUST_PIN, INPUT);
  starttime = millis(); 
  Serial.begin(9600);
}

double pcs2ugm3 (double concentration_pcs)
{
    double pi = 3.14159;
    // All particles are spherical, with a density of 1.65E12 µg/m3
    double density = 1.65 * pow (10, 12);
    // The radius of a particle in the PM2.5 channel is .44 µm
    double r25 = 0.44 * pow (10, -6);
    double vol25 = (4/3) * pi * pow (r25, 3);
    double mass25 = density * vol25; // ug
    double K = 3531.5; // per m^3 

    return concentration_pcs * K * mass25;
}

double DustSensor::dustConcentration(){
  pinMode(DUST_PIN, INPUT);
  starttime = millis();
    duration = pulseIn(DUST_PIN, LOW);
    lowpulseoccupancy = lowpulseoccupancy+duration;
    while (true){
      lowpulseoccupancy = lowpulseoccupancy+duration;
      duration = pulseIn(DUST_PIN, LOW);
      if ((millis()-starttime) >= sampletime_ms)//if the sampel time == 30s
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
          return pcs2ugm3(concentration);
      }
    else continue;
    }
    return 0;
}



static struct aqi {
    float clow;
    float chigh;
    int llow;
    int lhigh;
} aqi[] = {
  {0.0,    12.4,   0, 50},
  {12.1,   35.4,  51, 100},
  {35.5,   55.4, 101, 150},
  {55.5,  150.4, 151, 200},
  {150.5, 250.4, 201, 300},
  {250.5, 350.4, 301, 350},
  {350.5, 500.4, 401, 500},
};

int DustSensor::get_aqi (double ugm3)
{
  int i;

  for (i = 0; i < 7; i++) {
    if (ugm3 >= aqi[i].clow &&
        ugm3 <= aqi[i].chigh) {
        // Ip =  [(Ihi-Ilow)/(BPhi-BPlow)] (Cp-BPlow)+Ilow,
        return ((aqi[i].lhigh - aqi[i].llow) / (aqi[i].chigh - aqi[i].clow)) * 
            (ugm3 - aqi[i].clow) + aqi[i].llow;
    }
  }

  return 0;
}
