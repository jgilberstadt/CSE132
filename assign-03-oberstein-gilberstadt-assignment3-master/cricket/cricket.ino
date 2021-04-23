/* cricket
 *  
 *  CSE 132 - Assignment 3
 *  
 *  Fill this out so we know whose assignment this is.
 *  
 *  Name: Jason Oberstein
 *  WUSTL Key: joberstein / 457621
 *  
 *  and if two are partnered together
 *  
 *  Name: Josh Gilberstadt
 *  WUSTL Key: josh.gilberstadt / 455174
 */

int rate = 250;
unsigned long next = 0;

const int filterCounts = 8;
float temperatures[filterCounts];
unsigned int count = 0;
float avg = 0;
boolean initial = true;

const int blink_duration = 200;
unsigned long next_blink = 0;
boolean on = false;

void setup() {
  Serial.begin(9600);
  pinMode(12, OUTPUT);
  pinMode(A0, INPUT);
  analogReference(INTERNAL);
}

void loop() {
   if (millis() > next_blink && !initial){
    int period = 60000/(7*(avg-10)+40);
    if (on) {
      digitalWrite(12, LOW);
      next_blink += period;
    } else {
      digitalWrite(12, HIGH);
      next_blink += blink_duration;
    }
    on = !on;
  }
  if (millis() > next) {
    avg -= temperatures[count] / 8.0;
    temperatures[count] = 100 * (analogRead(A0) / 930.0) - 50;

    if (initial) {
      if (count == 7) {
        initial = false;
      }

      avg = count * avg / (count + 1.0) + temperatures[count] / (count + 1.0);
    } else {
      avg += temperatures[count] / 8.0;
    }
    
//    Serial.print("average: ");
//    Serial.println(avg);
//    Serial.print("raw: ");
//    Serial.println(temperatures[count]);
    Serial.print(temperatures[count]);
    Serial.print(",");
    Serial.println(avg);
    
    count = (count + 1) % filterCounts;
    next += rate;
  }
}
