#include <Arduino.h>   

// Check in Range inRange(x, 0, 200)
bool inRange(int val, int minimum, int maximum)
{
  return ((minimum <= val) && (val <= maximum));
}

/*
void eepromWriteInt(int adr, int wert) {
// 2 Byte Integer Zahl im EEPROM ablegen an der Adresse
// Eingabe: 
//   adr: Adresse +0 und +1 wird geschrieben
//   wert: möglicher Wertebereich -32,768 bis 32,767
// Ausgabe: 
//   -
// 2 Byte Platz werden belegt.
//
// Matthias Busse 5.2014 V 1.0

byte low, high;

  low=wert&0xFF;
  high=(wert>>8)&0xFF;
  EEPROM.write(adr, low); // dauert 3,3ms 
  EEPROM.write(adr+1, high);
  EEPROM.commit();
  Serial.println(F("..write State to EEPROM ready."));
  
  return;
} //eepromWriteInt

int eepromReadInt(int adr) {
// 2 Byte Integer Zahl aus dem EEPROM lesen an der Adresse
// Eingabe: 
//   adr: Adresse +0 und +1 wird gelesen
// Ausgabe: int Wert
//
// Matthias Busse 5.2014 V 1.0

byte low, high;

  low=EEPROM.read(adr);
  high=EEPROM.read(adr+1);
  return low + ((high << 8)&0xFF00);
} //eepromReadInt

*/
void loadDefault(){
  
    //k = eepromReadInt(adr0);
    web = EEPROM.read(C_WEB);
    
    Serial.print(" web ");
    Serial.println(web);
    
    
       
    
    
    /*
    SLEGCENT = eepromReadInt(adr1);
    if (SLEGCENT < 1) {SLEGCENT = 400;}

    SLEGLOOK = eepromReadInt(adr2);
    if (SLEGLOOK < 1) {SLEGLOOK = 340;}

    SR = eepromReadInt(adr3);
    if (SR < 1) {SR = 5;}

    CMOTPWR = eepromReadInt(adr4);
    if (CMOTPWR < 1) {CMOTPWR = 255;}

    LMOTPWR = eepromReadInt(adr5);
    if (LMOTPWR < 1) {LMOTPWR = 150;}   

    BTIME = eepromReadInt(adr12);
    if (BTIME < 1) {BTIME = 20;}   
    */
}

void shwConfig(byte STATE){

    
    S_CONFIG =  "-Config-";
    if (STATE){
      S_CONFIG += " READ\n\r";
    } else {
      S_CONFIG += " WRITE\n\r";
    }
    
    S_CONFIG += "WEB:";
    S_CONFIG += web;
    S_CONFIG += " IR: ";
    S_CONFIG += IR;
    S_CONFIG += " Mod: ";
    S_CONFIG += mode;
    S_CONFIG += "\n\r";
    Serial.print(S_CONFIG);
}



void randomSound(int minINT, int maxINT, int maxFiles){

  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  unsigned long RNDcurrentMillis = millis();

  //RNDinterval = random(3000, 5000);
  if (DEBUG_SOUND){
  Serial.print(" | interv ");
  Serial.print(RNDinterval);
  Serial.print(" | cur ");
  Serial.print(RNDcurrentMillis);
  Serial.print(" | prev ");
  Serial.print(RNDpreviousMillis);
  Serial.print(" | diff ");
  Serial.print(RNDcurrentMillis - RNDpreviousMillis);
  Serial.print(" | State ");
  }
  //delay(50);

  if (RNDcurrentMillis - RNDpreviousMillis >= RNDinterval) {
    // save the last time you blinked the LED
    RNDinterval = random(minINT, maxINT);
    
    RNDpreviousMillis = RNDcurrentMillis;

    file = random(1, maxFiles);
    if (DEBUG_SOUND){
    Serial.print("beeep.. NR:  ");
    Serial.print(file);
    }

    myDFPlayer.playFolder(01, file);
    
  }
  
  if (DEBUG_SOUND){
  Serial.println("..");
    //delay(50);
  }

  
}

void onConnect(){
    Serial.println("Stick Connected.");   
    //oled.clear();
    //line = 10;
    //showinfo("Stick online");
    //delay(200);
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

float readFuel(unsigned char PIN){
      /* OLD
      float sensorValue = analogRead(PIN);
       // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
      float voltage = sensorValue * (5 / 1023.0);
      // print out the value you read:
      // FAKTOR 4.59 bei 10 Volt //
      //Serial.println(voltage * 4.59);
      float result = voltage * COR;
      //Serial.println(result); //Endgültigen Spannungswert im seriellen Monitor anzeigen
      //float result = wert2;
      END OLD*/
      
       voltageSensorVal1 = analogRead(PIN);    // read the current sensor value (0 - 1023) 
       vOut1 = (voltageSensorVal1 / 1024) * vCC;             // convert the value to the real voltage on the analog pin
      float result =  vOut1 * factor;     

      
      if (result <= 16) {result = 16;} 
      if (result >= 17) {result = 17;}
     //Serial.println(result);
      
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

  if ( (FuelB >= 14)&&(FuelB <= 20)){
  FuelB_P =  map(FuelB, 14, 19, 0, 100); ///Map for 100%
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
