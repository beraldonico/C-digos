#include "defines.hpp"
#include "DHT_Sensor.hpp"
#include "LUX_Sensor.hpp"
#include "Moisture_sensor.hpp"
#include "WaterLevel_Sensor.hpp"
#include "WiFi_Module.hpp"
#include <soc/rtc_wdt.h>

DHT_Sensor DHT_22_1 = DHT_Sensor(DHT22PIN1, DHT22);
DHT_Sensor DHT_22_2 = DHT_Sensor(DHT22PIN2, DHT22);
DHT_Sensor DHT_22_3 = DHT_Sensor(DHT22PIN3, DHT22);
LUX_Sensor Lux_1;
Moisture_Sensor Moisture_1;
WaterLevel_Sensor WaterLevel_1;
WaterLevel_Sensor WaterLevel_2;

unsigned long PreviousTime;
String JSON;

const char* ssid = "MLB_2.4G";
const char* password = "Harmonia12";
const char* servername = "http://192.168.0.206:8000/greenhouse/new_read";
const char* ntpServer = "pool.ntp.org";

void setup() {
    Serial.begin(9600);
    while (!Serial) {
        delay(5);
    }
    // Initialize device.
    Wire.begin(SDAPIN, SCLPIN);
    Begin_DHT(DHT_22_1, "DHT BOT", DHT22PIN1);
    Begin_DHT(DHT_22_2, "DHT MID", DHT22PIN2);
    Begin_DHT(DHT_22_3, "DHT TOP", DHT22PIN3);
    Begin_Lux(Lux_1, "LUX", SDAPIN, SCLPIN, BH1750::CONTINUOUS_HIGH_RES_MODE, 0x23);
    Begin_Moisture(Moisture_1, "MOISTURE", MOISTUREPIN);
    Begin_WaterLevel(WaterLevel_1, "Water Level UMI", WATERLEVELPIN1, MAXANALOGWATER1, MINANALOGWATER1, WATERPIN1);
    Begin_WaterLevel(WaterLevel_2, "Water Level IRRI", WATERLEVELPIN2, MAXANALOGWATER2, MINANALOGWATER1, WATERPIN2);
    Begin_Wifi(ssid, password, ntpServer);
    beginWDT();
    PreviousTime = millis();
}

void loop() {
    rtc_wdt_feed();
    if (millis() - PreviousTime >= DELAY){
        restart_wifi();

        Serial.println("Nova Leitura! ");
        Read_DHT(DHT_22_1);
        Read_DHT(DHT_22_2);
        Read_DHT(DHT_22_3);
        Read_Lux(Lux_1);
        Read_Moisture(Moisture_1);
        Read_WaterLevel(WaterLevel_1);
        Read_WaterLevel(WaterLevel_2);
        
        JSON = Mount_JSON(DHT_22_1, DHT_22_2, DHT_22_3, Lux_1, Moisture_1, WaterLevel_1, WaterLevel_2);
        WiFi_SendPOST(JSON, servername);
        PreviousTime = millis();
    }
    else if (millis() < PreviousTime){
        PreviousTime = millis();
    }
}

void beginWDT(){
    rtc_wdt_protect_off();      //Disable RTC WDT write protection
    //Set stage 0 to trigger a system reset after 1000ms
    rtc_wdt_set_stage(RTC_WDT_STAGE0, RTC_WDT_STAGE_ACTION_RESET_SYSTEM);
    rtc_wdt_set_time(RTC_WDT_STAGE0, 10000);
    rtc_wdt_enable();           //Start the RTC WDT timer
    rtc_wdt_protect_on();       //Enable RTC WDT write protection
}