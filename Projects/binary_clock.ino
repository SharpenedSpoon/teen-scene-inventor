/*

Binary Timer

Purpose:
  This is a timer that keeps the seconds in binary, and displays it in a row of LEDs

Hardware:
  * 8 LEDs, connected to pins 0, 1, 2, 3, 4, 5, 6, 7

*/

int ledPins[] = {0, 1, 2, 3, 4, 5, 6, 7};
int currentTime = 0;
int timeInterval = 1000; // 1 "unit" is 1000 ms

void setup() {
  for (int i = 0; i < 8; i++) {
    int currentLedPin = ledPins[i]; // sets currentLedPin to be the i'th number in the ledPins array
    pinMode(currentLedPin, OUTPUT); // set pin mode to output
  }
}

void loop() {

  // ----- Turn off all lights (to reset and prep them)
  for (int i = 0; i < 8; i++) {
    int currentLedPin = ledPins[i]; // sets currentLedPin to be the i'th number in the ledPins array
    digitalWrite(currentLedPin, LOW); // turn off the LED
  }
  
  currentTime = currentTime + 1;
  
  for (int i = 0; i < 8; i++) {
    int currentLedPin = ledPins[i];
    if (bitRead(currentTime, i) == 1) {
      digitalWrite(currentLedPin, HIGH);
    }
  }
  
  delay(timeInterval);
}
