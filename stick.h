#include <Arduino.h>

void notify()
{
    /* Stick Command */   
    //SHIFT
    if( Ps3.event.button_down.circle && (SHIFT == 0))  {SHIFT = SH_CIRCLE;}
    if( Ps3.event.button_down.cross && (SHIFT == 0))  {SHIFT = SH_CROSS;}
    if( Ps3.event.button_down.ps && (SHIFT == 0))  {SHIFT = SH_PLUS;}
    if( Ps3.event.button_down.l1 && (SHIFT == 0))  {SHIFT = SH_L1;}
    if( Ps3.event.button_down.l2 && (SHIFT == 0))  {SHIFT = SH_L2;}
    
    ///no Mode 3 activ
    if (mode != 3){   
    if( Ps3.event.button_down.down && (SHIFT == 0))  {STcmd =":SE10";} //Play the first mp3 }
    if( Ps3.event.button_down.left && (SHIFT == 0))  {STcmd =":SE13";}
    if( Ps3.event.button_down.up && (SHIFT == 0))    {STcmd =":SE11"; }    
    if( Ps3.event.button_down.right && (SHIFT == 0)) {next=true;} 
    
    ///Circle shift --> ab hier noch die MD Codes einfügen
    if( Ps3.event.button_down.down && (SHIFT == SH_CIRCLE))  {STcmd =":SE09";}
    if( Ps3.event.button_down.left && (SHIFT == SH_CIRCLE))  {STcmd =":SE03";}
    if( Ps3.event.button_down.up && (SHIFT == SH_CIRCLE))    {STcmd =":SE01";}   
    if( Ps3.event.button_down.right && (SHIFT == SH_CIRCLE)) {STcmd =":SE06";}   

    //Cross Shift   
    if( Ps3.event.button_down.down && (SHIFT == SH_CROSS))  {STcmd ="$-";}
    if( Ps3.event.button_down.up && (SHIFT == SH_CROSS))    {STcmd ="$+";}  
    if( Ps3.event.button_down.right && (SHIFT == SH_CROSS)) {STcmd ="$f";}
    if( Ps3.event.button_down.left && (SHIFT == SH_CROSS))  {STcmd ="$m";}

  
    //PS Shift
    if( Ps3.event.button_down.cross && (SHIFT == SH_PLUS)) {STcmd ="DISDR";}
    if( Ps3.event.button_down.circle && (SHIFT == SH_PLUS)) {STcmd ="hreset";}

    
    if( Ps3.event.button_down.left && (SHIFT == SH_PLUS))  {
      STcmd ="#OP01";
      }

    //L1 Shift
    if( Ps3.event.button_down.down && (SHIFT == SH_L1))  { STcmd =":SE08";}
    if( Ps3.event.button_down.left && (SHIFT == SH_L1))  { STcmd =":SE02";}
    if( Ps3.event.button_down.up && (SHIFT == SH_L1))    { STcmd =":SE07";}  
    if( Ps3.event.button_down.right && (SHIFT == SH_L1)) { STcmd =":SE04";}   

    // L2 Shift
    if( Ps3.event.button_down.circle && (SHIFT == SH_L2))  {STcmd =":CL00";}
    if( Ps3.event.button_down.cross && (SHIFT == SH_L2))  {STcmd ="center";}
    

    } else {
      /*****************##########           ARM Steering       ########### ********/
      if( Ps3.event.button_down.up && (SHIFT == 0))    {
           
           if(DEBUG_STICK) Serial.println (F("Arm Hoch"));
           
            GRIP_LIFT_STATUS = GRIP_LIFT_TOP;
            
            } 
      if( Ps3.event.button_up.up && (SHIFT == 0))    {
          if (DEBUG_STICK)Serial.println(F("Arm Hoch stop"));
          
           GRIP_LIFT_STATUS = GRIP_LIFT_STOP;
        }   

       
      if( Ps3.event.button_down.down && (SHIFT == 0))  {
            
            if (DEBUG_STICK) Serial.println(F("Arm Down"));
           
            
            GRIP_LIFT_STATUS = GRIP_LIFT_DOWN;
           
            }
      if( Ps3.event.button_up.down && (SHIFT == 0))  {
            if (DEBUG_STICK) Serial.println(F("Arm Down stop"));
       
           GRIP_LIFT_STATUS = GRIP_LIFT_STOP;
          
      }
      
      if( Ps3.event.button_down.left && (SHIFT == 0))  {
       
        if (DEBUG_STICK)Serial.println(F("Arm Raus start"));
        
        digitalWrite(GRIP_MOTB1, LOW );
        digitalWrite(GRIP_MOTB2, HIGH );     
        }
      if( Ps3.event.button_up.left && (SHIFT == 0))  {
        
        if (DEBUG_STICK)Serial.println(F("Arm Raus stop"));
        
          digitalWrite(GRIP_MOTB1,LOW);
          digitalWrite(GRIP_MOTB2,LOW);  
        }    
      if( Ps3.event.button_down.right && (SHIFT == 0))  {
          if (DEBUG_STICK)Serial.println(F("Arm rein start"));
        
          digitalWrite( GRIP_MOTB1, HIGH ); // direction = forward
          digitalWrite( GRIP_MOTB2, LOW ); // PWM speed = fast  
                
          }
      if( Ps3.event.button_up.right && (SHIFT == 0))  {
          
          if (DEBUG_STICK)Serial.println(F("Arm rein stop"));
          
          digitalWrite(GRIP_MOTB1,LOW);
          digitalWrite(GRIP_MOTB2,LOW); 
          } 
      //// Grippter Mode 2 plus L2

      if( Ps3.event.button_down.up && (SHIFT == SH_L2)){
          
          if (DEBUG_STICK)Serial.println(F("Grip Auf"));
          
          digitalWrite( GRIP_MOTA1, HIGH ); // direction = forward
          digitalWrite( GRIP_MOTA2, LOW ); // PWM speed = fast
          } 
      if( Ps3.event.button_up.up && (SHIFT == SH_L2)){
          
          if (DEBUG_STICK)Serial.println(F("Grip Auf stop"));
          
          digitalWrite(GRIP_MOTA1,LOW);
          digitalWrite(GRIP_MOTA2,LOW);           
          } 
      
      if( Ps3.event.button_down.down && (SHIFT == SH_L2))  {
          
          if (DEBUG_STICK)Serial.println(F("Grip zu"));
          
          digitalWrite( GRIP_MOTA1, LOW );  
          digitalWrite( GRIP_MOTA2, HIGH );
          
          }
      if( Ps3.event.button_up.down && (SHIFT == SH_L2))  {
         
          if (DEBUG_STICK) Serial.println(F("Grip zu stop"));
          
          digitalWrite(GRIP_MOTA1,LOW);
          digitalWrite(GRIP_MOTA2,LOW);       
          }

      if( Ps3.event.button_down.left && (SHIFT == SH_L2))  {
          if (Gpos <= 180) {Gpos=Gpos+15;}
            
            if (DEBUG_STICK) Serial.println(F("Dreh links start"));
            
            //Grip zu stop
            //output += Gpos;
            GrippRoll.write(Gpos); 
            
          }
      if( Ps3.event.button_down.left && (SHIFT == SH_L1))  {GrippRoll.write(0);}  

      if( Ps3.event.button_down.up && (SHIFT == SH_L1))  {STcmd ="O";}  

      if( Ps3.event.button_down.down && (SHIFT == SH_L1))  {STcmd ="I";}  
          
      if( Ps3.event.button_down.right && (SHIFT == SH_L2))  {  
          if(Gpos >=0){Gpos=Gpos-15;}

          if (DEBUG_STICK) Serial.println(F("Dreh rechts start"));
            
            GrippRoll.write(Gpos);
            
        }
      if( Ps3.event.button_down.right && (SHIFT == SH_L1))  {GrippRoll.write(180);} 
      
      if( Ps3.event.button_down.down && (SHIFT == SH_PLUS))  { STcmd ="D"; }
    if( Ps3.event.button_down.up && (SHIFT == SH_PLUS))    { STcmd ="T"; }  
    if( Ps3.event.button_down.right && (SHIFT == SH_PLUS)) { STcmd ="C";}
    
    if( Ps3.event.button_down.left && (SHIFT == SH_PLUS))  {
       STcmd ="#OP01";
      }
      /*
    if( Ps3.event.button_down.left && (SHIFT == 0))  {S_DEBUG_STICK += "Mid Awake + Human"; parseCommand(":SE14");}
    if( Ps3.event.button_down.up && (SHIFT == 0))    {S_DEBUG_STICK += "Full Awake"; parseCommand(":SE11");}    
    if( Ps3.event.button_down.right && (SHIFT == 0)) {S_DEBUG_STICK += "Full Awake + next Sound"; parseCommand(":SE14");}
    */
    }

    
    if( Ps3.event.button_down.l3 && (SHIFT == SH_L1)) {

    if (DEBUG_STICK){
        Serial.print(F("Toggle Speed"));
        Serial.println(OverSpeed);
    }
      
      ToggleSpeed(); 
      SHIFT = 0;
      
      }

    //L2 Shift
     //// CHANGE MODE ///
    if( Ps3.event.button_down.l3 && (SHIFT == SH_L2))
    {
      
      STcmd ="MOD"; 
      /*
      mode++;
      if (mode >= 4) mode=0;
      if (DEBUG_STICK){
      Serial.print("Mode = ");
      Serial.println(mode);
      }
      
      Serial2.print("mode");
      Serial2.print(mode);
      Serial2.print("\r");
      //SendOutput ("mode"+mode);
      */
      SHIFT = 0;
     // parseCommand("CALL");
     
     //ShwMode();
      
    } 
    
    if( Ps3.event.button_up.ps ) SHIFT = 0;
    if( Ps3.event.button_up.circle )SHIFT = 0;
    if( Ps3.event.button_up.cross ) SHIFT = 0;
    if( Ps3.event.button_up.l1 ) SHIFT = 0;
    if( Ps3.event.button_up.l2 ) SHIFT = 0;
    if( Ps3.event.button_up.l3 ) SHIFT = 0;

    //---------------- Analog stick value events ---------------
    
   if( abs(Ps3.event.analog_changed.stick.lx) + abs(Ps3.event.analog_changed.stick.ly) > 2 ){
       //Serial.print("Moved the left stick:");
       //Serial.print(" x="); Serial.print(Ps3.data.analog.stick.lx, DEC);
        
      // posX = map(Ps3.data.analog.stick.lx, -128, 128, 0, 180);
       posX = map(Ps3.data.analog.stick.lx, -128, 128, 30, 150);
       if (OverSpeed == 1){
       posY = map(Ps3.data.analog.stick.ly, -128, 128, 30, 150); //Speed should be manipulated
       } else {
        posY = map(Ps3.data.analog.stick.ly, -128, 128, 70, 110); //Speed should be manipulated
       }

       if ((posY >= 85) && (posY <=  95)) { posY = 90;} ///Death Zone Range
       
      

      if( Ps3.data.button.l2 ) {

        if (DEBUG_STICK){
          
       Serial.print (F( "\nDome- posX="));
       Serial.println ( posX );
       
        }

        //Serial.println(posX);
        isCenter = false;
        DomeRot.write(posX);
      } else {
     
       
      int corr = map(posX, 30,150,-10,10);
     
     if (inRange(posX, 70, 110)){
       DriveSpeed.write(posY); //right
       DriveDir.write(posY);   //left
          
     } else {
      
       DriveSpeed.write(posY - corr); //right
       DriveDir.write(posY + corr);   //left
      
     }



      } //End Drive 
      
       

     if (DEBUG_STICK){  
     Serial.print(F( "\n posY="));
     Serial.print (posY);
     Serial.print(F( "\nSHIFT: "));
     Serial.print ( SHIFT );
     
     }
    } 
    
    
  
   //---------------------- Battery events ---------------------
    if( battery != Ps3.data.status.battery ){
        battery = Ps3.data.status.battery;
        
        //Serial.print("The controller battery is ");
        if (DEBUG_STICK){
          Serial.print (F( "The controller battery is: "));
          
        }
        
        if( battery == ps3_status_battery_charging )      STICK_AKKU_STAT = CHARGING;
        else if( battery == ps3_status_battery_full )     STICK_AKKU_STAT = FULL;
        else if( battery == ps3_status_battery_high )     STICK_AKKU_STAT = HIGHT;
        else if( battery == ps3_status_battery_low)       STICK_AKKU_STAT = LOWR;
        else if( battery == ps3_status_battery_dying )    STICK_AKKU_STAT = DYING;
        else if( battery == ps3_status_battery_shutdown ) STICK_AKKU_STAT = SHUTDOWN;
        else STICK_AKKU_STAT = NOT_CONNECT;

        //oled.clear();

        switch (STICK_AKKU_STAT){
          case CHARGING:
          if (DEBUG_STICK) Serial.println (F("Stick CHARGING"));
          break;
          case FULL:
          //S_DEBUG_STICK += "FULL \n";
          if (DEBUG_STICK) Serial.println (F("FULL"));
          break;
          case HIGHT:
          //S_DEBUG_STICK += "HIGHT \n";
          if (DEBUG_STICK) Serial.println (F("HIGHT"));
          //oled.println("Stick High\r");
          break;
          case LOWR:
          //S_DEBUG_STICK += "LOWR \n";
          if (DEBUG_STICK) Serial.println (F("LOWR"));
          //oled.println("Stick Low");
          break;
          case DYING:
          //S_DEBUG_STICK += "DYING \n";
          if (DEBUG_STICK) Serial.println (F("DYING"));
          //oled.println("Stick DYING");
          break;
          case SHUTDOWN:
          //S_DEBUG_STICK += "SHUTDOWN \n";
          if (DEBUG_STICK) Serial.println (F("SHUTDOWN"));
          //oled.println("Stick GO DOWN");
          break;

          case NOT_CONNECT:
          //S_DEBUG_STICK += "SHUTDOWN \n";
          if (DEBUG_STICK) Serial.println (F("NOT_CONNECT"));
          //oled.println("Stick GO DOWN");
          break;

          default:
          if (DEBUG_STICK) Serial.println (F("Undefined"));
          break;


          
        }

    }

    
}
