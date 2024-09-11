#include <SoftwareSerial.h>
// #include <TimerOne.h> // ex https://github.com/delta-G/TimerOne/blob/master/examples/Interrupt/Interrupt.ino

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
SoftwareSerial lora(2, 3); // RX, TX



void setup()
{
    Serial.begin(57600);
    lora.begin(57600);
    delay(10);
    // lora.write("AT");
    // lora.write("?");
    // lora.write("\r\n");
}

void loop()
{
    // if (lora.available())
    // {
    //     Serial.write(lora.read());
    // }
    // if (Serial.available())
    // {
    //     lora.write(Serial.read());
    // }
    send_AT_command("68656C6C6F2C20776F726C642133"); //send "hello, world"
    delay(200);

}

void send_AT_command(const char *command)
{
    // if(strlen(command)%2==1){
    //     command
    // }

    lora.write("AT+PSEND=");
    lora.write(command);
    lora.write("\r\n");
}


// void checkSerial()
// {
//     // 시리얼에 들어오는 데이터가 있는지 확인
//     if (Serial.available() > 0)
//     {
//         // 시리얼 데이터 읽기 및 출력
//         while (Serial.available() > 0)
//         {
//             char incomingByte = Serial.read();  // 데이터 읽기
//             Serial.print("Received: ");
//             Serial.println(incomingByte);  // 읽은 데이터 출력
//         }
//     }
// }
