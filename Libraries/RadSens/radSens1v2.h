#ifndef _RADSENS1V2_H_
#define _RADSENS1V2_H_


#include <Arduino.h>
#include <Wire.h>
#include <defines.h>


class ClimateGuard_RadSens1v2 {
    private:
        uint8_t _sensor_address;
        uint8_t _data[19] = { 0 };
       /* uint8_t  _chip_id;
        uint8_t _firmware_ver;
        uint32_t _pulse_cnt;*/
        bool updateData();
    public:
        uint8_t chip_id, firmware_ver, I2C_addr;
        float IntensyStatic, IntensyDyanmic;
        uint32_t pulses;
        bool HVGenState;
        ClimateGuard_RadSens1v2(uint8_t sensorAddress);
        ~ClimateGuard_RadSens1v2();
        bool radSens_init();
        uint8_t getChipId();
        uint8_t getFirmwareVersion();
        float getRadIntensyDyanmic();
        float getRadIntensyStatic();
        uint32_t getNumberOfPulses();
        uint8_t getSensorAddress();
        bool getHVGeneratorState();
        uint8_t getSensitivity();
        bool setHVGeneratorState(bool state);
        bool setSensitivity(uint8_t sens);
        bool get(); //Считывание изменяющихся регистров и запись в публичные переменные. возвращает 1 если успех
        bool get(bool full); //Считывание всех регистров (включая версию прошивки и другие технические значения) и запись в публичные переменные. возвращает 1 если успех

};

#endif // _RADSENS1V2_H_