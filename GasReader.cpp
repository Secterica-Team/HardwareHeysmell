#include <Wire.h>
#include "GasReader.h"


/************************Hardware Related Macros************************************/
#define         MQ_PIN                       (0)     //define which analog input channel you are going to use
#define         RL_VALUE                     (2.5)     //define the load resistance on the board, in kilo ohms
#define         RO_CLEAN_AIR_FACTOR          (10)  //RO_CLEAR_AIR_FACTOR=(Sensor resistance in clean air)/RO,
                                                     //which is derived from the chart in datasheet

#define         READ_SAMPLE_INTERVAL         (50)    //define how many samples you are going to take in normal operation
#define         READ_SAMPLE_TIMES            (5)    

/**********************Application Related Macros**********************************/
#define         GAS_LPG                      (0)
#define         GAS_CO                       (1)
#define         GAS_SMOKE                    (2)
/*****************************Globals***********************************************/
float           LPGCurve[3]  =  {2.3,0.21,-0.47};
float           COCurve[3]  =  {2.3,0.72,-0.34};    
float           SmokeCurve[3] ={2.3,0.53,-0.44};                                                          
float           Ro           =  0.4;               




float MQResistanceCalculation(int raw_adc)
{
  return ( ((float)RL_VALUE*(4095-raw_adc)/raw_adc));
}


float MQRead(int mq_pin)
{
  int i;
  float rs=0;

  for (i=0;i<READ_SAMPLE_TIMES;i++) {
    rs += MQResistanceCalculation(analogRead(mq_pin));
    delay(READ_SAMPLE_INTERVAL);
  }

  rs = rs/READ_SAMPLE_TIMES;

  return rs;  
}

int  MQGetPercentage(float rs_ro_ratio, float *pcurve)
{
  return (pow(10,( ((log(rs_ro_ratio)-pcurve[1])/pcurve[2]) + pcurve[0])));
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



int GasReader::get_lpg_concentration(){
  return MQGetGasPercentage(MQRead(MQ_PIN)/Ro,GAS_LPG);
}

int GasReader::get_co_concentration(){
  return MQGetGasPercentage(MQRead(MQ_PIN)/Ro,GAS_CO);
}

int GasReader::get_smk_concentration(){
  return MQGetGasPercentage(MQRead(MQ_PIN)/Ro,GAS_SMOKE);
}
