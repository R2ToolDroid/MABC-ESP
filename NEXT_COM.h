#include <Arduino.h>


////Telemetrie Commands Start////
    // 0= start| 1=com | 2=setup | 3= move
    
      if (cmd == "com") {
       
        PAGE = 1;
      // myDFPlayer.next();
   
      }
      if (cmd == "start") {
        
        PAGE = 0;
        ShwMode();
        //Play(02,001);
        }
      if (cmd == "setup") {
         
        PAGE = 2;
       // myDFPlayer.next();
       //Play(02,001);
        }
        
      if (cmd == "resetS") {
       SendOutput(":SE00");  
      }
      
      if (cmd == "manama") {
       
       
       RNDSound = false;

      myDFPlayer.playFolder(05,8);
       //delay(100);
       SendOutput(":SE57"); 
      //PAGE = 3;
      //myDFPlayer.next();
      //Play(02,001);
      } 
      

        
      if (cmd == "move") {
     
      PAGE = 3;
      //myDFPlayer.next();
      //Play(02,001);
      } 
      if (cmd == "service") {
        
      PAGE = 4;
     // myDFPlayer.next();
      //Play(02,001);
      } 
      if (cmd == "tools") {
        
      PAGE = 5;
      //Play(02,001);
      //myDFPlayer.next();
      } 
      if (cmd == "tools_2") {
      
      PAGE = 6;
      //Play(02,001);
      //myDFPlayer.next();
      } 

      if (cmd == "human") {
        
      Serial2.print(F("mode2"));
      Serial2.print('\r');

      SendOutput("*RC01");
      mode = 2;
      
      } 

      if (cmd == "MOD"){

       mode++;
      if (mode >= 4) mode=0;
        ShwMode();

      SendOutput("@3M-Service-3");
      SendOutput("@3t");
      
      delay(100);
      Serial2.print("mode");
      Serial2.print(mode);
      Serial2.print("\r");  
  
      } 
      
      if (cmd == "CALL") {
     
      NextCom(WiFi.localIP().toString());
      return;
      } /// End of Call
      
      
           
      if (cmd == "M23") {
        
      }
      if (cmd == "M32") {
        
      }
      if (cmd == "LOOK") {
        
      }

////END Telemetrie Commands////
