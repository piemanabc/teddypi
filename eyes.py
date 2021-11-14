import gpiozero
import time

# !!!           !!!#
# start variables
# !!!           !!!#

# Eye LEDs
eye_led = gpiozero.LED(6)

# Eye 0 (left)
l_pin_in = 3
l_pin_out = 7

# Eye 1 (right)
r_pin_in = 2
R_pin_out = 8

# Servo
servo = gpiozero.Servo(40)