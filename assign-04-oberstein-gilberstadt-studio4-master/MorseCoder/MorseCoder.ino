#include"MorseCodes.h"

const int led = 12;

const int unit = 500;
unsigned long next = 0;
unsigned long now;

String current;
int index;
boolean reading = false;
boolean lit = false;


void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {
  // No Need to Modify this.  Put most of your code in "convertIncomingCharsToMorseCode()"
  convertIncomingCharsToMorseCode();
}


void convertIncomingCharsToMorseCode() {
  now = millis();
  if (now > next) {
    if (reading) {
      if (lit) {
        digitalWrite(led, LOW);
        next = now + unit;
        lit = false;

        if (index >= current.length()) {
          next += 2*unit;
          reading = false;
        }
      } else {
        switch(current[index]) {
          case ' ':
            next = now + 7*unit;
            reading = false;
            break;
          case '.':
            digitalWrite(led, HIGH);
            lit = true;
            next = now + unit;
            break;
          case '-':
            digitalWrite(led, HIGH);
            lit = true;
            next = now + 3*unit;
            break;
        }

        index++;
      }
    }
    
    else if (Serial.available() > 0) {
      current = morseEncode(Serial.read());
      if (current != "") {
        index = 0;
        reading = true;
      }
    }
  }
}

char toUpper(char c) {
  if ('a' <= c && c <= 'z') {
    return c - 32;
  } else {
    return c;
  }
}
