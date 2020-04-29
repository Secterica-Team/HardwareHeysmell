#include <Wire.h>


//
// Created by maxley on 30/04/2020.
//

#include "GasReader.h"

long GasReader::readGasValue(){
  return analogRead(GAS_MQ2_PIN);
}
