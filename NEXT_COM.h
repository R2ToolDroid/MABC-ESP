#include <Arduino.h>


////Telemetrie Commands Start////
    // 0= start| 1=com | 2=setup | 3= move
    
      if (cmd == "com") {
        Serial.println("com erkannt");
        PAGE = 1;
      // myDFPlayer.next();
      
      }
      if (cmd == "start") {
        Serial.println("start erkannt"); 
        PAGE = 0;
        ShwMode();
        //Play(02,001);
        }
      if (cmd == "setup") {
      Serial.println("setup erkannt"); 
        PAGE = 2;
       // myDFPlayer.next();
       //Play(02,001);
        }
      if (cmd == "move") {
      Serial.println("move erkannt"); 
      PAGE = 3;
      //myDFPlayer.next();
      //Play(02,001);
      } 
      if (cmd == "service") {
      Serial.println("service erkannt"); 
      PAGE = 4;
     // myDFPlayer.next();
      //Play(02,001);
      } 
      if (cmd == "tools") {
      Serial.print("tools erkannt"); 
      PAGE = 5;
      //Play(02,001);
      //myDFPlayer.next();
      } 
      if (cmd == "tools_2") {
      Serial.print("tools_2 erkannt"); 
      PAGE = 6;
      //Play(02,001);
      //myDFPlayer.next();
      } 

      if (cmd == "human") {
      Serial.print("human erkannt"); 

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

      //delay(200);
      
        
      }
      
      if (cmd == "STICK") {
      Serial.print("Stick erkannt");   
      INmode = 1; ///Shadow
      inm = "STICK ";
      
      }
      if (cmd == "COIN") {
      Serial.print("Coin erkannt");
      INmode = 0; ///Coin
      inm = "COIN  ";
     
      }
      if (cmd == "CALL") {
      Serial.print("CALL erkannt"); 
      //COR = float(NewCor)/100;
      NextCom(WiFi.localIP().toString());
      return;
      } /// End of Call
      
      if (cmd == "SEND") {
      Serial.print("SEND erkannt");
      flash = true; 
      }
      
      if (cmd == "CB12") {
        Serial.print("CB12 erkannt");
        }
      
      if (cmd == "M23") {
        Serial.print("M23 erkannt");
       
        }
      if (cmd == "M32") {
       Serial.print("M32 erkannt");
      
         }
      if (cmd == "LOOK") {
       Serial.print("LOOK erkannt");
         }

////END Telemetrie Commands////
