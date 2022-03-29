#ifndef DEFINES_H
#define DEFINES_H

#define DEBUG 0
#define PORT 8000
// Set to true to define Relay as Normally Open (NO)
#define RELAY_NO true
#define NUM_RELAYS 8
#define ONBOARDLED 2

#define HEATERPIN 33 //peltier down rele 4 /
#define HEATERVENTILATIONPIN 12 //fan down rele 7
#define ACPIN 32 // peltier up rele 1
#define ACVENTILATIONPIN 14 //fan up rele 6
#define LIGHTPIN 25 //lux rele 2
#define HUMIDIFIERPIN 13 //umi rele 8
#define VENTILATIONPIN 27 //fan 12 V rele 5
#define IRRIGATIONPIN 26 //irri rele 3

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
//#include <ArduinoJson.h>
//#include <AsyncJson.h>
void beginWDT();

#endif