from serial import Serial
import pyautogui
import time

# Windows example ports -> ser = serial.Serial('COM6', 9600, timeout=1)
# macOS example ports -> ser = serial.Serial('/dev/cu.HC-06', 9600, timeout=1)
ser = Serial('COM9', 9600, timeout=1)
ser1 = Serial('COM11', 9600, timeout=1)


time.sleep(2)


previous_status = "NONE"
previous_status_1 = "NONE"
while True:
    if ser.in_waiting:
        # Read a line from the serial buffer, decode and strip whitespace
        line = ser.readline().decode('utf-8').strip()
        print("Received:", line)

        # Map the received command to the corresponding keystroke
        if line == "LEFT" and previous_status != "LEFT":
            print("Triggering LEFT arrow key")
            pyautogui.press('left')
            previous_status = "LEFT"
        elif line == "RIGHT" and previous_status != "RIGHT":
            print("Triggering RIGHT arrow key")
            pyautogui.press('right')
            previous_status = "RIGHT"
        elif line == "DUCK" and previous_status != "DUCK":
            print("Triggering DOWN arrow key (DUCK)")
            pyautogui.press('down')
            previous_status = "DUCK"
        elif line == "JUMP" and previous_status != "JUMP":
            print("Triggering UP arrow key (JUMP)")
            pyautogui.press('up')
            previous_status = "JUMP"
        elif line == "NONE":
            previous_status = "NONE"

    if ser1.in_waiting:
        # Read a line from the serial buffer, decode and strip whitespace
        line1 = ser1.readline().decode('utf-8').strip()
        print("Received:", line1)
        # Map the received command to the corresponding keystroke
        if line1 == "LEFT" and previous_status_1 != "LEFT":
            print("Triggering LEFT arrow key")
            pyautogui.press('left')
            previous_status_1 = "LEFT"
        elif line1 == "RIGHT" and previous_status_1 != "RIGHT":
            print("Triggering RIGHT arrow key")
            pyautogui.press('right')
            previous_status_1 = "RIGHT"
        elif line1 == "DUCK" and previous_status_1 != "DUCK":
            print("Triggering DOWN arrow key (DUCK)")
            pyautogui.press('down')
            previous_status_1 = "DUCK"
        elif line1 == "JUMP" and previous_status_1 != "JUMP":
            print("Triggering UP arrow key (JUMP)")
            pyautogui.press('up')
            previous_status_1 = "JUMP"
        elif line1 == "NONE":
            previous_status_1 = "NONE"