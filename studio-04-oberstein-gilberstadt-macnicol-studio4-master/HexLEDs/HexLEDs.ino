void setup() {
  Serial.begin(9600);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
}

int ascii;
void loop() {
  if (Serial.available() > 0) {
    ascii = Serial.read();
    if (ascii - '0' < 10) {
      Serial.println(ascii - '0');
    } else {
      Serial.println(ascii - 'a' + 10);
    }
  }
  
  digitalWrite(12, HIGH);
  delay(500);
  digitalWrite(12, LOW);
  digitalWrite(11, HIGH);
  delay(500);
  digitalWrite(11, LOW);
  digitalWrite(10, HIGH);
  delay(500);
  digitalWrite(10, LOW);
  digitalWrite(9, HIGH);
  delay(500);
  digitalWrite(9, LOW);
}
