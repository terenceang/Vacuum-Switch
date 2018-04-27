/****************************************************************
* VacuumSwitch.ino
*
* Author : Terence Ang
*
* Firmware for Auto Vacuum Switch.
*
* This code is Partsware; send me any useful unsed parts if 
* you've found our code helpful. 
*
* Distributed as-is; no warranty is given.
***************************************************************/

#define THR 10 // currentValue Threshold
#define onDLY 300 // Turn On delay = 1sec
#define offDLY 6000 // Turn Off delay = 5sec
#define HoldValue 700 // how long before switch off delay is activated.
#define SSR D1 //Pin for SSR.
#define modeSwitch D3 // Auto or manual mode - Auto = Low

int currentValue = 0;
#define debug

// the setup routine runs once when you press reset:
void setup() {
	// initialize serial communication at 9600 bits per second:
	Serial.begin(115200);
	pinMode(SSR, OUTPUT);
	pinMode(modeSwitch, INPUT_PULLUP);
	digitalWrite(modeSwitch, HIGH);
}

uint16_t ctValue = 0; 
// the loop routine runs over and over again forever:
void loop() {

	//Check modeSwitch - if mode switch is off (manual) keep the SSR on.
	if (digitalRead(modeSwitch)) {
		ctValue = analogRead(A0); //read the sensor value.
	}
	else
	{
		ctValue = THR + 1; // keep the sensorValue above Threshold level to keep the SSR on
	}

	Serial.println(digitalRead(modeSwitch));

	//Check CT for current flow
	if (ctValue > THR) {
		currentValue += 5; //abitary number, got it by testing against actual value.
		if (currentValue >= HoldValue) currentValue = offDLY; // set max values to prevent overflow.
	}
	else {
		currentValue--;
		if (currentValue <= 0) currentValue = 0; //set min value to prevent underflow.
	}

#ifdef debug
	Serial.print(ctValue);
	Serial.print(" : ");
	Serial.println(currentValue);
#endif

	if (currentValue > onDLY) {
		digitalWrite(SSR, HIGH); //turn on SSR after CT signal is pn for est 1 sec or so, to prevent inrush current from tripping the circuit.
	}
	else
	{
		digitalWrite(SSR, LOW); //turn off SSR after 5 secs delay, to clean up left over debri while the bandsaw is powering down.
	}
}


