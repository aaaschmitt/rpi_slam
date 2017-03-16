#include "Arduino.h"
#include "Servo.h"
#include "Wire.h"

#define INT_SIZE sizeof(int)
#define LONG_SIZE sizeof(long)

// Servo
Servo servo;
#define SERVO_PIN 9
#define TRIGGER_PIN 5
#define ECHO_PIN 6


// I2C
#define SLAVE_ADDRESS 0x04
#define I2C_PIN 13
bool sendData = 0;

void setup()
{
	Serial.begin(9600);
	setupServo();
	setupI2C();
}

void loop()
{
	// The main loop is in sendDisanceData
	Serial.print("Stuff is not here anymore");
}

void setupServo() {
	pinMode(TRIGGER_PIN, OUTPUT);
	pinMode(ECHO_PIN, INPUT);
	servo.attach(SERVO_PIN, 0, 180); // pwm pin 9, with min and max degree
}

void setupI2C() {
	pinMode(I2C_PIN, OUTPUT);
	Wire.begin(SLAVE_ADDRESS);
	Wire.onReceive(receiveData);
	Wire.onRequest(sendDistanceData);
}

void receiveData(int byteCount){
	if (byteCount) {
		while(Wire.available()) {
			sendData = Wire.read();
		}
	}
}

void sendDistanceData(void) {
	while(sendData) {
		servo.write(0);
		unsigned long distance = 0;
		for (int degree = 0; degree < 180; degree += 5) {
			servo.write(degree);
			delay(10);
			distance = calculateDistance(TRIGGER_PIN, ECHO_PIN);
			Wire.write('$');
			Wire.write(distance);
			Wire.write('|');
			Wire.write(degree);
			Wire.write('$');
		}
	}
}

/**
 * Function for calculating the distance measured by the Ultrasonic sensor
 */
unsigned long calculateDistance(int triggerPin, int echoPin){

	// Send a sound wave pulse on the trigger pin
	digitalWrite(triggerPin, LOW);
	delayMicroseconds(2);
	digitalWrite(triggerPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(triggerPin, LOW);

	// Listen for the bounce back
	unsigned long duration = pulseIn(echoPin, HIGH);
	unsigned long distance= duration * 0.034 / 2.0;
	return distance;
}
