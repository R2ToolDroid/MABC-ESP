#include <Arduino.h>  


void telnet(){


    switch (TelnetStream.read()) {
    case 'R':
    TelnetStream.stop();
    delay(100);
    ESP.restart();
      break;
    case 'C':
      TelnetStream.println("bye bye");
      TelnetStream.flush();
      TelnetStream.stop();
      break;
  }

  //TelnetStream.print("\r");
  //TelnetStream.print(" Hallo Aus dem Telnet");
  //TelnetStream.print("\r");
  
}
