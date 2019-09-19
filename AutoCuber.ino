#include "MotorDriver.h"
#include "CubeRotate.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <avr/wdt.h>
#include "RotaryEncoder.h"

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

RotaryEncoder rc(38, 37, 36);

MotorDriver M1 = MotorDriver(2, 3);
MotorDriver M2 = MotorDriver(4, 5);
MotorDriver M3 = MotorDriver(6, 7);
MotorDriver M4 = MotorDriver(8, 9);

MotorDriver M5 = MotorDriver(22, 23);
MotorDriver M6 = MotorDriver(24, 25);
MotorDriver M7 = MotorDriver(26, 27);
MotorDriver M8 = MotorDriver(28, 29);

CubeRotate CR = CubeRotate(M1, M2, M3, M4, M5, M6, M7, M8);

int face = 1;

bool rpi_ready = false;
bool solve_mode = false;

void reset_device() {
	wdt_enable(WDTO_15MS); // turn on the WatchDog and don't stroke it.
	for (;;) { 
		// do nothing and wait for the eventual...
	}
}

void setup()
{
	Serial.begin(9600);

	lcd.begin(20, 4);
	lcd.clear();
	lcd.backlight();

	lcd.setCursor(0, 1);
	lcd.print("Starting up...");

	MCUSR = 0;  // clear out any flags of prior resets.
}

void loop() {

	if (!rpi_ready) {
		delay(200);
		Serial.write(90);
	}

	if (Serial.available() > 0) {

		int rx, iterations;
		if (!solve_mode) {
			rx = Serial.read();
		}
		else {
			while (Serial.available() < 2);
			rx = Serial.read();
			iterations = Serial.read() - 48;
		}

		if (rx == 79) {
			if (!rpi_ready) {
				rpi_ready = true;
			}

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

			while (!rc.PollSwitch()) {
				int change = rc.PollRotate();
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

			switch (selection) {
				case 0:
					lcd.clear();
					lcd.setCursor(0, 1);
					lcd.print("Solving cube...");
					// lcd.setCursor(0, 2);
					// lcd.print("Press to cancel.");
					Serial.write(95);
					break;
				case 1:
					lcd.clear();
					lcd.setCursor(0, 1);
					lcd.print("Scrambling cube...");
					// lcd.setCursor(0, 2);
					// lcd.print("Press to cancel.");
					//CR.Scramble();
					solve_mode = true;
					Serial.write(99);
					//Serial.flush();
					//reset_device();
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
			reset_device();
		}

		switch(rx) {
			case 80:

				if (!rpi_ready) {
					rpi_ready = true;
				}

				CR.ShowNext(face);
				face += 1;

				// Tell RPI that face operation has finished (92 if totally finished, 91 if only side finished)
				if (face > 7) {
					Serial.write(92);
					solve_mode = true;
				} else {
					Serial.write(91);
				}

				break;
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

		Serial.flush();
	}
}
