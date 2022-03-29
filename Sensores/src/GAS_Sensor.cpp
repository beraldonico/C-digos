#include "GAS_sensor.hpp"

void Begin_Gas(GAS_Sensor &Sensor_GAS, String Name, int PIN){
    Sensor_GAS.Save_Name(Name);
    Sensor_GAS.Save_Pin(PIN);
#if DEBUG
    Serial.println(F("------------------------------------"));
    Serial.print(F("GAS Name: ")); Serial.println(Sensor_GAS.Get_Name());
    Serial.print(F("GAS PIN:  ")); Serial.println(Sensor_GAS.Get_Pin());
    Serial.println(F("------------------------------------"));
#endif
}

void Read_Gas(GAS_Sensor &Sensor_GAS){
    Sensor_GAS.Save_Pure_Gas(analogRead(Sensor_GAS.Get_Pin()));
    Sensor_GAS.Save_Gas(Convert_Value(Sensor_GAS));
#if DEBUG
    Serial.println(F("------------------------------------"));
    Serial.print(F("GAS Name:       ")); Serial.println(Sensor_GAS.Get_Name());
    Serial.print(F("GAS Pure Value: ")); Serial.println(Sensor_GAS.Get_Pure_Gas());
    Serial.print(F("GAS Value:      ")); Serial.println(Sensor_GAS.Get_Gas_Quality());
    Serial.println(F("------------------------------------"));
#endif
}

String Convert_Value(GAS_Sensor &Sensor_GAS){
    int gas_value = Sensor_GAS.Get_Pure_Gas();
    if (gas_value < 100)
        return "Good";
    else if (gas_value > 100 && gas_value < 500)
        return "bad";
    return "";
}