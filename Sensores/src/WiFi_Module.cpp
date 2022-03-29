#include "WiFi_Module.hpp"

void Begin_Wifi(const char* ssid, const char* password, const char* ntpServer){
    int i = 0;
    int LED_state;
#if DEBUG
    Serial.print(F("SSID:     ")); Serial.println(ssid);
    Serial.print(F("Password: ")); Serial.println(password);
#endif
    Serial.print(F("Connecting"));
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED){
        delay(500);
        Serial.print(F("."));
        pinMode(ONBOARDLED, INPUT);
        LED_state = digitalRead(ONBOARDLED);
        pinMode(ONBOARDLED, OUTPUT);
        digitalWrite(ONBOARDLED, !LED_state);
        i++;
        if (i == 30)
            ESP.restart();
    }
    pinMode(ONBOARDLED, OUTPUT);
    digitalWrite(ONBOARDLED, LOW);
    Serial.println();
    Serial.print("Connected to WiFi network with IP Address: "); Serial.println(WiFi.localIP());
    
    configTime(0, 0, ntpServer);
}

String Mount_JSON(DHT_Sensor &DHT1, DHT_Sensor &DHT2, DHT_Sensor &DHT3, LUX_Sensor &LUX1, Moisture_Sensor &Moisture, WaterLevel_Sensor &WaterLevel1, WaterLevel_Sensor &WaterLevel2){
    String JSON = "{\"timestamp\": ";
    JSON += GetTimeStamp();

    JSON += ", \"Temp\": ";
    JSON += (DHT1.Get_Temp() + DHT2.Get_Temp() + DHT3.Get_Temp())/(DHT1.Get_read_temp() + DHT3.Get_read_temp()+ DHT3.Get_read_temp());
    JSON += ", \"RH\": ";
    JSON += (DHT1.Get_RH() + DHT2.Get_RH() + DHT3.Get_RH())/(DHT1.Get_read_rh() + DHT3.Get_read_rh()+ DHT3.Get_read_rh());
    
    JSON += ", \"Water_Level_Irrigation\": ";
    JSON += WaterLevel1.Get_Level();
    JSON += ", \"Water_Level_Umidity\": ";
    JSON += WaterLevel2.Get_Level();
    
    JSON += ", \"Soil_Moisture\": ";
    JSON += Moisture.Get_Moisture();

    JSON += ", \"LUX_Index\": ";
    JSON += LUX1.Get_Lux();
    JSON += "}";
    
    Serial.print(F("JSON: ")); Serial.println(JSON);
    return JSON;
}

void WiFi_SendPOST(String JSON, const char* &servername){
    if (WiFi.status() == WL_CONNECTED){
        WiFiClient client;
        HTTPClient http;
#if DEBUG
        Serial.print(F("ServerName: ")); Serial.println(servername);
#endif
        http.begin(client, servername);
        http.addHeader("Content-Type", "application/json");
        http.POST(JSON);
        http.end();
    }
    else{
        WiFi.disconnect();
        WiFi.reconnect();
    }
}

unsigned long GetTimeStamp() {
    time_t now;
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        return(0);
    }
    time(&now);
    return now;
}

void restart_wifi(){
    int i = 0;
    while (WiFi.status() != WL_CONNECTED){
        pinMode(ONBOARDLED, OUTPUT);
        digitalWrite(ONBOARDLED, HIGH);
        WiFi.disconnect();
        WiFi.reconnect();
        pinMode(ONBOARDLED, OUTPUT);
        digitalWrite(ONBOARDLED, LOW);
        if (i == 30)
            ESP.restart();
        i++;
    }
}