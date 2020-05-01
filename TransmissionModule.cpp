//
// Created by Max on 04-Mar-20.
//

#include "TransmissionModule.h"

/**
 * Ability to setup the wifi client
 */

void TransmissionModule::setup_wifi(){
 delay(1000);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(NETWORK_SSID);

  WiFi.begin(NETWORK_SSID, PASSWORD);

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


/**
 * Sends a message to the client
 */

void TransmissionModule::sendMessage(char* topic,const char* message){
  this -> client.publish(topic, message);
  Serial.println("Trying to publish...");
  Serial.println();
}

TransmissionModule::TransmissionModule(){
    Serial.begin(9600);
    WiFiClient espClient;
    this -> client = PubSubClient(this -> eClient);
    this -> setup_wifi();
    client.setServer(MQTT_SERVER, 1883);
  }



void TransmissionModule::init(){
  Serial.begin(9600);
  this -> client = PubSubClient(this -> eClient);
  this -> setup_wifi();
  this -> client.setServer(MQTT_SERVER, 1883);
  this -> client.setCallback(callback);
}
/**
 * An ability to reconnect
 */
void TransmissionModule::reconnect(){
   while (!this -> client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Subscribe
      this -> client.subscribe("secterica/heysmell/sensors_info");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}



void TransmissionModule::callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  message_sent = 1;
  Serial.println();
  }
//}
