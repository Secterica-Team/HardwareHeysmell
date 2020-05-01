//
// Created by maxley on 30/04/2020.
//

#ifndef PERMUTATION_GEN_GASREADER_H
#define PERMUTATION_GEN_GASREADER_H
#include "constants.h"
#pragma once


class GasReader {
   public:
  int get_lpg_concentration();
  int get_co_concentration();
  int get_smk_concentration();
  int rval;
  
};


#endif 
