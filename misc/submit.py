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

    # FIXME: Doesn't exit the program, see boppreh/keyboard#626
    keyboard.on_press_key("F4", lambda event: exit(1))
    print(f"Exit by pressing F4.")

    # Click "Play"
    m.press(x_pos, y_pos)
    time.sleep(0.1)
    m.release(x_pos, y_pos)

    # Walk to dagger
    keyboard.press("w")
    time.sleep(2)
    keyboard.release("w")

    try:
        # Submit infinite scores
        while True:
            # Wait round time
            time.sleep(SCORE_TIME)

            # SCORE_TIME seconds have passed, kill ourselves by fall
            keyboard.press("w")
            time.sleep(WALK_TIME)
            keyboard.release("w")

            # Wait for death screen
            time.sleep(2)

            # Click "Retry"
            m.press(x_pos, y_pos)
            time.sleep(0.1)
            m.release(x_pos, y_pos)
    except KeyboardInterrupt:
        print("\rCtrl-C detected. Exiting...")

if __name__ == '__main__':
    main()
