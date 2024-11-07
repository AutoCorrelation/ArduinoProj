int v;          // 속도
int vmax;       // 최대 속도
int Sigpin = 11;  // 신호 입력 핀

int flame = 7;     // 화재 감지 센서 핀
int ledPin = 8;    // LED 핀
int buzzerPin = 9; // 피에조 부저 핀
int state = 0;

void setup() {
  Serial.begin(9600);
  pinMode(Sigpin, INPUT);
  pinMode(flame, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // 속도 측정 부분
  unsigned long T;          // 주기
  double f;                 // 주파수 
  char s[20];               // Serial 출력 Length
  vmax = 0;
  while (digitalRead(Sigpin)); 
  while (!digitalRead(Sigpin));
 
  T = pulseIn(Sigpin, HIGH) + pulseIn(Sigpin, LOW); // 주기 측정
  f = 1 / (double) T;            // 주파수 측정
  v = int((f * 1e6) / 44.0);    // 속도 측정

  if (v >= 2 && v <= 50) {               // 속도가 50km/h 이하인 경우에만
    vmax = max(v, vmax); 
    sprintf(s, "% 3d km / h", vmax);  // Serial 출력
    Serial.println(s);        // Serial 출력
    delay(30);              // Delay 500m/s// 속도의 Max값 측정
  }



  // 화재 감지 부분
  state = digitalRead(flame);

  if (state == 0) {
    digitalWrite(ledPin, HIGH);   // LED 켜기
    tone(buzzerPin, 1000);        // 피에조 부저 1000Hz 주파수로 울리기
    delay(100);
    noTone(buzzerPin);
  } else {
    digitalWrite(ledPin, LOW);    // LED 끄기
    noTone(buzzerPin);            // 피에조 부저 끄기
    delay(100);
  }
}