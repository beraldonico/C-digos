#ifndef LUXSENSOR_H
#define LUXSENSOR_H

#include "defines.hpp"

class LUX_Sensor: public BH1750{
    private:
        String  sensor_name;
        float   Lux_Value;
        int     SDA;
        int     SCL;
    public:
        LUX_Sensor():BH1750(){};
        void Save_Lux(float value){
            this->Lux_Value = !isnan(value) ? value : 0;
        }
        void Save_Name(String value){
            this->sensor_name = value;
        }
        void Save_Pin(int SDA, int SCL){
            this->SDA = SDA;
            this->SCL = SCL;
        }
        float Get_Lux(){
            return this->Lux_Value;
        }
        String Get_Name(){
            return this->sensor_name;
        }
        int Get_SDA(){
            return this->SDA;
        }
        int Get_SCL(){
            return this->SCL;
        }
};

void Begin_Lux(LUX_Sensor &Sensor_LUX, String Name, int SDA, int SCL, BH1750::Mode mode, byte addr);
void Read_Lux(LUX_Sensor &Sensor_LUX);

#endif