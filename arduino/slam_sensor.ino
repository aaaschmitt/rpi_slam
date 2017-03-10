#include "Arduino.h"
#include "Servo.h"

Servo servo;

static int SERVO_PIN = 9;
static int TRIGGER_PIN = 5;
static int ECHO_PIN = 6;

void setup()
{
	pinMode(TRIGGER_PIN, OUTPUT);
	pinMode(ECHO_PIN, INPUT);
	servo.attach(SERVO_PIN, 0, 180); // pwm pin 9, with min and max degree
}

void loop()
{
	Serial.begin(9600);
	servo.write(0);
	unsigned long distance = 0;
	for (int degree = 0; degree < 180; degree += 5) {
		servo.write(degree);
		delay(500);
		distance = calculateDistance(TRIGGER_PIN, ECHO_PIN);
		sendDistance(distance, degree);
	}
}

void sendDistance(long distance, int theta) {
	Serial.print("$");
	Serial.print(distance);
	Serial.print("|");
	Serial.print(theta);
	Serial.print("$\n");
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
