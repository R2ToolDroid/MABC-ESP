#include <Arduino.h>

byte CheckSensor(){

    byte sig;

      IRSensor = analogRead(IR_SENSOR);
      if (IRSensor > 1000){
        sig = HIGH;
      } else {
        sig = LOW;
      }

    return sig;
  
}

void autoDome() {

    long rndNum;
    int domeSpeed;
    isCenter = false;

    //output += "\r\n - Dome Status=";
    //output +=    domeStatus      ; 
    
    if (domeStatus == 0)  // Dome is currently stopped - prepare for a future turn
    {
      
        if (domeTargetPosition == 0)  // Dome is currently in the home position - prepare to turn away
        {
          
            domeStartTurnTime = millis() + (random(3, 10) * 1000);          
            rndNum = random(5,354);
            domeTargetPosition = rndNum;  // set the target position to a random degree of a 360 circle - shaving off the first and last 5 degrees
            
            if (domeTargetPosition < 180)  // Turn the dome in the positive direction
            {
              
                domeTurnDirection = 1;
                
                domeStopTurnTime = domeStartTurnTime + ((domeTargetPosition / 360) * time360DomeTurn);
              
            } else  // Turn the dome in the negative direction
            {
                    
                domeTurnDirection = -1;
                
                domeStopTurnTime = domeStartTurnTime + (((360 - domeTargetPosition) / 360) * time360DomeTurn);
              
            }
          
        } else  // Dome is not in the home position - send it back to home
        {
          
            domeStartTurnTime = millis() + (random(3, 10) * 1000);
            
            if (domeTargetPosition < 180)
            {
              
                domeTurnDirection = -1;
                
                domeStopTurnTime = domeStartTurnTime + ((domeTargetPosition / 360) * time360DomeTurn);
              
            } else
            {
                    
                domeTurnDirection = 1;
                
                domeStopTurnTime = domeStartTurnTime + (((360 - domeTargetPosition) / 360) * time360DomeTurn);
              
            }
            
            domeTargetPosition = 0;
          
        }
      
        domeStatus = 1;  // Set dome status to preparing for a future turn
               
        #ifdef DEBUG
          output += "Dome Automation: Initial Turn Set";
          output +=  "Current Time: ";
          output +=  millis();
          output += "- Next Start Time: ";
          output += domeStartTurnTime;
          output += " - ";
          output += "Next Stop Time: ";
          output += domeStopTurnTime;
          output += " - ";          
          output += "Dome Target Position: ";
          output += domeTargetPosition;
          output += "\r\n ";
        #endif

    }
    
    
    if (domeStatus == 1)  // Dome is prepared for a future move - start the turn when ready
    {
      
        if (domeStartTurnTime < millis())
        {
          
             domeStatus = 2; 
             
             #ifdef DEBUG
                output += "Dome Automation: Ready To Start Turn\r\n";
             #endif
          
        }
    }
    
    if (domeStatus == 2) // Dome is now actively turning until it reaches its stop time
    {
      
        if (domeStopTurnTime > millis())
        {
          
              domeSpeed = domeAutoSpeed * domeTurnDirection;

              int DomePulseSpeed = map(domeSpeed,-100,100,0,180);
          
              //SyR->motor(domeSpeed);
             DomeRot.write(DomePulseSpeed);
              
             #ifdef DEBUG
               output += "Turning Now!!\r\n";
                
             #endif
          
          
        } else  // turn completed - stop the motor
        {
              domeStatus = 0;
              //SyR->stop();
              DomeRot.write(90);
              
              #ifdef DEBUG
               output += "STOP TURN!!\r\n";
              #endif
        }
      
    }

  if (output !=""){
    Serial.println(output);
    output="";
  }

}


void domeCenter(){

    byte sens = CheckSensor();
        
    if (findCenter == true ) {     
          
      if(sens == true && isCenter == false){
         DomeRot.write(180); ///find Position Center    
         domePos = false; 
         domeFindCenterTime = CurDomeFindTime;
      } else {             
         
         findCenter = false;
         Serial.println("Dome is Center");
         //DomeRot.write(90);
         domePos = true;  
         isCenter = true;
         
      }    
         
    }    

    if (domePos != false) {
      DomeRot.write(90);
      domePos = false;
      
    }

    if (debug){
    
    //Serial.print("dome FInd = ");
    //Serial.print(domeFindCenterTime);
    //Serial.println(isCenter);
    //Serial.print(" Curr= ");
    //Serial.print(CurDomeFindTime);
    //Serial.print(" isCenter ");
    //Serial.print(isCenter);
    //Serial.print(" IR = ");
    //Serial.print(sens);
    //Serial.print(" domePos=");
    //Serial.println(domePos);
    }
    
}
