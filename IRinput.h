#include <Arduino.h>  

void IRSensor(){

  int16_t t = pulseIn(sensorPin, HIGH);
  
  unsigned long curMillis = millis();
    if (DEBUG_IR){
    Serial.print(F( "IR Signal "));
    Serial.println(t);
    Serial.print(F(" CountTrig"));
    Serial.println(countTrig);
    }


    
  /// Wartet bis 7000 von Ping verstrichen sind
  
   if (curMillis - prevTick >= interval) { 
      //sig = false; //prevTick = 0; 
      //Serial.println("auslöser blocken");    
      in = true;
      }

    //Serial.print("current Time ");
    //Serial.print(curMillis);
    //Serial.print(" last Tick ");
    //Serial.print(prevTick);
    //Serial.println(" .");

    if (curMillis - prevTick >= 10000){
      if (Hin == true) {
      ///Reset Action 10 Seconds after Tick
        
       // Serial.println(" .Action");
        SendOutput("*RC00");
        myDFPlayer.playFolder(03,06);
        
        Hin = false;
      }
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

        if (DEBUG_INPUT){    
        Serial.print(" Ping A ");
        Serial.print(d);
        Serial.print(" mm ");


        
        
        Serial.println(" Tig Nummer:");
        }
        if (countTrig >= IRFolder ) {countTrig = 2;}
        countTrig++;

        //Serial.print(countTrig);
        if ( d <= 150 ){
          
          myDFPlayer.playFolder(04,05);
          SendOutput("center");
          STcmd = ":SE53";
          SendOutput("*RD00");
          Hin = true;
        } else {
          
        myDFPlayer.playFolder(04,countTrig);
            SendOutput("center");
          if (HoloAction == true){
            SendOutput("*RD01");
            SendOutput("center");
            SendOutput("*H110");
            HoloAction = false;
            Hin = true;
          } else {
            
              //SendOutput("*RC01");
              SendOutput("*RD01");
              HoloAction = true;
              Hin = true;
          }
        
        }
        prevTick = curMillis;
        in = false;
        
      }
        
      
    }
  
  }

  
}  //end Function
