/*

Multiplayer Button Clicker

Purpose:
  A multiplayer game where two players try to press their button as quickly as possible in a given time.

Hardware:
  * Two buttons wired to pins 8 and 9, respectively
  * LCD display

*/

#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2); // init library with pins we're using

int playerOnePin = 8;
int playerTwoPin = 9;
int playerOneScore = 0;
int playerTwoScore = 0;
int totalGameTime = 10000; // 1 "unit" is 1000 ms
int gameClock;

boolean playerOneJustPressed = false;
boolean playerTwoJustPressed = false;

void setup() {
  gameClock = totalGameTime;
  
  pinMode(playerOnePin, INPUT);
  pinMode(playerTwoPin, INPUT);
  
  lcd.begin(16, 2); // init with 2 lines of 16 characters
  lcd.clear();
  
  Serial.begin(9600);
}

void loop() {
  Serial.println(gameClock);
  if (gameClock <= 0) {
    lcd.clear();
    // print game over
    lcd.setCursor(0,0);
    lcd.print("GAME OVER");
    
    for (int i = 0; i < 3; i++) {
      delay(200);
      lcd.print("."); // DRAMATIC EFFECT!
    }
    
    delay(500);
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Winner: ");
    if (playerOneScore > playerTwoScore) {
      lcd.print("Player 1");
    } else if (playerOneScore < playerTwoScore) {
      lcd.print("Player 2");
    } else {
      lcd.print("TIE.. :(");
    }
    
    while (digitalRead(playerOnePin) != LOW && digitalRead(playerTwoPin) != LOW) {
      // wait for both buttons to be pressed to restart
    }
    
    // reset game!
    playerOneScore = 0;
    playerTwoScore = 0;
    gameClock = totalGameTime;
  } else {
    int playerOneButtonState;
    int playerTwoButtonState;
    
    playerOneButtonState = digitalRead(playerOnePin);
    playerTwoButtonState = digitalRead(playerTwoPin);
    
    gameClock = gameClock - 10;
    
    if (playerOneButtonState == LOW) { // player one button is pressed
      playerOneJustPressed = true;
    } else { // not being pressed
      if (playerOneJustPressed) { // we just released the kraken. ... I mean, button.
        playerOneJustPressed = false;
        playerOneScore = playerOneScore + 1;
      }
    }
    
    if (playerTwoButtonState == LOW) { // player two button is pressed
      playerTwoJustPressed = true;
    } else { // not being pressed
      if (playerTwoJustPressed) { // we just released the kraken. ... I mean, button.
        playerTwoJustPressed = false;
        playerTwoScore = playerTwoScore + 1;
      }
    }
    
    lcd.setCursor(0,0);
    lcd.print("P 1: " + String(playerOneScore));
    lcd.setCursor(0,1);
    lcd.print("P 2: " + String(playerTwoScore));
    
    lcd.setCursor(12, 0);
    lcd.print("TIME");
    
    lcd.setCursor(12, 1);
    lcd.print(String(gameClock / 1000));
  }
  
}
