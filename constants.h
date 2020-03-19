//
// Created by Max on 09-Mar-20.
//

#ifndef AIRQUALITY_CONSTANTS_H
#define AIRQUALITY_CONSTANTS_H

#define HUMIDITY TRUE
#define WIFITRANSMITTER TRUE
#define DUST TRUE

#pragma once


/**
 * CONSTANTS FOR HUMIDITY SENSOR DHT
 * You can change the type whether you use another dht
 * The basic pin is any
 * , better not use 15
 */
#ifdef HUMIDITY

#define DHTTYPE DHT11
#define DHTPIN  3
#endif
/**
 * CONSTANTS FOR BMP-180 PRESSURE
 */
#ifdef PRESSURE
#endif

/**
 * CONSTANTS FOR AMN-21 VIBRAION
 */
#ifdef VIBRATION
#endif

#ifdef CLOCK
#endif

/**
 * CONSTANTS FOR PPD42 
 */

#ifdef DUST
#define DUST_PIN 16
#endif

#ifdef MQ2
#endif

#ifdef MQ9B
#endif

#ifdef WIFITRANSMITTER

#define PASSWORD "IDontLikeWhiskas"
#define NETWORK_SSID "TheFatGrayCat"
#define MQTT_SERVER "broker.hivemq.com"
#endif

#endif //AIRQUALITY_CONSTANTS_H
