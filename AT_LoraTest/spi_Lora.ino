#include <SoftwareSerial.h>

SoftwareSerial lora(2, 3); // RX, TX

void setup()
{
  Serial.begin(57600);
  lora.begin(57600);
  delay(10);
  // lora.write("AT?");
  // lora.write("\r\n");
}

void loop()
{
  if (lora.available())
  {
    Serial.write(lora.read());
  }
  if (Serial.available()) {
    lora.write(Serial.read());
  }
}