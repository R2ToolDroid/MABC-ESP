#include <Arduino.h>    

void SendOutput(String dcmd) {   ///VIA SHD_PULS to MD Dome Board

    //delay(200);
   
    if (DEBUG_COM){
      S_DEBUG_COM += dcmd;
      S_DEBUG_COM += "\n";
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

    //Serial.print("myvol= ");
    //Serial.println(vol);
    
   
   tmp_cmd = cmd;
    //CONFIG
    if (cmd == "CONFIG"){     
        CONFIG = true; 
        shwConfig(RE);
    }
    if (cmd == "OTA-OFF") {
      EEPROM.write(C_WEB, OTA_OFF);
      EEPROM.commit();  
      web = false;
      shwConfig(WR);
    }
    if (cmd == "OTA-ON") {
       EEPROM.write(C_WEB, OTA_ON);
       EEPROM.commit(); 
       web = true;
       shwConfig(WR);
    }
    
   
   
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
    DEBUG_COM = true;
      if (DEBUG_COM){
          S_DEBUG_COM += "#Comando - debug#\n";
          S_DEBUG_COM += cmd;
          S_DEBUG_COM += "\n";
       }
       
  
  S_DEBUG_COM += __FILE__ " " __DATE__ " " __TIME__;
  S_DEBUG_COM += "\n##### Master_Body_Controller ESP32  #####";
  S_DEBUG_COM += "\nComandos von RC - CoinTaster - Wfif Modul werde verarbeitet";
  S_DEBUG_COM += "\nINPUT:";
  S_DEBUG_COM += "\n..... Nextion Display .............Serial 1 RX";
  S_DEBUG_COM += "\n..... From WIFI....................Serial 2 RX";
  S_DEBUG_COM += "\n";
  S_DEBUG_COM += "\nOUTPUT:";
  S_DEBUG_COM += "\n..... NEXTION Display an ..........Serial 1 TX";
  S_DEBUG_COM += "\n..... To Dome Drive................Serial 2 TX";
  S_DEBUG_COM += "\n";
  S_DEBUG_COM += "\n...fuer DebugMode debug eingeben...";
  S_DEBUG_COM += "\n...ende DebugMode debug off eingeben...";
  S_DEBUG_COM += "\n...SERIAL is DEBUG 115200 - 9600 BAUD !!";
  S_DEBUG_COM += "\n........................................";
  S_DEBUG_COM += "\nDEBUG_COM";
  S_DEBUG_COM += "\nDEBUG_STICK";
  S_DEBUG_COM += "\nDEBUG_INPUT";
  S_DEBUG_COM += "\nDEBUG_OUTPUT";
  S_DEBUG_COM += "\nDEBUG_SOUND";
  S_DEBUG_COM += "\n........................................";
  S_DEBUG_COM += "\nDF Player Status";
  S_DEBUG_COM += "\nreadState--------------------";
  S_DEBUG_COM += myDFPlayer.readState(); //read mp3 state
  S_DEBUG_COM += "\nreadVolume--------------------";
  S_DEBUG_COM += myDFPlayer.readVolume(); //read current volume
  S_DEBUG_COM += "\n...MODE = ";
  S_DEBUG_COM += mode;
  S_DEBUG_COM += "\n...PAGE = ";
  S_DEBUG_COM += PAGE;
  S_DEBUG_COM += "\n...Stick Enable = ";
  S_DEBUG_COM += StickConnect;
  S_DEBUG_COM += "\n####Fuel Data A% = ";
  S_DEBUG_COM += FuelA_P;
  S_DEBUG_COM += "\n Fuel A: ";
  S_DEBUG_COM += FuelA;
  S_DEBUG_COM += "\n####Fuel Data B% = ";
  S_DEBUG_COM += FuelB_P;
  S_DEBUG_COM += "\n Fuel B: ";
  S_DEBUG_COM += FuelB;
  S_DEBUG_COM += "\n- Akku Status Stick : ";
  S_DEBUG_COM += STICK_AKKU_STAT;
  S_DEBUG_COM += "\n";
    }

    if (cmd == "debug off") {
    if (DEBUG_COM){
         S_DEBUG_COM +=  "#Comando - debug off#";
         S_DEBUG_COM += cmd;
         S_DEBUG_COM += "\n";
       }
      DEBUG_COM = false;
      DEBUG_OUTPUT = false;
      DEBUG_INPUT = false;
      DEBUG_SOUND = false;
      DEBUG_STICK = false;
    }

    if (cmd == "DEBUG_OUTPUT") { DEBUG_OUTPUT = true;}
    if (cmd == "DEBUG_INPUT") { DEBUG_INPUT = true;}
    if (cmd == "DEBUG_SOUND") { DEBUG_SOUND = true;}
    if (cmd == "DEBUG_STICK") { DEBUG_STICK = true;}
    if (cmd == "DEBUG_IR") { DEBUG_IR = true;}



    
#include "NEXT_COM.h" 
#include "COIN_COM.h"    

      if (cmd == "find") {
      //Serial2.print("find\r");
      SendOutput("find");
      }
      
    if (cmd == "DISDR") {
      if (DEBUG_COM){
      S_DEBUG_COM += "disconnect..."; 
      S_DEBUG_COM += "\n";   
      }
       Ps3.end();
       StickConnect = false;
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
    if (DEBUG_COM){
        S_DEBUG_COM += "# Comando reset #";
        //S_DEBUG_COM += cmd;
        S_DEBUG_COM += "\n";   
      }
     //ESP.restart();
     mode = 3; ///Service
      
      //Serial2.print("mode3\r");           // hier geht es weiter zum  SHD_PULSE
      
      //delay(100);
      SendOutput("mode3");
      SendOutput(":SE10");
 
    }

    if (cmd == "hreset") {
    if (DEBUG_COM){
        S_DEBUG_COM += "# Comando hreset #";
        //S_DEBUG_COM += cmd;
        S_DEBUG_COM += "\n"; 
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
    if (DEBUG_COM){
         S_DEBUG_COM += "#Comando - mode1#";
        // S_DEBUG_COM += cmd;
         S_DEBUG_COM += "\n";
       }
      Serial2.print("mode1\r");       
      mode=1;
      
      ShwMode();
    }
  
    if (cmd == "mode2") {
    if (DEBUG_COM){
         S_DEBUG_COM += "#Comando - mode2#";
        // S_DEBUG_COM += cmd;
         S_DEBUG_COM += "\n";
       }
      Serial2.print("mode2\r");       
      mode=2;
      ShwMode();
    }
  
    if (cmd == "mode3") {
    if (DEBUG_COM){
         S_DEBUG_COM += "#Comando - mode3#";
        // S_DEBUG_COM += cmd;
         S_DEBUG_COM += "\n";
       }
      Serial2.print("mode3\r");
      mode=3;
      ShwMode();
    }
  
    if (cmd == "mode0") {
    if (DEBUG_COM){
         S_DEBUG_COM += "#Comando - mode0#";
         S_DEBUG_COM += cmd;
         S_DEBUG_COM += "\n";
       }
      //Serial2.print("mode0\r");
      SendOutput("mode0");
      mode=0;
      ShwMode();
    }

    ///VOICE COMMANDS///
    if (cmd == "usb") {
    if (DEBUG_COM){
         S_DEBUG_COM += "#Comando - tool0 (usb)#";
         S_DEBUG_COM += cmd;
         S_DEBUG_COM += "\n";
       }
      ///Action
      
      SendOutput("usb");
      delay(500);
      SendOutput(":OP03");
      //mode=0;
      //mode=3;
      //DomeTurnPos = true;
     // TargetPos = 400;
    }

    if (cmd == "tool1") {
    if (DEBUG_COM){
         S_DEBUG_COM += "#Comando - tool1#";
         S_DEBUG_COM += cmd;
         S_DEBUG_COM += "\n";
       }
      SendOutput("tool1");     
      delay(500);
      SendOutput(":OP04");
      
    }

    if (cmd == "tool2") {
    if (DEBUG_COM){
         S_DEBUG_COM += "######Comando - tool2######";
         S_DEBUG_COM += cmd;
         S_DEBUG_COM += "\n";
       }
      ///Action
      SendOutput("tool2");
      delay(500); 
      SendOutput(":OP05");
      
    }

    if (cmd == "tool3") {
    if (DEBUG_COM){
         S_DEBUG_COM += "######Comando - tool3######";
         S_DEBUG_COM += cmd;
         S_DEBUG_COM += "\n";
       }
      SendOutput("tool3");     
      delay(500);
      SendOutput(":OP06");
      
    }

    if (cmd == "tool4") {
    if (DEBUG_COM){
         S_DEBUG_COM += "######Comando - tool4######";
         S_DEBUG_COM += cmd;
         S_DEBUG_COM += "\n";
       }
      ///Action
      //Serial2.print("tool4\r");
      //mode=0;
      SendOutput("tool4");
    }

    if (cmd == "tool5") {
    if (DEBUG_COM){
         S_DEBUG_COM += "######Comando - tool5######";
         S_DEBUG_COM += cmd;
         S_DEBUG_COM += "\n";
       }
      ///Action
      //Serial2.print("tool5\r");
      //mode=0;
      SendOutput("tool5");
    }

    if (cmd == "tool6") {
    if (DEBUG_COM){
         S_DEBUG_COM += "######Comando - tool6######";
         S_DEBUG_COM += cmd;
         S_DEBUG_COM += "\n";
       }
      ///Action
      //Serial2.print("tool6\r");
      //mode=0;
      //SendOutput("tool7");
    }

    if (cmd == "tool7") {
    if (DEBUG_COM){
         S_DEBUG_COM += "######Comando - tool7######";
         S_DEBUG_COM += cmd;
         S_DEBUG_COM += "\n";
       }
      ///Action
      //Serial2.print("tool7\r");
      //mode=0;
      
    }
    
    if (cmd == "tool8") {
    if (DEBUG_COM){
         S_DEBUG_COM += "######Comando - tool8######";
         S_DEBUG_COM += cmd;
         S_DEBUG_COM += "\n";
       }
      ///Action
      //Serial2.print("tool7\r");
      //mode=0;
      
    }
    if (cmd == "tool9") {
    if (DEBUG_COM){
         S_DEBUG_COM += "######Comando - tool9######";
         S_DEBUG_COM += cmd;
         S_DEBUG_COM += "\n";
       }
      ///Action
      //Serial2.print("tool7\r");
      //mode=0;
      
    }
    if (cmd == "tool10") {
    if (DEBUG_COM){
         S_DEBUG_COM += "######Comando - tool10######";
         S_DEBUG_COM += cmd;
         S_DEBUG_COM += "\n";
       }
      ///Action
      //Serial2.print("tool7\r");
      //mode=0;
      
    }
    
    

    /// Filtern ob Dome Komando oder nicht ///
    
    if (cmd.startsWith(":")) {
      if (DEBUG_COM){
        S_DEBUG_COM += "######Comando Pefix : DOME ######";
        S_DEBUG_COM += cmd;
        S_DEBUG_COM += "\n";
      }
      SendOutput(cmd);
     
    }

    if (cmd.startsWith("@")) {
      if (DEBUG_COM){
        S_DEBUG_COM += "######Comando Pefix : DOME ######";
        S_DEBUG_COM += cmd;
        S_DEBUG_COM += "\n";
      }
      SendOutput(cmd);
     
    }

    if (cmd.startsWith("#")) {
      if (DEBUG_COM){
        S_DEBUG_COM += "######Comando Prefix # BODY ######";
        S_DEBUG_COM += cmd;
        S_DEBUG_COM += "\n";
      }
     
      SendOutput(cmd);
    }
    

    if (cmd.startsWith("$")) {
     
      if (DEBUG_COM){
        S_DEBUG_COM += "######Comando Prefix $ SOUND######";
        S_DEBUG_COM += cmd;
        S_DEBUG_COM += "\n";
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

        vol = 10;
        myDFPlayer.volume(10);
        
      }
      if (cmd == "$f") {
        vol = -80;
        myDFPlayer.volume(20);
        
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
      if (DEBUG_COM){
        S_DEBUG_COM += "######Comando Prefix * HOLO ######";
        S_DEBUG_COM += cmd;
        S_DEBUG_COM += "\n";
      }
     SendOutput(cmd);
    }

    if (cmd.startsWith("@")) 
    {
      if (DEBUG_COM){
        S_DEBUG_COM += "######Comando Prefix @ Display ######";
        S_DEBUG_COM += cmd;
        S_DEBUG_COM += "\n";
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
