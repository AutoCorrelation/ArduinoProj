#include "GG.h"

// 생성자에서 LCD 객체를 초기화합니다.
GG::GG() : lcd(LCD_IICAddress, 16, 2) {}

GG::~GG() {}

// 초기화 메서드
bool GG::init() {
    Serial.begin(9600);
    while (!oxygen.begin(Oxygen_IICAddress)) {
        Serial.println("I2c device number error !");
        delay(1000);
    }
    Serial.println("I2c connect success !");
    lcd.init();
    lcd.backlight();
    lcd.print("Hello, world!");
    oxygen.calibrate(20.9, 0);
    delay(1000);
}

// 측정 및 LCD 출력 메서드
void GG::measureAndDisplay() {
    float oxygenData = oxygen.getOxygenData(COLLECT_NUMBER);
    lpf(oxygenData);  // 저주파 필터 적용

    Serial.print(" oxygen concentration is ");
    Serial.print(oxygenData);
    Serial.println(" %vol");

    char O2_buffer[32];
    sprintf(O2_buffer, "O2:%.3f%%vol", oxygenData);
    lcd.setCursor(0, 0);
    lcd.printstr(O2_buffer);

    char CO2_buffer[32];
    sprintf(CO2_buffer, "CO2:%.3f%%vol", 0.5);
    lcd.setCursor(0, 1);
    lcd.printstr(CO2_buffer);

    delay(10);
}

// 저주파 필터 메서드
void GG::lpf(float data) {
    lpfdata = ALPHA * lpfdata + (1 - ALPHA) * data;
}

void GG::calcRER(){
    float o2Data = oxygen.getOxygenData(COLLECT_NUMBER);
    float co2Data = 3.0f;
    float RER = co2Data/o2Data;
    float B = (1-RER)/0.3;
    float A = 1-A;
}

void GG::displayPPM(){

}