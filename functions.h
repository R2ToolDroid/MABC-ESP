#include <Arduino.h>   

// Check in Range inRange(x, 0, 200)
bool inRange(int val, int minimum, int maximum)
{
  return ((minimum <= val) && (val <= maximum));
}


void loadDefault(){
    
    web = EEPROM.read(C_WEB);
    IR =  EEPROM.read(C_IR);
    FUEL = EEPROM.read(C_FUEL);
    DISP = EEPROM.read(C_DISPL);
    mode = EEPROM.read(C_MOD);

    if (web == 255) web = 1;
    if (IR == 255) IR = 1;
    if (FUEL == 255) FUEL = 1;
    if (DISP == 255) DISP = 1;
    if (mode == 255) mode = 0;
 
}

void shwConfig(byte STATE){

    
    Serial.print(F( "-Config- "));
    if (STATE){
      Serial.println(F(" READ"));
    } else {
      Serial.println(F( " WRITE"));
    }
    
    Serial.print(F("WEB:"));
    Serial.print (EEPROM.read(C_WEB));
     Serial.print(F(" IR: "));
    Serial.print (EEPROM.read(C_IR)) ;

    Serial.print(F(" FUEL-Sens: "));
    Serial.print ( EEPROM.read(C_FUEL)) ;
    
    Serial.print(F(" Mod: "));
    Serial.print (EEPROM.read(C_MOD));

    Serial.print(F(" Displ: "));
    Serial.println ( EEPROM.read(C_DISPL));
   
}



void randomSound(int minINT, int maxINT, int maxFiles){

  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  unsigned long RNDcurrentMillis = millis();

  //RNDinterval = random(3000, 5000);
  if (DEBUG_SOUND){
  Serial.print(F(" | interv "));
  Serial.print(RNDinterval);
  Serial.print(F(" | cur "));
  Serial.print(RNDcurrentMillis);
  Serial.print(F(" | prev "));
  Serial.print(RNDpreviousMillis);
  Serial.print(F(" | diff "));
  Serial.print(RNDcurrentMillis - RNDpreviousMillis);
  Serial.print(F(" | State "));
  }
  //delay(50);

  if (RNDcurrentMillis - RNDpreviousMillis >= RNDinterval) {
    // save the last time you blinked the LED
    RNDinterval = random(minINT, maxINT);
    
    RNDpreviousMillis = RNDcurrentMillis;

    file = random(1, maxFiles);
    if (DEBUG_SOUND){
    Serial.print(F("beeep.. NR:  "));
    Serial.print(file);
    }

    myDFPlayer.playFolder(01, file);
    
  }
  
  if (DEBUG_SOUND){
  Serial.println(F(".."));
    //delay(50);
  }

  
}

void onConnect(){
    Serial.println(F("Stick Connected."));   
    
    myDFPlayer.playFolder(01, 2);
}



void resetSequence(){
  
  Serial2.print(":SE00");           // hier geht es weiter zum Marcduino Dome Controller
  Serial2.print('\r');

  Serial2.print("center");           // hier geht es weiter zum Dome Controller
  Serial2.print('\r'); 
  
}
                
void NextEnd() {

  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);

  
}

void ToggleSpeed(){

   if (OverSpeed == 0){
    OverSpeed = 1;
    Serial1.print("r2.val=1");
      NextEnd();
   } else {
    OverSpeed = 0;
    Serial1.print("r2.val=0");
      NextEnd();
   }
}

uint32_t readADC_Cal(int ADC_Raw)
{
  esp_adc_cal_characteristics_t adc_chars;
  
  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1100, &adc_chars);
  return(esp_adc_cal_raw_to_voltage(ADC_Raw, &adc_chars));
}

float readFuel(unsigned char PIN){

      //float MV = analogReadMilliVolts(PIN);
      
      AN_Pot1_Result = analogRead(PIN);
      if (AN_Pot1_Result >= 4060) AN_Pot1_Result = 0;
      Voltage = readADC_Cal(AN_Pot1_Result);
      float  result = Voltage/100.0;
      result = result + COR;
      //Serial.println(Voltage/1000.0); // Print Voltage (in V)
      
      if (result <= 3) result=0;

     if (DEBUG_FUEL) {
      Serial.print(F("Read Fuel Data from PIN: "));
      Serial.print(PIN);
      Serial.print(F(" Result "));
      Serial.print(result);

      Serial.print(F( " Analog Data: "));
      Serial.println(AN_Pot1_Result);

      //Serial.print(F(" Mini Volt "));
      //Serial.println(MV);
     }
     
      
     return result;  
}


void NextCom(String data){

 //Serial1.print("t0.txt=\"it works!\"");

 Serial1.print("t0.txt=\"");
 Serial1.print(data);
 Serial1.print(" _\"");
 
 NextEnd();  
 
}

