#include "HumiditySensor.h"
#include "TransmissionModule.h"
#include "DustSensor.h"

//HumiditySensor *humiditySensor = new HumiditySensor;
TransmissionModule transmissionModule;
DustSensor dust;

void setup() {
   Serial.begin(9600);
   delay(300);
   transmissionModule.setup_wifi();
   transmissionModule.init();
}

void loop() {
  /* Serial.print(humiditySensor -> getTemperature());
   Serial.println(" C");
   Serial.print(humiditySensor -> getHumidity());
   Serial.println(" %");
   
   
   delay(300);*/

if (!transmissionModule.client.connected()) {
   transmissionModule.reconnect();
   }
   transmissionModule.client.loop();
   
   transmissionModule.sendMessage("secterica/heysmell/sensors_info", "Some spam");
   transmissionModule.client.publish("secterica/heysmell/sensors_info", "Some spam 2");
   delay(3000);
}
