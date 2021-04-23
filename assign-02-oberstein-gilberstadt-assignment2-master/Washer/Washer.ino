//Fill in the values below with the pins that you chose to use
const int POT_PIN = A0;
const int BUTTON_PIN = 6;

const int HOT_PIN = 12;
const int COLD_PIN = 11;
const int DRY_PIN = 10;
const int LOCK_PIN = 9;

const unsigned long cold = 5000;
const unsigned long medium = 7000;
const unsigned long hot = 7000;
const unsigned long econDry = 2000;
const unsigned long deluxDry = 7000;

unsigned long next;

bool mediumOn;


enum State {
  offEcon,
  offDelux,
  offSupDelux,
  washEcon,
  washDelux,
  washSupDelux,
  dryEcon,
  dryDelux
};

State s = offEcon;
State wash;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(HOT_PIN, OUTPUT);
  pinMode(COLD_PIN, OUTPUT);
  pinMode(DRY_PIN, OUTPUT);
  pinMode(LOCK_PIN, OUTPUT);
}

void loop() {
  Serial.println(s);
  if ((int) s < 3) {
    //dishwasher is off
    s = (State) (analogRead(POT_PIN) / 342);

    if (digitalRead(BUTTON_PIN) == 0) {
      //run dishwasher
      digitalWrite(LOCK_PIN, HIGH);
      s = (State) ((int) s + 3);
      wash = s;

      if (s == 3) {
        //economy
        digitalWrite(COLD_PIN, HIGH);
        next = millis() + cold;
      } else {
        //delux or super delux
        digitalWrite(HOT_PIN, HIGH);
        next = millis() + hot;
        mediumOn = false;
      }
    }
  } else if ((int) s < 6) {
    //dishwasher is on
    s = (State) (analogRead(POT_PIN) / 342 + 3);
    
    if (millis() >= next) {
      if ((int) wash == 5 && !mediumOn) {
        digitalWrite(COLD_PIN, HIGH);
        next = millis() + medium;
        mediumOn = true;
      } else {
        s = (State) ((int) s + 3);

        //run dryer
        digitalWrite(COLD_PIN, LOW);
        digitalWrite(HOT_PIN, LOW);
        digitalWrite(DRY_PIN, HIGH);

        if (s == 6) {
          next = millis() + econDry;
        } else {
          next = millis() + deluxDry;
        }
      }
    }
  } else {
    //dryer is on
    if (millis() >= next) {
      digitalWrite(DRY_PIN, LOW);
      digitalWrite(LOCK_PIN, LOW);
      s = (State) (analogRead(POT_PIN) / 342);
    }
  }
}
