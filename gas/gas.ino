void send_read_live_data_simple();
void receive_read_live_data_simple();
float decodeIEEE754(uint8_t *data);


void setup()
{
    Serial.begin(9600);                     // Serial Monitor와의 통신 속도 설정
    Serial1.begin(38400, SERIAL_8N1, 2, 3); // Serial1 통신 속도 및 핀 설정
}

void loop()
{
    send_read_live_data_simple();    // 데이터 요청 전송
    receive_read_live_data_simple(); // 데이터 수신 및 처리
    delay(100);                      // 100ms 대기
}

void send_read_live_data_simple()
{
    // 0x10, 0x13, 0x06, 0x10, 0x1F, 0x00, 0x58
    Serial1.write(0x10); // DLE
    Serial1.write(0x13); // RD
    Serial1.write(0x06); // 길이 또는 필요한 값
    Serial1.write(0x10); // DLE
    Serial1.write(0x1F); // EOF
    Serial1.write(0x00); // 추가 데이터
    Serial1.write(0x58); // 체크섬 또는 추가 데이터
}


// IEEE-754 32비트 부동소수점 숫자로 변환하는 함수
float decodeIEEE754(uint8_t *data) {
    uint32_t value = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
    float result;
    memcpy(&result, &value, sizeof(result));
    return result;
}

void receive_read_live_data_simple() {
    uint8_t data[4]; // CD CC CC 3D를 저장할 배열
    int count = 0; // 배열 인덱스
    bool dataReady = false; // 데이터가 준비되었는지 여부

    while (Serial1.available()) {
        uint8_t byte = Serial1.read();
        Serial.print(byte, HEX);
        Serial.print("|");

        // 첫 7바이트는 무시하고 8바이트부터 CD CC CC 3D를 확인
        if (count >= 7 && count < 11) {
            data[count - 7] = byte; // 0번째 인덱스부터 시작
            if (count - 7 == 3) { // 4바이트가 다 채워지면
                // 순서를 바꿉니다: 3D CC CC CD
                uint8_t reorderedData[4] = { data[3], data[0], data[1], data[2] };
                float decodedValue = decodeIEEE754(reorderedData);
                Serial.print("Decoded Value: ");
                Serial.println(decodedValue);
                dataReady = true; // 데이터가 준비되었음을 표시
            }
        }

        count++;
    }

    // 마지막 출력 후 줄 바꿈
    if (dataReady) {
        Serial.println();
    }
}
