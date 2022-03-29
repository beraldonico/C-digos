#ifndef AMSENSOR_H
#define AMSENSOR_H

#include "defines.hpp"
#include <Adafruit_AM2320.h>
#include <SPI.h>

class AM_Sensor: public Adafruit_AM2320{
    private:
        String  sensor_name;
        float   temp_Value;
        float   RH_Value;
        uint32_t delayMS;
    public:
        AM_Sensor():Adafruit_AM2320(){};
        void Save_Temp(float value){
            this->temp_Value = !isnan(value) ? value : -1000;
        }
        void Save_RH(float value){
            this->RH_Value = !isnan(value) ? value : -1000;
        }
        void Save_Name(char *value){
            this->sensor_name = value;
        }
        void Save_Delay(uint32_t value){
            this->delayMS = value;
        }
        uint32_t Get_Delay(){
            return this->delayMS;
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
};

void Begin_AM(AM_Sensor &Sensor_AM);
void Read_AM(AM_Sensor &Sensor_AM);

#endif