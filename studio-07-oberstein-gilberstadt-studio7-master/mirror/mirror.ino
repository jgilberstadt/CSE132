unsigned int presses = 0;
boolean pressed = false;

void setup() {
  Serial.begin(9600);
  pinMode(12, OUTPUT);
  pinMode(11, INPUT_PULLUP);
}

void loop() {
  if (pressed && digitalRead(11) == 1) {
    digitalWrite(12, LOW);
    pressed = false;
  }
  
  if (!pressed && digitalRead(11) == 0) {
    digitalWrite(12, HIGH);
    presses++;
    Serial.println(presses);
    pressed = true;
  }
}
