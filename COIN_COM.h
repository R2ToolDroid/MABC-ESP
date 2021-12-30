#include <Arduino.h>

/*
################  COIN COMMANDS   ###########
*/

  
    if (cmd == "CBD1") {
    
    SendOutput("mode1");
    //delay(100);
    SendOutput(":SE10");
    //delay(100);
    SendOutput("center");
    //delay(100);
    mode = 1 ;  
    
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
     
     
      
    }

    if (cmd == "CBD3" ){
      SendOutput(":SE10");
      ShwMode();
      
    }///END CBD
    
    ////TEST//
    if (cmd == "CB0") {         
      //mode=1;
      SendOutput("usb");     
      delay(500);
      SendOutput(":OP03");
      //delay(100);
      
    }
   
    ///// Komando/////
    if (cmd == "CB1") {
      //mode=1;
      SendOutput("tool1");
      delay(500); 
      SendOutput(":OP04");
      //delay(100);
      
    }

    /////Tool Komando/////

    if (cmd == "CB2") {       
      //mode=1;
       SendOutput("tool3");     
      delay(500);
      SendOutput(":OP06");
     // delay(100);
     
    }
    ///// Komando/////

    if (cmd == "CB3") {
      SendOutput(":SE09");  
      SendOutput("mode0");        
      RNDSound = false;
      myDFPlayer.playFolder(05,8);//disco
      
    }
    
    if (cmd == "CB4") {
      RNDSound = false;
      SendOutput(":SE03");
      myDFPlayer.playFolder(01,2);
      
    }

    if (cmd == "CB5") {
       SendOutput(":SE06");
       RNDSound = false;
       myDFPlayer.playFolder(04,2);
       
    }

    if (cmd == "CB6") {
       SendOutput("#OP03");
       
    }

    if (cmd == "CB7") {
      SendOutput("#OP02");
      
    }

    if (cmd == "CB8") {
      SendOutput("#SAON");
      
    }

    if (cmd == "CB9") {
      SendOutput("#OP01");
      
    }

    if (cmd == "CB10") {
     SendOutput("#FION");
     
    }

    if (cmd == "CB11") {
    SendOutput("#FIOFF");
    
    }
    
     if (cmd == "CB12") {
      SendOutput("#OPD1");
      
    }

    if (cmd == "CB13") {
    SendOutput("#OPD2");
          
    }
    
    if (cmd == "CB14") {
      SendOutput("#OPD3");
      
      
    }

    if (cmd == "CB15") {
      SendOutput("#OPD4");
      
      
    }

    if (cmd == "CB16") {
    SendOutput("#OP00");
    
      
    }

    if (cmd == "CB17") {
    SendOutput("#CL00");
    
      
    }

   
