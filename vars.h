#include <Arduino.h>                           

//// No Delay option
// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;      

unsigned long previousMillis1 = 0;    

byte State;
int wait = 0;
int battery = 0;

// constants won't change :
const long interval = 5000;           // interval at which to blink (milliseconds)
const long interval1 = 5000;           // interval at which to blink (milliseconds)

int durch = 1;

String cmd; //Consolen Input
byte debug; //Debug function
String data; //Serial Data
String inm = "COIN"; //Inputmode String
String calldata; //String Datarequest
String calldatabuff;

int mode = 0; // Default Mode  0 = Random
              // RC Mode       1 = RC Control
              // RC Show       2 = Human
              // RC Show       3 = Service

int INmode = 0; /// 0 == Input auf Coin und Nextion
                /// 1 == Input auf  Stick and Nextion

float PowerA = 0;
float PowerB = 0;              


//////TELEMETRIE

int PAGE = 0;  //9 = NotConnect| 0= start| 1=com | 2=setup | 3= move
float COR =  4.7;
int TmpCor ;
int NewCor = COR*100 ;
int adr0=103; //COR
byte flash = false;

const int NRED = 63488;
const int NYELLOW = 65504;
const int NGREEN = 1120;

/* ######PIN ASIGMENT */
//unsigned char PIN;

#define DRIVE_SPEED 12
#define DRIVE_DIR 13
#define DOME_ROT 14

// SERIAL PINS : //
// Serial     UoTX  UoRX
// Serial1    19 TX  18 RX
// Serial2    23 TX  22 RX

#define FUEL_CELL_A 25 // A1
#define FUEL_CELL_B 26 //A0
#define IR_SENSOR 27 //A3

#define GRIP_MOTA1 32
#define GRIP_MOTA2 33

#define GRIP_MOTB1 2 
#define GRIP_MOTB2 4

#define GRIP_LIFT 15
#define GRIP_ROLL 5

int pos1 = 90;
int pos2 = 90;
int pos3 = 90;
int pos4 = 90;

int IRSensor;

byte F_TRIG = false;

float vIn1;                                // measured voltage (3.3V = max. 16.5V, 5V = max 25V)
float vOut1;
float voltageSensorVal1;                   // value on defined pin (0 - 1023)
const float factor = 5.128;               // reduction factor of the Voltage Sensor shield
const float vCC = 4.85;  ///Systemspannung


/// MP3 
// Set some defaults for start up
// 0 = full volume, 255 off
byte vol = 20;
boolean firstLoadOnConnect = false;
