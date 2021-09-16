#include <Arduino.h>


void showinfo(String info) {

  if (info == ""){
    return;
  }
  //oled.clear();
  //info += "\r";
  oled.println(info);
 
  delay(500);
  

  
}
