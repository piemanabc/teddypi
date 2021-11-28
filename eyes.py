import gpiozero
from time import sleep

# !!!           !!!#
# start variables
# !!!           !!!#

# Eye LEDs
eye_led = gpiozero.LED(6)

# Eye 0 (left)
l_eye = gpiozero.MotionSensor(3)

# Eye 1 (right)
r_eye = gpiozero.MotionSensor(2)

# Servo
servo = gpiozero.Servo(4)

while True:
    if l_eye.motion_detected():
        servo.min()
        sleep(1)
        servo.mid()
        sleep(1)
        servo.max()
        sleep(1)