#include <Arduino_JSON.h>
#include "HumiditySensor.h"
#include "TransmissionModule.h"
#include "DustSensor.h"
#include "GasReader.h"
#include "constants.h"

JSONVar messageBuffer;

#define uS_TO_S_FACTOR 1000000  //Conversion factor for micro seconds to seconds
#define TIME_TO_SLEEP  300       //Time ESP32 will go to sleep (in seconds)

RTC_DATA_ATTR int bootCount = 0;

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
   esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
}

void loop() {
    
  
   double temperature = (humiditySensor -> getTemperature());
   double humidity = (humiditySensor -> getHumidity());
   double dustConc = dust -> dustConcentration();
   double co_conc = gasReader -> get_co_concentration(analogRead(34));
   Serial.println(gasReader -> get_co_concentration(analogRead(34)));
   Serial.println(dustConc);
   int val2 = dustConc * 100;
   dustConc = (double) val2/100;
   delay(300);
   messageBuffer["id"] = "CZ1";
   messageBuffer["hum"] = humidity;
   messageBuffer["tmp"] = temperature;
   messageBuffer["co"] = co_conc;
   messageBuffer["co2"] = gasReader -> get_smk_concentration(analogRead(34))/2;
   messageBuffer["lpg"] = gasReader ->get_lpg_concentration(analogRead(34));
   messageBuffer["smk"] = gasReader -> get_smk_concentration(analogRead(34));
   messageBuffer["dus"] = dustConc;
   messageBuffer["aqi"] = max(dust -> get_aqi(dustConc), gasReader -> get_aqi(co_conc));
   String stringToSend = JSON.stringify(messageBuffer);

   Serial.println(analogRead(34));
   Serial.println(stringToSend.c_str());

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
   esp_deep_sleep_start();
}
