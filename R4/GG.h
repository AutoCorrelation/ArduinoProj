#ifndef GG_H
#define GG_H

#include <DFRobot_OxygenSensor.h>
#include <LiquidCrystal_I2C.h>

#define Oxygen_IICAddress ADDRESS_3
#define COLLECT_NUMBER 1 // collect number, the collection range is 1-100.
#define LCD_IICAddress 0x27
#define ALPHA 0.9

class GG {
public:
    GG();
    ~GG();

    void init(int Serial_buad, uint8_t O2adrr,  );           // 초기화 메서드
    void displayRER(); // 측정 및 LCD 출력 메서드
    void displayPPM();

private:
    DFRobot_OxygenSensor oxygen; // 산소 센서 객체
    LiquidCrystal_I2C lcd;       // LCD 객체
    float lpfdata;                // 저주파 필터 데이터
    void lpf(float data);         // 저주파 필터 메서드
    void calcRER();
    float RER;
};

#endif
