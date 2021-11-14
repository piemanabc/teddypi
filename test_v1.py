from gpiozero import LED # import gpio
from time import sleep # import sleep function

red = LED(40)

while True:
    red.on()
    sleep(1)
    red.off()
    sleep(1)