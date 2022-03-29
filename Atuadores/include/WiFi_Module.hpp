#ifndef WIFIMODULE_H
#define WIFIMODULE_H

#include "defines.hpp"

void Begin_Wifi(const char* ssid, const char* password, const char* ntpServer);
unsigned long GetTimeStamp();
void restart_wifi();

#endif