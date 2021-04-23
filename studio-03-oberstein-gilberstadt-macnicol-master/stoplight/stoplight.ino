const unsigned long driveTime = 6000;
const unsigned long slowTime = 3041;
const unsigned long walkTime = 5000;
const unsigned long flashTime = 500;

unsigned long now;

unsigned long nextSwitch = 0;
unsigned long flashNow = 0;
bool flash = false;


enum State {
  Drive,
  SlowDrive,
  Walk,
  SlowWalk
};

State s = SlowWalk;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop() {
  now = millis();
  

  if (now >= nextSwitch) {
    //switch states
    s = (State) (((int) s + 1) % 4);
    
    switch (s) {
      case Drive:
        digitalWrite(13, LOW); //red light off
        digitalWrite(11, HIGH); //green light on
        nextSwitch = now + driveTime;
        break;
      case SlowDrive:
        digitalWrite(11, LOW); //green light off
        digitalWrite(12, HIGH); //yellow light on
        nextSwitch = now + slowTime;
        break;
      case Walk:
        digitalWrite(12, LOW); //yellow light off
        digitalWrite(13, HIGH); //red light on
        digitalWrite(9, HIGH); //walk light on
        digitalWrite(10, LOW); //stop hand off
        nextSwitch = now + walkTime;
        break;
      case SlowWalk:
        digitalWrite(9, LOW); //walk light off
        nextSwitch = now + slowTime;
        flash = false;
        break;
    }
  }

  if (s != Walk) {
    if (now >= flashNow) {
      if (flash) {
        digitalWrite(10, LOW); //stop hand off
      } else {
        digitalWrite(10, HIGH); //stop hand on
      }

      flashNow = now + flashTime;
      flash = !flash;
    }
  }
}
