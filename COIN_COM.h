#include <Arduino.h>

/*
################  COIN COMMANDS   ###########
*/

  
    if (cmd == "CBD1") {
    
    SendOutput("mode1");
    //delay(100);
    SendOutput(":SE00");
    //delay(100);
    SendOutput("center");
    //delay(100);
    mode = 1 ;  
    if (DEBUG_COM){
    S_DEBUG_COM += "######Comando CBD1######\n";
    }
    ShwMode();
    RNDSound = false;
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
      RNDSound = true;
      
      break;
      case 1:
     // Serial2.print("$18\r");     ///DOME MD
     SendOutput("mode1");
     RNDSound = false;
      break;
      case 2:
     // Serial2.print("$19\r");     ///DOME MD
      SendOutput("mode2");
      RNDSound = false;
      SendOutput("*RC01");
      break;
      case 3:
     // Serial2.print("$110\r");     ///DOME MD
     SendOutput("mode3");
     RNDSound = false;
      break;      
      default:
     // Serial2.print("$226\r");
      break;
      
     }// End Switch
      if (DEBUG_COM){
      S_DEBUG_COM += "######Comando CBD2######\n";
      }
    }

    if (cmd == "CBD3" ){
      SendOutput(":SE10");
      ShwMode();
      if (DEBUG_COM){
      S_DEBUG_COM += "######Comando CBD3######\n";
      }
    }///END CBD3
    
    ////TEST//
    if (cmd == "CB0") {         
      mode=1;
      SendOutput("tool1");     
      //delay(100);
      SendOutput(":OP03");
      //delay(100);
      if (DEBUG_COM){
      S_DEBUG_COM += ("######Comando CB0 ######\n");
      }
    }
   
    ///// Komando/////
    if (cmd == "CB1") {
      mode=1;
      SendOutput("tool2");
     // delay(100); 
      SendOutput(":OP04");
      //delay(100);
      if (DEBUG_COM){
      S_DEBUG_COM += "######Comando - CB1######\n";
      }
    }

    /////Tool Komando/////

    if (cmd == "CB2") {       
      mode=1;
      SendOutput("tool3");
      //delay(100);
      SendOutput(":OP05");
     // delay(100);
     if (DEBUG_COM){
      S_DEBUG_COM += "######Comando CBD3######\n";
     }
    }
    ///// Komando/////

    if (cmd == "CB3") {
      SendOutput(":SE09");  
      SendOutput("mode0");        
      RNDSound = false;
      myDFPlayer.playFolder(05,8);//disco
      if (DEBUG_COM){
      S_DEBUG_COM += "######Comando Manama######\n";
      }
    }
    
    if (cmd == "CB4") {
      RNDSound = false;
      SendOutput(":SE03");
      myDFPlayer.playFolder(01,2);
      if (DEBUG_COM){
      S_DEBUG_COM += "######Comando - CB4 Smirk######\n";
      }
    }

    if (cmd == "CB5") {
       SendOutput(":SE06");
       RNDSound = false;
       myDFPlayer.playFolder(04,2);
       if (DEBUG_COM){
       S_DEBUG_COM += "######Comando - CB5 Scream######\n";
       }
    }

    if (cmd == "CB6") {
       SendOutput("#OP03");
       if (DEBUG_COM){
       S_DEBUG_COM += "######Comando - CB6 Charging######\n";
       }
    }

    if (cmd == "CB7") {
      SendOutput("#OP02");
      if (DEBUG_COM){
       S_DEBUG_COM += "######Comando - CB7 Big Door ######\n"; 
      }
    }

    if (cmd == "CB8") {
      SendOutput("#SAON");
      if (DEBUG_COM){
      S_DEBUG_COM +=   "######Comando - CB8 Schrauber ON ######\n";  
      }
    }

    if (cmd == "CB9") {
      SendOutput("#OP01");
      if (DEBUG_COM){
      S_DEBUG_COM += "######Comando - CB9 Gripper Door ######\n";
      }
    }

    if (cmd == "CB10") {
     SendOutput("#FION");
     if (DEBUG_COM){
      S_DEBUG_COM += "######Comando - CB10 Fire ON ####\n";
     }
    }

    if (cmd == "CB11") {
    SendOutput("#FIOFF");
    if (DEBUG_COM){
      S_DEBUG_COM += "######Comando - CB11 Fire OFF ####\n";
    }
    }
    
     if (cmd == "CB12") {
      SendOutput("#OPD1");
      if (DEBUG_COM){
      S_DEBUG_COM += "######Comando - CB12 Shuba 1####\n";
      }
    }

    if (cmd == "CB13") {
    SendOutput("#OPD2");
    if (DEBUG_COM){
      S_DEBUG_COM += "######Comando - CB13 Shuba 2####\n";
    }
      
    }
    
    if (cmd == "CB14") {
      SendOutput("#OPD3");
      if (DEBUG_COM){
      S_DEBUG_COM += "######Comando - CB14 Shuba 3####\n";
      }
      
    }

    if (cmd == "CB15") {
      SendOutput("#OPD4");
      if (DEBUG_COM){
      S_DEBUG_COM += "######Comando - CB15 Shuba 4####\n";
      }
      
    }

    if (cmd == "CB16") {
    SendOutput("#OP00");
    if (DEBUG_COM){
      S_DEBUG_COM += "######Comando - CB16 Open Body All####\n";
    }
      
    }

    if (cmd == "CB17") {
    SendOutput("#CL00");
    if (DEBUG_COM){
      S_DEBUG_COM += "######Comando - CB17 Close Body All####\n";
    }
      
    }

   
