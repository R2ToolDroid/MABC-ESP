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
  
    
    ///No Shift and Mode 3 activ
    if (mode != 3){
    if( Ps3.event.button_down.down && (SHIFT == 0))  {output += "Quite Mode"; parseCommand(":SE10");}
    if( Ps3.event.button_down.left && (SHIFT == 0))  {output += "Mid Awake + Human"; parseCommand(":SE13");}
    if( Ps3.event.button_down.up && (SHIFT == 0))    {output += "Full Awake"; parseCommand(":SE11");}    
    if( Ps3.event.button_down.right && (SHIFT == 0)) {output += "Full Awake + next Sound"; parseCommand(":SE14");}
    } else {
      /*****************##########           ARM Steering       ########### ********/
      if( Ps3.event.button_down.up && (SHIFT == 0))    {
           if(Apos <=180) { Apos = Apos+10;}
            output += "Arm Hoch";
            //output += Apos;
            GrippLift.write(Apos);
            } 
      if( Ps3.event.button_up.up && (SHIFT == 0))    {output += "Arm Hoch stop";}   
       
      if( Ps3.event.button_down.down && (SHIFT == 0))  {
            if (Apos >=0) {Apos = Apos-10;}
            output += "Arm Down"; 
            //output += Apos;
            GrippLift.write(Apos);
            }
      if( Ps3.event.button_up.down && (SHIFT == 0))  {output += "Arm Down stop"; }
      
      if( Ps3.event.button_down.left && (SHIFT == 0))  {
        output += "Arm Raus start";
        digitalWrite(GRIP_MOTB1, LOW );
          digitalWrite(GRIP_MOTB2, HIGH );     
        }
      if( Ps3.event.button_up.left && (SHIFT == 0))  {
        output += "Arm Raus stop";
          digitalWrite(GRIP_MOTB1,LOW);
          digitalWrite(GRIP_MOTB2,LOW);  
        }    
      if( Ps3.event.button_down.right && (SHIFT == 0))  {
          output += "Arm rein start";
          digitalWrite( GRIP_MOTB1, HIGH ); // direction = forward
        digitalWrite( GRIP_MOTB2, LOW ); // PWM speed = fast  
                
          }
      if( Ps3.event.button_up.right && (SHIFT == 0))  {
          output += "Arm rein stop";
          digitalWrite(GRIP_MOTB1,LOW);
          digitalWrite(GRIP_MOTB2,LOW); 
          } 
//// Grippter Mode 2 plus L2

      if( Ps3.event.button_down.up && (SHIFT == SH_L2)){
          output += "Grip Auf";
          digitalWrite( GRIP_MOTA1, HIGH ); // direction = forward
          digitalWrite( GRIP_MOTA2, LOW ); // PWM speed = fast
          } 
      if( Ps3.event.button_up.up && (SHIFT == SH_L2)){
          output += "Grip Auf stop";
          digitalWrite(GRIP_MOTA1,LOW);
          digitalWrite(GRIP_MOTA2,LOW);           
          } 
      
      if( Ps3.event.button_down.down && (SHIFT == SH_L2))  {
          output += "Grip zu"; 
          digitalWrite( GRIP_MOTA1, LOW );  
          digitalWrite( GRIP_MOTA2, HIGH );
          
          }
      if( Ps3.event.button_up.down && (SHIFT == SH_L2))  {
          output += "Grip zu stop"; 
          digitalWrite(GRIP_MOTA1,LOW);
          digitalWrite(GRIP_MOTA2,LOW);       
          }

      if( Ps3.event.button_down.left && (SHIFT == SH_L2))  {
          if (Gpos <= 180) {Gpos=Gpos+15;}
            output += "Dreh links start";
            //output += Gpos;
            GrippRoll.write(Gpos); 
            
          }
      if( Ps3.event.button_down.left && (SHIFT == SH_L1))  {output += "Dreh links max";GrippRoll.write(0);SHIFT = 0;}  
          
      if( Ps3.event.button_down.right && (SHIFT == SH_L2))  {  
          if(Gpos >=0){Gpos=Gpos-15;}
            output += "Dreh rechts start";
            //output += Gpos;
            GrippRoll.write(Gpos);
            
        }
      if( Ps3.event.button_down.right && (SHIFT == SH_L1))  {output += "Dreh rechts max";GrippRoll.write(180);SHIFT = 0;} 
      

      
      
      /*
    if( Ps3.event.button_down.left && (SHIFT == 0))  {output += "Mid Awake + Human"; parseCommand(":SE14");}
    if( Ps3.event.button_down.up && (SHIFT == 0))    {output += "Full Awake"; parseCommand(":SE11");}    
    if( Ps3.event.button_down.right && (SHIFT == 0)) {output += "Full Awake + next Sound"; parseCommand(":SE14");}
    */
    }

    ///Circle shift --> ab hier noch die MD Codes einfügen
    if( Ps3.event.button_down.down && (SHIFT == SH_CIRCLE))  {output += "Dicso Manama"; parseCommand(":SE57");parseCommand("$84"); SHIFT = 0;}
    if( Ps3.event.button_down.left && (SHIFT == SH_CIRCLE))  {output += "Fast Smirk"; parseCommand(":SE03");SHIFT = 0;}
    if( Ps3.event.button_down.up && (SHIFT == SH_CIRCLE))    {output += "Scream"; parseCommand(":SE01"); SHIFT = 0;}   
    if( Ps3.event.button_down.right && (SHIFT == SH_CIRCLE)) {output += "Short Circuit"; parseCommand(":SE06");SHIFT = 0;}   

    //Cross Shift   
    if( Ps3.event.button_down.down && (SHIFT == SH_CROSS))  {output += "Volume Down"; parseCommand("$-"); SHIFT = 0;}
    if( Ps3.event.button_down.up && (SHIFT == SH_CROSS))    {output += "Volume Up"; parseCommand("$+"); SHIFT = 0;}  
    if( Ps3.event.button_down.right && (SHIFT == SH_CROSS)) {output += "Holos Off"; parseCommand("*ST00");SHIFT = 0;}
    if( Ps3.event.button_down.left && (SHIFT == SH_CROSS))  {output += "Holos On"; parseCommand("*RD00");SHIFT = 0;}

  
    //PS Shift
    if( Ps3.event.button_down.cross && (SHIFT == SH_PLUS)) {output += "Stick Dissable";parseCommand("DISDR");StickConnect=0;SHIFT = 0;}
    if( Ps3.event.button_down.circle && (SHIFT == SH_PLUS)) {output += "Reset MABC";parseCommand("reset");SHIFT = 0;}

    if( Ps3.event.button_down.down && (SHIFT == SH_PLUS))  {output += "PS Down"; parseCommand("D"); SHIFT = 0;}
    if( Ps3.event.button_down.up && (SHIFT == SH_PLUS))    {output += "PS Up"; parseCommand("T"); SHIFT = 0;}  
    if( Ps3.event.button_down.right && (SHIFT == SH_PLUS)) {output += "PS Right"; parseCommand("C");SHIFT = 0;}
    if( Ps3.event.button_down.left && (SHIFT == SH_PLUS))  {output += "PS Left"; parseCommand("*RD00");SHIFT = 0;}

    

    //L1 Shift
    if( Ps3.event.button_down.down && (SHIFT == SH_L1))  {output += "Leia Message"; parseCommand(":SE08"); SHIFT = 0;}
    if( Ps3.event.button_down.left && (SHIFT == SH_L1))  {output += "Wave"; parseCommand(":SE02");SHIFT = 0;}
    if( Ps3.event.button_down.up && (SHIFT == SH_L1))    {output += "Cantina Dance"; parseCommand(":SE07"); SHIFT = 0;}  
    if( Ps3.event.button_down.right && (SHIFT == SH_L1)) {output += "Wave 2"; parseCommand(":SE04");SHIFT = 0;}
    
    if( Ps3.event.button_down.l3 && (SHIFT == SH_L1)) {output += "Toggle Speed"; ToggleSpeed(); Serial.println(OverSpeed);SHIFT = 0;}

    //L2 Shift
     //// CHANGE MODE ///
    if( Ps3.event.button_down.l3 && (SHIFT == SH_L2))
    {
      mode++;
      if (mode >= 4) mode=0;
      Serial.print("Mode = ");
      Serial.println(mode);
       
      Serial2.print("mode");
      Serial2.print(mode);
      Serial2.print("\r");
      switch (mode){
      case 0:
      Serial2.print("$12\r");     ///DOME MD
      break;
      case 1:
      Serial2.print("$18\r");     ///DOME MD
      break;
      case 2:
      Serial2.print("$19\r");     ///DOME MD
      break;
      case 3:
      Serial2.print("$110\r");     ///DOME MD
      break;      
      default:
      Serial2.print("$226\r");
      break;  
      }    
      SHIFT = 0;
      parseCommand("CALL");
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
        
       posX = map(Ps3.data.analog.stick.lx, -128, 128, 0, 180);
       if (OverSpeed == 1){
       posY = map(Ps3.data.analog.stick.ly, -128, 128, 30, 150); //Speed should be manipulated
       } else {
        posY = map(Ps3.data.analog.stick.ly, -128, 128, 70, 110); //Speed should be manipulated
       }

       if ((posY >= 85) && (posY <=  95)) { posY = 90;} ///Death Zone Range
       
      

      if( Ps3.data.button.l2 ) {
        
        Serial.print("Dome- posX="); Serial.println(posX);
        DomeRot.write(posX);
      } else {
     
        //if (mode = 1)
       //Serial.print(" posX="); Serial.println(posX);
       DriveDir.write(posX);

       

      }

      Serial.print(" posY="); Serial.println(posY);
       DriveSpeed.write(posY);
 
     Serial.print("SHIFT: ");
     Serial.println(SHIFT);
    } 
    
    
    
  
   //---------------------- Battery events ---------------------
    if( battery != Ps3.data.status.battery ){
        battery = Ps3.data.status.battery;
        Serial.print("The controller battery is ");
        if( battery == ps3_status_battery_charging )      STICK_AKKU_STAT = CHARGING;
        else if( battery == ps3_status_battery_full )     STICK_AKKU_STAT = FULL;
        else if( battery == ps3_status_battery_high )     STICK_AKKU_STAT = HIGHT;
        else if( battery == ps3_status_battery_low)       STICK_AKKU_STAT = LOWR;
        else if( battery == ps3_status_battery_dying )    STICK_AKKU_STAT = DYING;
        else if( battery == ps3_status_battery_shutdown ) STICK_AKKU_STAT = SHUTDOWN;
        else Serial.println("UNDEFINED");

        switch (STICK_AKKU_STAT){
          case CHARGING:
          Serial.println("CHARGING");
          break;
          case FULL:
          Serial.println("FULL");
          break;
          case HIGHT:
          Serial.println("HIGHT");
          break;
          case LOWR:
          Serial.println("LOWR");
          break;
          case DYING:
          Serial.println("DYING");
          break;
          case SHUTDOWN:
          Serial.println("SHUTDOWN");
          break;

          default:

          break;


          
        }

    }

    
}
