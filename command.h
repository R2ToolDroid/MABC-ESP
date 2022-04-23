#include <Arduino.h>    

void SendOutput(String dcmd) {   ///VIA SHD_PULS to MD Dome Board

    //delay(200);
   
    if (DEBUG_OUTPUT){
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

    if (cmd == "IR-ON") {
       EEPROM.write(C_IR, IR_ON);
       EEPROM.commit(); 
       IR = true;
       shwConfig(WR);
    } 
    if (cmd == "IR-OFF") {
       EEPROM.write(C_IR, IR_OFF);
       EEPROM.commit(); 
       IR = false;
       shwConfig(WR);
    } 

    if (cmd == "DM-0") {
       EEPROM.write(C_MOD, 0);
       EEPROM.commit();    
       shwConfig(WR);
    } 
    if (cmd == "DM-1") {
       EEPROM.write(C_MOD, 1);
       EEPROM.commit();    
       shwConfig(WR);
    } 
    if (cmd == "DM-2") {
       EEPROM.write(C_MOD, 2);
       EEPROM.commit();    
       shwConfig(WR);
    } 
    
    if (cmd == "DM-3") {
       EEPROM.write(C_MOD, 3);
       EEPROM.commit();    
       shwConfig(WR);
    } 

    if (cmd == "FUEL-ON") {
       EEPROM.write(C_FUEL, FUEL_ON);
       EEPROM.commit();    
       shwConfig(WR);
    } 

    if (cmd == "FUEL-OFF") {
       EEPROM.write(C_FUEL, FUEL_OFF);
       EEPROM.commit();    
       shwConfig(WR);
    } 

    if (cmd == "DISPL-OFF") {
       EEPROM.write(C_DISPL, DISPL_OFF);
       EEPROM.commit();    
       shwConfig(WR);
    } 

    if (cmd == "DISPL-ON") {
       EEPROM.write(C_DISPL, DISPL_ON);
       EEPROM.commit();    
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
      if (cmd == ":SE09"){RNDSound = false;myDFPlayer.playFolder(05,7);}//disco
      if (cmd == ":SE10"){myDFPlayer.playFolder(02,1);RNDSound = false;}
      if (cmd == ":SE11"){myDFPlayer.playFolder(01,14);RNDSound = true;}
      if (cmd == ":SE12"){myDFPlayer.playFolder(02,2);}
      if (cmd == ":SE13"){myDFPlayer.playFolder(02,4);RNDSound = true;}
      if (cmd == ":SE14"){myDFPlayer.playFolder(02,5);RNDSound = true;}
      if (cmd == ":SE15"){myDFPlayer.playFolder(04,1);}
      if (cmd == ":SE51"){myDFPlayer.playFolder(04,1);}
      if (cmd == ":SE55"){myDFPlayer.playFolder(05,4);}
      
      if (cmd == "$87"){RNDSound = false;myDFPlayer.playFolder(05,4);}  ///Musik
      if (cmd == "$5"){myDFPlayer.playFolder(02,3);}  //Whistle
      if (cmd == "$3"){myDFPlayer.playFolder(02,6);}  //Happy
      if (cmd == "NO"){myDFPlayer.playFolder(03,7);}  //NO
      if (cmd == "$2"){myDFPlayer.next();}  //Talk  
      if (cmd == "CROSS"){
        myDFPlayer.playFolder(04,countTrig3);
        countTrig3++;
        if (countTrig3 >= 15) countTrig3 = 2;
        
        }  //Talk Service 
      if (cmd == "#OF00"){myDFPlayer.playFolder(01,20);}   
      
      
        
  if (cmd == "debug") {
    
        
  
  Serial.println ( __FILE__ " " __DATE__ " " __TIME__);
  Serial.println (F( "# Master_Body_Controller ESP32  #"));
  Serial.println (F(  "Comandos von RC - CoinTaster - Wifi Modul werde verarbeitet"));
  Serial.println (F("INPUT:"));
  Serial.println (F("..... Nextion Display .............Serial 1 RX"));
  Serial.println (F("..... From WIFI....................Serial 2 RX"));
  Serial.println (F("OUTPUT:"));
  Serial.println (F("..... NEXTION Display an ..........Serial 1 TX"));
  Serial.println (F("..... To Dome Drive................Serial 2 TX"));
  Serial.println (F("...fuer DebugMode debug eingeben..."));
  Serial.println (F("...ende DebugMode debug off eingeben..."));
  Serial.println (F("...SERIAL is DEBUG 115200 - 9600 BAUD !!"));
  Serial.println (F("........................................"));
  Serial.println (F("DEBUG_STICK"));
  Serial.println (F("DEBUG_INPUT"));
  Serial.println (F("DEBUG_OUTPUT"));
  Serial.println (F("DEBUG_SOUND"));
  Serial.println (F("DEBUG_FUEL"));
  Serial.println (F("DEBUG_IR"));
  Serial.println (F("DEBUG_DRIVE"));
  Serial.println (F( "........................................"));
  Serial.print (F("DF Player Status"));
  Serial.print (F(" readState----"));
  Serial.println ( myDFPlayer.readState()); //read mp3 state
  Serial.print (F("readVolume--------------------"));
  Serial.println ( myDFPlayer.readVolume()); //read current volume
  Serial.print (F("...MODE = "));
  Serial.println (mode);
  Serial.print (F( "...PAGE = "));
  Serial.println ( PAGE);
  Serial.print (F( "...Stick Enable = "));
  Serial.println ( StickConnect);
  Serial.print (F("####Fuel Data A% = "));
  Serial.print( FuelA_P);
  Serial.print  (F(" Fuel A: "));
  Serial.println(FuelA);
  Serial.print  (F("####Fuel Data B% = "));
  Serial.print ( FuelB_P);
  Serial.print  (F(" Fuel B: "));
  Serial.println ( FuelB);
  Serial.print  (F("- Akku Status Stick : "));
  Serial.println ( STICK_AKKU_STAT );
  
    }

    if (cmd == "debug off") {
    
      
      DEBUG_OUTPUT = false;
      DEBUG_INPUT = false;
      DEBUG_SOUND = false;
      DEBUG_STICK = false;
      DEBUG_IR = false;
      DEBUG_FUEL = false;
      DEBUG_DRIVE = false;
    }

    if (cmd == "DEBUG_OUTPUT") { DEBUG_OUTPUT = true;}
    if (cmd == "DEBUG_INPUT") { DEBUG_INPUT = true;}
    if (cmd == "DEBUG_SOUND") { DEBUG_SOUND = true;}
    if (cmd == "DEBUG_STICK") { DEBUG_STICK = true;}
    if (cmd == "DEBUG_IR") { DEBUG_IR = true;}
    if (cmd == "DEBUG_FUEL") { DEBUG_FUEL = true;}
    if (cmd == "DEBUG_DRIVE") { DEBUG_DRIVE = true;}


    
#include "NEXT_COM.h" 
#include "COIN_COM.h"    

      if (cmd == "find") {
      //Serial2.print("find\r");
      SendOutput("find");
      }
      
    if (cmd == "DISDR") {
      
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
    
     //ESP.restart();
     mode = 3; ///Service
      
      //Serial2.print("mode3\r");           // hier geht es weiter zum  SHD_PULSE
      
      //delay(100);
      SendOutput("mode3");
      SendOutput(":SE10");
 
    }

    if (cmd == "hreset") {
    
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
    
      Serial2.print("mode1\r");       
      mode=1;
      
      ShwMode();
      SendOutput("@3M-Remote-1");
      SendOutput("@3t");
    }
  
    if (cmd == "mode2") {
    
      Serial2.print("mode2\r");       
      mode=2;
      ShwMode();

      SendOutput("@3M-Human-2");
      SendOutput("@3t");
    }
  
    if (cmd == "mode3") {
    
      Serial2.print("mode3\r");
      mode=3;
      ShwMode();
      SendOutput("@3M-Service-3");
      SendOutput("@3t");
    }
  
    if (cmd == "mode0") {
    
      //Serial2.print("mode0\r");
      SendOutput("mode0");
      mode=0;
      ShwMode();
      
      SendOutput("@3M-RND-0");
      SendOutput("@3t");
    }

    ///VOICE COMMANDS///
    if (cmd == "usb") {
    
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
    
      SendOutput("tool1");     
      delay(500);
      SendOutput(":OP04");
      
    }

    if (cmd == "tool2") {
    
      ///Action
      SendOutput("tool2");
      delay(500); 
      SendOutput(":OP05");
      
    }

    if (cmd == "tool3") {
    
      SendOutput("tool3");     
      delay(500);
      SendOutput(":OP06");
      
    }

    if (cmd == "tool4") {
    
      ///Action
      //Serial2.print("tool4\r");
      //mode=0;
      SendOutput("tool4");
    }

    if (cmd == "tool5") {
    
      ///Action
      //Serial2.print("tool5\r");
      //mode=0;
      SendOutput("tool5");
    }

    if (cmd == "tool6") {
    
      ///Action
      //Serial2.print("tool6\r");
      //mode=0;
      //SendOutput("tool7");
    }

    if (cmd == "tool7") {
    
      
    }
    
    if (cmd == "tool8") {
    
      ///Action
      //Serial2.print("tool7\r");
      //mode=0;
      
    }
    if (cmd == "tool9") {
    
      ///Action
      //Serial2.print("tool7\r");
      //mode=0;
      
    }
    if (cmd == "tool10") {
    
      ///Action
      //Serial2.print("tool7\r");
      //mode=0;
      
    }
    
    

    /// Filtern ob Dome Komando oder nicht ///
    
    if (cmd.startsWith(":")) {
      
      SendOutput(cmd);
     
    }

    if (cmd.startsWith("@")) {
      
      SendOutput(cmd);
     
    }

    if (cmd.startsWith("#")) {   
     
      SendOutput(cmd);
      
    }
    

    if (cmd.startsWith("$")) {
     
      

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
      
     SendOutput(cmd);
    }

    if (cmd.startsWith("@")) 
    {
      
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
