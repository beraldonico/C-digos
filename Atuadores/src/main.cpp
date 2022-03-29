#include "defines.hpp"
#include "Relay_Module.hpp"
#include "WiFi_Module.hpp"
#include <soc/rtc_wdt.h>

// Assign each GPIO to a relay
int relaypins[NUM_RELAYS] = {HEATERPIN, ACPIN, LIGHTPIN, HUMIDIFIERPIN, VENTILATIONPIN, IRRIGATIONPIN, HEATERVENTILATIONPIN, ACVENTILATIONPIN};
int relaystate[NUM_RELAYS];

// Replace with your network credentials
const char* ssid = "MLB_2.4G";
const char* password = "Harmonia12";
const char* ntpServer = "pool.ntp.org";
AsyncWebServer server(PORT);

void notFound(AsyncWebServerRequest *request){
    request->send(404, "application/json", "{\"message\":\"Not found\"}");
}

void setup(){
    Serial.begin(9600);
    relayReset(relaypins, relaystate);
    Begin_Wifi(ssid, password, ntpServer);

    // Route for root / web page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "application/json", "{\"message\":\"Welcome\"}"); });

    server.on("/action", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                    // Send a GET request to <ESP_IP>/action?heater=on&AC=on&light=off&humidifier=on&ventilation=on&irrigation=on
                    int params = request->params();
                    for (int i = 0; i < params; i++){
#if DEBUG
                        Serial.println(F("--------------------------------")); 
                        Serial.println(F("nova demanda !!!"));
                        Serial.print(F("i:         ")); Serial.println(i);
                        Serial.print(F("Pino:      ")); Serial.println(relaypins[i]);
                        Serial.print(F("Old state: ")); Serial.println(relaystate[i]);
                        Serial.print(F("Valor:     ")); Serial.println(request->getParam(i)->value());
#endif
                        if (request->getParam(i)->value() == "on"){
                            relaystate[i] = LOW;
                            if (i == 0 || i == 1) {
                                Serial.println(F("liga ventilador")); 
                                relaystate[i + 6] = LOW;
                            }
                        }
                        else if (request->getParam(i)->value() == "off"){
                            relaystate[i] = HIGH;
                            if (i == 0 || i == 1){
                                relaystate[i + 6] = HIGH;
                                Serial.println(F("desliga ventilador"));
                            }
                        }
#if DEBUG
                        Serial.print(F("New state: ")); Serial.println(relaystate[i]);
                        Serial.println(F("--------------------------------")); 
#endif
                    }
                    relayState(relaypins, relaystate);
                    request->send(200, "text/plain", "OK");
              });
    server.onNotFound(notFound);
    server.begin();
}
  
void loop() {
    rtc_wdt_feed();
    restart_wifi();
}

void beginWDT(){
    rtc_wdt_protect_off();      //Disable RTC WDT write protection
    //Set stage 0 to trigger a system reset after 1000ms
    rtc_wdt_set_stage(RTC_WDT_STAGE0, RTC_WDT_STAGE_ACTION_RESET_SYSTEM);
    rtc_wdt_set_time(RTC_WDT_STAGE0, 5000);
    rtc_wdt_enable();           //Start the RTC WDT timer
    rtc_wdt_protect_on();       //Enable RTC WDT write protection
}