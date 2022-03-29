#include "Moisture_sensor.hpp"

void Begin_Moisture(Moisture_Sensor &Sensor_Moisture, String Name, int PIN){
    Sensor_Moisture.Save_Name(Name);
    Sensor_Moisture.Save_Pin(PIN);
#if DEBUG
    Serial.println(F("------------------------------------"));
    Serial.print(F("Moisture Name: ")); Serial.println(Sensor_Moisture.Get_Name());
    Serial.print(F("Moisture PIN:  ")); Serial.println(Sensor_Moisture.Get_Pin());
    Serial.println(F("------------------------------------"));
#endif
}

void Read_Moisture(Moisture_Sensor &Sensor_Moisture){
    Sensor_Moisture.Save_Pure_Moisture(analogRead(Sensor_Moisture.Get_Pin()));
    Sensor_Moisture.Save_Moisture(Convert_Value(Sensor_Moisture));
#if DEBUG
    Serial.println(F("------------------------------------"));
    Serial.print(F("Moisture Name:       ")); Serial.println(Sensor_Moisture.Get_Name());
    Serial.print(F("Moisture Pure Value: ")); Serial.println(Sensor_Moisture.Get_Pure_Moisture());
    Serial.print(F("Moisture Value:      ")); Serial.println(Sensor_Moisture.Get_Moisture());
    Serial.println(F("------------------------------------"));
#endif
}

int Convert_Value(Moisture_Sensor &Sensor_Moisture){
    int percentValue = 0;
    percentValue = map(Sensor_Moisture.Get_Pure_Moisture(), MOISTUREMIN, MOISTUREMAX, 0, 100);
    return percentValue;
}