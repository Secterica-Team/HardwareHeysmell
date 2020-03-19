#include <ETH.h>
#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <WiFiGeneric.h>
#include <WiFiMulti.h>
#include <WiFiScan.h>
#include <WiFiServer.h>
#include <WiFiSTA.h>
#include <WiFiType.h>
#include <WiFiUdp.h>

#include <dummy.h>

#ifndef AIRQUALITY_TRANSMISSIONMODULE_H
#define AIRQUALITY_TRANSMISSIONMODULE_H

#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

//
// Created by Max on 04-Mar-20.
//



#pragma once


#include "constants.h"




class TransmissionModule {
  private:
  WiFiClient eClient;
  

  public:
  void setup_wifi();
  void reconnect();
  void sendMessage(char* topic, const char* message);
  void init();
  static void callback(char* topic, byte* message, unsigned int length);

  PubSubClient client;
  
  TransmissionModule();
  

};


#endif //AIRQUALITY_TRANSMISSIONMODULE_H
