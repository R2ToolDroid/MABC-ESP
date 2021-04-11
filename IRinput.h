#include <Arduino.h>  

void CheckIR(int pause){

  IRSensor = analogRead(IR_SENSOR);
  
 // Serial.print("IR = ");
 // Serial.println(IRSensor);
  //ActionDelay(6000);
  //F_TRIG = false;
  unsigned long currentMillis1 = millis();

  unsigned long timer;
  
  
  if ((IRSensor <= 100) && (wait == 0)) { 
    F_TRIG = true;
    timer = currentMillis1;
   // Serial.println("IMPULSE");
    
    //Serial3.print("$2\r");
    parseCommand("$2");
  } 

  int diff = currentMillis1 - timer;

  if (diff  >= pause){
    wait = 0;
  } else {
    wait = 1;
  }
  
  
  
  
}
