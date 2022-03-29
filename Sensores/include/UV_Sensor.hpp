#ifndef UVSENSOR_H
#define UVSENSOR_H

#include "defines.hpp"

class UV_Sensor {
    private:
        String  sensor_name;
        int     UV_Value;
        int     UV_Pure_Value;
        int     sensor_PIN;
        int     delay;
    public:
        void Save_Pure_UV(uint16_t value){
            this->UV_Pure_Value = value;
        }
        void Save_delay(int value){
            this->delay = value;
        }
        void Save_UV(int value){
            this->UV_Value = value;
        }
        void Save_Name(String value){
            this->sensor_name = value;
        }
        void Save_Pin(int value){
            this->sensor_PIN = value;
        }
        int Get_Pin(){
            return this->sensor_PIN;
        }
        int Get_Pure_UV(){
            return this->UV_Pure_Value;
        }
        int Get_UV(){
            return this->UV_Value;
        }
        String Get_Name(){
            return this->sensor_name;
        }
        int Get_delay(){
            return this->delay;
        }
};

void Begin_UV(UV_Sensor &sensor, String Name, int PIN, int delay);
void Read_UV(UV_Sensor &sensor);
int Convert_Value(UV_Sensor &sensor);

#endif