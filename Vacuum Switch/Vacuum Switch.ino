
#define THR 10 // sensor Threshold
#define onDLY 300 // Turn On delay = 1sec
#define offDLY 6000 // Turn Off delay = 5sec
#define HoldValue 700 // how long before switch off delay is activated.
#define SSR D1

int currentValue = 0;

// the setup routine runs once when you press reset:
void setup() {
	// initialize serial communication at 9600 bits per second:
	Serial.begin(115200);
	pinMode(SSR, OUTPUT);
}

uint16_t sensorValue = 0; 
// the loop routine runs over and over again forever:
void loop() {

	sensorValue = analogRead(A0);

	if (sensorValue > THR) {
		currentValue += 5;
		if (currentValue >= 700) currentValue = 6000;
	}
	else {
		currentValue--;
		if (currentValue <= 0) currentValue = 0;
	}

	Serial.print(sensorValue);
	Serial.print(" : ");
	Serial.println(currentValue);

	if (currentValue > onDLY) {
		digitalWrite(SSR, HIGH);
	}
	else
	{
		digitalWrite(SSR, LOW);
	}

}


