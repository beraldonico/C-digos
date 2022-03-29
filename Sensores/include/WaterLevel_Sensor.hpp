#ifndef WATERLEVEL_H
#define WATERLEVEL_H

#include "defines.hpp"

class WaterLevel_Sensor {
    private:
        String  sensor_name;
        int     waterlevel_Value;
        int     waterlevel_Pure_Value;
        int     sensor_PIN;
        int     max_analog;
        int     min_analog;
        int     LED_PIN;
    public:
        void Save_Pure_Level(uint16_t value){
            this->waterlevel_Pure_Value = value;
        }
        void Save_Level(int value){
            this->waterlevel_Value = value;
        }
        void Save_Name(String value){
            this->sensor_name = value;
        }
        void Save_Pin(int value){
            this->sensor_PIN = value;
        }
        void Save_Max(int value){
            this->max_analog = value;
        }
        void Save_Min(int value){
            this->min_analog = value;
        }
        void Save_LED(int value){
            this->LED_PIN = value;
        }
        int Get_Pin(){
            return this->sensor_PIN;
        }
        uint16_t Get_Pure_Level(){
            return this->waterlevel_Pure_Value;
        }
        int Get_Level(){
            return this->waterlevel_Value;
        }
        String Get_Name(){
            return this->sensor_name;
        }
        int Get_Max(){
            return this->max_analog;
        }
        int Get_Min(){
            return this->min_analog;
        }
        int Get_LED(){
            return this->LED_PIN;
        }
};

void Begin_WaterLevel(WaterLevel_Sensor &Sensor_WaterLevel, String Name, int PIN, int max_analog, int min_analog, int LED_PIN);
void Read_WaterLevel(WaterLevel_Sensor &Sensor_WaterLevel);
int Convert_Value(WaterLevel_Sensor &Sensor_WaterLevel);

#endif