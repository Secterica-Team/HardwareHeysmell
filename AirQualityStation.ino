#include <Arduino_JSON.h>
#include "HumiditySensor.h"
#include "TransmissionModule.h"
#include "DustSensor.h"

JSONVar messageBuffer;

HumiditySensor *humiditySensor = new HumiditySensor;
TransmissionModule transmissionModule;
DustSensor *dust = new DustSensor;

void setup() {
   Serial.begin(9600);
   delay(300);
   transmissionModule.setup_wifi();
   transmissionModule.init();
}

void loop() {
   double temperature = (humiditySensor -> getTemperature());
   double humidity = (humiditySensor -> getHumidity());
   double dustConc = dust -> dustConcentration();
   Serial.println(" %");
   
   
   delay(300);
   messageBuffer["loc"] = "Chernivtsi";
   messageBuffer["temp"] = temperature;
   messageBuffer["hu"] = humidity;
   messageBuffer["dus"] = dustConc;
   String stringToSend = JSON.stringify(messageBuffer);
   
   

if (!transmissionModule.client.connected()) {
   transmissionModule.reconnect();
   }
   transmissionModule.client.loop();
   
   transmissionModule.sendMessage("secterica/heysmell/sensors_info", stringToSend.c_str());
   Serial.println(stringToSend.c_str());
   delay(3000);
}
