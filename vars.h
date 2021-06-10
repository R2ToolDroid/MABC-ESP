#include <Arduino.h>                           

//// No Delay option
// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;      
//unsigned long previousMillis1 = 0;    

byte web = true;

byte State;
int wait = 0;
int battery = 0;
byte StickConnect = 0;
byte OverSpeed = 0; //1 High  0 Low

// constants won't change :
const long interval = 5000;           // interval at which to blink (milliseconds)
//const long interval1 = 5000;           // interval at which to blink (milliseconds)

//int durch = 1;

String cmd; //Consolen Input
byte debug = false; //Debug function
String output;
String data; //Serial Data
String inm = "COIN"; //Inputmode String
String calldata; //String Datarequest
String calldatabuff;

int mode = 1; // Default Mode  0 = Random
              // RC Mode       1 = RC Control
              // RC Show       2 = Human
              // RC Show       3 = Service Arm Control

int INmode = 0; /// 0 == Input auf Coin und Nextion
                /// 1 == Input auf  Stick and Nextion

float PowerA = 0;
float PowerB = 0;              
int STICK_AKKU_STAT = 6; //Akkustatus Stick

int FuelA = 0;
int FuelB = 0;
int FuelA_P = 0;
int FuelB_P = 0;

#define CHARGING 0
#define FULL 1
#define HIGHT 2
#define LOWR 3
#define DYING 4
#define SHUTDOWN 5
#define NOT_CONNECT 6

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
// Serial2    23 TX  27 RX_Test Board   27_PCB!!

//I2C   21 SDA     22 SDC for PCB Board

// MP3 DFPlayer RX25  TX26

//#define FUEL_CELL_A 25 // A1
#define FUEL_CELL_B 35 //A0
#define IR_SENSOR 34 //A3 vorher 27

//Claw
#define GRIP_MOTA1 32
#define GRIP_MOTA2 33

//Arm:
#define GRIP_MOTB1 2 
#define GRIP_MOTB2 4

#define GRIP_LIFT 5
#define GRIP_ROLL 15



//Define Arm Move
#define ARM_IN_OUT  1
#define ARM_UP_DOWN 2
#define ARM_ROLL    3
#define ARM_GRIPP   4

#define STOP      1
#define R_LEFT    2
#define R_RIGHT   3


//SHIFT STICK

#define SH_CROSS 1
#define SH_CIRCLE 2
#define SH_L1 3
#define SH_L2 4
#define SH_L3 5
#define SH_PLUS 6

int SHIFT = 0;

int posX = 90;
int posY = 90;
int posTemp;

int Gpos = 90; //Gripper Roll Pos
int Apos = 90; //Arm Lift Pos

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


//Move Sensor
byte NachL = false;
byte NachR = false;
byte Mitte = false;
byte Ping = false;
int Sdiff = 0;

//AutoDome function

// Dome Automation Variables
boolean domeAutomation = true;
int domeTurnDirection = 1;  // 1 = positive turn, -1 negative turn
float domeTargetPosition = 0; // (0 - 359) - degrees in a circle, 0 = home
unsigned long domeStopTurnTime = 0;    // millis() when next turn should stop
unsigned long domeStartTurnTime = 0;  // millis() when next turn should start
int domeStatus = 0;  // 0 = stopped, 1 = prepare to turn, 2 = turning
int time360DomeTurn = 2500;  // milliseconds for dome to complete 360 turn at domeAutoSpeed - Valid Values: 2000 - 8000 (2000 = 2 seconds)
byte domeAutoSpeed = 70;     // Speed used when dome automation is active - Valid Values: 50 - 100
byte isCenter = false;
byte findCenter = true;
byte domePos = false;
unsigned long domeFindCenterTime = 0;
unsigned long CurDomeFindTime = 0;
unsigned long maxFindTime = 3000;
