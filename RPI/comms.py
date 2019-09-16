#!/user/bin/env python
from time import sleep
import serial
from rubik_solver import utils
from pic import manual_analyse, analyse

# Format into single instruction list from solution
def format_instruction_list(ins):
    ins = " ".join(str(e) for e in ins)
    ins = ins.split(" ")
    # Decode moves
    moves = []
    for mov in ins:
        if len(mov) == 1:
            moves.append(mov.encode())
        else:
            if mov[1] != "'":
                moves.append(mov[0].encode())
                moves.append(mov[0].encode())
            else:
                moves.append(chr(ord(mov[0]) + 1).encode())
    return moves

# Open serial communication with Arduino Mega
ser = serial.Serial("/dev/ttyUSB0", 9600) # Establish the connection on a specific port
ser.flushInput()

cube = ""
moves = []
arduino_ready = False

while True:
    
    if ser.inWaiting() > 0:
        
        rx = ser.read() # Read one byte
        
        # Check if arduino is now ready
        if not arduino_ready:
            if ord(rx) == 90:
                arduino_ready = True
                print("Arduino ready signal received.")
                # Tell arduino to begin showing faces for scanning
                ser.write(chr(80).encode())
                print("Starting face scanning procedure...")
        else:
            if ord(rx) == 91: # Shown a face
                # Take image and scan
                print("Scanning face...")
                cube += analyse()
                # Show next face
                ser.write(chr(80).encode())
                print("Showing next face...")
            elif ord(rx) == 92: # Finished showing all faces and reset
                # Calculate solution
                print("Calculating solution...")
                solution = utils.solve(cube, 'Kociemba')
                # Format into list of instructions
                print("Formatting solution into simple instructions...")
                moves = format_instruction_list(solution)
                # Break if failed to calculate
                if not moves:
                    break
                # Send first move
                print("Sending move: {0}".format(moves[0]))
                ser.write(moves.pop(0))
            elif ord(rx) == 93: # Finished a move
                # Send next move
                print("Sending move: {0}".format(moves[0]))
                ser.write(moves.pop(0))
                # Check if moves list is now empty
                if not moves:
                    break
                
        ser.flush()

print("Rubik's solve complete!")
# Close serial connection
print("Closing serial connection...")
ser.close()
print("End.")