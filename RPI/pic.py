from picamera import PiCamera
from time import sleep
from PIL import Image
import numpy as np
import scipy
import scipy.misc
import scipy.cluster
import binascii
import struct
from colormath.color_objects import LabColor, sRGBColor
from colormath.color_conversions import convert_color

camera = PiCamera()
camera.resolution = (1000, 1000)
camera.framerate = 30
sleep(2)
camera.shutter_speed = camera.exposure_speed
camera.exposure_mode = 'off'
g = camera.awb_gains
camera.awb_mode = 'off'
camera.awb_gains = g

area = (445, 320, 815, 690)
rot = 44

def analyse():
    
    camera.capture('/home/pi/Pictures/image.png')
    img = Image.open('/home/pi/Pictures/image.png')
    img = img.rotate(rot)
    img = img.rotate(270)
    #img.save('/home/pi/Pictures/image.jpg')
    img = img.crop((200, 350, 800, 900))
    
    #img = Image.open("/home/pi/Pictures/rubiks-side-B.png")
    img = img.rotate(2)
    img = img.crop((110, 95, 475, 460))
    #img.save('/home/pi/Pictures/cropped.png')
    
    width, height = img.size
    incr = float(width) / 3.0
    
    colours = []
    for i in range(3):
        for j in range(3):
            # Find dominant colour
            im = img.crop((incr * j, incr * i, incr * j + incr, incr * i + incr)).resize((150, 150))
            #im = cropped_img.resize((150, 150))
            ar = np.asarray(im)
            shape = ar.shape
            ar = ar.reshape(scipy.product(shape[:2]), shape[2]).astype(float)

            # Find clusters
            NUM_CLUSTERS = 6
            codes, dist = scipy.cluster.vq.kmeans(ar, NUM_CLUSTERS)

            vecs, dist = scipy.cluster.vq.vq(ar, codes)
            counts, bins = scipy.histogram(vecs, len(codes))

            index_max = scipy.argmax(counts)
            peak = codes[index_max]
            colours.append([peak[0], peak[1], peak[2]])
    
    # Convert to HSL (H-only) - Ensures lighting independance
    hsl = []
    actual = []
    for colour in colours:
        r = colour[0] / 255.0
        g = colour[1] / 255.0
        b = colour[2] / 255.0        
        mx = max(r, g, b)
        mn = min(r, g, b)
        
        l = (mn + mx) / 2.0
        
        if l < 0.5:
            s = (mx - mn) / (mx + mn)
        else:
            s = (mx - mn) / (2.0 - mx - mn)
        
        if mn == mx:
            s = 0
        
        if mx == r:
            h = (g - b) / (mx - mn)
        elif mx == g:
            h = 2.0 + (b - r) / (mx - mn)
        elif mx == b:
            h = 4.0 + (r - g) / (mx - mn)
        h *= 60
        if h < 0:
            h += 360
        hsl.append((h, s, l))
        if s < 0.3:
            actual.append("w")
        else:
            actual.append("unknown")
    colours = hsl
    
    known_colours = {"r": (342, 0.80, 0.5), "b": (194, 0.98, 0.5), "g": (128, 1.0, 0.5), "y": (78, 1.0, 0.5), "o": (13.7, 0.72, 0.5)}

    for i in range(len(colours)):
        if actual[i] != "w":
            best_dist = 99e9
            best_colour = "unknown"
            for key, value in known_colours.items():
                h, s, l = value
                s *= 360 # Normalize
                a, b, c = colours[i]
                b *= 360 # Normalize
                dist = abs(h - a) + abs(s - b)
                if dist < best_dist:
                    best_dist = dist
                    best_colour = key
            actual[i] = (best_colour)
    
    actual = ''.join(actual)
    print(colours)
    print(actual)
#    y = input("Correct? y/n")
#    if y == "n":
#        actual = input("Enter actual: ")
    return actual

