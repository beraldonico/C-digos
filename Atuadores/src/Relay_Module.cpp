#include "Relay_Module.hpp"

void relayReset(int *relaypins, int *relaystate){
    for(int i = 0; i < NUM_RELAYS; i++){
        pinMode(relaypins[i], OUTPUT);
        if(RELAY_NO){
            digitalWrite(relaypins[i], HIGH);
            relaystate[i] = HIGH;
        }
        else{
            digitalWrite(relaypins[i], LOW);
            relaystate[i] = LOW;
        }
    }
}

void relayState(int *relaypins, int *relaystate){
    Serial.println(F("--------------------------------")); 
    for (int i = 0; i < NUM_RELAYS; i++){
        digitalWrite(relaypins[i], relaystate[i]);
        Serial.print(F("i:         ")); Serial.println(i);
        Serial.print(F("Pino:      ")); Serial.println(relaypins[i]);
        Serial.print(F("Estado:    ")); Serial.println(relaystate[i]);
        Serial.println(F("--------------------------------")); 
    }
}