
/*  
  #########################################################################
  ######  Automatische Bewegung und Controller Koordination          ######
  ######       Doc Snyder Tool Droid Master_Body_Controller          ######
  #########################################################################

  #### Coin Button as Telemetric Input now
  #### A0 Power A
  #### A1 Power B

  ####Select ESP32 Wrover Module with minimal SPiFFS
*/

/*  WEBSERVER CONFIG */



#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>
#include <EEPROM.h>  
#include <ESP32_Servo.h>
#include <Ps3Controller.h>
#include <SoftwareSerial.h>
#include <Wire.h> 
#include <LSS.h>
#include "DFRobotDFPlayerMini.h"
#include "esp_adc_cal.h"

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char* host = "R2-esp32";

//const char* ssid = "Webmex-Safe-02";
//const char* password = "tronic307";

const char* ssid = "R2_Router";
const char* password = "tronic307";

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
SoftwareSerial L_SERIAL; // Port 5

Servo DomeRot;
Servo DriveSpeed;
Servo DriveDir;
Servo GrippRoll;
//Servo GrippLift;

#define LSS_ID (0)
#define LSS_BAUD (LSS_DefaultBaud)
#define LSS_SERIAL (L_SERIAL)

LSS myLSS = LSS(0);

#include "vars.h"
#include "minidispl.h"
#include "functions.h"
#include "command.h"
#include "stick.h"
#include "IRinput.h"
#include "app.h"

void setup(void) {

  randomSeed(analogRead(0));  //Random ??

  EEPROM.begin(2048);
 
  Serial.begin(115200);  
  
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  
  loadDefault();

  if (web == true){ 
  /*** WEBSERVER START ***/
  // Connect to WiFi network
  WiFi.begin(ssid, password);
  Serial.println(F(""));
  
int wlwait = 0;

  // Wait for connection
  if ((WiFi.status() != WL_CONNECTED)||(wlwait <=5)) {
    delay(500);
    Serial.print(F("."));
    wlwait++;
  }

  
  Serial.println (F(""));
  Serial.print (F("Connected to "));
  Serial.println(ssid);
  Serial.print(F("IP address: "));
  
  Serial.println(WiFi.localIP());
  IPADRESS = WiFi.localIP().toString(); 
  
  
  /*use mdns for host name resolution*/
  if (!MDNS.begin(host)) { //http://R2-esp32.local
    Serial.println(F("Error setting up MDNS responder!"));
    while (1) {
      delay(1000);
    }
  }
  Serial.println(F("mDNS responder started"));
  
  /*return index page which is stored in serverIndex*/
  server.on("/", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", loginIndex);
  });

  server.on("/ON", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", serverIndex);
    Serial.println(F("get a ON from Web"));
    
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
  Serial.print(F("APP-Server IP address: "));
  Serial.println(IP);
  IPADRESS = IP.toString(); 
  server2.begin();
/*APP SERVER END*/
 
  
  }

 Wire.begin();
   
  
  /*** WEBSERVER END ***/
 Serial1.begin(9600,SERIAL_8N1,18,19); // Serial 19 RX  18 TX NEXTION (COM1)  TESTBOARD 19,18
 Serial2.begin(9600,SERIAL_8N1,27,23); // Serial 27 RX  23 TX Outpull All Input Command
 //I2C   21 SDA     22 SDC for PCB Board
 mp3.begin(9600, SWSERIAL_8N1, 25, 26, false, 256);  // speed, type, RX, TX
 L_SERIAL.begin(9600, SWSERIAL_8N1, 7, 5, false, 256);

 LSS::initBus(LSS_SERIAL, LSS_BAUD);

 

  if (!myDFPlayer.begin(mp3, true, false)) {  //Use softwareSerial to communicate with mp3.
    
    Serial.println(myDFPlayer.readType(),HEX);
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    //while(true);
    delay(3000);
  }
  Serial.println(F("DFPlayer Mini online."));
  //showinfo("Soundmodul online.");
  
  
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
  if (DEBUG_SOUND){
  Serial.println( F("readState--------------------"));
  Serial.println( myDFPlayer.readState()); //read mp3 state
  Serial.println( F("readVolume--------------------"));
  Serial.println( myDFPlayer.readVolume()); //read current volume
  Serial.println( F("readEQ--------------------"));
  Serial.println( myDFPlayer.readEQ()); //read EQ setting
  Serial.println( F ("readFileCounts--------------------"));
  Serial.println( myDFPlayer.readFileCounts()); //read all file counts in SD card
  Serial.println( F("readCurrentFileNumber--------------------"));
  Serial.println( myDFPlayer.readCurrentFileNumber()); //read current play file number
  Serial.println( F("readFileCountsInFolder--------------------"));
  Serial.println( myDFPlayer.readFileCountsInFolder(3)); //read fill counts in folder SD:/03";
  Serial.println( F("---Wait---"));
  
  } // End Debug
  maxFilesinFolder = myDFPlayer.readFileCountsInFolder(1);

  OLED_Start();
 
  if (web == false){
    myDFPlayer.play(1);  //Play the first mp3 
  } else {
    myDFPlayer.play(2);  //Play 
  }

  myLSS.move(liftPos);

  /*
  delay(1000);
  myLSS.moveT(600,2000);
  delay(3000);
  myLSS.moveT(-500,2000);
  //myLSS.move(1800);
  */
  delay(2000);

  //myLSS.move(-1800);

  Ps3.attach(notify);
  Ps3.attachOnConnect(onConnect);
    //Ps3.begin("01:02:03:04:05:06");
  Ps3.begin("01:1a:7d:da:71:12"); ///#645
 
  pinMode(IR_SENSOR, INPUT_PULLUP);

  /* Setup Servos and Motors */
  
  DomeRot.attach(DOME_ROT);
  DriveSpeed.attach(DRIVE_SPEED);
  DriveDir.attach(DRIVE_DIR);
  GrippRoll.attach(GRIP_ROLL);
  

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
    
  Serial.println(F("R2...Ready"));
   
  SendOutput("mode0");

  ///Nextion Start
  Serial1.print(F("page start"));
  NextEnd();
  
  Serial1.print(F("t0.txt=\""));
  Serial1.print(F("...START !"));
  Serial1.print(F(" _\""));
  NextEnd();  

  ShwMode();

  liftPos = 0;   

  
  
}


