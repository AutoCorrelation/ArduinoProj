/*!
 * @brief Read oxygen concentration ,The unit is concentration percent (% vol).
 * @n step: we must first determine the iic device address, will dial the code switch A0, A1 (ADDRESS_0 for [0 0]), (ADDRESS_1 for [1 0]), (ADDRESS_2 for [0 1]), (ADDRESS_3 for [1 1]).
 * @n Then calibrate the oxygen sensor
 * @n note: it takes time to stable oxygen concentration, about 10 minutes.
 * @n The experimental phenomenon is that a certain percentage of oxygen concentration is printed on the serial port.
 * @n Because the oxygen concentration in oxygen air is certain, the data will not be greater than 25% vol.
 * @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author ZhixinLiu(zhixin.liu@dfrobot.com)
 * @version V1.0
 * @date 2021-10-22
 * @url https://github.com/DFRobot/DFRobot_OxygenSensor
 */
#include "DFRobot_OxygenSensor.h"
#include "LiquidCrystal_I2C.h"

/**
 * i2c slave Address, The default is ADDRESS_3.
 * ADDRESS_0   0x70  i2c device address.
 * ADDRESS_1   0x71
 * ADDRESS_2   0x72
 * ADDRESS_3   0x73
 */
#define Oxygen_IICAddress ADDRESS_3
#define COLLECT_NUMBER 1 // collect number, the collection range is 1-100.
#define LCD_IICAddress 0x27
#define ALPHA 0.9
DFRobot_OxygenSensor oxygen;
LiquidCrystal_I2C lcd(LCD_IICAddress, 16, 2);
void lpf(float data);
float lpfdata;

void setup(void)
{
  Serial.begin(9600);
  while (!oxygen.begin(Oxygen_IICAddress))
  {
    Serial.println("I2c device number error !");
    delay(1000);
  }
  Serial.println("I2c connect success !");
  lcd.init();
  lcd.backlight();
  lcd.printstr("Hello,world!");
  oxygen.calibrate(20.9, 0);
  delay(1000);
}

void loop(void)
{
  float oxygenData = oxygen.getOxygenData(COLLECT_NUMBER);
  lpf(oxygenData);
  // float oxygenData = oxygen.justread();
  Serial.print(" oxygen concentration is ");
  Serial.print(oxygenData);
  Serial.println(" %vol");
  // lcd.clear();
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

/*-----------------------------------------------------------*/
void lpf(float data)
{

  lpfdata = ALPHA*lpfdata + (1-ALPHA)*data;
  // return 0;
}