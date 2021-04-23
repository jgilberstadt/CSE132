int rowStart = 2;
int colStart = 9;

int counter = 0;

void setup() {
  Serial.begin(9600);
  for (int row = 0; row < 7; row++) {
    pinMode(rowStart + row, OUTPUT);
  }
  for (int col = 0; col < 5; col++) {
    pinMode(colStart + col, OUTPUT);
  }
}

void loop() {
  for (int col = 0; col < 5; col++) {
    digitalWrite(colStart + col, HIGH);
  }

  delay(2000);

  digitalWrite(colStart, LOW);
  for (int row = 0; row < 7; row++) {
    digitalWrite(rowStart + row, HIGH);
  }

  delay(2000);

  for (int row = 1; row < 7; row++) {
    digitalWrite(rowStart + row, LOW);
  }

  delay(2000);
}
