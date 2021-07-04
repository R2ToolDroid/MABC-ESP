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
    output += "######Comando CBD1######\n";
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
 
      output += "######Comando CBD2######";
    }

    if (cmd == "CBD3" ){
      SendOutput(":SE10");
      ShwMode();
      output += "######Comando CBD3######";
    }///END CBD3
    
    ////TEST//
    if (cmd == "CB0") {         
      mode=1;
      SendOutput("tool1");     
      //delay(100);
      SendOutput(":OP03");
      //delay(100);
      output += ("######Comando CB0 ######");
    }
   
    ///// Komando/////
    if (cmd == "CB1") {
      mode=1;
      SendOutput("tool2");
     // delay(100); 
      SendOutput(":OP04");
      //delay(100);
      output += "######Comando - CB1######";
    }

    /////Tool Komando/////

    if (cmd == "CB2") {       
      mode=1;
      SendOutput("tool3");
      //delay(100);
      SendOutput(":OP05");
     // delay(100);
      output += "######Comando CBD3######";
    }
    ///// Komando/////

    if (cmd == "CB3") {
      SendOutput(":SE09");  
      SendOutput("mode0");        
      RNDSound = false;
      myDFPlayer.playFolder(05,8);//disco
      output += "######Comando Manama######";
      
    }
    
    if (cmd == "CB4") {
      RNDSound = false;
      SendOutput(":SE03");
      myDFPlayer.playFolder(01,2);
      output += "######Comando - CB4 Smirk######";
    }

    if (cmd == "CB5") {
       SendOutput(":SE06");
       RNDSound = false;
       myDFPlayer.playFolder(04,2);
       output += "######Comando - CB5 Scream######";
    }

    if (cmd == "CB6") {
       SendOutput("#OP03");
       output += "######Comando - CB6 Charging######";
    }

    if (cmd == "CB7") {
      SendOutput("#OP02");
      
       output += "######Comando - CB7 Big Door ######"; 
    }

    if (cmd == "CB8") {
      SendOutput("#SAON");
      output +=   "######Comando - CB8 Schrauber ON ######";  
      
    }

    if (cmd == "CB9") {
      SendOutput("#OP01");
      output += "######Comando - CB9 Gripper Door ######";
    }

    if (cmd == "CB10") {
     SendOutput("#FION");
      output += "######Comando - CB10 Fire ON ####";
      
    }

    if (cmd == "CB11") {
    SendOutput("#FIOFF");
      output += "######Comando - CB11 Fire OFF ####";
      
    }
    
     if (cmd == "CB12") {
      SendOutput("#OPD1");
      output += "######Comando - CB12 Shuba 1####";
    }

    if (cmd == "CB13") {
    SendOutput("#OPD2");
      output += "######Comando - CB13 Shuba 2####";
      
    }
    
    if (cmd == "CB14") {
      SendOutput("#OPD3");
      output += "######Comando - CB14 Shuba 3####";
      
    }

    if (cmd == "CB15") {
      SendOutput("#OPD4");
      output += "######Comando - CB15 Shuba 4####";
      
    }

    if (cmd == "CB16") {
    SendOutput("#OP00");
      output += "######Comando - CB16 Open Body All####";
      
    }

    if (cmd == "CB17") {
    SendOutput("#CL00");
      output += "######Comando - CB17 Close Body All####";
      
    }

   
