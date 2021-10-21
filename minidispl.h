#include <Arduino.h>


void OLED_Start() {

  display.display();
  delay(500); // Pause for 2 seconds
  // Clear the buffer
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  // Display static text
  display.println("System Start...");
  display.display(); 
  delay(1000);

for(int16_t i=0; i<= 100; i++) {
    display.clearDisplay();
       
    display.print("%"); 
    // The INVERSE color is used so rectangles alternate white/black
    display.drawRect(8,8,104,12,1);
    
    display.fillRect(10, 10, i, 8, 1);
    display.print(i);
    display.setCursor(10, 22);
    display.display(); // Update screen with each newly-drawn rectangle
    delay(60);
    
  }

   
}

void OLED_status(bool web, String IPADRESS, String cmd, int mode, byte stick, int STICK_AKKU, int vol,int FuelB) {
  
     unsigned long currentMillis2 = millis();

  if (currentMillis2 - previousMillis2 >= 1000) {
    // save the last time you blinked the LED
    previousMillis2 = currentMillis2;

  String calldatabuff;
  int FuelA;
  //int FuelB;
  int volumen = map(vol,-100,150, 0,32);
  int mainBatt = map(FuelB, 24,0, 0,32);
  display.clearDisplay();

  //display.drawCircle(0, 100, 4, WHITE);
  //POWER ROWS
  display.drawRect(118, 0, 10, 32, WHITE);
  display.drawRect(106, 0, 10, 32, WHITE);

  display.fillRect(101,volumen,3,32,WHITE); //Lautstärke

  display.fillRect(120,mainBatt,6,30,WHITE); //BattFuel

  if (stick == false) {
    //Stick inActiv:
  display.drawRoundRect(90,12,8,20,3,WHITE);  //Stick Fuel
  display.drawCircle(93, 7, 4, WHITE);
  //display.fillRect(108,5,6,32,WHITE);  //Stick Fuel
  
  } else {
    //Stick Activ
    display.fillRoundRect(90,12,8,20,3,WHITE);  //Batt Fuel
    display.fillCircle(93, 7, 4, WHITE);

    FuelA = map(STICK_AKKU,0,6, 1,32);
      
      display.fillRect(108,FuelA,6,30,WHITE);  //Stick Fuel

  }
  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  // Display static text
  if (web == false){
  display.println("R2 App active");
  } else {
  display.println("OTA - ready");  
  display.println(IPADRESS);  
  }
  //display.println("System Start...");

  switch (mode){
          case 0:
          calldatabuff = " 0-RANDOM ";
          //myDFPlayer.playFolder(01,023);
          break;
          case 1:
          calldatabuff = " 1-REMOTE ";
          //myDFPlayer.playFolder(02,001);
          break;
          case 2:
          calldatabuff = " 2-HUMAN  ";
          //myDFPlayer.playFolder(02,004);
           break; 
          case 3:
          calldatabuff = " 3-SERVICE";
          //myDFPlayer.playFolder(02,005);
          break;
    
          default:
          calldatabuff = " - No ";
          break;
       }

  display.setCursor(0, 16);
  display.print("M");
  display.println(calldatabuff);
  
  display.setCursor(0, 25);
  display.print("C ");
  display.println(cmd);
  display.display(); 
  } // END INTERVall
  
}


void OLED_config() {
  
}
