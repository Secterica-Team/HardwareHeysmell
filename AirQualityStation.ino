#include <Arduino_JSON.h>
#include "HumiditySensor.h"
#include "TransmissionModule.h"
#include "DustSensor.h"
#include "GasReader.h"

JSONVar messageBuffer;

HumiditySensor *humiditySensor = new HumiditySensor;
TransmissionModule transmissionModule;
DustSensor *dust = new DustSensor;
GasReader gasReader;

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
   Serial.println(dustConc);
   delay(300);
   messageBuffer["id"] = "CZ1";
   messageBuffer["hum"] = humidity;
   messageBuffer["tmp"] = temperature;
   messageBuffer["co"] = gasReader.readGasValue();
   messageBuffer["co2"] = 10;
   messageBuffer["lpg"] = 300;
   messageBuffer["smk"] = 20;
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
