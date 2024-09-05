#include <SPI.h>
// #include <LoRa.h>
/** Hardware info
 * https://docs.arduino.cc/tutorials/uno-r4-wifi/cheat-sheet/#spi
 * https://docs.rakwireless.com/Product-Categories/WisDuo/RAK3272S-Breakout-Board/Datasheet/
 *
 * COPI-D11
 * CIPO-D12
 * SCK-D13
 * CS-D10
 * RST=D9
 */
// const int CS = 10;
const char txData[] = "Testing!";

const int frequency = 922230000; //922.23Mhz
int Init_Lora(int CS=10, int RST=9);

void setup()
{
    // Initialize Serial Monitor for debugging
    Serial.begin(9600);

    // Optional: Set custom pins for NSS, Reset, and DIO0
    

    if (!Init_Lora())
    {
        // Initialization failed
        Serial.println("LoRa initialization failed. Check your connections.");
        while (true)
            ; // Halt execution
    }
    Serial.println("LoRa initialization successful.");
    delay(100);
}

void loop()
{
    int test = 5;
    // SPI.transfer((uint8_t*)rxBuffer,sizeof(rxBuffer)-1);
    test = SPI.transfer(0x01);
    delay(10);
    // rxBuffer[sizeof(rxBuffer)-1]='\0';
    Serial.println(test);
    delay(100);

}

int Init_Lora(int CS, int RST){
    pinMode(CS,OUTPUT);
    digitalWrite(CS,LOW);

    pinMode(RST,OUTPUT);
    digitalWrite(RST,LOW);
    delay(10);
    digitalWrite(RST,HIGH);
    delay(10);


    SPI.begin();
    return 1;
}

// void loop()
// {
//     char rxData[50];
//     size_t size = sizeof(rxData) - 1;
//     // SPI.transfer((void *)txData, size);
//     for (size_t i=1;i<size;i++){
//         rxData[i] = SPI.transfer(0x00); //send dummy data to receive
//     }
//     rxData[size]='\0'; //null-terminating end of string

//     Serial.println(rxData);

//     delay(100);
// }
