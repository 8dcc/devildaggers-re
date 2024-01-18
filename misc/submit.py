#!/usr/bin/python

# Usage: https://github.com/8dcc/devildaggers-re

import time
import keyboard
from pymouse import PyMouse
from PIL import Image, ImageGrab

# Seconds, accepts decimals
SCORE_TIME = 312.5
WALK_TIME  = 8

def main():
    m = PyMouse()

    print("Pause the game and move the mouse to the \"Play\" text.")
    print("Getting position in 5 seconds...")
    time.sleep(5)

    x_pos, y_pos = m.position()
    print(f"Starting in 5 seconds with menu position: ({x_pos}, {y_pos})")
    time.sleep(5)

    # FIXME: exit() doesn't exit the program, see boppreh/keyboard#626
    keyboard.on_press_key("F4", lambda event: print("TODO"))
    print(f"Exit by pressing F4.")

    # Click "Play"
    m.press(x_pos, y_pos)
    time.sleep(0.05)
    m.release(x_pos, y_pos)
    time.sleep(0.5)

    # Walk to dagger
    keyboard.press("w")
    time.sleep(2)
    keyboard.release("w")

    try:
        # Submit infinite scores
        while True:
            time.sleep(0.5)

            # Wait round time, look down and hold attack
            m.press(x_pos, y_pos + 200)
            time.sleep(SCORE_TIME)
            m.release(x_pos, y_pos + 200)

            # SCORE_TIME seconds have passed, kill ourselves by fall
            keyboard.press("w")
            time.sleep(WALK_TIME)
            keyboard.release("w")

            # Wait for death screen
            time.sleep(2)

            # Click "Retry"
            m.press(x_pos, y_pos)
            time.sleep(0.05)
            m.release(x_pos, y_pos)
    except KeyboardInterrupt:
        print("\rCtrl-C detected. Exiting...")

if __name__ == '__main__':
    main()
