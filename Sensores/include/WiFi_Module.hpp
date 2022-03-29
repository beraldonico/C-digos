#ifndef WIFIMODULE_H
#define WIFIMODULE_H

#include "defines.hpp"
#include "DHT_Sensor.hpp"
#include "GAS_Sensor.hpp"
#include "LUX_Sensor.hpp"
#include "Moisture_sensor.hpp"
#include "WaterLevel_Sensor.hpp"
#include "WiFi_Module.hpp"

void Begin_Wifi(const char* ssid, const char* password, const char* ntpServer);
String Mount_JSON(DHT_Sensor &DHT1, DHT_Sensor &DHT2, DHT_Sensor &DHT3, LUX_Sensor &LUX1, Moisture_Sensor &Moisture, WaterLevel_Sensor &WaterLevel1, WaterLevel_Sensor &WaterLevel2);
void WiFi_SendPOST(String JSON, const char* &servername);
unsigned long GetTimeStamp();
void restart_wifi();

#endif