def simple(s):
    camera.capture('/home/pi/Pictures/image.png')
    img = Image.open('/home/pi/Pictures/image.png')
    img = img.rotate(rot)
    img = img.rotate(270)
    #img.save('/home/pi/Pictures/image.jpg')
    img = img.crop((200, 350, 800, 900))
    img.save("/home/pi/Pictures/rubiks-side-{0}.png".format(s))
    return 'b'

def test():
    camera.capture('/home/pi/Pictures/image.jpg')
    img = Image.open('/home/pi/Pictures/image.jpg')
    img = img.rotate(rot)
    img.save('/home/pi/Pictures/image.jpg')
    cropped_img = img.crop(area)
    #cropped_img = cropped_img.rotate(270)
    cropped_img.save('/home/pi/Pictures/image.jpg')

def analyse_face():
    camera.capture('/home/pi/Pictures/image.png')

    img = Image.open('/home/pi/Pictures/image.png')
    img = img.rotate(rot)
    img = img.rotate(270)
    #img.save('/home/pi/Pictures/image.png'.format(s))
    cropped_img = img.crop(area)
    cropped_img.save('/home/pi/Pictures/image.png')

    colours = []
    for i in range(3):
        for j in range(3):
            # Find dominant colour
            im = cropped_img.crop((123.33 * j, 123.33 * i, 123.33 * j + 123.33, 123.33 * i + 123.33)).resize((150, 150))
            #im = cropped_img.resize((150, 150))
            ar = np.asarray(im)
            shape = ar.shape
            ar = ar.reshape(scipy.product(shape[:2]), shape[2]).astype(float)

            # Find clusters
            NUM_CLUSTERS = 6
            codes, dist = scipy.cluster.vq.kmeans(ar, NUM_CLUSTERS)

            vecs, dist = scipy.cluster.vq.vq(ar, codes)
            counts, bins = scipy.histogram(vecs, len(codes))

            index_max = scipy.argmax(counts)
            peak = codes[index_max]
            colours.append([peak[0], peak[1], peak[2]])
            
    # Convert to HSL (H-only) - Ensures lighting independance
    hsl = []
    for colour in colours:
        r = colour[0] / 255.0
        g = colour[1] / 255.0
        b = colour[2] / 255.0        
        mx = max(r, g, b)
        mn = min(r, g, b)
        
        l = (mn + mx) / 2.0
        
        if l < 0.5:
            s = (mx - mn) / (mx + mn)
        else:
            s = (mx - mn) / (2.0 - mx - mn)
        
        if mn == mx:
            s = 0
        
        if mx == r:
            h = (g - b) / (mx - mn)
        elif mx == g:
            h = 2.0 + (b - r) / (mx - mn)
        elif mx == b:
            h = 4.0 + (r - g) / (mx - mn)
        h *= 60
        if h < 0:
            h += 360
        hsl.append((h, s, l))
    colours = hsl

    # R B G W Y O
    known_colours = {"r": (0, 1), "b": (240, 1), "g": (120, 1), "w": (0, 0), "y": (60, 1), "o": (39, 1)}
    
    # Convert to Lab
    #for key, value in known_colours.items():
    #    known_colours[key] = convert_color(value, LabColor, target_illuminant='d65')
    #print(colours)
    
    actual = []
    for color in colours:
        best_dist = 99e9
        best_colour = "unknown"
        for key, value in known_colours.items():
            r, g = value
            l, a, b = color
            dist = abs(l - r) + abs(a - g)
            if dist < best_dist:
                best_dist = dist
                best_colour = key
        actual.append(best_colour)

    actual = ''.join(actual)
        
    print(colours)
    print(actual)
#    y = input("Correct? y/n")
#    if y == "n":
#        actual = input("Enter actual: ")
    return actual

def manual_analyse():
    man = input("Enter string: ")
    return man

if __name__ == "__main__":
    analyse()
