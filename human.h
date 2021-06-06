#include <Arduino.h>   

void human(){
     if (movementSensor.dataReady()) {
        ir1 = movementSensor.getRawIR1();
        ir2 = movementSensor.getRawIR2();
        ir3 = movementSensor.getRawIR3();
        ir4 = movementSensor.getRawIR4();
        temp = movementSensor.getTMP();
        movementSensor.startNextSample();
        Sdiff = ir2 - ir4 ; ///Differenz

        int gap = 200;  /// Lücke wo nichts verfolgt wird

        int range = ir2+ir4;  /// Abstand

        if (range >= 1000){
          // gap = 250;
          //digitalWrite(ledPinC, HIGH);
          Ping = true;
            } else {
           // digitalWrite(ledPinC, LOW);
            }

      // if (range > 3000) { //here}
        
        if (debug)
        {  
        //Serial.print(F("1:BOT["));
        //Serial.print(ir1);
        Serial.print(F(" 2:RH["));
        Serial.print(ir2);
        //Serial.print(F("], 3:TOP["));
        //Serial.print(ir3);
        Serial.print(F("], 4:LH["));
        Serial.print(ir4);
        //Serial.print(F("], temp["));
        //Serial.print(temp);
        Serial.print(F("], diff["));
        Serial.print(Sdiff);    
        Serial.print(F("]"));
        //Serial.print(F("], millis["));
        //Serial.print(millis());
        //Serial.print(F("]"));

        Serial.print("----range[");
        Serial.print(range);
        Serial.print("]----gap");
        Serial.print(gap);
        Serial.println();
        }        
        ///////////////////////////////////////
        //Bewegungs Kalkulation
        ///////////////////////////////////////
        //Bei RH Impulse nach rechts drehen bis LH Impuls gleich ist
           
        byte diff = false; 
   
        if ((Sdiff >= gap)||(Sdiff <= -gap)){ diff = true;}

        if (diff){

           if (ir4 > ir2){ ////turn right
               // Serial.println("Dreh nach Rechts");
                //digitalWrite(ledPin2, HIGH);  //Dreh nach R
                //analogWrite(DMOT_L,Htempo); 
                //servoDispatch.moveTo(0,50,0,500);
                DomeRot.write(0);
           }    
           
            if (ir2 > ir4){ ////turn left
                //Serial.println("Dreh nach DMOT_L");
                //digitalWrite(ledPin1, HIGH);  //Dreh nach L
                //analogWrite(DMOT_R,Htempo); 
                //servoDispatch.moveTo(0,50,0,1200);
                DomeRot.write(180);
           } 
        } else {
          //analogWrite(DMOT_R, 0); 
          //analogWrite(DMOT_L, 0); 
          //digitalWrite(ledPin2, LOW);  
          //digitalWrite(ledPin1, LOW);  
          DomeRot.write(90);
          //Serial.println("--Mitte--");
         // tempPos = 90;
          
        }

      /*****Vertikal system Holo ***/
       /*
        vpos1 = map(ir3, -1300, 800, 180, 90); ///verstellung nach oben
        vpos2 = map(ir1, -1300, 800, 0, 90);   /// Verstellung nach unten

        Vdiff = ir3 - ir1 ; ///Differenz
        
        Hdiff = false;
        
        if ((Vdiff >= 200)||(Vdiff <= -200)){ Hdiff = true;}

        if (Hdiff){

           if (ir3 > ir1){ ////turn top
               //Serial.println("Dreh nach oben");
               tempPos = vpos1;
           }    
           
            if (ir1 > ir3){ ////turn bot
                //Serial.println("Dreh nach unten");
                tempPos = vpos2;
           } 
        } else {
          
          //Serial.println("--Mitte--");
          //tempPos = 90;
          
        }
         /*  
        HoloV.write(tempPos); 
        delay(50);
        if (debug){
        Serial.print ("action ");
        Serial.print (Hdiff);
        
        Serial.print ("Temp Pos ");
        Serial.print (tempPos);
       // Serial.print ("  S 3  ");
        //Serial.print (vpos1);
        Serial.print (" raw O ");
        Serial.print (ir3);
         
        //7Serial.print ("  S 3 unten ");
        //Serial.print(ir3);
        //Serial.print (vpos2);
        Serial.print (" raw U ");
        Serial.print(ir1);
        Serial.print("   Vdiff: ");
        Serial.println(Vdiff);
        }
        */
    }
    
  
}
