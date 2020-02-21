#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
#include <SPI.h>
#include "Adafruit_SleepyDog.h"
#include <Keyboard.h>

#ifndef TILTDEMO_H
#define TILTDEMO_H


// Define range of possible acceleration values.
#define MIN_ACCEL -10.0
#define MAX_ACCEL 10.0

#define red   0xFF
#define green 0xFF
#define blue  0x00

// n that will count 
int n = 0;
// counter for number of movements
int counter = 0;
// to access Y movement
int moving = 0;

//thresholds
int xThresh = 10;
int yThresh = 8;


 void  setup() {
  delay(10000);
  CircuitPlayground.begin();
 }

 void loop() {
    // Grab the acceleration
    float accelX = CircuitPlayground.motionX();
    float accelY = CircuitPlayground.motionY();
    float accelZ = CircuitPlayground.motionZ();

  if (CircuitPlayground.leftButton()){
    Serial.print(String(accelX)+","+String(accelY)+","+String(accelZ)+"\n");
  }
      
    if (accelX > xThresh && moving < 6 && abs(accelY) > yThresh){
      moving = moving+1;
      Serial.print("Moving " + String(moving)+ "  ");

    } else if (accelX > xThresh && moving > 5 && abs(accelY) < yThresh) {
      moving = 0;
      counter = counter +1;
      Serial.print("Counting" + String(counter)+" "); 
      Keyboard.print(counter-1);
      CircuitPlayground.strip.setPixelColor(counter - 1, red, green, blue);
      if (counter > 10){
        Keyboard.print(counter-2);
        CircuitPlayground.playTone(131, 500);
        CircuitPlayground.playTone(262, 500);
         CircuitPlayground.playTone(523, 500);
         
         
      }
    }


    // Light up all the pixels the interpolated color.
   
    CircuitPlayground.strip.show();
    
    
    
  }




#endif
