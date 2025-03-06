#include <RCSwitch.h>
#include <LowPower.h>

#define LOCKPIN 3
#define ALARM 8
#define TRANSMITTER 10
#define BREAK_TOLERANCE_MILLIS 2000

RCSwitch mySwitch = RCSwitch();

int brokenAtMillis = -1;
bool isPotentiallyBroken = false;
bool isBroken = false;

// interrupt function -> will wake up
void wakeUp() {
  Serial.print("RISING INTERRUPT ON PIN ");
  Serial.println(LOCKPIN);
  Serial.println("Lock maybe broken. Waking up!");
  isPotentiallyBroken = true;
  brokenAtMillis = millis();
}

void setup() {
  mySwitch.enableTransmit(TRANSMITTER);
  pinMode(LOCKPIN, INPUT_PULLUP); // pullup resistor
  pinMode(ALARM, OUTPUT);
  Serial.begin(9600);
  
  // Attach the interrut for waking the system up
  attachInterrupt(digitalPinToInterrupt(LOCKPIN), wakeUp, RISING);
  Serial.println("Lock initialized...");
}

void loop() {
  // potential breach check
  if(!isPotentiallyBroken && !isBroken) {
    Serial.println("Going to sleep...");
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF); // go to sleep forever
  } else {
    if(!isBroken) {
      // check false alarm
      int lock = digitalRead(LOCKPIN);
      if(lock == LOW) {
        isPotentiallyBroken = false;
        Serial.println("False alarm!");
      }
    }

    // check breach -> Threshold
    if(brokenAtMillis + BREAK_TOLERANCE_MILLIS < millis()) {
      isBroken = true;
      Serial.println("Lock broken!");
    }
  }
  
  if(isBroken) {
    Serial.println("Sending 433MHz signal");
    mySwitch.send(1001, 24);
    tone(ALARM, 1000);
    delay(250);
    tone(ALARM, 700);
    delay(250);
  }
}
