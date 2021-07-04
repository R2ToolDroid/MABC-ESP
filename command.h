#include <Arduino.h>    

void SendOutput(String dcmd) {   ///VIA SHD_PULS to MD Dome Board

    //delay(200);
    
    if (debug){
      Serial.println(dcmd);
    }
    
    Serial2.print(dcmd);
    Serial2.print('\r'); 
    cmd = "";
    return;
}

void parseCommand(String cmd) {
/*
################  MAIN CONTROLLER COMMANDS   ###########
*/
   ///Sound Sqeuenzes DFPlayer ///
      if (cmd == ":SE00"){myDFPlayer.playFolder(01,8);}
      if (cmd == ":SE01"){myDFPlayer.playFolder(04,1);}
      if (cmd == ":SE02"){myDFPlayer.playFolder(01,14);}
      if (cmd == ":SE03"){myDFPlayer.playFolder(01,2);}
      if (cmd == ":SE04"){myDFPlayer.playFolder(01,7);}
      if (cmd == ":SE05"){RNDSound = false;myDFPlayer.playFolder(05,3);}
      if (cmd == ":SE06"){RNDSound = false;myDFPlayer.playFolder(04,2);}//faint
      if (cmd == ":SE07"){RNDSound = false;myDFPlayer.playFolder(05,3);}
      if (cmd == ":SE08"){RNDSound = false;myDFPlayer.playFolder(05,1);}
      if (cmd == ":SE09"){RNDSound = false;myDFPlayer.playFolder(05,8);}//disco
      if (cmd == ":SE10"){myDFPlayer.playFolder(02,1);RNDSound = false;}
      if (cmd == ":SE11"){myDFPlayer.playFolder(01,14);RNDSound = true;}
      if (cmd == ":SE12"){myDFPlayer.playFolder(02,2);}
      if (cmd == ":SE13"){myDFPlayer.playFolder(02,4);RNDSound = true;}
      if (cmd == ":SE14"){myDFPlayer.playFolder(02,5);RNDSound = true;}
      if (cmd == ":SE15"){myDFPlayer.playFolder(04,1);}
      if (cmd == ":SE51"){myDFPlayer.playFolder(04,1);}

      if (cmd == "$87"){RNDSound = false;myDFPlayer.playFolder(05,4);}  ///Musik
      if (cmd == "$5"){myDFPlayer.playFolder(02,3);}  //Whistle
      if (cmd == "$3"){myDFPlayer.playFolder(02,6);}  //Happy
      if (cmd == "NO"){myDFPlayer.playFolder(03,7);}  //NO
      if (cmd == "$2"){myDFPlayer.next();}  //Talk  
      if (cmd == "#OF00"){myDFPlayer.playFolder(01,20);}   
      
    
  if (cmd == "debug") {
      if (debug){
          Serial.println("######Comando - debug######");
         Serial.println(cmd);
       }
       debug=1;
  
  Serial.println(F(__FILE__ " " __DATE__ " " __TIME__));
  Serial.println("##### Master_Body_Controller ESP32 03.04.2021 #####");
  Serial.println("Comandos von RC - CoinTaster - Wfif Modul werde verarbeitet");
  Serial.println("INPUT:");
  Serial.println("..... Nextion Display .............Serial 1 RX");
  Serial.println("..... From WIFI....................Serial 2 RX");
  Serial.println("");
  Serial.println("OUTPUT:");
  Serial.println("..... NEXTION Display an ..........Serial 1 TX");
  Serial.println("..... To Dome Drive................Serial 2 TX");
  Serial.println("");
  Serial.println("...fuer DebugMode debug eingeben...");
  Serial.println("...ende DebugMode debug off eingeben...");
  Serial.println("...SERIAL is DEBUG 115200 - 9600 BAUD !!");
  Serial.println("........................................");
  Serial.println("DF Player Status");
  Serial.println(F("readState--------------------"));
  Serial.println(myDFPlayer.readState()); //read mp3 state
  Serial.println(F("readVolume--------------------"));
  Serial.println(myDFPlayer.readVolume()); //read current volume
  Serial.print("...MODE = ");
  Serial.println(mode);
  Serial.print("...PAGE = ");
  Serial.println(PAGE);
  Serial.print("...Stick Enable = ");
  Serial.println(StickConnect);
  Serial.print("####Fuel Data A% = ");
  Serial.print(FuelA_P);
  Serial.print(" Fuel A: ");
  Serial.print(FuelA);
  Serial.print("####Fuel Data B% = ");
  Serial.print(FuelB_P);
  Serial.print(" Fuel B: ");
  Serial.println(FuelB);
  Serial.print("- Akku Status Stick : ");
  Serial.println(STICK_AKKU_STAT);
  
    }

    if (cmd == "debug off") {
    if (debug){
         Serial.println("######Comando - debug off######");
         Serial.println(cmd);
       }
       debug=0;
    }
#include "NEXT_COM.h" 
#include "COIN_COM.h"    

      if (cmd == "find") {
      //Serial2.print("find\r");
      SendOutput("find");
      }
      
    if (cmd == "DISDR") {
      Serial.print("disconnect...");    
       Ps3.end();
       StickConnect = 0;
       STICK_AKKU_STAT = 6;
      }
      
      
  
    if (cmd == "center") {
    //Serial2.print("center");           // hier geht es weiter zum Dome Controller
    //Serial2.print('\r');
    SendOutput("center");
    }

    if (cmd == "C") {
    Serial2.print("C");           // Body Center
    Serial2.print('\r');

    myDFPlayer.playFolder(02,001);
    
    }

    if (cmd == "T") {
    Serial2.print("T");           // Body Center
    Serial2.print('\r');
    }

    if (cmd == "D") {
    Serial2.print("D");           // Body Center
    Serial2.print('\r');
    }

    if (cmd == "O") {
    Serial2.print("O");           // Body Center
    Serial2.print('\r');
    }

    if (cmd == "I") {
    Serial2.print("I");           // Body Center
    Serial2.print('\r');
    }
    
    
    if (cmd == "reset") {
    if (debug){
        Serial.println("######Comando reset ######");
        Serial.println(cmd);
      }
     //ESP.restart();
     mode = 3; ///Service
      
      //Serial2.print("mode3\r");           // hier geht es weiter zum  SHD_PULSE
      
      //delay(100);
      SendOutput("mode3");
      SendOutput(":SE10");
 
    }

    if (cmd == "hreset") {
    if (debug){
        Serial.println("######Comando reset ######");
        Serial.println(cmd);
      }
     //ESP.restart();
     mode = 0; ///Service
      
      //Serial2.print("mode0\r");           // hier geht es weiter zum  SHD_PULSE
      //delay(100);
      SendOutput("mode0");
      SendOutput(":SE10");
      myDFPlayer.playFolder(03,007);
      delay(3000);
      ESP.restart();
    }  
    

    

    if (cmd == "mode1") {
    if (debug){
         Serial.println("######Comando - mode1######");
         Serial.println(cmd);
       }
      Serial2.print("mode1\r");       
      mode=1;
      
      ShwMode();
    }
  
    if (cmd == "mode2") {
    if (debug){
         Serial.println("######Comando - mode2######");
         //Serial.println(cmd);
       }
      Serial2.print("mode2\r");       
      mode=2;
      ShwMode();
    }
  
    if (cmd == "mode3") {
    if (debug){
         Serial.println("######Comando - mode3######");
         Serial.println(cmd);
       }
      Serial2.print("mode3\r");
      mode=3;
      ShwMode();
    }
  
    if (cmd == "mode0") {
    if (debug){
         Serial.println("######Comando - mode0######");
         Serial.println(cmd);
       }
      //Serial2.print("mode0\r");
      SendOutput("mode0");
      mode=0;
      ShwMode();
    }

    ///VOICE COMMANDS///
    if (cmd == "tool0") {
    if (debug){
         Serial.println("######Comando - tool0######");
         Serial.println(cmd);
       }
      ///Action
      Serial2.print("usb\r");
      SendOutput("usb");
      //mode=0;
      mode=3;
      DomeTurnPos = true;
      TargetPos = 400;
    }

    if (cmd == "tool1") {
    if (debug){
         Serial.println("######Comando - tool1######");
         Serial.println(cmd);
       }
      ///Action
      //Serial2.print("tool1\r");
      //mode=0;
      mode=3;
      SendOutput("tool1");
     // DomeTurnPos = true;
     // TargetPos = 500;
      
    }

    if (cmd == "tool2") {
    if (debug){
         Serial.println("######Comando - tool2######");
         Serial.println(cmd);
       }
      ///Action
      SendOutput("tool2");
      mode=3;
     // DomeTurnPos = true;
     // TargetPos = 600;
      
    }

    if (cmd == "tool3") {
    if (debug){
         Serial.println("######Comando - tool3######");
         Serial.println(cmd);
       }
      ///Action
     // Serial2.print("tool3\r");
      SendOutput("tool3");
      mode=3;
      //DomeTurnPos = true;
      //TargetPos = 800;
      
    }

    if (cmd == "tool4") {
    if (debug){
         Serial.println("######Comando - tool4######");
         Serial.println(cmd);
       }
      ///Action
      //Serial2.print("tool4\r");
      //mode=0;
      SendOutput("tool4");
    }

    if (cmd == "tool5") {
    if (debug){
         Serial.println("######Comando - tool5######");
         Serial.println(cmd);
       }
      ///Action
      //Serial2.print("tool5\r");
      //mode=0;
      SendOutput("tool5");
    }

    if (cmd == "tool6") {
    if (debug){
         Serial.println("######Comando - tool6######");
         Serial.println(cmd);
       }
      ///Action
      //Serial2.print("tool6\r");
      //mode=0;
      //SendOutput("tool7");
    }

    if (cmd == "tool7") {
    if (debug){
         Serial.println("######Comando - tool7######");
         Serial.println(cmd);
       }
      ///Action
      //Serial2.print("tool7\r");
      //mode=0;
      
    }
    
    if (cmd == "tool8") {
    if (debug){
         Serial.println("######Comando - tool8######");
         Serial.println(cmd);
       }
      ///Action
      //Serial2.print("tool7\r");
      //mode=0;
      
    }
    if (cmd == "tool9") {
    if (debug){
         Serial.println("######Comando - tool9######");
         Serial.println(cmd);
       }
      ///Action
      //Serial2.print("tool7\r");
      //mode=0;
      
    }
    if (cmd == "tool10") {
    if (debug){
         Serial.println("######Comando - tool10######");
         Serial.println(cmd);
       }
      ///Action
      //Serial2.print("tool7\r");
      //mode=0;
      
    }
    
    

    /// Filtern ob Dome Komando oder nicht ///
    
    if (cmd.startsWith(":")) {
      if (debug){
        Serial.println("######Comando Pefix : DOME ######");
        Serial.println(cmd);
      }

     
     
      SendOutput(cmd);


      
    }

    if (cmd.startsWith("#")) {
      if (debug){
        Serial.println("######Comando Prefix # BODY ######");
        Serial.println(cmd);
      }
     
      SendOutput(cmd);
    }
    

    if (cmd.startsWith("$")) {
     
      if (debug){
        Serial.println("######Comando Prefix $ SOUND######");
        Serial.println(cmd);
      }

      if (cmd == "$+") {   
        vol = vol-10;     
        
        myDFPlayer.volumeUp();  
      }

      if (cmd == "$-") {
        vol = vol+10;
        myDFPlayer.volumeDown();
        
      }
      if (cmd == "$m") {
        
        myDFPlayer.volume(10);
        
      }
      if (cmd == "$f") {
        
        myDFPlayer.volume(30);
        
      }
      
      if (cmd == "$R") {
        
        //myDFPlayer.volume(30);
        RNDSound = true;
      }

      if (cmd == "$s") {
        
        //myDFPlayer.volume(30);
        RNDSound = false;
      }


      
      
     SendOutput(cmd);
    }

    
    if (cmd.startsWith("*")) 
    {
      if (debug){
        Serial.println("######Comando Prefix * HOLO ######");
        Serial.println(cmd);
      }
     SendOutput(cmd);
    }

    NextCom(cmd);
    cmd="";
}

