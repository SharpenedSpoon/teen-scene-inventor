/*

The Love Meter (Analog version)

Purpose:
  This (unfortunately named - see http://en.wikipedia.org/wiki/Love_tester_machine )
  program will read in the temperature from a sensor and light up LEDs correspondingly.
  Unlike the other Love Meter, this one will light up LEDs with varying brightness,
  instead of just turning them on or off. As such, we need to connect the LEDs to
  pins with PWM support.

Hardware:
  * Temperature sensor connected to A0
  * 6 LEDs, connected to pins 3, 5, 6, 9, 10, 11

*/

int sensorPin = A0;
int ledPins[] = {3, 5, 6, 9, 10, 11};

void setup() {
  for (int i = 0; i < 6; i++) {
    int currentLedPin = ledPins[i]; // sets currentLedPin to be the i'th number in the ledPins array
    pinMode(currentLedPin, OUTPUT); // set pin mode to output
  }
}

void loop() {

  // ----- Turn off all lights (to reset and prep them)
  for (int i = 0; i < 6; i++) {
    int currentLedPin = ledPins[i]; // sets currentLedPin to be the i'th number in the ledPins array
    digitalWrite(currentLedPin, LOW); // turn off the LED
  }

  // ----- Figure out what temperature it is
  int sensorValue = analogRead(sensorPin); // gives value from 0 - 1023

  float sensorVolts = sensorValue * (5.0 / 1024.0); // converts to equivalent voltage between 0.0V and 5.0V

  float degC = (sensorVolts - 0.5) * 100.0; // converts voltage to temperature in celsius

  float degF = (degC * 9.0/5.0) + 32.0; // converts celsius to farenheit


  // ----- Figure out how many lights to light up
  int highestLedPinToTurnOn;
  float lowestTemperatureToSense = 65.0;
  float temperatureIntervalSize = 5.0;
  // example: lowest = 65, interval = 5. Then we measure if the temperature is greater than
  // 65 - if so light the first LED. If the temp is greater than 70 then the first and second
  // LEDs will be on with some brightness. If the temp is greater than 75..... and so on.
  for (int i = 0; i < 6; i++) {
    int currentLedPin = ledPins[i]; // sets currentLedPin to be the i'th number in the ledPins array
    float currentMinTempToCheck = lowestTemperatureToSense + (i * temperatureIntervalSize);
    float currentMaxTempToCheck = lowestTemperatureToSense + ((i + 1) * temperatureIntervalSize);

    int currentLightLevel = mapTemperatureToLightLevel(degF, currentMinTempToCheck, currentMaxTempToCheck);
    analogWrite(currentLedPin, currentLightLevel);
  }

  delay(300); // give a delay between checks
}

/*
 * This function takes a temperature and the low & high values of a temperature interval
 * to test.
 * Example:
 *     We test temperatures against an interval of 65 - 70 degrees Farenheit.
 *     A temperature of 60 degrees will give a light value of 0 (no light)
 *     A temperature of 75 degrees will give a light value of 255 (full brightness)
 *     A temperature of 67.5 degrees will give a light value of 128 (about half brightness)
 */
int mapTemperatureToLightLevel(float temperature, float minTemperatureValue, float maxTemperatureValue) {
  int output;
  if (temperature <= minTemperatureValue) {
    output = 0;
  } else if (temperature >= maxTemperatureValue) {
    output = 255;
  } else {
    // we are inside the interval, so scale the brightness appropriately
    output = 255 * ( (temperature - minTemperatureValue) / (maxTemperatureValue - minTemperatureValue) );
  }

  return output;
}
