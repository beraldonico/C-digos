#ifndef GASSENSOR_H
#define GASSENSOR_H

#include "defines.hpp"

class GAS_Sensor {
    private:
        String  sensor_name;
        String  gas_Value;
        int     gas_Pure_Value;
        int     sensor_PIN;
    public:
        void Save_Pure_Gas(int value){
            this->gas_Pure_Value = value;
        }
        void Save_Gas(String value){
            this->gas_Value = value;
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
        uint16_t Get_Pure_Gas(){
            return this->gas_Pure_Value;
        }
        String Get_Gas_Quality(){
            return this->gas_Value;
        }
        String Get_Name(){
            return this->sensor_name;
        }
};

void Begin_Gas(GAS_Sensor &Sensor_GAS, String Name, int PIN);
void Read_Gas(GAS_Sensor &Sensor_GAS);
String Convert_Value(GAS_Sensor &Sensor_GAS);

#endif