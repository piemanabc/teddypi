import gpiozero
from time import sleep


# Eye LEDs
l_eye_led = gpiozero.PWMLED(12)  # these pins may need to be moved
r_eye_led = gpiozero.PWMLED(16)

# Eye 0 (left)
l_eye = gpiozero.MotionSensor(17)

# Eye 1 (right)
r_eye = gpiozero.MotionSensor(27)

# Servo
servo = gpiozero.Servo(4)

# loop forever

while True:
    # if Motion seen on the left of the device (from teddy pov)

    if l_eye.motion_detected:
        print("left motion!")
        servo.value = -1
        l_eye_led.blink(on_time=2, fade_in_time=1, fade_out_time=1, n=1) and r_eye_led.blink(on_time=2, fade_in_time=1,
                                                                                             fade_out_time=1, n=1)
        sleep(1)

    # if Motion seen on the left and right of the device (from teddy pov)

    elif l_eye.motion_detected and r_eye.motion_detected:
        print("middle motion or I cant see you!")
        servo.value = 0
        l_eye_led.blink(on_time=2, fade_in_time=1, fade_out_time=1, n=1) and r_eye_led.blink(on_time=2, fade_in_time=1,
                                                                                             fade_out_time=1, n=1)
        sleep(1)

    # if Motion seen on the right of the device (from teddy pov)

    elif r_eye.motion_detected:
        servo.value = 1
        print("right motion!")
        l_eye_led.blink(on_time=2, fade_in_time=1, fade_out_time=1, n=1) and r_eye_led.blink(on_time=2, fade_in_time=1,
                                                                                             fade_out_time=1, n=1)
        sleep(1)

    # if no Motion seen (from teddy pov)

    elif not l_eye.motion_detected and not r_eye.motion_detected:
        servo.value = 0
        print("where are you?")
        sleep(1)
