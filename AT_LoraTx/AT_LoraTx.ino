#include <SoftwareSerial.h>
#define FLAME_PIN 10
#define TEMPERATURE_PIN A0
#define VELOCITY_PIN 11

enum Section
{
    SECTION_1 = 1,
    SECTION_2,
    SECTION_3,
    SECTION_4
};

SoftwareSerial lora(2, 3); // RX, TX

struct SensorData
{
    uint8_t section = SECTION_1;
    int32_t speed;
    int32_t temperature;
    int is_fire;
};

SensorData sensor_data;

SensorData getData();
char *data2hex(SensorData sensor_data);

void setup()
{
    pinMode(FLAME_PIN, INPUT);
    
    // pinmode(TEMPERATURE_PIN, INPUT);
    Serial.begin(57600);
    lora.begin(57600);
    delay(10);
}

void loop()
{
    // sensor_data.section = 2;      // enum (1 byte)
    // sensor_data.speed = 100;      // integer (4 bytes)
    // sensor_data.temperature = 20; // integer (4 bytes, 음수 포함)
    // sensor_data.is_fire = false;  // boolean (1 byte)

    sensor_data = getData();

    /**
     * @brief Send sensor_data
     * @param sensor_data
     */
    char command[30];
    sprintf(command, "AT+PSEND=%s", data2hex(sensor_data));
    lora.write(command);
    lora.write("\r\n");

    // Serial.println(sensor_data.speed);
    Serial.println(sensor_data.speed);
    Serial.println(sensor_data.temperature);
    Serial.println(sensor_data.is_fire);

    delay(1000); // 1초 대기
}

char *data2hex(SensorData _data)
{
    static char hex_data[23]; // static으로 선언하여 함수 외부에서도 접근 가능하게 함

    char hex_section[3];
    sprintf(hex_section, "%02x", _data.section);

    char hex_speed[9];
    sprintf(hex_speed, "%08x", _data.speed);

    // 음수 온도를 2의 보수로 변환하여 16진수로 표현
    char hex_temperature[9];
    sprintf(hex_temperature, "%08x", _data.temperature);

    char hex_is_fire[3];
    sprintf(hex_is_fire, "%02x", _data.is_fire);

    // 16진수 문자열을 하나로 결합
    sprintf(hex_data, "%s%s%s%s", hex_section, hex_speed, hex_temperature, hex_is_fire);

    return hex_data;
}

SensorData getData()
{
    SensorData _data;

    _data.is_fire = digitalRead(FLAME_PIN);
    _data.temperature = (analogRead(TEMPERATURE_PIN) * 500 / 1023.0);
    //_data.speed = (1e6 / (pulseIn(VELOCITY_PIN,HIGH)+pulseIn(VELOCITY_PIN,LOW))) / 44.0;
    _data.speed = 2;

    return _data; // 'sensor_data' 대신 '_data' 반환
}
