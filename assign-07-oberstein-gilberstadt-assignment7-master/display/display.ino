/* display
 *  
 *  CSE 132 - Assignment 7
 *  
 *  Fill this out so we know whose assignment this is.
 *  
 *  Name: Jason Oberstein
 *  WUSTL Key: 457621
 *  
 *  Name: Josh Gilberstadt
 *  WUSTL Key: 455174
 *  
 */

#include "font.h"


byte currentValue;
byte c;
int charIndex = 0;
int rowStart = 2;
int colStart = 9;
int row = 0;
int col = 0;

int counter = 0;

int pause = 5;

void setup() {
  Serial.begin(9600);
  
  for (int row = 0; row < 7; row++) {
    pinMode(rowStart + row, OUTPUT);
  }
  for (int col = 0; col < 5; col++) {
    pinMode(colStart + col, OUTPUT);
  }
}

void loop ()
{
  if (Serial.available()) {
    c = Serial.read();
    if (c == 's') {
      if (charIndex == 0) {
        charIndex = 95;
      } else {
        charIndex--;
      }
    } else if (c == 'd') {
      charIndex = (charIndex + 1) % 96;
    }
    Serial.println(charIndex);
  }

  display(charIndex);
}

void display(byte index) {
  col = 0;
  
  while (col < 5) {
    row = 0;
    digitalWrite(colStart + col, LOW);
    currentValue = font_5x7[charIndex][col];
    
    while (row < 7) {
      if ((currentValue >> (7 - row)) % 2 == 1) {
        digitalWrite(rowStart + row, HIGH);
      } else {
        digitalWrite(rowStart + row, LOW);
      }
      
      row++;
    }

    delay(pause);
    digitalWrite(colStart + col, HIGH);
    col++;
  }
}
