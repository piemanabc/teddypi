import gpiozero
from time import sleep


# Eye LEDs
eye_led = gpiozero.LED(6)

# Eye 0 (left)
l_eye = gpiozero.MotionSensor(17)

# Eye 1 (right)
r_eye = gpiozero.MotionSensor(27)

# Servo
servo = gpiozero.Servo(4)

while True:
    if l_eye.motion_detected:
        print("left motion!")
        servo.value = -1
        sleep(2)

    elif l_eye.motion_detected and r_eye.motion_detected or not l_eye.motion_detected and not r_eye.motion_detected:
        print("middle motion or I cant see you!")
        servo.value = 0
        sleep(2)

    elif r_eye.motion_detected:
        servo.value = 1
        print("right motion!")
        sleep(2)
