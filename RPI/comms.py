#!/user/bin/env python
from time import sleep
import serial
from rubik_solver import utils
from pic import analyse_face, manual_analyse, simple, analyse

def calc_moves(ins):
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

ser = serial.Serial("/dev/ttyUSB0", 9600) # Establish the connection on a specific port

ser.flushInput()

scanning = 0

c = ""
moves = []
s = ['U', 'L', 'F', 'R', 'B', 'D', 'Z']
while True:
    if ser.inWaiting() > 0:
        inputValue = ser.read(1)
        if scanning < 7:
            #if scanning == 0:
            #    c += simple(s[scanning])
            #    print(c)
            ser.write(b'A')
            scanning += 1
            ready = False
            while not ready:
                if ser.inWaiting() > 0:
                    inputValue = ser.read(1)
                    if ord(inputValue) == 35:
                        print("ShowNext complete!")
                        #if scanning != 6:
                        if scanning != 7:
                            c += analyse()
                            print(c)
                        ready = True
                sleep(0.1)
        if scanning == 7:
            ins = utils.solve(c, 'Kociemba')
            moves = calc_moves(ins)
            scanning += 1
        if scanning > 7:
            ser.write(moves.pop(0))
            sleep(.1)
            if not moves:
                break
            
        sleep(.1)
    
#bwbgybbbrgoyggybwgyywrrwyyogrwrwbygwrorbbggwroowooroyo
#bwbgybbbrrorbbggwryywrrwyyogoyggybwgoowooroyogrwrwbygw
