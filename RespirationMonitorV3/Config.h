#ifndef _CONFIG_H_
#define _CONFIG_H_

#define SCREEN_WIDTH 128        // OLED display width in pixels
#define SCREEN_HEIGHT 64        // OLED display height in pixels
#define OLED_RESET 4           // Reset pin for OLED display
#define Oxygen_IICAddress ADDRESS_3  // I2C address for oxygen sensor
#define COLLECT_NUMBER 40       // Number of samples to collect (1-100)
#define LCD_IICAddress 0x3C    // I2C address for OLED display

// Pin definitions
#define MOTOR_PWM_PIN 9
#define ENCODER_PIN_A 2
#define ENCODER_PIN_B 4
#define ENCODER_BUTTON_PIN 3

// I2C addresses
#define SENSOR_I2C_ADDRESS 0x40

#endif