#!/user/bin/env python
from time import sleep
import serial
import kociemba
from pic import manual_analyse, analyse

def human_comms():
    print("Hello, I am...\n")
    sleep(.8)
    print("S ystematic")
    sleep(.4)
    print("A ndroid")
    sleep(.4)
    print("N etwork")
    sleep(.4)
    print("D iode")
    sleep(.4)
    print("E nergy")
    sleep(.4)
    print("R ubik's")
    sleep(.4)
    print("S ystem\n")
    sleep(.4)
    print("But you may call me Sanders...\n")
    sleep(1.5)
    print("Just as Kentucky Fried Chicken's secret process unlocks the flavour, I'm going to unlock this Rubik's cube.\n")
    sleep(3.5)
    print("Now, what can Sanders do for you?\n")
    sleep(1.5)
    print("1. Solve the cube like KFC solves your hunger")
    print("2. Scramble the cube because our secret recipe will always be secret")
    print("3. There is no escape\n")
    return input("Choose your flavour (1/2/3): ")

# Converts colour blocks e.g. ooywwbgrg into cube string notation e.g. UUFBBDLRU
def cube_string_notation(colours, required_order):

    # Find centre tile of each face
    cube_string = []
    for face in required_order:
        cube_string.append(colours[required_order.index(face) * 9 + 4])

    # Map colours to cube string notation
    for color, face in zip(cube_string, required_order):
        colours = colours.replace(color, face)
    
    return colours


# Compress instructions for more efficient processing by arduino
def compress_instructions(ins):
    moves = []
    idx = 0
    while idx < len(ins):
        ndx = 1
        while True:
            if idx + ndx >= len(ins):
                break
            elif ins[idx] == ins[idx + ndx]:
                ndx += 1
            else:
                break
        moves.append((ins[idx] + str(ndx)).encode())
        idx += ndx
    return moves

# Format into single instruction list from solution
def format_instruction_list(ins):
    #ins = " ".join(str(e) for e in ins)
    ins = ins.split(" ")
    # Decode moves
    moves = []
    for mov in ins:
        if len(mov) == 1:
            moves.append(mov)
        else:
            if mov[1] != "'":
                moves.append(mov[0])
                moves.append(mov[0])
            else:
                moves.append(chr(ord(mov[0]) + 1))
    return compress_instructions(moves)

# Open serial communication with Arduino Mega
ser = serial.Serial("/dev/ttyUSB0", 9600) # Establish the connection on a specific port
ser.flushInput()

scan_order = ['U', 'L', 'F', 'R', 'B', 'D']
required_order = ['U', 'R', 'F', 'D', 'L', 'B']
cube = {}
moves = []
arduino_ready = False

print("System frying up...")

while True:
    
    if ser.inWaiting() > 0:
        
        rx = ser.read() # Read one byte
        
        # Check if arduino is now ready
        if not arduino_ready:
            if ord(rx) == 90:
                arduino_ready = True
                answer = human_comms()
                if answer == 1:
                    ser.write(chr(80).encode())
                    print("\nIt's time to show your face. Come down to the Buttermilk nebula for 11 herbs and spices you won't be able to resist.")
                elif answer == 2:
                    ser.write(chr(81).encode())
                    print("\nScramble scramble! KFC university offers free scrambled egg courses with every employment contract!")
                elif answer == 3:
                    print("\nI hope you found a seat. I want you to be safe. Goodbye.")
                    break
        else:
            if ord(rx) == 91: # Shown a face
                # Take image and scan
                print("\nI'm scanning a face... Not yours.")
                cube[scan_order[0]] = analyse()
                # Remove face from scanning stack
                scan_order.pop(0)
                # Show next face
                ser.write(chr(80).encode())
                print("\nLet's flip that cube around just like you'll be learning to flip zingers at KFC University.")
            elif ord(rx) == 92: # Finished showing all faces and reset
                print("\nTime to deep fry. I'm calculating a solution...")
                # Re-organise scan order
                cube_formatted = ""
                for face in required_order:
                    cube_formatted += cube[face]
                # Convert to cube string notation
                cube_formatted = cube_string_notation(cube_formatted, required_order)
                # Calculate solution
                #print("Calculating solution...")
                solution = kociemba.solve(cube_formatted)
                #print("Solution found!")
                # Format into list of instructions
                #print("Formatting solution into simple instructions...")
                moves = format_instruction_list(solution)
                print("\nYour order is ready.\n")
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

print("\nThis bargain bucket of bolts is done. By using this program you have agreed to a lifetime of servitude to KFC inc.")
# Close serial connection
#print("Closing serial connection...")
ser.close()
#print("End.")