/*//BODY Action with Prefix #
 
DO ALL SE Marcduino Commands with : Prefix 


Panels:
#CL00
#CL01 - 05

#OP00
#OP01 - 05

Panels Flutter:

#OF00
#OF01 - 05

ARMS :

#OPUA   //Upper Arm
#OPLA   //Lower Arm

#CLUA   //Upper Arm
#CLLA   //Lower Arm

#LGA   //Lift Gripper Arm
#DGA   //Down Gripper Arm

#CC    //lose Claw
#OC    //open Claw

#CPUL  //CPU Arm Lift
#CPUD  //CPU Arm Down

#CPU1  //CPU Arm On
#CPU0  //CPU Arm Off


DRAWER:

#OPD0  //ALL Drawer open
#OPD1 - #OPD4

#CLD0  //All Drawer close
#CLD1  - #CLD4

GADGETS:

---Fire---
#F0    //Fire Stop  TEST
#FOUT  //Move Out   TEST
#FIN   //Move In    TEST

---Spray---

#SP1   //Spray On
#SP0   //Spray Off

----ANIMATION----

#GAON   //Open Door lift Arm and move Gripp
:SE00   //reset that move

#FION   // Open Door Move Fire out
#FIOFF  // Move Fire In and close Door
//Check position Input for Status//

#SPRAY  // Move Spary ON and Off

#SAON   // Open Door Move Arm and play On/off with Motor

*/
