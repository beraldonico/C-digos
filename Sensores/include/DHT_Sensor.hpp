#ifndef DHTSENSOR_H
#define DHTSENSOR_H

#include "defines.hpp"

class DHT_Sensor: public DHT_Unified{
    private:
        String  sensor_name;
        float   temp_Value;
        float   RH_Value;
        int     PIN;   
        int     read_temp;
        int     read_rh;
        int32_t delay;
    public:
        DHT_Sensor(int DHTPIN, uint8_t DHTTYPE): DHT_Unified(DHTPIN, DHTTYPE){};
        void Save_Temp(float value){
            if (isnan(value)){
                this->temp_Value = 0;
                this->read_temp = 0;
            }
            else{
                this->temp_Value = value;
                this->read_temp = 1;
            }
            
        }
        void Save_RH(float value){
            if (isnan(value)){
                this->RH_Value = 0;
                this->read_rh = 0;
            }
            else{
                this->RH_Value = value;
                this->read_rh = 1;
            }
        }
        void Save_Name(String value){
            this->sensor_name = value;
        }
        void Save_Pin(int value){
            this->PIN = value;
        }
        void Save_delay(int value){
            this->delay = value;
        }
        float Get_Temp(){
            return this->temp_Value;
        }
        float Get_RH(){
            return this->RH_Value;
        }
        String Get_Name(){
            return this->sensor_name;
        }
        int Get_Pin(){
            return this->PIN;
        }
        int Get_read_temp(){
            return this->read_temp;
        }
        int Get_read_rh(){
            return this->read_rh;
        }
        int Get_dealy(){
            return this->delay;
        }
};

void Begin_DHT(DHT_Sensor &Sensor_DHT, String Name, int DHTPIN);
void Read_DHT(DHT_Sensor &Sensor_DHT);

#endif