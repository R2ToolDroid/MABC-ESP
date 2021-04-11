#include <Arduino.h>

/*
################  SHADOW_MD_PULE COMMANDS   ###########
*/

    if (cmd == "DISDR") {
      Serial.print("Dissabling Drive Stick");
     // mp3Trigger.play(30);
      } 
      
     if (cmd == "ENDR") {
      Serial.print("Enabling Drive Stick");
      //mp3Trigger.play(52);
      }  
     if (cmd == "OVSPON") {
       Serial.print("Overspeed");
     
      }  

     if (cmd == "OVSPOFF") {
      Serial.print("Overspeed OFF");
     
      }  
      if (cmd == "DOMEAON") {
      Serial.print("Dome Automation ON");

      Serial2.print("mode1\r");
      mode=1;
      }  
      if (cmd == "DOMEAOFF") {
      Serial.print("Dome Automation OFF");
      
      Serial2.print("mode1\r");
      
      }  

      if (cmd == "HUMAN HOLO") {
      Serial.print("Dome Automation OFF");

      Serial2.print("mode2\r");
      mode = 2;
      
      } 


      if (cmd == "mode0") {
      Serial.print("mode0");
      Serial2.print("mode0\r");
      mode = 0;
      } 

      if (cmd == "mode1") {
      Serial.print("mode1");
      Serial2.print("mode1\r");
      mode = 1;
      } 
      if (cmd == "mode3") {
      Serial.print("mode3");
      Serial2.print("mode3\r");
      mode = 3;
      } 




      

/*
################  SHADOW_MD_PULE COMMANDS END  ###########
##########################################################
*/
