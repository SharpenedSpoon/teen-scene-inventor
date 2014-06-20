/*

The Love Meter

Purpose:
	This (unfortunately named - see http://en.wikipedia.org/wiki/Love_tester_machine )
	program will read in the temperature from a sensor and light up LEDs correspondingly.

Hardware:
	* Temperature sensor connected to A0
	* 6 LEDs, connected to pins 0, 1, 2, 3, 4, 5

*/

int sensorPin = A0;
int ledPins[] = {0, 1, 2, 3, 4, 5};

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
	// LEDs will be on. If the temp is greater than 75..... and so on.
	for (int i = 0; i < 6; i++) {
		int currentLedPin = ledPins[i]; // sets currentLedPin to be the i'th number in the ledPins array
		float currentTemperatureToCheck = lowestTemperatureToSense + (i * temperatureIntervalSize);

		if (degF >= currentTemperatureToCheck) {
			digitalWrite(currentLedPin, HIGH);
		}
	}

	delay(300); // give a delay between checks
}
