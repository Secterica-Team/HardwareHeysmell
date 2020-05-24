
#include "GasReader.h"


/************************Hardware Related Macros************************************/
#define         MQ_PIN                       (34)     //define which analog input channel you are going to use
#define         RL_VALUE                     (2.7)     //define the load resistance on the board, in kilo ohms
#define         RO_CLEAN_AIR_FACTOR          (10)  //RO_CLEAR_AIR_FACTOR=(Sensor resistance in clean air)/RO,
                                                     //which is derived from the chart in datasheet

#define         READ_SAMPLE_INTERVAL         (50)    //define how many samples you are going to take in normal operation
#define         READ_SAMPLE_TIMES            (5)    

/**********************Application Related Macros**********************************/
#define         GAS_LPG                      (0)
#define         GAS_CO                       (1)
#define         GAS_SMOKE                    (2)
/*****************************Globals***********************************************/
float           COCurve[2]  =  {-3.46,4.725};  
float           LPGCurve[2]  =  {-2.06, 2.794};                                                        
float           SmokeCurve[2] ={-1.97, 2.89};                                                        
float           Ro           =  3.2;
int             read_value   =  0;               




float MQResistanceCalculation(float raw_adc)
{
  return ( ((float)RL_VALUE*((6024-raw_adc)/raw_adc)));
}

float MQRead(int mq_pin)
{
  int i;
  float rs=0;

  for (i=0;i<READ_SAMPLE_TIMES;i++) {
    rs += MQResistanceCalculation(read_value);
    delay(READ_SAMPLE_INTERVAL);
  }

  rs = rs/READ_SAMPLE_TIMES;

  return rs;  
}

int  MQGetPercentage(float rs_ro_ratio, float *pcurve)
{
  
  return (pow(10, ((log(rs_ro_ratio)*pcurve[0]) + pcurve[1])));
}

int MQGetGasPercentage(float rs_ro_ratio, int gas_id)
{
  if ( gas_id == GAS_LPG ) {
     return MQGetPercentage(rs_ro_ratio,LPGCurve);
  } else if ( gas_id == GAS_CO ) {
     return MQGetPercentage(rs_ro_ratio,COCurve);
  } else if ( gas_id == GAS_SMOKE ) {
     return MQGetPercentage(rs_ro_ratio,SmokeCurve);
  }    

  return 0;
}



int GasReader::get_lpg_concentration(int val){
  read_value = val;
  return MQGetGasPercentage((MQRead(MQ_PIN)/Ro),GAS_LPG);
}

int GasReader::get_co_concentration(int val){
  read_value = val;
  Serial.println(read_value);
  return MQGetGasPercentage(MQRead(MQ_PIN)/Ro,GAS_CO);
}

int GasReader::get_smk_concentration(int val){
  read_value = val;
  return MQGetGasPercentage(MQRead(MQ_PIN)/Ro,GAS_SMOKE);
}


static struct aqi {
    float clow;
    float chigh;
    int llow;
    int lhigh;
} aqi[] = {
  {0.0,    4.4,   0, 50},
  {4.5,   9.4,  51, 100},
  {9.5,   12.4, 101, 150},
  {12.5,  15.4, 151, 200},
  {15.5, 30.4, 201, 300},
  {30.5, 40.4, 301, 350},
  {40.5, 50.4, 401, 500},
};

int GasReader::get_aqi(int concentration){
  int i;

  for (i = 0; i < 7; i++) {
    if (concentration >= aqi[i].clow &&
        concentration <= aqi[i].chigh) {
        // Ip =  [(Ihi-Ilow)/(BPhi-BPlow)] (Cp-BPlow)+Ilow,
        return ((aqi[i].lhigh - aqi[i].llow) / (aqi[i].chigh - aqi[i].clow)) * 
            (concentration - aqi[i].clow) + aqi[i].llow;
    } else if (i == 6) return 500;
  }
  

  return 0;
}
