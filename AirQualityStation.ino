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
   gasReader -> rval = analogRead(0);
   Serial.println(analogRead(0));
   Serial.println(dustConc);
   delay(300);
   messageBuffer["id"] = "CZ1";
   messageBuffer["hum"] = 43; //humidity;
   messageBuffer["tmp"] = 23;// temperature;
   messageBuffer["co"] = 1;//gasReader -> get_co_concentration();
   messageBuffer["co2"] = 115; //300 + gasReader -> get_co_concentration()/2;
   messageBuffer["lpg"] = 0; //gasReader ->get_lpg_concentration();
   messageBuffer["smk"] = 1;//gasReader -> get_smk_concentration();
   messageBuffer["dus"] = dustConc;
   String stringToSend = JSON.stringify(messageBuffer);
   
   

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
