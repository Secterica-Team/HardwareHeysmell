
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

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
