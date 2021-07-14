#include <Arduino.h>  

void IRSensor(){

  int16_t t = pulseIn(sensorPin, HIGH);
  
  unsigned long curMillis = millis();

  
  /// Wartet bis 7000 von Ping verstrichen sind
  
   if (curMillis - prevTick >= interval) { 
      //sig = false; //prevTick = 0; 
      //Serial.println("auslöser blocken");    
      in = true;
      }
  
  if (t == 0)
  {
    // pulseIn() did not detect the start of a pulse within 1 second.
    //Serial.println("timeout");
  }
  else if (t > 1850)
  {
    // No detection.
    //Serial.println(-1);
  }
  else
  {
    // Valid pulse width reading. Convert pulse width in microseconds to distance in millimeters.
    int16_t d = (t - 1000) * 3 / 4;
 
    // Limit minimum distance to 0.
    if (d < 0) { d = 0; } 
  
    //Serial.print(d);
    //Serial.println(" mm");
    if ( (d >= 100) && ( in == true) ){
      //prevTick = curMillis;

      if (in == true){
        
        Serial.print(" Ping A ");
        Serial.print(d);
        Serial.println(" mm");
        Serial.println(" Tig Nummer:");

        if (countTrig >= 8 ) {countTrig = 2;}
        countTrig++;

        Serial.print(countTrig);
        if ( d <= 150 ){
          
          myDFPlayer.playFolder(04,1);
          
          SendOutput("center");
          
        } else {
          
        myDFPlayer.playFolder(04,countTrig);
        
        }
        prevTick = curMillis;
        in = false;
      }
        
      
    }
  
  }

  
}  //end Function
