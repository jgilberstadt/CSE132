/* helloworld
 *
 * output simple hello message
 *
 */

int sec = 0;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  Serial.println("Hello, world!");
}

void loop() {
  Serial.print(sec);
  digitalWrite(13, HIGH);
  Serial.print(" sec have elapsed; millis = ");
  Serial.println(millis());
  delay(100);
  digitalWrite(13, LOW);
  delay(900);
  sec++;
}
