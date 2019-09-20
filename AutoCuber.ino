// Signal transmission
#include <Wire.h>
// Controlling LCD
#include <LiquidCrystal_I2C.h>
// Resetting arduino
#include <avr/wdt.h>

// Making rotations and moving rails
#include "CubeRotate.h"
// Interpretting rotary encoder inputs
#include "RotaryEncoder.h"

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
RotaryEncoder rc(38, 37, 36);
CubeRotate CR = CubeRotate(Rail(2, 3, 4, 5), Rail(6, 7, 8, 9), Rail(22, 23, 24, 25), Rail(26, 27, 28, 29));

// Set starting face
int face = 1;

// Set starting states
bool rpi_ready = false;
bool solve_mode = false;

// Resets arduino after putting rails in default state (extended and vertical)
void reset_device() {
	CR.RestoreDefaultState();
	// Turn on the WatchDog and don't stroke it
	wdt_enable(WDTO_15MS);
	// Do nothing and wait for the eventual...
	for (;;) {}
}

void setup()
{
	// Open serial connection with 9600 bps baudrate
	Serial.begin(9600);

	// Initialise LCD (20 columns, 4 rows)
	lcd.begin(20, 4);
	lcd.clear();
	lcd.backlight();

	// Output starting message
	lcd.setCursor(0, 0);
	lcd.print("AutoCuber");
	lcd.setCursor(0, 1);
	lcd.print("by Dulhan Jayalath");
	lcd.setCursor(0, 2);
	lcd.print("Connecting to RPI3B");
	lcd.setCursor(0, 3);
	lcd.print("Please wait ...");

	MCUSR = 0;  // Clear out any flags of prior resets
}

void loop() {

	// While waiting for connection, send ready signal to RPI
	if (!rpi_ready) {
		delay(200);
		Serial.write(90);
	}

	if (Serial.available() > 0) {

		int rx, iterations;
		// Read one byte in normal mode (Single character instruction)
		if (!solve_mode) {
			rx = Serial.read();
		}
		// Read two bytes in solve mode (Single character instruction + Number of iterations)
		else {
			while (Serial.available() < 2);
			rx = Serial.read();
			iterations = Serial.read() - 48;
		}

		// 79 is RPI ready signal
		if (rx == 79) {

			// Set RPI to ready state
			if (!rpi_ready) {
				rpi_ready = true;
			}

			// Start option selection dialog
			int selection = 0;

			lcd.clear();
			lcd.setCursor(0,0);
			lcd.print("1. Solve Cube");
			lcd.setCursor(0, 1);
			lcd.print("2. Scramble Cube");
			lcd.setCursor(0, 2);
			lcd.print("3. Exit");
			lcd.setCursor(0, 3);
			lcd.print("Selected: 1");
			lcd.setCursor(0, 0);
			lcd.cursor();

			// Change selection on rotation and wait for
			// push button to be pressed
			while (!rc.PollSwitch()) {

				// Get rotation
				int change = rc.PollRotate();

				// Only refresh display if a change is made
				if (change != 0) {
					selection -= change;
					if (selection < 0) {
						selection += 3;
					} else if (selection > 2) {
						selection -= 3;
					}

					lcd.setCursor(10, 3);
					lcd.print(String(selection + 1));
					lcd.setCursor(0, selection);
				}
			}

			lcd.cursor();

			// Act on selection
			switch (selection) {
				case 0:
					lcd.clear();
					lcd.setCursor(0, 1);
					lcd.print("Solving cube...");
					Serial.write(95);
					break;
				case 1:
					lcd.clear();
					lcd.setCursor(0, 1);
					lcd.print("Scrambling cube...");
					solve_mode = true;
					Serial.write(99);
					break;
				case 2:
					Serial.write(98);
					Serial.flush();
					lcd.clear();
					lcd.setCursor(0, 1);
					lcd.print("Powering off...");
					for (;;) {}
					break;
			}
		} else if (rx == 'Z') {
			// Z signal always indicates something has completed and it is
			// now time to reset the arduino
			reset_device();
		}

		switch(rx) {
			// 80 is signal for showing a new face
			case 80:

				// Show the next face
				CR.ShowNext(face);
				// Increment face for next time
				face += 1;

				// Tell RPI that face operation has finished (92 if totally finished, 91 if only side finished)
				if (face > 7) {
					Serial.write(92);
					solve_mode = true;
				} else {
					Serial.write(91);
				}

				break;
			// General rotations
			// 93 message indicates the operation has finished
			case 'R':
				CR.R(iterations);
				Serial.write(93);
				break;
			case 'S':
				CR.R(iterations, true);
				Serial.write(93);
				break;
			case 'L':
				CR.L(iterations);
				Serial.write(93);
				break;
			case 'M':
				CR.L(iterations, true);
				Serial.write(93);
				break;
			case 'U':
				CR.U(iterations);
				Serial.write(93);
				break;
			case 'V':
				CR.U(iterations, true);
				Serial.write(93);
				break;
			case 'D':
				CR.D(iterations);
				Serial.write(93);
				break;
			case 'E':
				CR.D(iterations, true);
				Serial.write(93);
				break;
			case 'F':
				CR.Fr(iterations);
				Serial.write(93);
				break;
			case 'G':
				CR.Fr(iterations, true);
				Serial.write(93);
				break;
			case 'B':
				CR.B(iterations);
				Serial.write(93);
				break;
			case 'C':
				CR.B(iterations, true);
				Serial.write(93);
				break;
			case 'Y':
				CR.Y(iterations);
				Serial.write(93);
				break;
		}

		// Wait for all write operations to complete
		Serial.flush();
	}
}
