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