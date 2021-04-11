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

Servo DomeRot;
Servo DriveSpeed;
Servo DriveDir;
Servo GrippRoll;
Servo GrippLift;


#include "vars.h"
#include "functions.h"
#include "command.h"
#include "stick.h"
#include "IRinput.h"

void setup(void) {

  Ps3.attach(notify);
  Ps3.attachOnConnect(onConnect);
    //Ps3.begin("01:02:03:04:05:06");
  Ps3.begin("01:1a:7d:da:71:12");

  pinMode(FUEL_CELL_A, INPUT_PULLUP);
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


  Serial.println("R2...Ready");
  

  ///Nextion Start
  Serial1.print("page start");
  NextEnd();
  Serial1.print("t0.txt=\"");
  Serial1.print("...Connected");
  Serial1.print(" _\"");
  NextEnd();  

     
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
  
  CheckIR(5000);
  if(Ps3.isConnected()){

    
    
  }
       
  
 
 // displayFuel();

  if (PAGE == 0) {NextUpdate(40);
   
    }
  if (PAGE == 2) { //Rsetup(40);
  }

  readNextion();
  readWifi();
  readCom(); 
   
 
  
}





   
