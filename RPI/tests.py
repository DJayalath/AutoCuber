import kociemba
from time import sleep

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


scan_order = ['U', 'L', 'F', 'R', 'B', 'D']
required_order = ['U', 'R', 'F', 'D', 'L', 'B']
cube = {}

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

for face in scan_order:
    cube[face] = input("Enter face {0}: ".format(face))

# Re-organise scan order
cube_formatted = ""
for face in required_order:
    cube_formatted += cube[face]
# Convert to cube string notation
cube_formatted = cube_string_notation(cube_formatted, required_order)
solution = kociemba.solve(cube_formatted)
print(solution)