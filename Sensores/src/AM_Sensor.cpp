#include "AM_Sensor.hpp"

void Begin_AM(AM_Sensor &Sensor_AM){
    Sensor_AM.begin();
    sensor_t sensor;
    Sensor_AM.temperature().getSensor(&sensor);
    Sensor_AM.Save_Name(sensor.name);
    Sensor_AM.Save_Delay(sensor.min_delay / 1000);
#if DEBUG
    Serial.println(F("------------------------------------"));
    Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
    Serial.print  (F("Min Delay:   ")); Serial.print(sensor.min_delay / 1000); Serial.println(F("ms"));
    Serial.println(F("------------------------------------"));
    Serial.println(F("Temperature Sensor"));
    Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
    Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
    Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
    Serial.println(F("------------------------------------"));
    Sensor_AM.humidity().getSensor(&sensor);
    Serial.println(F("Humidity Sensor"));
    Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
    Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
    Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
    Serial.println(F("------------------------------------"));
    Serial.print  (F("AM Name:   ")); Serial.println(Sensor_AM.Get_Name());;
    Serial.print  (F("AM Delay:  ")); Serial.print(Sensor_AM.Get_Delay()); Serial.println(F("ms"));
    Serial.println(F("------------------------------------"));
#endif
}

void Read_AM(AM_Sensor &Sensor_AM){
    //delay(Sensor_AM.Get_Delay());
    sensors_event_t event;
    Sensor_AM.temperature().getEvent(&event);
    Sensor_AM.Save_Temp(event.temperature);
    Sensor_AM.humidity().getEvent(&event);
    Sensor_AM.Save_RH(event.relative_humidity);
#if DEBUG
    Serial.println(F("------------------------------------"));
    Serial.print(F("DEBUGGING of ")); Serial.println(Sensor_AM.Get_Name());
    Serial.print(F("Temperature storaged: ")); Serial.println(Sensor_AM.Get_Temp());
    Serial.print(F("Humidity storaged:    ")); Serial.println(Sensor_AM.Get_RH());
    Serial.println(F("------------------------------------"));
#endif
}