#include <Arduino.h>   



void onConnect(){
    Serial.println("Connected.");
}

void ToggleSpeed(){

   if (OverSpeed == 0){
    OverSpeed = 1;
   } else {
    OverSpeed = 0;
   }
}

void resetSequence(){
  
  //servoSequencer.play(SeqBodyPanelAllSoftClose, SizeOfArray(SeqBodyPanelAllSoftClose), (GROUP_DOORS));
  
  //Serial3.print(":CL00");           // hier geht es weiter zum Marcduino Dome Controller
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




void NextUpdate(int TT) {


  ///Serial.print("t0.txt=\"it works!\"")///
   unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
  
  //Serial.println(readFuel(FUEL_CELL_A));
  //Serial.println(ReadFuel(FUEL_CELL_B));
  int FuelA = readFuel(FUEL_CELL_A);
  int FuelB = readFuel(FUEL_CELL_B);

  //Serial1.print("n1.val=");
  //Serial.print(FuelA);
  //NextEnd();

  int FuelA_P =  map(FuelA, 16, 19, 0, 100); ///Map for 100%
  
  Serial1.print("j1.pco=");
  Serial1.print("65504"); ///yellow
  NextEnd(); 
  
  if (FuelA <= 16){
    FuelA_P = 5;
    Serial1.print("j1.pco=");
    Serial1.print("63488"); ///RED
    NextEnd(); 
    
    }
    
  if (FuelA_P >= 80) {
  Serial1.print("j1.pco=");
  Serial1.print("1120"); ///GREEN
  NextEnd(); 
  }
  

  
  
  Serial1.print("j1.val=");
  Serial1.print(FuelA_P);
  NextEnd();
  

  Serial1.print("n0.val=");
  Serial1.print(FuelB);
  NextEnd();

  int FuelB_P =  map(FuelB, 16, 19, 0, 100); ///Map for 100%

  Serial1.print("j0.pco=");
  Serial1.print("65504"); ///yellow
  NextEnd(); 
  
  if (FuelB <= 16){
    FuelB_P = 5;
    //Serial1.print("j0.pco=");
    //Serial1.print("63488"); ///RED
    //NextEnd(); 
    }

  if (FuelB_P > 80) {
   Serial1.print("j0.pco=");
   Serial1.print("1120"); ///GREEN
   NextEnd(); 
  } 
  

  
  Serial1.print("j0.val=");
  Serial1.print(FuelB_P);
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

void printOutput()
{
    if (output != "")
    {
        if (Serial) Serial.println(output);
        output = ""; // Reset output string
    }
}
