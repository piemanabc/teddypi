#include <Servo.h>

// int usefull servo shit
Servo eyes;

int pos = 0;


// start eye 0 vars L
  int L_pin_in = 3;
  int L_pin_out = 7; 

// start eye 1 vars R
  int R_pin_in = 2;
  int R_pin_out = 8; 

// eye led
  int eye_led = 6;

// Variables for mainloop
  int motion;
  int fadeAmount = 1;
  int brightness = 1;

  //to change how long it takes to fade in and out, alter this variable 10 for fast, 45 for around a 3sec fade 
  int fadetimemulti = 45;

  
void setup() {
  // put your setup code here, to run once:

  eyes.attach(5);
  
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // start eye 0 pins  
  pinMode(L_pin_out, OUTPUT);
  pinMode(L_pin_in, INPUT);

  
  //start eye 1 pins
  pinMode(R_pin_out,OUTPUT);
  pinMode(R_pin_in,INPUT);


}

void loop() {
    motion = checkEars(L_pin_in, L_pin_out, R_pin_in, R_pin_out);
    setServo (motion);
    eyes.write(90);
    
}


// check ears is the function that will check either ear's state and return the useful data
// Code 3 = No motion detected
// code 0 = left ear motion detected (motion on right)
// code 1 = right ear motion detected (motion on left)
// code 2 = left and right motion detected (motion center)
// code 4 = something has gone wong

// servo 0 angle == arm to left == eyes to right
// servo 180 angle == arm to right == eyes to left

int checkEars(int pinin0, int pinout0, int pinin1, int pinout1) {
    int ear0state = digitalRead(pinin0);    
    int ear1state = digitalRead(pinin1);

    if (ear0state == 0 && ear1state == 0) {
      // no motion
      return 3;
      } else if (ear0state == 1 && ear1state == 0) {
        // ear 0 left (right motion)
      return 0;
      
      }  else if (ear0state == 0 && ear1state == 1) {
        // ear 1 right (left motion)
      return 1;
      
      }  else if (ear0state == 1 && ear1state == 1) {
        // Both ears(all motion)
      return 2;
      
      } else {
        return 4;       
      }
  }

int setServo(int sight) {
  if (sight == 4) {
    Serial.println("Something went wrong...");
    for (int i = 0; i <= 7; i++) {
      digitalWrite(L_pin_out, HIGH);   // turn the LED on 
      digitalWrite(L_pin_out, LOW);    // turn the LED off
      delay(100);
      digitalWrite(R_pin_out, HIGH);   // turn the LED on 
      digitalWrite(R_pin_out, LOW);    // turn the LED off 
      delay(100); 
      }
      brightness = 1;

    //motion in left ear (motion on right)
    } else if (sight == 0) {
      eyes.write(0);
      Serial.println("motion in left ear (movement on right)");
      while (brightness != 0){
        analogWrite(eye_led, brightness);
        brightness = brightness + fadeAmount;
        delay(fadetimemulti);
            if (brightness <= 0 || brightness >= 255) {
              fadeAmount = -fadeAmount;
            }
       }
       brightness = 1; 

    //motion in right ear (movement on left)
    } else if (sight == 1) {
      eyes.write(180);
      Serial.println("motion in right ear (movement on left)");
     while (brightness != 0){
        analogWrite(eye_led, brightness);
        brightness = brightness + fadeAmount;
        delay(fadetimemulti);
            if (brightness <= 0 || brightness >= 255) {
              fadeAmount = -fadeAmount;
            }
     }
     brightness = 1;

      // All motion
    } else if (sight == 2) {
      eyes.write(90);
      Serial.println("Motion in both ears. Lighting eyes no servo movements");
      while (brightness != 0){
        analogWrite(eye_led, brightness);
        brightness = brightness + fadeAmount;
        delay(fadetimemulti);
            if (brightness <= 0 || brightness >= 255) {
              fadeAmount = -fadeAmount;
            }
      }
      brightness = 1;
      
      // No movement detected. waiting
    }else if (sight == 3) {
      eyes.write(90);
      Serial.println("no motion detected");
      brightness = 0;
      delay(300);
    } else {
      Serial.println(sight);
      brightness = 1;
      }
  }
