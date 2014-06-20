/*

Bomb Counter

Purpose:
  Written by one of my students! When you press the button, it starts a countdown until
  it gets to 0, then explodes and waits for a button press to reset to start.
  
Hardware:
  * LED wired to 7
  * Button wired to 6
  * LCD display
  * Buzzer wired to 9

*/

int led = 7;
const int button1Pin = 6;
int timeleft = 10;
#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);
const int buzzerPin = 9;
const int songLength = 1;
char notes[] = "c"; 
int beats[] = {4};
int tempo = 150;

boolean waiting=true;

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Tactical Nuke");
  pinMode(buzzerPin, OUTPUT);
  pinMode(button1Pin, INPUT);
}


void loop() {
  int button1State;
  button1State = digitalRead(button1Pin);
  while (waiting && button1State == HIGH) {
    button1State = digitalRead(button1Pin);
  }
  waiting = false;
  timeleft--;
  if (timeleft < 0) {
    lcd.setCursor(0,1);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print("BOOM!!");
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,0);
    lcd.print("BOOM!!");
    
    // wait to be reset
    button1State = digitalRead(button1Pin);
    while (button1State == HIGH) {
      button1State = digitalRead(button1Pin);
    }
    
    timeleft = 10;
    waiting = true;
    delay(100);
    lcd.clear();
    lcd.print("Tactical Nuke");

  } else {
    lcd.setCursor(0,1);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print("Inbound ETA: " + String(timeleft));

    digitalWrite (led, HIGH);
    
    int i, duration;
    for (i = 0; i < songLength; i++) 
    {
      duration = beats[i] * tempo;  
      if (notes[i] == ' ')          
      {
        delay(duration);           
      }
      else                          
      {
        tone(buzzerPin, frequency(notes[i]), duration);
        delay(duration); 
        digitalWrite (led, LOW);             
      }
      delay(1000);            
    }
  }

}




int frequency(char note) 
{
  int i;
const int numNotes = 8;  // number of notes we're storing
char names[] = {'c'};
int frequencies[] = {262};
for (i = 0; i < numNotes; i++)  
{
  if (names[i] == note)         
  {
    return(frequencies[i]);     
  }
}
return(0);  
}