void ShwMode(){

   // myDFPlayer.playFolder(02,001);

    switch (mode){
          case 0:
          calldatabuff = " 0-RANDOM ";
          myDFPlayer.playFolder(01,023);
          break;
          case 1:
          calldatabuff = " 1-REMOTE ";
          myDFPlayer.playFolder(02,001);
          break;
          case 2:
          calldatabuff = " 2-HUMAN  ";
          myDFPlayer.playFolder(02,004);
           break; 
          case 3:
          calldatabuff = " 3-SERVICE";
          myDFPlayer.playFolder(02,005);
          break;
    
          default:
          calldatabuff = " - No ";
          break;
       }

      
      delay (500);   
      //NextCom(calldatabuff);
      if (PAGE == 0){
      Serial1.print("t1.txt=\"");
      Serial1.print(calldatabuff);
      Serial1.print(" _\"");
      NextEnd(); 
      }
  
}




void NextUpdate(int TT) {


  ///Serial.print("t0.txt=\"it works!\"")///
   unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

  //OverSpeed
    //Serial.print("t1.txt=\"MODE: \"")
   if (OverSpeed == 1){
      Serial1.print("r2.val=1");
      NextEnd();
   } else {
      Serial1.print("r2.val=0");
      NextEnd();
   }

  
 
  

  switch (STICK_AKKU_STAT){
      case CHARGING:
      FuelA_P = 100;
      break;
      case FULL:
      FuelA_P = 90;
      break;
      case HIGHT:
      FuelA_P = 80;
      break;
      case LOWR:
      FuelA_P = 70;
      break;
      case DYING:
      FuelA_P = 40;
      break;
      case SHUTDOWN:
      FuelA_P = 30;
      break;

      case NOT_CONNECT:
      FuelA_P = 0;
      break;

      default:
      FuelA_P = 0;
      break;
    
  }
   
   
  if (FuelA_P < 30){
    Serial1.print("j1.pco=");
    Serial1.print("63488"); ///RED
    NextEnd(); 
    } else if ( (FuelA_P > 30)&&(FuelA_P < 70) ) {
     Serial1.print("j1.pco=");
     Serial1.print("65504"); ///yellow
     NextEnd(); 
   } else if (FuelA_P > 70) {
     Serial1.print("j1.pco=");
     Serial1.print("1120"); ///GREEN
     NextEnd(); 
   }   
  Serial1.print("j1.val=");
  Serial1.print(FuelA_P);
  NextEnd();

  Serial1.print("n1.val=");
  Serial1.print(FuelA);
  NextEnd();

/// END FUEL A

  if ( (FuelB >= 8)&&(FuelB <= 25)){
  FuelB_P =  map(FuelB, 8, 22, 0, 100); ///Map for 100%
  }
  
  if (FuelB_P < 30){
    
    Serial1.print("j0.pco=");
    Serial1.print("63488"); ///RED
    NextEnd(); 
    } else if ((FuelB_P > 30)&&(FuelB_P < 70)) {
     Serial1.print("j0.pco=");
     Serial1.print("65504"); ///yellow
     NextEnd(); 
    } else if (FuelB_P > 70) {
      Serial1.print("j0.pco=");
      Serial1.print("1120"); ///GREEN
      NextEnd(); 
    } 

  Serial1.print("j0.val=");
  Serial1.print(FuelB_P);
  NextEnd();

  Serial1.print("n0.val=");
  Serial1.print(FuelB);
  NextEnd();

  Serial1.print("bt0.pic=1");
  NextEnd();

  if (StickConnect){
  Serial1.print("r3.val=1");
  NextEnd();
  } else {
   Serial1.print("r3.val=0");
  NextEnd(); 
  }

  Serial1.print("r1.val=1");
  NextEnd();
  
  TT++;
if (TT > 100) {TT = 0;}

  Serial1.print("bt0.pic=2");
  NextEnd();
  } /// END Update Intervall
  
}


void ArmMove( int GRIP_LIFT_STATUS ){

     if ( GRIP_LIFT_STATUS_BEFORE != GRIP_LIFT_STATUS  ){
         
      switch (GRIP_LIFT_STATUS){
        
        case GRIP_LIFT_TOP:   
        myLSS.moveT(1200, 3000);
        liftPos = liftPos+5;
        break;
      
        case GRIP_LIFT_DOWN:
        myLSS.moveT(-1200, 3000);
        liftPos = liftPos-5;
        break;
      
        case GRIP_LIFT_STOP:
        myLSS.hold();
        liftPos = liftPos;
        break;
      
      default:
      myLSS.hold();
      liftPos = liftPos;
      break;
      
     }// End Switch
     
    } // end Each
    
     GRIP_LIFT_STATUS_BEFORE = GRIP_LIFT_STATUS;

      
}
