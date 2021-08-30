/*  
  #########################################################################
  ######  Automatische Bewegung und Controller Koordination          ######
  ######       Doc Snyder Tool Droid Master_Body_Controller          ######
  #########################################################################

  #### Coin Button as Telemetric Input now
  #### A0 Power A
  #### A1 Power B
*/

/*  WEBSERVER CONFIG */



#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>
#include <ESP32_Servo.h>
#include <Ps3Controller.h>
#include <SoftwareSerial.h>
#include <Wire.h> 
#include "DFRobotDFPlayerMini.h"

const char* host = "R2-esp32";

const char* ssid = "Webmex-Safe-02";
const char* password = "tronic307";

//const char* ssid = "R2_Router";
//const char* password = "tronic307";

//APP
const char* ssid2 = "R2-ESP32-MABAC"; //name of the wifi-network created by the ESP32
const char* pass2 = "tronic307"; //replace with a more secure password!

WebServer server(80);

//APP
WiFiServer server2(9750);
bool connected = false;
WiFiClient client;

#include "index_page.h"
#include "login_page.h"

DFRobotDFPlayerMini myDFPlayer;

SoftwareSerial mp3; // RX, TX

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
#include "app.h"


void setup(void) {

  randomSeed(analogRead(0));  //Random ??
  
  pinMode(FUEL_CELL_B, INPUT_PULLUP);
  Serial.begin(115200); 
  
  CheckCellCon(); /// Check if we start with WIFI OTA

  if (web == true){ 
  /*** WEBSERVER START ***/
  // Connect to WiFi network
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  /*use mdns for host name resolution*/
  if (!MDNS.begin(host)) { //http://R2-esp32.local
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");
  
  /*return index page which is stored in serverIndex*/
  server.on("/", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", loginIndex);
  });

  server.on("/ON", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", serverIndex);
    Serial.println("get a ON from Web");
    
  });

  
  server.on("/serverIndex", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", serverIndex);
  });
  /*handling uploading firmware file */
  server.on("/update", HTTP_POST, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    ESP.restart();
  }, []() {
    HTTPUpload& upload = server.upload();
    if (upload.status == UPLOAD_FILE_START) {
      Serial.printf("Update: %s\n", upload.filename.c_str());
      if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { //start with max available size
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      /* flashing firmware to ESP */
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_END) {
      if (Update.end(true)) { //true to set the size to the current progress
        Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
       
      } else {
        Update.printError(Serial);
      }
    }
  });
  server.begin();
  
  }  else {          // edif web true
  
      //Start App Server
  /*** APP SERVER **/
  WiFi.softAP(ssid2, pass2);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("APP-Server IP address: ");
  Serial.println(IP);
  server2.begin();
/*APP SERVER END*/
  
  
  }

 
  
  /*** WEBSERVER END ***/
 Serial1.begin(9600,SERIAL_8N1,18,19); // Serial 19 RX  18 TX NEXTION (COM1)  TESTBOARD 19,18
 Serial2.begin(9600,SERIAL_8N1,27,23); // Serial 27 RX  23 TX Outpull All Input Command
 //I2C   21 SDA     22 SDC for PCB Board
 mp3.begin(9600, SWSERIAL_8N1, 25, 26, false, 256);  // speed, type, RX, TX

  if (!myDFPlayer.begin(mp3, true, false)) {  //Use softwareSerial to communicate with mp3.
    
    Serial.println(myDFPlayer.readType(),HEX);
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    //while(true);
    delay(3000);
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms 
  //----Set volume----
  myDFPlayer.volume(10);  //Set volume value (0~30).
  myDFPlayer.volumeUp(); //Volume Up
  myDFPlayer.volumeDown(); //Volume Down
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
  int delayms=100;  ///delay OEM 100
  //----Mp3 play----
  //----Read imformation----
  S_DEBUG_OUTPUT = "readState--------------------";
  S_DEBUG_OUTPUT += "\n";
  S_DEBUG_OUTPUT += myDFPlayer.readState(); //read mp3 state
  S_DEBUG_OUTPUT += "\n";
  S_DEBUG_OUTPUT += "readVolume--------------------";
  S_DEBUG_OUTPUT += "\n";
  S_DEBUG_OUTPUT += myDFPlayer.readVolume(); //read current volume
  S_DEBUG_OUTPUT += "\n";
  S_DEBUG_OUTPUT += "readEQ--------------------";
  S_DEBUG_OUTPUT += "\n";
  S_DEBUG_OUTPUT += myDFPlayer.readEQ(); //read EQ setting
  S_DEBUG_OUTPUT += "\n";
  S_DEBUG_OUTPUT += "readFileCounts--------------------";
  S_DEBUG_OUTPUT += "\n";
  S_DEBUG_OUTPUT += myDFPlayer.readFileCounts(); //read all file counts in SD card
  S_DEBUG_OUTPUT += "\n";
  S_DEBUG_OUTPUT += "readCurrentFileNumber--------------------";
  S_DEBUG_OUTPUT += "\n";
  S_DEBUG_OUTPUT += myDFPlayer.readCurrentFileNumber(); //read current play file number
  S_DEBUG_OUTPUT += "\n";
  
  S_DEBUG_OUTPUT += "readFileCountsInFolder--------------------";
  S_DEBUG_OUTPUT += "\n";
  S_DEBUG_OUTPUT += myDFPlayer.readFileCountsInFolder(3); //read fill counts in folder SD:/03";
  S_DEBUG_OUTPUT += "\n";
  S_DEBUG_OUTPUT += "---Wait---";
  S_DEBUG_OUTPUT += "\n";
  
  maxFilesinFolder = myDFPlayer.readFileCountsInFolder(1);

  delay(8000);

  //Serial.println(F("myDFPlayer.play(1)"));
  if (web == false){
  myDFPlayer.play(1);  //Play the first mp3 
  } else {
    myDFPlayer.play(2);  //Play 
  }
  
  delay(3000);

  Ps3.attach(notify);
  Ps3.attachOnConnect(onConnect);
    //Ps3.begin("01:02:03:04:05:06");
  Ps3.begin("01:1a:7d:da:71:12"); ///#645
  

  //pinMode(FUEL_CELL_A, INPUT_PULLUP);
  //pinMode(FUEL_CELL_B, INPUT_PULLUP);

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

   Wire.begin();
    
  Serial.println("R2...Ready");
  
  SendOutput("mode0");

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
        if (DEBUG_INPUT){
            S_DEBUG_INPUT += "I received from COM Serial: \n";
            S_DEBUG_INPUT += data;
            S_DEBUG_INPUT += "\n";
        }
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
         
          if (DEBUG_INPUT){
              S_DEBUG_INPUT += "I received from COM1 NEXTION: \n";
              S_DEBUG_INPUT += data;
              S_DEBUG_INPUT += "\n";
          }
         
          parseCommand(data);
          data = "";
         Serial1.flush();
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
           if (DEBUG_INPUT){
              S_DEBUG_INPUT += "I received from COM2 COIN/WIFI: \n";
              S_DEBUG_INPUT += data;
              S_DEBUG_INPUT += "\n";
          }        
        parseCommand(data);
        data = "";
        Serial2.flush();
        }// end data
    } // end serial
     
}

