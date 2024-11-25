#include <Wire.h>             // I2C communication library
#include <Adafruit_GFX.h>     // Adafruit graphics library
#include <Adafruit_SSD1306.h> // SSD1306 OLED display library
#include <DFRobot_OxygenSensor.h> // DFRobot Oxygen sensor library
#include <SparkFun_STC3x_Arduino_Library.h> // SparkFun CO2 sensor library

#define SCREEN_WIDTH 128 // OLED display width in pixels
#define SCREEN_HEIGHT 64 // OLED display height in pixels
#define OLED_RESET 4     // Reset pin for OLED display (can be any pin if not used)
#define Oxygen_IICAddress ADDRESS_3 // I2C address for Oxygen sensor
#define COLLECT_NUMBER 1 // Number of samples to collect (range 1-100)
#define LCD_IICAddress 0x3C // I2C address for OLED display
#define ALPHA 0.9 // Alpha value for filtering (not used in this code)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // OLED display object
DFRobot_OxygenSensor oxygen; // Oxygen sensor object
STC3x co2; // CO2 sensor object

void setup()
{
    Serial.begin(9600); // Initialize serial communication at 9600 baud rate

    // Initialize Oxygen sensor
    while (!oxygen.begin(Oxygen_IICAddress))
    {
        Serial.println("Oxygen I2C device number error!");
        delay(1000);
    }

    // Initialize CO2 sensor
    if (co2.begin() == false)
    {
        Serial.println(F("Sensor not detected. Please check wiring. Freezing..."));
        while (1);
    }

    // Set binary gas for CO2 sensor
    if (co2.setBinaryGas(STC3X_BINARY_GAS_CO2_AIR_25) == false)
    {
        Serial.println(F("Could not set the binary gas! Freezing..."));
        while (1);
    }

    // Initialize OLED display
    display.begin(SSD1306_SWITCHCAPVCC, LCD_IICAddress);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 28);
    Serial.println("I2C connect success!");
    display.println("I2C connect success!");
    display.display();
    delay(1000);
    display.clearDisplay();

    // Calibrate Oxygen sensor
    oxygen.calibrate(20.9, 0);
    delay(1000);
}

void loop()
{
    float oxygenData = oxygen.getOxygenData(COLLECT_NUMBER); // Get oxygen data
    static float co2data = 0; // Variable to store CO2 data

    // Get CO2 data
    if (co2.measureGasConcentration())
    {
        co2data = co2.getCO2();
        delay(100);        
    }

    // Display Oxygen data on OLED
    display.clearDisplay();
    char O2_buffer[32];
    sprintf(O2_buffer, "O2:%.3f%%vol", oxygenData);
    display.setCursor(0, 0);
    display.println(O2_buffer);
    display.display();

    // Display CO2 data on OLED
    char CO2_buffer[32];
    sprintf(CO2_buffer, "CO2:%.3f%%vol", co2data);
    display.setCursor(0, 28);
    display.println(CO2_buffer);
    display.display();
    
    // Print data to Serial Monitor
    Serial.println(O2_buffer);
    Serial.println(CO2_buffer);
    delay(1000);
}