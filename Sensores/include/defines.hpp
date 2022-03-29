#ifndef DEFINES_H
#define DEFINES_H

#define ONBOARDLED 2
#define DHT22PIN1 32
#define DHT22PIN2 33
#define DHT22PIN3 25
#define SCLPIN 22
#define SDAPIN 21

#define MOISTUREPIN 35
#define MOISTUREMAX 1000
#define MOISTUREMIN 4095

#define WATERLEVELPIN1 34
#define MAXANALOGWATER1 2000
#define MINANALOGWATER1 0
#define WATERPIN1 26

#define WATERLEVELPIN2 39
#define MAXANALOGWATER2 2000
#define MINANALOGWATER2 0
#define WATERPIN2 27

#define DEBUG 0
#define DELAY 5000

#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <DHT.h>
#include <DHT_U.h>
#include <BH1750.h>
#include <WiFi.h>
#include <HTTPClient.h>

void beginWDT();

#endif