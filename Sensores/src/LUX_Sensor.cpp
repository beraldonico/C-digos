#include "LUX_Sensor.hpp"

void Begin_Lux(LUX_Sensor &Sensor_LUX, String Name, int SDA, int SCL, BH1750::Mode mode, byte addr){
    Sensor_LUX.begin(mode, addr);
    Sensor_LUX.Save_Name(Name);
    Sensor_LUX.Save_Pin(SDA, SCL);
#if DEBUG
    Serial.println(F("------------------------------------"));
    Serial.print(F("LUX Name: ")); Serial.println(Sensor_LUX.Get_Name());
    Serial.print(F("LUX SDA:  ")); Serial.println(Sensor_LUX.Get_SDA());
    Serial.print(F("LUX SCL:  ")); Serial.println(Sensor_LUX.Get_SCL());
    Serial.print(F("LUX Mode: 0x")); Serial.println(mode, HEX);
    Serial.print(F("LUX addr: 0x")); Serial.println(addr, HEX);
    Serial.println(F("------------------------------------"));
#endif
}

void Read_Lux(LUX_Sensor &Sensor_LUX){
    Sensor_LUX.Save_Lux(Sensor_LUX.readLightLevel());
#if DEBUG
    Serial.println(F("------------------------------------"));
    Serial.print(F("DEBUGGING of ")); Serial.println(Sensor_LUX.Get_Name());
    Serial.print(F("LUX Index storaged: ")); Serial.println(Sensor_LUX.Get_Lux());
    Serial.println(F("------------------------------------"));
#endif
}