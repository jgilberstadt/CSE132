#include "assemblyFunctions.h"
#include "printRegs.h"

void testHasAOne() {
  Serial.println("**** Testing hasAOne() (only prints errors in tests) ****");  
  if(hasAOne(0) == true) {
      Serial.println("hasAOne() error on: 0");
  }
  // Test for errors with all other values
  for(byte b=1; b!=0; b++) {
    if(hasAOne(b) == false) {
      Serial.print("hasAOne() error on: ");
      Serial.println(b);
    }
  }  
}

void testByteToAscii() {
 Serial.println("**** Testing addInt8ToInt() (only prints errors in tests) ****");  
  int x = 0;
  for (char c = '0'; c <= '9'; ++c) { // tests each character from 0 to 9
       if (byteToAscii(x) != c) {
          Serial.println("byteToAscii failed at c = ");
          Serial.print(c); 
       }
       ++x;
  }
}


void testInt8ToInt() {
  Serial.println("**** Testing int8ToInt() (only prints errors in tests) ****");  
    for(int expected=-128;expected<128;expected++) { // -128 to 127
    int8_t input  = expected;
    int result = int8ToInt(input);
    if(result != expected) {
      Serial.print("Error. ");
      Serial.print(input);
      Serial.print(" expected ");
      Serial.print(expected);
      Serial.print(" but was ");
      Serial.println(result);
    } 
  }   
}



void testAddInt8ToInt() {
  Serial.println("**** Testing addInt8ToInt() (only prints errors in tests) ****");  // added 5 additional test cases
  int8_t int8Values[]  = {0, 1, -1,  1, -1,  -1,  127, -128, -127, -127, 100, -100, 127, -2, 100, -5, -100};
  int    int16Values[] = {0, 1,  1, -1, -1, 256, -127,  128,  128, -127, 300, 1000, 127, 127, 15300, -5, -100};
  int    results[]     = {0, 2,  0,  0, -2, 255,    0,    0,    1, -254, 400,  900, 254, 125, 15400, -10, -200};
  const int numTests = sizeof(results)/sizeof(int);

  for(int i=0;i<numTests;i++) {
    int8_t int8 = int8Values[i];     // Signed 8-bit int
    int    int16 = int16Values[i];   // Signed 16-bit int
    int    expected = results[i];
    int    result = addInt8ToInt(int8, int16);
    if(result != expected) {
      Serial.print("Error. ");
      Serial.print(int8);
      Serial.print(" + "); 
      Serial.print(int16);
      Serial.print(" expected ");
      Serial.print(expected);
      Serial.print(" but was ");
      Serial.println(result);
    }
  }  
}



void testAdd4Int8() {
  Serial.println("**** Testing add4Int8() (only prints errors in tests) ****"); // added 7 test cases 
  int8_t as[]   = {127, -1,  1, -128, 7, 7, 7, 127, 0, 127, 50};
  int8_t bs[]   = {127, -1, -1, -128, 7, 7, 7, 1, -127, 127, -51};
  int8_t cs[]   = {127, -1,  1, -128, 0, 7, 7, -127, 127, 2, 52};
  int8_t ds[]   = {127, -1, -1, -128, 0, 0, 7, -1, -127, -1, -53};
  int results[] = {508, -4,  0, -512, 14, 21, 28, 0, -127, 255, -2};  
  const int numTests = sizeof(results)/sizeof(int);
  
  for(int i=0;i<numTests;i++) {
    int8_t a = as[i];
    int8_t b = bs[i];
    int8_t c = cs[i];
    int8_t d = ds[i];
    int    expected = results[i];   // Signed 16-bit int
    
    int result = add4Int8(a,b,c,d);
    if(result != expected) {
      Serial.print("Error. ");
      Serial.print(a);
      Serial.print(" + "); 
      Serial.print(b);
      Serial.print(" + "); 
      Serial.print(c);
      Serial.print(" + "); 
      Serial.print(d);
      Serial.print(" expected ");
      Serial.print(expected);
      Serial.print(" but was ");
      Serial.println(result);
    }
  }  
}

void testAverage() {
  Serial.println("**** Testing average() (only prints errors in tests) ****");  // added 5 test cases
  byte  as[]      = {0, 255, 127,  1, 0,   5, 10, 30, 200, 15, 30};
  byte  bs[]      = {0, 255, 128,  0, 1, 100, 20, 100, 60, 16, 41};
  byte  results[] = {0, 255, 127,  0, 0,  52, 15, 65, 130, 15, 35};
  const int numTests = sizeof(results)/sizeof(byte);

  for(int i=0;i<numTests;i++) {
    byte a = as[i];
    byte b = bs[i];
    byte expected = results[i];
    byte result = average(a,b);
    if(result != expected) {
      Serial.print("Error. (");
      Serial.print(a);
      Serial.print(" + "); 
      Serial.print(b);
      Serial.print(")/2 expected ");
      Serial.print(expected);
      Serial.print(" but was ");
      Serial.println(result);
    }
  }
}


void setup() {
  Serial.begin(9600);
  Serial.println("Starting program...");
  testHasAOne();
  testByteToAscii();
  testInt8ToInt();
  testAddInt8ToInt();
  testAdd4Int8(); 
  testAverage(); 
  Serial.println("Testing Done!");
}

void loop() { /* unused */ }
