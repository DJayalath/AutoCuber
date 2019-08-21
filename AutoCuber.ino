// Define pin connections & motor's steps per revolution
const int dirPin = 4;
const int stepPin = 3;
const int stepsPerRevolution = 200;

int steps = 0;

void setup()
{
	// Declare pins as Outputs
	pinMode(stepPin, OUTPUT);
	pinMode(dirPin, OUTPUT);
}
void loop()
{
	// Set motor direction clockwise
	digitalWrite(dirPin, HIGH);

	// Spin motor slowly
	for (int x = 0; x < stepsPerRevolution; x++)
	{
		digitalWrite(stepPin, HIGH);
		delayMicroseconds(1000);
		digitalWrite(stepPin, LOW);
		delayMicroseconds(1000);
		steps++;
		if (steps >= 200) {
			steps = 0;
		}
	}
	delay(1000); // Wait a second

	// Set motor direction counterclockwise
	digitalWrite(dirPin, LOW);

	// Spin motor quickly
	for (int x = 0; x < stepsPerRevolution; x++)
	{
		digitalWrite(stepPin, HIGH);
		delayMicroseconds(1000);
		digitalWrite(stepPin, LOW);
		delayMicroseconds(1000);
		steps--;
		if (steps <= -1) {
			steps = 199;
		}
	}
	delay(1000); // Wait a second
}