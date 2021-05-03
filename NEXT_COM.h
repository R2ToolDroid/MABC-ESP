#include <Arduino.h>


////Telemetrie Commands Start////
    // 0= start| 1=com | 2=setup | 3= move
    
      if (cmd == "com") {
        Serial.println("com erkannt");
        PAGE = 1;
      }
      if (cmd == "start") {
        Serial.println("start erkannt"); 
        PAGE = 0;
        ShwMode();
        }
      if (cmd == "setup") {
      Serial.println("setup erkannt"); 
        PAGE = 2;
        }
      if (cmd == "move") {
      Serial.println("move erkannt"); 
      PAGE = 3;
      } 
      if (cmd == "service") {
      Serial.println("service erkannt"); 
      PAGE = 4;
      } 
      if (cmd == "tools") {
      Serial.print("tools erkannt"); 
      PAGE = 5;
      } 
      if (cmd == "tools_2") {
      Serial.print("tools_2 erkannt"); 
      PAGE = 6;
      } 

      if (cmd == "human") {
      Serial.print("human erkannt"); 

      Serial2.print("mode2");
      Serial2.print('\r');

      SendOutput("*RC01");
      
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