///COM3


void loop() {

  if ( mode == 2 ){
   IRSensor();
  }

  if (web == false){
     App();
  } else {
    server.handleClient();
  }
 
   //Serial.println(analogRead(FUEL_CELL_B));
  
  
  //CheckIR(5000);
  if (RNDSound){
    randomSound(5000,20000,maxFilesinFolder);
    //randomSound(int minINT, int maxINT, int maxFiles)
  }
  
  if(Ps3.isConnected()){
    StickConnect = 1;
    
  } else {
    StickConnect = 0;
    
  }
 
  if (PAGE == 0) {
    NextUpdate(40);
    }
  if (PAGE == 2) { 
    //Rsetup(40);}
  }

  readNextion();
  readWifi();
  readCom(); 
  
  if(DEBUG_COM){
  Serial.print(S_DEBUG_COM);
  S_DEBUG_COM = "";
  }
  if(DEBUG_INPUT){
  Serial.print(S_DEBUG_INPUT);
  S_DEBUG_INPUT = "";
  }
  if(DEBUG_STICK){
  Serial.print(S_DEBUG_STICK);
  S_DEBUG_STICK = "";
  }
  if(DEBUG_OUTPUT){
  Serial.print(S_DEBUG_OUTPUT);
  S_DEBUG_OUTPUT = "";
  }
  
  
 
  
}





   
