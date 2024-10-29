import serial
import sys
import os

port = '/dev/ttyACM0'
baudrate = 9600

try:
    ser = serial.Serial(port, baudrate, timeout=1)
    print(f"Serial port {port} opened successfully.")
except serial.SerialException as e:
    print(f"Error opening serial port: {e}")
    sys.exit(1)

def clear_screen():
    if os.name == 'nt':
        os.system('cls')
    else:
        print("\033[2J\033[H", end='')

try:
    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            
            clear_screen()
            
            dizi = line.split(",");
            for i in dizi:
                print(i)

except KeyboardInterrupt:
    print("\nExiting...")
    
finally:
    ser.close()
