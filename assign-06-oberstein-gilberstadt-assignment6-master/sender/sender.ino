/* 
 *  
 *  CSE 132 - Assignment 6
 *  
 *  Fill this out so we know whose assignment this is.
 *  
 *  Name: Jason Oberstein
 *  WUSTL Key: 457621
 *  
 *  and if two are partnered together
 *  
 *  Name: Josh Gilberstadt
 *  WUSTL Key: 455174
 */

int potPin = A0;
int tempPin = A1;

unsigned long next = 0;
unsigned long current;
const int interval = 1000;
int potValue;
const int tooHigh = 800;

void setup() {
  Serial.begin(9600);
  pinMode(potPin, INPUT);
  pinMode(tempPin, INPUT);
}

void loop() {
  current = millis();
  potValue = analogRead(potPin);

  if (current > next) {
    sendLong(0x32, current);
    sendInt(0x33, potValue);
    sendInt(0x34, analogRead(tempPin));
    sendStr(0x30, "test string");

    if (potValue > tooHigh) {
      sendStr(0x31, "High alarm");
    }
    
    next = current + interval;
  }
}

void sendInt(byte type, int val) {
  Serial.write('!');
  Serial.write(type);
  for (int i = 1; i >= 0; i--) {
    Serial.write(val>>(8*i));
  }
}

void sendLong(byte type, long val) {
  Serial.write('!');
  Serial.write(type);
  for (int i = 3; i >= 0; i--) {
    Serial.write(val>>(8*i));
  }
}

void sendStr(byte type, String str) {
  int size = str.length();
  char char_array[size + 1];
  str.toCharArray(char_array, size + 1);
  
  Serial.write('!');
  Serial.write(type);
  Serial.write(size>>8);
  Serial.write(size);
  Serial.write(char_array);
}