////MAIN SERIAL READ
void readCom(){
  if(Serial.available() > 0)
    {
        data = Serial.readStringUntil('\n');
        if (DEBUG_INPUT){
            Serial.println (F( "I received from COM Serial: "));
            Serial.print(data);
           
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
              Serial.println (F( "I received from COM1 NEXTION: "));
              Serial.print(data);
             
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
              Serial.println(F("I received from COM2 COIN/WIFI: "));
              Serial.print(data);
              
          }        
        parseCommand(data);
        data = "";
        Serial2.flush();
        }// end data
    } // end serial
     
}

///COM3


void loop() {

  if(FUEL) FuelB = readFuel(FUEL_CELL_B);
  
  
  if ( mode == 2 ){
    
   if (IR) IRSensor();
   
  }

  
  if (mode == 3 ){  
    ArmMove(GRIP_LIFT_STATUS);  
  }
  
  if (web == false){
     App();
  } else {
    server.handleClient();
  }
 
  
  if (RNDSound){
    randomSound(5000,20000,maxFilesinFolder);
    //randomSound(int minINT, int maxINT, int maxFiles)
  }
  
  if(Ps3.isConnected()){
    StickConnect = true;
    
  } else {
    StickConnect = false;
    
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

  if (DISP){ 
  OLED_status(web,IPADRESS,tmp_cmd,mode,StickConnect, STICK_AKKU_STAT, vol, FuelB);
  }
  
  if (next){
     myDFPlayer.next();
     next=false;
  }

  if (STcmd != ""){
    parseCommand(STcmd);
    STcmd = "";
  }

  
}





   
