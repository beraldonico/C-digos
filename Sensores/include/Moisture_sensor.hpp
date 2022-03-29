#ifndef MOISTURESENSOR_H
#define MOISTURESENSOR_H

#include "defines.hpp"

class Moisture_Sensor {
    private:
        String  sensor_name;
        int     moisture_Value;
        int     moisture_Pure_Value;
        int     sensor_PIN;
    public:
        void Save_Pure_Moisture(int value){
            this->moisture_Pure_Value = value;
        }
        void Save_Moisture(int value){
            this->moisture_Value = value;
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
        uint16_t Get_Pure_Moisture(){
            return this->moisture_Pure_Value;
        }
        int Get_Moisture(){
            return this->moisture_Value;
        }
        String Get_Name(){
            return this->sensor_name;
        }
};

void Begin_Moisture(Moisture_Sensor &Sensor_Moisture, String Name, int PIN);
void Read_Moisture(Moisture_Sensor &Sensor_Moisture);
int Convert_Value(Moisture_Sensor &Sensor_Moisture);

#endif