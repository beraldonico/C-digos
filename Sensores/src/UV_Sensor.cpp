#include "UV_Sensor.hpp"

void Begin_UV(UV_Sensor &sensor, String Name, int PIN, int delay){
    sensor.Save_Name(Name);
    sensor.Save_Pin(PIN);
    sensor.Save_delay(delay);
#if DEBUG
    Serial.println(F("------------------------------------"));
    Serial.print(F("UV Name: ")); Serial.println(sensor.Get_Name());
    Serial.print(F("UV PIN:  ")); Serial.println(sensor.Get_Pin());
    Serial.print(F("Delay:   ")); Serial.println(sensor.Get_delay());
    Serial.println(F("------------------------------------"));
#endif
}

void Read_UV(UV_Sensor &sensor){
    //delay(sensor.Get_delay());
    sensor.Save_Pure_UV(analogRead(sensor.Get_Pin()));
    sensor.Save_UV(Convert_Value(sensor));
#if DEBUG
    Serial.println(F("------------------------------------"));
    Serial.print(F("UV Name:       ")); Serial.println(sensor.Get_Name());
    Serial.print(F("UV Pure Value: ")); Serial.println(sensor.Get_Pure_UV());
    Serial.print(F("UV Value:      ")); Serial.println(sensor.Get_UV());
    Serial.println(F("------------------------------------"));
#endif
}

int Convert_Value(UV_Sensor &sensor){
    int percentValue = 0;
    percentValue = map(sensor.Get_Pure_UV(), 0, 1000, 0, 10);
    return percentValue;
}