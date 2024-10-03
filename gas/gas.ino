void setup(){
    Serial.begin(57600);
}

void loop(){
    int senV = analogRead(A1);

    Serial.println(senV);
    delay(1000);
}