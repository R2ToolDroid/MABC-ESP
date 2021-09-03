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
    if( Ps3.event.button_down.down && (SHIFT == 0))  { parseCommand(":SE10");} //Play the first mp3 }
    if( Ps3.event.button_down.left && (SHIFT == 0))  { parseCommand(":SE13");}
    if( Ps3.event.button_down.up && (SHIFT == 0))    { parseCommand(":SE11");}    
    if( Ps3.event.button_down.right && (SHIFT == 0)) { myDFPlayer.next();} 
    
///Circle shift --> ab hier noch die MD Codes einfügen
    if( Ps3.event.button_down.down && (SHIFT == SH_CIRCLE))  { parseCommand(":SE09");}
    if( Ps3.event.button_down.left && (SHIFT == SH_CIRCLE))  {parseCommand(":SE03");}
    if( Ps3.event.button_down.up && (SHIFT == SH_CIRCLE))    { parseCommand(":SE01");}   
    if( Ps3.event.button_down.right && (SHIFT == SH_CIRCLE)) { parseCommand(":SE06");}   

    //Cross Shift   
    if( Ps3.event.button_down.down && (SHIFT == SH_CROSS))  {parseCommand("$-");}
    if( Ps3.event.button_down.up && (SHIFT == SH_CROSS))    { parseCommand("$+");}  
    if( Ps3.event.button_down.right && (SHIFT == SH_CROSS)) {myDFPlayer.volume(20);  parseCommand("*ST00");}
    if( Ps3.event.button_down.left && (SHIFT == SH_CROSS))  {myDFPlayer.volume(10);  parseCommand("*RD00");}

  
    //PS Shift
    if( Ps3.event.button_down.cross && (SHIFT == SH_PLUS)) {parseCommand("DISDR");StickConnect=0;}
    if( Ps3.event.button_down.circle && (SHIFT == SH_PLUS)) {parseCommand("hreset");}

    
    if( Ps3.event.button_down.left && (SHIFT == SH_PLUS))  {
      parseCommand("#OP01");
      }

    

    //L1 Shift
    if( Ps3.event.button_down.down && (SHIFT == SH_L1))  { parseCommand(":SE08");}
    if( Ps3.event.button_down.left && (SHIFT == SH_L1))  { parseCommand(":SE02");}
    if( Ps3.event.button_down.up && (SHIFT == SH_L1))    { parseCommand(":SE07");}  
    if( Ps3.event.button_down.right && (SHIFT == SH_L1)) { parseCommand(":SE04");}   

    // L2 Shift
    if( Ps3.event.button_down.circle && (SHIFT == SH_L2))  {parseCommand(":CL00");}
    if( Ps3.event.button_down.cross && (SHIFT == SH_L2))  {parseCommand("center");}
    

    } else {
      /*****************##########           ARM Steering       ########### ********/
      if( Ps3.event.button_down.up && (SHIFT == 0))    {
           if(Apos <=180) { Apos = Apos+10;}
            //S_DEBUG_STICK += "Arm Hoch\n";
            //output += Apos;
            GrippLift.write(Apos);
            } 
      if( Ps3.event.button_up.up && (SHIFT == 0))    {//S_DEBUG_STICK += "Arm Hoch stop\n";
        }   
       
      if( Ps3.event.button_down.down && (SHIFT == 0))  {
            if (Apos >=0) {Apos = Apos-10;}
            //S_DEBUG_STICK += "Arm Down\n"; 
            //output += Apos;
            GrippLift.write(Apos);
            }
      if( Ps3.event.button_up.down && (SHIFT == 0))  {//S_DEBUG_STICK += "Arm Down stop\n"; 
      }
      
      if( Ps3.event.button_down.left && (SHIFT == 0))  {
        //S_DEBUG_STICK += "Arm Raus start\n";
        digitalWrite(GRIP_MOTB1, LOW );
          digitalWrite(GRIP_MOTB2, HIGH );     
        }
      if( Ps3.event.button_up.left && (SHIFT == 0))  {
        S_DEBUG_STICK += "Arm Raus stop\n";
          digitalWrite(GRIP_MOTB1,LOW);
          digitalWrite(GRIP_MOTB2,LOW);  
        }    
      if( Ps3.event.button_down.right && (SHIFT == 0))  {
          //S_DEBUG_STICK += "Arm rein start\n";
          digitalWrite( GRIP_MOTB1, HIGH ); // direction = forward
        digitalWrite( GRIP_MOTB2, LOW ); // PWM speed = fast  
                
          }
      if( Ps3.event.button_up.right && (SHIFT == 0))  {
          //S_DEBUG_STICK += "Arm rein stop\n";
          digitalWrite(GRIP_MOTB1,LOW);
          digitalWrite(GRIP_MOTB2,LOW); 
          } 
//// Grippter Mode 2 plus L2

      if( Ps3.event.button_down.up && (SHIFT == SH_L2)){
          //S_DEBUG_STICK += "Grip Auf\n";
          digitalWrite( GRIP_MOTA1, HIGH ); // direction = forward
          digitalWrite( GRIP_MOTA2, LOW ); // PWM speed = fast
          } 
      if( Ps3.event.button_up.up && (SHIFT == SH_L2)){
          //S_DEBUG_STICK += "Grip Auf stop\n";
          digitalWrite(GRIP_MOTA1,LOW);
          digitalWrite(GRIP_MOTA2,LOW);           
          } 
      
      if( Ps3.event.button_down.down && (SHIFT == SH_L2))  {
          //S_DEBUG_STICK += "Grip zu\n"; 
          digitalWrite( GRIP_MOTA1, LOW );  
          digitalWrite( GRIP_MOTA2, HIGH );
          
          }
      if( Ps3.event.button_up.down && (SHIFT == SH_L2))  {
          //S_DEBUG_STICK += "Grip zu stop\n"; 
          digitalWrite(GRIP_MOTA1,LOW);
          digitalWrite(GRIP_MOTA2,LOW);       
          }

      if( Ps3.event.button_down.left && (SHIFT == SH_L2))  {
          if (Gpos <= 180) {Gpos=Gpos+15;}
            //S_DEBUG_STICK += "Dreh links start\n";
            //output += Gpos;
            GrippRoll.write(Gpos); 
            
          }
      if( Ps3.event.button_down.left && (SHIFT == SH_L1))  {GrippRoll.write(0);}  

      if( Ps3.event.button_down.up && (SHIFT == SH_L1))  {parseCommand("O");}  

      if( Ps3.event.button_down.down && (SHIFT == SH_L1))  {parseCommand("I");}  
          
      if( Ps3.event.button_down.right && (SHIFT == SH_L2))  {  
          if(Gpos >=0){Gpos=Gpos-15;}
            //S_DEBUG_STICK += "Dreh rechts start\n";
            //S_DEBUG_STICK += Gpos;
            GrippRoll.write(Gpos);
            
        }
      if( Ps3.event.button_down.right && (SHIFT == SH_L1))  {GrippRoll.write(180);} 
      
      if( Ps3.event.button_down.down && (SHIFT == SH_PLUS))  { parseCommand("D"); }
    if( Ps3.event.button_down.up && (SHIFT == SH_PLUS))    { parseCommand("T"); }  
    if( Ps3.event.button_down.right && (SHIFT == SH_PLUS)) { parseCommand("C");}
    
    if( Ps3.event.button_down.left && (SHIFT == SH_PLUS))  {
       parseCommand("#OP01");
      }
      /*
    if( Ps3.event.button_down.left && (SHIFT == 0))  {S_DEBUG_STICK += "Mid Awake + Human"; parseCommand(":SE14");}
    if( Ps3.event.button_down.up && (SHIFT == 0))    {S_DEBUG_STICK += "Full Awake"; parseCommand(":SE11");}    
    if( Ps3.event.button_down.right && (SHIFT == 0)) {S_DEBUG_STICK += "Full Awake + next Sound"; parseCommand(":SE14");}
    */
    }

    
    if( Ps3.event.button_down.l3 && (SHIFT == SH_L1)) {
      S_DEBUG_STICK += "Toggle Speed\n"; 
      S_DEBUG_STICK += OverSpeed;
      ToggleSpeed(); 
      SHIFT = 0;
      
      }

    //L2 Shift
     //// CHANGE MODE ///
    if( Ps3.event.button_down.l3 && (SHIFT == SH_L2))
    {
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
      
      SHIFT = 0;
     // parseCommand("CALL");
     
     ShwMode();
      
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
        S_DEBUG_STICK += "\nDome- posX=";
        S_DEBUG_STICK += posX;
        S_DEBUG_STICK += "\n";
        }

        //Serial.println(posX);
        isCenter = false;
        DomeRot.write(posX);
      } else {
     
        //if (mode = 1)
       //Serial.print(" posX="); Serial.println(posX);
       //DriveDir.write(posX);

       

     // }

     // Serial.print(" posY="); Serial.println(posY);

     
     // Gerade aus
     

      
      //Serial.print(" Dir :");
      //Serial.print(posX);

      //Serial.print(" correction : ");
      int corr = map(posX, 30,150,-10,10);
      //Serial.print(corr);
    
      // mitte 90 finden

      // 95  links   85 rechts
      
     //if (posX == 90){
     if (inRange(posX, 70, 110)){
       DriveSpeed.write(posY); //right
       DriveDir.write(posY);   //left
       
       //Serial.print("|  left pwm :");
       //Serial.print(posY);
       //Serial.print(" right pwm :");
       //Serial.println(posY);


         
     } else {
      
       DriveSpeed.write(posY - corr); //right
       DriveDir.write(posY + corr);   //left
       
       //Serial.print("|  left pwm :");
       //Serial.print(posY - corr);
       //Serial.print(" right pwm :");
       //Serial.println(posY + corr);
      
     }



      } //End Drive 
      
     

     

       

     if (DEBUG_STICK){  
     S_DEBUG_STICK += "\n posY=";
     S_DEBUG_STICK += posY;
     S_DEBUG_STICK += "\nSHIFT: ";
     S_DEBUG_STICK += SHIFT;
     S_DEBUG_STICK += "\n";
     }
    } 
    
    
  
   //---------------------- Battery events ---------------------
    if( battery != Ps3.data.status.battery ){
        battery = Ps3.data.status.battery;
        
        //Serial.print("The controller battery is ");
        if (DEBUG_STICK){
          S_DEBUG_STICK += "The controller battery is ";
          S_DEBUG_STICK += "\n";
        }
        
        if( battery == ps3_status_battery_charging )      STICK_AKKU_STAT = CHARGING;
        else if( battery == ps3_status_battery_full )     STICK_AKKU_STAT = FULL;
        else if( battery == ps3_status_battery_high )     STICK_AKKU_STAT = HIGHT;
        else if( battery == ps3_status_battery_low)       STICK_AKKU_STAT = LOWR;
        else if( battery == ps3_status_battery_dying )    STICK_AKKU_STAT = DYING;
        else if( battery == ps3_status_battery_shutdown ) STICK_AKKU_STAT = SHUTDOWN;
        else S_DEBUG_STICK += "UNDEFINED \n";

        switch (STICK_AKKU_STAT){
          case CHARGING:
          S_DEBUG_STICK += "CHARGING \n";
          break;
          case FULL:
          S_DEBUG_STICK += "FULL \n";
          break;
          case HIGHT:
          S_DEBUG_STICK += "HIGHT \n";
          break;
          case LOWR:
          S_DEBUG_STICK += "LOWR \n";
          break;
          case DYING:
          S_DEBUG_STICK += "DYING \n";
          break;
          case SHUTDOWN:
          S_DEBUG_STICK += "SHUTDOWN \n";
          break;

          default:

          break;


          
        }

    }

    
}
