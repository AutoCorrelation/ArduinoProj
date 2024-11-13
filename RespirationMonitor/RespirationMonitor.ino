#include <Wire.h>             //i2c통신을 사용하기 때문에 아두이노의 i2c 통신용 라이브러리가 필요
#include <Adafruit_GFX.h>     // adafruit의 그래픽 관련 라이브러리
#include <Adafruit_SSD1306.h> // ssd1306 제어용 라이브러리
#include <DFRobot_OxygenSensor.h>
#include <SparkFun_STC3x_Arduino_Library.h>

#define SCREEN_WIDTH 128 // OLED 디스플레이의 가로 픽셀수
#define SCREEN_HEIGHT 64 // OLED 디스플레이의 세로 픽셀수
#define OLED_RESET 4     // 리셋핀이 있는 oled의 리셋핀에 연결할 아두이노의 핀 번호, 리셋핀이 없는 모듈은 임의의 숫자를 넣어도 됨.

// 0x3C주소로 디스플레이 장치를 초기화

#define Oxygen_IICAddress ADDRESS_3
#define COLLECT_NUMBER 1 // collect number, the collection range is 1-100.
#define LCD_IICAddress 0x27
#define ALPHA 0.9
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // 디스플레이 객체 생성1
DFRobot_OxygenSensor oxygen;
STC3x co2;

void setup()
{
    Serial.begin(9600);
    while (!oxygen.begin(Oxygen_IICAddress))
    {
        Serial.println("Oxygen I2c device number error !");
        delay(1000);
    }
    if (co2.begin() == false)
    {
        Serial.println(F("Sensor not detected. Please check wiring. Freezing..."));
        while (1)
            ;
    }
    if (co2.setBinaryGas(STC3X_BINARY_GAS_CO2_AIR_25) == false)
    {
        Serial.println(F("Could not set the binary gas! Freezing..."));
        while (1)
            ;
    }
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 28);
    Serial.println("I2c connect success !");
    display.println("sex1");
    display.display();
    delay(1000);
    display.clearDisplay();

    Serial.println("I2c connect success !");
    oxygen.calibrate(20.9, 0);
    delay(1000);
}

void loop()
{
    float oxygenData = oxygen.getOxygenData(COLLECT_NUMBER);
    static float co2data = 0;
    // float oxygenData = oxygen.justread();
    if (co2.measureGasConcentration())
    {
        co2data = co2.getCO2();
        delay(100);        
    }
    display.clearDisplay();
    char O2_buffer[32];
    sprintf(O2_buffer, "O2:%.3f%%vol", oxygenData);
    display.setCursor(0, 0);
    display.println(O2_buffer);
    display.display();

    char CO2_buffer[32];
    sprintf(CO2_buffer, "CO2:%.3f%%vol", co2data);
    display.setCursor(0, 28);
    display.println(CO2_buffer);
    display.display();
    
    Serial.println(O2_buffer);
    Serial.println(CO2_buffer);
    delay(1000);
}