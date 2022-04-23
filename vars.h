#include <Arduino.h>                           

byte DEBUG_INPUT = false;
byte DEBUG_STICK = false;
byte DEBUG_DRIVE = false;

byte DEBUG_OUTPUT = false;
byte DEBUG_SOUND = false;
byte DEBUG_IR = false;
byte DEBUG_FUEL = false;

byte IR = true;
byte FUEL = true;
byte DISP = true;

byte DoorOpen = false;

byte HoloAction = false;

///EEPROM ADRESSES
//int adr0=103; //WEB -|| OTA-ON =1 | OTA-OFF = 2 :  0: undefined  1: true  2:false

#define RE true
#define WR false

#define C_WEB 1 // EPROM SPEICHER
#define OTA_ON 1 //true
#define OTA_OFF 0 //false

#define C_IR 2 // EPROM IR Sensor 
#define IR_ON 1
#define IR_OFF 0

#define C_FUEL 3 //Internal Fuel Cell Control  1:true 2:false
#define FUEL_ON 1  
#define FUEL_OFF 0

#define C_DISPL 4
#define DISPL_ON 1
#define DISPL_OFF 0

#define C_MOD 5

int k;
//// END EEPROM

byte CONFIG = false;
String S_CONFIG = "";


// Command processing stuff
// maximum number of characters in a command (63 chars since we need the null termination)
#define CMD_MAX_LENGTH 64 

// memory for command string processing
char cmdString[CMD_MAX_LENGTH];


unsigned long previousMillis = 0;   
unsigned long previousMillis2 = 0;      
byte web = false;
int line = 0;

String IPADRESS = "00.00.00.00";

byte State;
int wait = 0;
int battery = 0;
byte StickConnect = false;
byte OverSpeed = false; //1 High  0 Low
byte next = false;
String STcmd = "";

// constants won't change :
const long interval = 5000;           // interval at which to blink (milliseconds)
//const long interval1 = 5000;           // interval at which to blink (milliseconds)

//int durch = 1;

String cmd; //Consolen Input
//byte debug = false; //Debug function
String tmp_cmd;

String data; //Serial Data
String inm = "COIN"; //Inputmode String
String calldata; //String Datarequest
String calldatabuff;

int mode = 0 ;// Default Mode  0 = Random
              // RC Mode       1 = RC Control
              // RC Show       2 = Human
              // RC Show       3 = Service Arm Control
              
// Random Sound
unsigned long RNDpreviousMillis = 0;        // will store last time LED was updated
// constants won't change:
long RNDinterval = 8000;           // interval at which to blink (milliseconds)
byte RNDSound = false;   
    
int file = 4;
int maxFilesinFolder;      

int TalkFolder;
int IRFolder;

//int INmode = 1; /// 0 == Input auf Coin und Nextion
//                /// 1 == Input auf  Stick and Nextion

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
float COR =  1.1 ;  //Voltage Reading Correction Faktor
int AN_Pot1_Result = 0;
float Voltage = 0.0;


int TmpCor ;
int NewCor = COR*100 ;
//int adr0=103; //COR
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


// Change this to match the Arduino pin connected to the sensor's OUT pin.
const uint8_t sensorPin = IR_SENSOR;
unsigned long prevTick = 0;  
//const long interval = 7000;
byte in = true;
byte Hin;
byte t_Hin ;
int countTrig = 1;
int countTrig2 = 1;
int countTrig3 = 2;

//Claw
#define GRIP_MOTA1 33  //vorher 32
#define GRIP_MOTA2 32  //vorher 33

//Arm:
#define GRIP_MOTB1 2 
#define GRIP_MOTB2 4

#define GRIP_LIFT 5
#define GRIP_ROLL 15

int liftPos = 0;

#define GRIP_LIFT_TOP 1
#define GRIP_LIFT_DOWN 2
#define GRIP_LIFT_STOP 3

int GRIP_LIFT_STATUS = GRIP_LIFT_STOP;
int GRIP_LIFT_STATUS_BEFORE = GRIP_LIFT_STOP;

unsigned long startTime = millis();

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

byte F_TRIG = false;

float vIn1;                                // measured voltage (3.3V = max. 16.5V, 5V = max 25V)
float vOut1;
float voltageSensorVal1;                   // value on defined pin (0 - 1023)
const float factor = 5.128;               // reduction factor of the Voltage Sensor shield
const float vCC = 4.85;  ///Systemspannung


/// MP3 
// Set some defaults for start up
// 0 = full volume, 255 off
int vol = 20;
boolean firstLoadOnConnect = false;


//Move Sensor
byte NachL = false;
byte NachR = false;
byte Mitte = false;
byte Ping = false;
int Sdiff = 0;
