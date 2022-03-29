#include "DHT_Sensor.hpp"

void Begin_DHT(DHT_Sensor &Sensor_DHT, String Name, int DHTPIN){
    Sensor_DHT.begin();
    Sensor_DHT.Save_Name(Name);
    Sensor_DHT.Save_Pin(DHTPIN);
    sensor_t sensor;
    Sensor_DHT.temperature().getSensor(&sensor);
    Sensor_DHT.Save_Pin(sensor.min_delay);
#if DEBUG
    sensor_t sensor;
    Sensor_DHT.temperature().getSensor(&sensor);
    Serial.println(F("------------------------------------"));
    Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
    Serial.println(F("------------------------------------"));
    Serial.println(F("Temperature Sensor"));
    Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
    Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
    Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
    Serial.println(F("------------------------------------"));
    Sensor_DHT.humidity().getSensor(&sensor);
    Serial.println(F("Humidity Sensor"));
    Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
    Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
    Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
    Serial.println(F("------------------------------------"));
    Serial.print  (F("DHT Name:   ")); Serial.println(Sensor_DHT.Get_Name());
    Serial.print  (F("DHT Pin:    ")); Serial.println(Sensor_DHT.Get_Pin());
    Serial.println(F("------------------------------------"));
#endif
}

void Read_DHT(DHT_Sensor &Sensor_DHT){
    delay(Sensor_DHT.Get_dealy());
    sensors_event_t event;
    Sensor_DHT.temperature().getEvent(&event);
    Sensor_DHT.Save_Temp(event.temperature);
    delay(10);
    Sensor_DHT.humidity().getEvent(&event);
    Sensor_DHT.Save_RH(event.relative_humidity);
#if DEBUG
    Serial.println(F("------------------------------------"));
    Serial.print(F("DEBUGGING of ")); Serial.println(Sensor_DHT.Get_Name());
    Serial.print(F("Temperature storaged: ")); Serial.println(Sensor_DHT.Get_Temp());
    Serial.print(F("Humidity storaged:    ")); Serial.println(Sensor_DHT.Get_RH());
    Serial.println(F("------------------------------------"));
#endif
}