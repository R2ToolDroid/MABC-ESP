#include <Arduino.h>

/*
################  COIN COMMANDS   ###########
*/

  
    if (cmd == "CBD1") {
      if (debug){
        Serial.println("######Comando CBD1######");
        Serial.println(cmd);
        
      }
    
    //servoSequencer.play(SeqBodyPanelAllSoftClose, SizeOfArray(SeqBodyPanelAllSoftClose), (GROUP_DOORS));
    //Serial1.print("5");     // to Coin Levelstatus
    Serial2.print("mode1");           // hier geht es weiter zum Dome Controller
    Serial2.print('\r');
  
    
    //Serial3.print(":CL00");           // Soft Close
    Serial2.print(":SE00");
    Serial2.print('\r');
    //Sysreset();

    Serial2.print("center");           // hier geht es weiter zum Dome Controller
    Serial2.print('\r'); 
    mode = 1 ;  
    
    }
     
    if (cmd == "CBD2" ){

      if (mode >=3) {
        mode=0;
        }else {
        mode = mode+1;
      }
    
    //Serial3.print("$12\r");     ///DOME MD
    //akustische Rückmeldung welcher mode
    
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
    
      
    Serial2.print("mode");       // DOME DRIVE
    Serial2.print(mode);
    Serial2.print('\r');  

    ///NextCom(String(mode));
      
    }

    if (cmd == "CBD3" ){

    Serial2.print(":SE10\r");  ///Quite Mode Dome
    
    
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
    
 
      
    }///END CBD3
    
    ////TEST//
    if (cmd == "CB0") {
    if (debug){
        Serial.println("######Comando CB0 ######");
        Serial.println(cmd);
      }

      
      Serial2.print("usb");           // hier geht es weiter zum  Dome Controller
      Serial2.print('\r');
      //delay(1000);
      Serial2.print(":OP03");           // hier geht es weiter zum Marcduino Dome Controller
      Serial2.print('\r');
      //delay(500);
      Serial2.print("$12");
      Serial2.print("\r");
    }
   
    
    
    
    ///// Komando/////
    if (cmd == "CB1") {
    if (debug){
          Serial.println("######Comando - CB1######");
         Serial.println(cmd);
       }
      
      Serial2.print("tool1");
      Serial2.print("\r");
      //delay(2000); 
      Serial2.print(":OP04");
      Serial2.print("\r");
      //delay(100);
      Serial2.print("$118");
      Serial2.print("\r");
    }

    /////Tool Komando/////

    if (cmd == "CB2") {
    if (debug){
          Serial.println("######Comando - CB2######");
         Serial.println(cmd);
       }
      
      Serial2.print("tool2");
      Serial2.print("\r");
      //delay(2000);
      Serial2.print("$12");
      Serial2.print("\r");
      //delay(500);
      Serial2.print(":OP05");
      Serial2.print("\r");
      
     
    }
    ///// Komando/////

    if (cmd == "CB3") {
    if (debug){
          Serial.println("######Comando - tool3######");
         Serial.println(cmd);
       }      

      
      Serial2.print(":OP07");
      Serial2.print("\r");
      //delay(500);
      Serial2.print(":OP08");
      Serial2.print("\r");
      //delay(500);
      
      Serial2.print("$12");
      Serial2.print("\r");

      
    }
    
    if (cmd == "CB4") {
    if (debug){
          Serial.println("######Comando - CB4######");
         Serial.println(cmd);
       }
          
     //OpenDoorLeft();     
    // OpenLowerArm(); 
    Serial2.print("#GAON");
    Serial2.print("\r");
     
    }

    if (cmd == "CB5") {
    if (debug){
          Serial.println("######Comando - CB5 Bohren######");
         Serial.println(cmd);
    }
    
    //OpenDoorRight();
   // OpenUpperArm();
     // Arm2();
    Serial2.print("#SAON");
    Serial2.print("\r");

    
   
    }

     if (cmd == "CB6") {
    if (debug){
          Serial.println("######Comando - CB6 Charging######");
         Serial.println(cmd);
       }
     
      //servoDispatch.moveTo(DOOR_CHARGEBAY , 150, 1300, 2050); 
     
      Serial2.print("$116");
      Serial2.print("\r");

      Serial2.print("#OP03");
      Serial2.print("\r");

      
    }

    if (cmd == "CB7") {
    if (debug){
          Serial.println("######Comando - CB7 Manama ######");
         Serial.println(cmd);
       }
       myDFPlayer.playFolder(05,7);
       
      Serial2.print(":SE57");
      Serial2.print("\r");     
     
      //servoSequencer.play(SeqBodyPanelDance, SizeOfArray(SeqBodyPanelDance), (GROUP_DOORS));     
    }

    if (cmd == "CB8") {
    if (debug){
          Serial.println("######Comando - CB8 Animation Lang Test ######");
         Serial.println(cmd);
       }

          
      //ANIMATION_PLAY_ONCE(player, test);

      
    }

    if (cmd == "CB9") {
    if (debug){
          Serial.println("######Comando - CB9 Drive ######");
         Serial.println(cmd);
       }
          
      Serial2.print("$211");
      Serial2.print("\r");
    // pwm.setPWM(14, 0, pulseWidth(KlappeAuf[4]));//Klappe 4
      
    }

    if (cmd == "CB10") {
    if (debug){
          Serial.println("######Comando - CB10 Move####");
         Serial.println(cmd);
       }
          
      Serial2.print("$217");
      Serial2.print("\r");
      //pwm.setPWM(12, 0, pulseWidth(KlappeAuf[2]));//Klappe 2
      
      
    }

    if (cmd == "CB11") {
    if (debug){
          Serial.println("######Comando - CB11 Wave####");
         Serial.println(cmd);
       }
          
      Serial2.print(":SE04");
      Serial2.print("\r");

      //servoSequencer.play(SeqBodyPanelWave2, SizeOfArray(SeqBodyPanelWave2), (GROUP_DOORS));
      
    }
    
    if (cmd == "CB12") {
    if (debug){
          Serial.println("######Comando - CB12 Smirk####");
         Serial.println(cmd);
       }
          
      Serial2.print(":SE03");
      Serial2.print("\r");

      //servoSequencer.play(SeqBodyPanelWaveFast, SizeOfArray(SeqBodyPanelWaveFast), (GROUP_DOORS));
      
    }

    if (cmd == "CB13") {
    if (debug){
          Serial.println("######Comando - CB13 Disco####");
         Serial.println(cmd);
       }
          
      Serial2.print(":SE07");
      Serial2.print("\r");
      //servoSequencer.play(SeqBodyPanelDance, SizeOfArray(SeqBodyPanelDance), (GROUP_DOORS));
     // Dance();
      
    }
    
    if (cmd == "CB14") {
    if (debug){
          Serial.println("######Comando - CB14 Open All####");
         Serial.println(cmd);
       }
          
      Serial2.print(":OP00");
      Serial2.print("\r");

     // servoSequencer.play(SeqBodyPanelAllOpen, SizeOfArray(SeqBodyPanelAllOpen), (GROUP_DOORS));

     // OpenAll();
      
    }

    if (cmd == "CB15") {
    if (debug){
          Serial.println("######Comando - CB15 Close All####");
         Serial.println(cmd);
       }
          
      Serial2.print(":CL00");
      Serial2.print("\r");

     // servoSequencer.play(SeqBodyPanelAllSoftClose, SizeOfArray(SeqBodyPanelAllSoftClose), (GROUP_DOORS));

     // CloseAll();
      
    }

    if (cmd == "CB16") {
    if (debug){
          Serial.println("######Comando - CB16 Sream####");
         Serial.println(cmd);
       }
          
      Serial2.print(":SE15");
      Serial2.print("\r");
      //servoSequencer.play(SeqBodyPanelAllFlutter, SizeOfArray(SeqBodyPanelAllFlutter), (GROUP_DOORS));
     //  DelayCall::schedule([] {
      //  servoSequencer.play(SeqBodyPanelAllSoftClose, SizeOfArray(SeqBodyPanelAllSoftClose), (GROUP_DOORS));
     //   }, 5000);
      //OpenAll();
      
    }

    if (cmd == "CB17") {
    if (debug){
          Serial.println("######Comando - CB17 Faint ####");
         Serial.println(cmd);
       }
      
      SendOutput(":SE06");

     // Faint();
      
    }

   
