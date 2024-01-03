#include <Servo.h>

Servo servotes;

int analogval;
int pin = 0;

void setup() {
  servotes.attach(9);
}

void loop() {
  analogval = analogRead(pin);
  analogval = map(analogval, 0, 1023, 0, 180);
  servotes.write(analogval);
  delay(15);
}
