#include <Arduino.h>

/*
################  COIN COMMANDS   ###########
*/

  
    if (cmd == "CBD1") {
    
    SendOutput("mode1");
    delay(100);
    SendOutput(":SE00");
    delay(100);
    SendOutput("center");
    delay(100);
    mode = 1 ;  
    output += "######Comando CBD1######\n";
    ShwMode();
    }
     
    if (cmd == "CBD2" ){

      if (mode >=3) {
        mode=0;
        }else {
        mode = mode+1;
      }
      ShwMode();
    switch (mode){
      case 0:
     // Serial2.print("$12\r");     ///DOME MD
      SendOutput("mode0");
      break;
      case 1:
     // Serial2.print("$18\r");     ///DOME MD
     SendOutput("mode1");
      break;
      case 2:
     // Serial2.print("$19\r");     ///DOME MD
      SendOutput("mode2");
      break;
      case 3:
     // Serial2.print("$110\r");     ///DOME MD
     SendOutput("mode3");
      break;      
      default:
     // Serial2.print("$226\r");
      break;
      
     }// End Switch
 
      output += "######Comando CBD2######";
    }

    if (cmd == "CBD3" ){

    SendOutput(":SE10");
    
    switch (mode){
      case 0:
      ///Serial2.print("$18\r");     ///DOME MD
      break;
      case 2:
      //Serial2.print("$19\r");     ///DOME MD
      break;
      case 3:
      //Serial2.print("$110\r");     ///DOME MD
      break;      
      default:
      //Serial2.print("$226\r");
      break;
      
      }  // end switch  
      output += "######Comando CBD3######";
    }///END CBD3
    
    ////TEST//
    if (cmd == "CB0") {         
      mode=3;
      SendOutput("usb");     
      delay(100);
      SendOutput(":OP03");
      delay(100);
      output += ("######Comando CB0 ######");
    }
   
    ///// Komando/////
    if (cmd == "CB1") {
      mode=3;
      SendOutput("tool1");
      delay(100); 
      SendOutput(":OP04");
      delay(100);
      output += "######Comando - CB1######";
    }

    /////Tool Komando/////

    if (cmd == "CB2") {       
      mode=3;
      SendOutput("tool2");
      delay(100);
      SendOutput(":OP05");
      delay(100);
      output += "######Comando CBD3######";
    }
    ///// Komando/////

    if (cmd == "CB3") {
      SendOutput("tool3");
      delay(100);
      SendOutput(":OP07");      
      delay(100);
      SendOutput(":OP08");
      
      output += "######Comando tool3######";
      
    }
    
    if (cmd == "CB4") {
      SendOutput("#GAON");
      output += "######Comando - CB4######";
    }

    if (cmd == "CB5") {
       SendOutput("#SAON");
       output += "######Comando - CB5 Bohren######";
    }

    if (cmd == "CB6") {
       SendOutput("#OP03");
       output += "######Comando - CB6 Charging######";
    }

    if (cmd == "CB7") {
       myDFPlayer.playFolder(05,8);
       delay(100);
       SendOutput(":SE57"); 
       output += "######Comando - CB7 Manama ######"; 
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

   
