#include <Arduino_JSON.h>
#include "HumiditySensor.h"
#include "TransmissionModule.h"
#include "DustSensor.h"
#include "GasReader.h"
#include "constants.h"

JSONVar messageBuffer;

HumiditySensor *humiditySensor = new HumiditySensor;
TransmissionModule transmissionModule;
DustSensor *dust = new DustSensor;
GasReader *gasReader = new GasReader;
extern int message_sent = 0;

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
   Serial.println(gasReader -> get_co_concentration(analogRead(34)));
   Serial.println(analogRead(34));
   delay(300);
   messageBuffer["id"] = "CZ1";
   messageBuffer["hum"] = humidity;
   messageBuffer["tmp"] = temperature;
   messageBuffer["co"] = gasReader -> get_co_concentration(analogRead(34));
   messageBuffer["co2"] = 300 + gasReader -> get_co_concentration(analogRead(34))/2;
   messageBuffer["lpg"] = gasReader ->get_lpg_concentration(analogRead(34));
   messageBuffer["smk"] = gasReader -> get_smk_concentration(analogRead(34));
   messageBuffer["dus"] = dustConc;
   messageBuffer["aqi"] = max(dust -> get_aqi(dustConc), gasReader -> get_aqi(gasReader -> get_co_concentration(analogRead(34))));
   String stringToSend = JSON.stringify(messageBuffer);

   Serial.println(analogRead(34));
   
   

if (!transmissionModule.client.connected()) {
   transmissionModule.reconnect();
   }
   transmissionModule.client.loop();
   while(message_sent == 0){
        
        if (!transmissionModule.client.connected()) {
           transmissionModule.reconnect();
           }
           transmissionModule.client.loop();
        transmissionModule.sendMessage("secterica/heysmell/sensors_info", stringToSend.c_str());
        delay(2000);
   }
   message_sent = 0;
   Serial.println(stringToSend.c_str());
   delay(30000);
}
