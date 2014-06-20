/*

LED Fighting

Purpose:
  This program is a "game" sort of I guess. There is a line of LEDs in a row,
  with a button on either side. When you press a button, it will "push" light
  towards the other side.

Hardware:
  * Two buttons connected to pins 1 and 2 (corresponding to player 1 and player 2!)
  * 6 LEDs, connected to pins 5, 6, 7, 8, 9, 10
  * Player 1's button should be on the side with LED 5, and Player 2 should be on the opposite side

*/

int playerOnePin = 1;
int playerTwoPin = 2;
int ledPins[] = {5, 6, 7, 8, 9, 10};

int gameLedDelay = 20; // increasing this will make the game "slower"

int currentPlayerSide = 1; // this keeps track of which side the LEDs have been pushed to

void setup() {
  pinMode(playerOnePin, INPUT);
  pinMode(playerTwoPin, INPUT);

  for (int i = 0; i <= 5; i++) {
    int currentLedPin = ledPins[i]; // sets currentLedPin to be the i'th number in the ledPins array
    pinMode(currentLedPin, OUTPUT); // set pin mode to output
  }

  // ----- Turn off all lights (to reset and prep them)
  for (int i = 0; i <= 5; i++) {
    int currentLedPin = ledPins[i]; // sets currentLedPin to be the i'th number in the ledPins array
    digitalWrite(currentLedPin, LOW); // turn off the LED
  }
}

void loop() {

  // ----- Gets the state of each button (remember, LOW means the button is pushed)
  int playerOneButtonState = digitalRead(playerOnePin);
  int playerTwoButtonState = digitalRead(playerTwoPin);

  // ----- We only allow playerOne to have input if the LEDs are on his or her side (and vice versa)
  if (currentPlayerSide == 1 && playerOneButtonState == LOW) {

    currentPlayerSide = 2; // switch sides

    // send the LEDs "upstream"
    for (int i = 1; i <= 5; i++) {
      int previousLedPin = ledPins[i - 1]; // sets previousLedPin to be (i - 1)'st number in ledPins array
      int currentLedPin = ledPins[i]; // sets currentLedPin to be the i'th number in the ledPins array

      digitalWrite(previousLedPin, LOW); // turn off the previous LED
      digitalWrite(currentLedPin, HIGH); // turn on the current LED
      delay(gameLedDelay);
    }

  } else if (currentPlayerSide == 2 && playerTwoButtonState == LOW) {

    currentPlayerSide = 1; // switch sides

    // send the LEDs "downstream"
    for (int i = 4; i >= 0; i--) {
      int previousLedPin = ledPins[i + 1]; // sets previousLedPin to be (i + 1)'st number in ledPins array
      int currentLedPin = ledPins[i]; // sets currentLedPin to be the i'th number in the ledPins array

      digitalWrite(previousLedPin, LOW); // turn off the previous LED
      digitalWrite(currentLedPin, HIGH); // turn on the current LED
      delay(gameLedDelay);
    }

  }
}
