#include <Arduino.h>


////Telemetrie Commands Start////
    // 0= start| 1=com | 2=setup | 3= move
    
      if (cmd == "com") {
        //Serial.println("com erkannt");
        if (DEBUG_COM){
        S_DEBUG_COM += "com erkannt\n";
        }
        PAGE = 1;
      // myDFPlayer.next();
   
      }
      if (cmd == "start") {
        if (DEBUG_COM){
        S_DEBUG_COM += "start erkannt\n"; 
        }
        PAGE = 0;
        ShwMode();
        //Play(02,001);
        }
      if (cmd == "setup") {
         if (DEBUG_COM){
         S_DEBUG_COM += "setup erkannt\n"; 
         }
        PAGE = 2;
       // myDFPlayer.next();
       //Play(02,001);
        }
        
      if (cmd == "resetS") {
       SendOutput(":SE00");  
      }
      
      if (cmd == "manama") {
       if (DEBUG_COM){
       S_DEBUG_COM += "manama\n"; 
       }
       
       RNDSound = false;

      myDFPlayer.playFolder(05,8);
       //delay(100);
       SendOutput(":SE57"); 
      //PAGE = 3;
      //myDFPlayer.next();
      //Play(02,001);
      } 
      

        
      if (cmd == "move") {
      if (DEBUG_COM){  
      S_DEBUG_COM +=  "move erkannt\n";
      }
      PAGE = 3;
      //myDFPlayer.next();
      //Play(02,001);
      } 
      if (cmd == "service") {
        if (DEBUG_COM){
        S_DEBUG_COM += "service erkannt\n" ;
        }
      PAGE = 4;
     // myDFPlayer.next();
      //Play(02,001);
      } 
      if (cmd == "tools") {
        if (DEBUG_COM){
        S_DEBUG_COM += "tools erkannt\n"; 
        }
      PAGE = 5;
      //Play(02,001);
      //myDFPlayer.next();
      } 
      if (cmd == "tools_2") {
      if (DEBUG_COM){
        S_DEBUG_COM += "tools_2 erkannt\n"; 
      }
      PAGE = 6;
      //Play(02,001);
      //myDFPlayer.next();
      } 

      if (cmd == "human") {
        if (DEBUG_COM){
        S_DEBUG_COM += "human erkannt\n"; 
        }
      Serial2.print("mode2");
      Serial2.print('\r');

      SendOutput("*RC01");
      mode = 2;
      
      } 

      if (cmd == "MOD"){

       mode++;
      if (mode >= 4) mode=0;
        ShwMode();
      
      delay(100);
      Serial2.print("mode");
      Serial2.print(mode);
      Serial2.print("\r");  
  
      } 
      
      if (cmd == "CALL") {
        if (DEBUG_COM){
          S_DEBUG_COM += "CALL erkannt\n"; 
        }//COR = float(NewCor)/100;
      NextCom(WiFi.localIP().toString());
      return;
      } /// End of Call
      
      if (cmd == "SEND") {
        if (DEBUG_COM){
        S_DEBUG_COM += "SEND erkannt\n";
        }
      flash = true; 
      } 
           
      if (cmd == "M23") {
        if (DEBUG_COM){
        S_DEBUG_COM += "M23 erkannt\n";
        }
      }
      if (cmd == "M32") {
        if (DEBUG_COM){
          S_DEBUG_COM += "M32 erkannt\n";
        }
         }
      if (cmd == "LOOK") {
        if (DEBUG_COM){
            S_DEBUG_COM += "LOOK erkannt\n";
        }
         }

////END Telemetrie Commands////
