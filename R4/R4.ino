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
#define COLLECT_NUMBER  2             // collect number, the collection range is 1-100.
#define LCD_IICAddress 0x27
DFRobot_OxygenSensor oxygen;
LiquidCrystal_I2C lcd(0x27,16,2);

void setup(void)
{
  Serial.begin(9600);
  while(!oxygen.begin(Oxygen_IICAddress)){
    Serial.println("I2c device number error !");
    delay(1000);
  }
  Serial.println("I2c connect success !");
  lcd.init();
  lcd.backlight();
  lcd.printstr("Hello,world!");
  delay(1000);
}

void loop(void)
{
  float oxygenData = oxygen.getOxygenData(COLLECT_NUMBER);
  Serial.print(" oxygen concentration is ");
  Serial.print(oxygenData);
  Serial.println(" %vol");
  lcd.clear();
  char buffer[32];
  sprintf(buffer,"O2:%.3f%%vol",oxygenData);
  lcd.setCursor(0,0);
  lcd.printstr(buffer);
  delay(10);
}

/*-----------------------------------------------------------*/


// /* RX-9 QR Sample Code
//  *  date: 2020.03.04
//  *  Carbon Dioxide Gas sensor(RX-9) with
//  *  ATMEGA328p, 16Mhz, 5V
//  *  file name: RX9SampleCodeQR_RX9
//  *  
//  *  RX-9 have 4 pin
//  *  E: EMF
//  *  T: Thermistor for sensor
//  *  G: GND
//  *  V: 3.3V > 200 mA
//  */
// #include "RX9QR.h"
// #define EMF_pin 0   // RX-9 E with A0 of arduino
// #define THER_pin 1  // RX-9 T with A1 of arduino
// #define ADCvolt 5
// #define ADCResol 1024
// #define Base_line 432
// #define meti 60  
// #define mein 120 //Automotive: 120, Home or indoor: 1440

// //CO2 calibrated number
// float cal_A = 398.0; // you can take the data from RX-9 bottom side QR data #### of first 4 digits. you type the data to cal_A as ###.#
// float cal_B = 62.45; // following 4 digits after cal_A is cal_B, type the data to cal_B as ##.##

// //CO2 Step range
// #define cr1  700      // Base_line ~ cr1
// #define cr2  1000     // cr1 ~ cr2
// #define cr3  2000     // cr2 ~ cr3
// #define cr4  4000     // cr3 ~ cr4 and over cr4

// // Thermister constant
// // RX-9 have thermistor inside of sensor package. this thermistor check the temperature of sensor to compensate the data
// // don't edit the number
// #define C1 0.00230088
// #define C2 0.000224
// #define C3 0.00000002113323296
// float Resist_0 = 15;

// //Timing
// unsigned int time_s = 0;
// unsigned int time_s_prev = 0;
// unsigned int time_s_set = 1;

// extern volatile unsigned long timer0_millis;

// //CO2 Value
// int status_sensor = 0;
// unsigned int co2_ppm = 0;
// unsigned int co2_step = 0;
// float EMF = 0;
// float THER = 0;

// RX9QR RX9(cal_A, cal_B, Base_line, meti, mein, cr1, cr2, cr3, cr4);

// void setup() {
//   // put your setup code here, to run once:
//   Serial.begin(9600);
 
// }

// void loop() {
//   // put your main code here, to run repeatedly:
//   time_s = millis()/1000;
//   if(time_s - time_s_prev >= time_s_set){
//     time_s_prev = time_s;
//     //every 1 sec
//     //read EMF data from RX-9, RX-9 Simple START-->
//     EMF = analogRead(EMF_pin);
//     delay(1);
//     EMF = EMF / (ADCResol - 1);
//     EMF = EMF * ADCvolt;
//     EMF = EMF / 6;
//     EMF = EMF * 1000;
//     // <-- read EMF data from RX-9, RX-9 Simple END 

//     //read THER data from RX-9, RX-9 Simple START-->
//     THER = analogRead(THER_pin);
//     delay(1);
//     THER = 1/(C1+C2*log((Resist_0*THER)/(ADCResol-THER))+C3*pow(log((Resist_0*THER)/(ADCResol-THER)),3))-273.15;
//     // <-- read THER data from RX-9, RX-9 Simple END
    
//     status_sensor = RX9.status_co2();   //read status_sensor, status_sensor = 0 means warming up, = 1 means stable
//     co2_ppm = RX9.cal_co2(EMF,THER);    //calculation carbon dioxide gas concentration. 
//     co2_step = RX9.step_co2();          //read steps of carbon dioixde gas concentration. you can edit the step range with cr1~cr4 above.
//     Serial.print("# ");                //Starting letter
//     if(co2_ppm <1000){
//       Serial.print("0");
//     }
//     else{      
//     }
//     Serial.print(co2_ppm); Serial.print(" ");
//     if(status_sensor){
//       Serial.print("NR"); 
//     }
//     else{
//       Serial.print("WU");
//       //it takes about 3 minutes to heating the sensor.
//       //while warming up. data is not correct. 
//     }
//     Serial.println(""); //CR LF
//   }  
// }