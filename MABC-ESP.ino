/*  
  #########################################################################
  ######  Automatische Bewegung und Controller Koordination          ######
  ######       Doc Snyder Tool Droid Master_Body_Controller          ######
  #########################################################################

  #### Coin Button as Telemetric Input now
  #### A0 Power A
  #### A1 Power B
  
*/

#include <ESP32_Servo.h>
#include <Ps3Controller.h>
//#include <SoftwareSerial.h>
//#include "DFRobotDFPlayerMini.h"

//DFRobotDFPlayerMini myDFPlayer;

//SoftwareSerial mp3; // RX, TX

Servo DomeRot;
Servo DriveSpeed;
Servo DriveDir;
Servo GrippRoll;
Servo GrippLift;


#include "vars.h"
#include "functions.h"
#include "command.h"
#include "stick.h"
//#include "IRinput.h"

void setup(void) {
/*
  mp3.begin(9600, SWSERIAL_8N1, 25, 26, false, 256);  // speed, type, RX, TX
  
  if (!myDFPlayer.begin(mp3)) {  //Use softwareSerial to communicate with mp3.
    
    Serial.println(myDFPlayer.readType(),HEX);
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms
  
  //----Set volume----
  myDFPlayer.volume(10);  //Set volume value (0~30).
  myDFPlayer.volumeUp(); //Volume Up
  myDFPlayer.volumeDown(); //Volume Down
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
  int delayms=100;
  //----Mp3 play----
  //----Read imformation----
  Serial.println(F("readState--------------------"));
  Serial.println(myDFPlayer.readState()); //read mp3 state
  Serial.println(F("readVolume--------------------"));
  Serial.println(myDFPlayer.readVolume()); //read current volume
  //Serial.println(F("readEQ--------------------"));
  //Serial.println(myDFPlayer.readEQ()); //read EQ setting
  Serial.println(F("readFileCounts--------------------"));
  Serial.println(myDFPlayer.readFileCounts()); //read all file counts in SD card
  Serial.println(F("readCurrentFileNumber--------------------"));
  Serial.println(myDFPlayer.readCurrentFileNumber()); //read current play file number
  Serial.println(F("readFileCountsInFolder--------------------"));
  Serial.println(myDFPlayer.readFileCountsInFolder(3)); //read fill counts in folder SD:/03
  Serial.println(F("--------------------"));

  Serial.println(F("myDFPlayer.play(1)"));
  
  myDFPlayer.play(1);  //Play the first mp3

*/

  Ps3.attach(notify);
  Ps3.attachOnConnect(onConnect);
    //Ps3.begin("01:02:03:04:05:06");
  Ps3.begin("01:1a:7d:da:71:12"); ///#645
  

  //pinMode(FUEL_CELL_A, INPUT_PULLUP);
  pinMode(FUEL_CELL_B, INPUT_PULLUP);

  pinMode(IR_SENSOR, INPUT_PULLUP);

  /*
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
  Serial.println("...MODE = ");
  Serial.println(mode);

  SERIAL is DEBUG 115200 BAUD !!
  */
  
  Serial.begin(115200);
  Serial1.begin(9600,SERIAL_8N1,19,18); // Serial 19 RX  18 TX NEXTION (COM1)
  Serial2.begin(9600,SERIAL_8N1,22,23); // Serial 22 RX  23 TX Outpull All Input Command
  
  /* Setup Servos and Motors */
  //myservo.attach(servoPin);
  DomeRot.attach(DOME_ROT);
  DriveSpeed.attach(DRIVE_SPEED);
  DriveDir.attach(DRIVE_DIR);
  GrippRoll.attach(GRIP_ROLL);
  GrippLift.attach(GRIP_LIFT);

  DomeRot.write(90);
  DriveSpeed.write(90);
  DriveDir.write(90);

  pinMode(GRIP_MOTA1, OUTPUT);
  pinMode(GRIP_MOTA2, OUTPUT);

  pinMode(GRIP_MOTB1, OUTPUT);
  pinMode(GRIP_MOTB2, OUTPUT);
  
  digitalWrite(GRIP_MOTA1, LOW); //L298 0 0 is Stop
  digitalWrite(GRIP_MOTA2, LOW); //L298 0 0 is Stop
  digitalWrite(GRIP_MOTB1, LOW); //L298 0 0 is Stop
  digitalWrite(GRIP_MOTB2, LOW); //L298 0 0 is Stop

  Serial.println("R2...Ready");
  

  ///Nextion Start
  Serial1.print("page start");
  NextEnd();
  
  Serial1.print("t0.txt=\"");
  Serial1.print("...START !");
  Serial1.print(" _\"");
  NextEnd();  

  ShwMode();

     
}






////MAIN SERIAL READ
void readCom(){
  if(Serial.available() > 0)
    {
        data = Serial.readStringUntil('\n');
        parseCommand(data);
        data = "";
        Serial.flush();
    } // end serial
}

////serialEvent1() NEXTION SERIAL1 READ


void readNextion(){
  if(Serial1.available() > 0 )
    {      
      data = Serial1.readStringUntil('\r');      
      if (data != "") {
        if (debug){
           // say what you got:
          Serial.print("I received from COM1: ");
          Serial.println(data);
        }
          parseCommand(data);
          data = "";
         //Serial1.flush();
      } // end data
    } // end Serial
}


///COM2 SERIAL2 WIFI READ
void readWifi(){

  if(Serial2.available() > 0)
    {
        //data = Serial2.readStringUntil('\r');

        data = Serial2.readStringUntil('\n');

        if (data != "") {
        if (debug){
           // say what you got:
          Serial.print("I received from COM2 COIN/WIFI: ");
          Serial.println(data);
        }
        //Serial2.print("OK\n");
        parseCommand(data);
        data = "";
        //Serial2.flush();
        }// end data
    } // end serial
     
}

///COM3


void loop() {
  
  //CheckIR(5000);
  
  if(Ps3.isConnected()){
    StickConnect = 1;
    
  } else {
    StickConnect = 0;
    
  }
      
  
 
 // displayFuel();

  if (PAGE == 0) {
    NextUpdate(40);
    }
  if (PAGE == 2) { 
    //Rsetup(40);}
  }

  readNextion();
  readWifi();
  readCom(); 
  printOutput(); 
 
  
}





   
