#include "WaterLevel_Sensor.hpp"

void Begin_WaterLevel(WaterLevel_Sensor &Sensor_WaterLevel, String Name, int PIN, int max_analog, int min_analog, int LED_PIN){
    Sensor_WaterLevel.Save_Name(Name);
    Sensor_WaterLevel.Save_Pin(PIN);
    Sensor_WaterLevel.Save_Max(max_analog);
    Sensor_WaterLevel.Save_Min(min_analog);
    Sensor_WaterLevel.Save_LED(LED_PIN);
    pinMode(LED_PIN, OUTPUT);
#if DEBUG
    Serial.println(F("------------------------------------"));
    Serial.print(F("Water Level Name:  ")); Serial.println(Sensor_WaterLevel.Get_Name());
    Serial.print(F("Water Level PIN:   ")); Serial.println(Sensor_WaterLevel.Get_Pin());
    Serial.println(F("------------------------------------"));
#endif
}

void Read_WaterLevel(WaterLevel_Sensor &Sensor_WaterLevel){
    Sensor_WaterLevel.Save_Pure_Level(analogRead(Sensor_WaterLevel.Get_Pin()));
    Sensor_WaterLevel.Save_Level(Convert_Value(Sensor_WaterLevel));
    if (Sensor_WaterLevel.Get_Level() < 40)
        digitalWrite(Sensor_WaterLevel.Get_LED(), HIGH);
    else
        digitalWrite(Sensor_WaterLevel.Get_LED(), LOW);
#if DEBUG
    Serial.println(F("------------------------------------"));
    Serial.print(F("Water Level Name:       ")); Serial.println(Sensor_WaterLevel.Get_Name());
    Serial.print(F("Water Level Pure Value: ")); Serial.println(Sensor_WaterLevel.Get_Pure_Level());
    Serial.print(F("Water Level Value:      ")); Serial.println(Sensor_WaterLevel.Get_Level());
    Serial.println(F("------------------------------------"));
#endif
}

int Convert_Value(WaterLevel_Sensor &Sensor_WaterLevel){
    int percentValue = 0;
    percentValue = map(Sensor_WaterLevel.Get_Pure_Level(), Sensor_WaterLevel.Get_Min(), Sensor_WaterLevel.Get_Max(), 0, 100);
    return percentValue;
}