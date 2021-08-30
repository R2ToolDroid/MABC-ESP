#include <Arduino.h>

////////////////////////////////
// command line builder, makes a valid command line from the input
byte buildCommand(char ch, char* output_str)
{
  static uint8_t pos=0;
  switch(ch)
 {
    case '\r':                          // end character recognized
      output_str[pos]='\0';   // append the end of string character
      pos=0;        // reset buffer pointer
      return true;      // return and signal command ready
      break;
    default:        // regular character
      output_str[pos]=ch;   // append the  character to the command string
      if(pos<=CMD_MAX_LENGTH-1)pos++; // too many characters, discard them.
      break;
  }
  
  return false;

  
}

void App(){
 if(!connected) {
    client = server2.available();
  }
  
  if(client.connected()) {
    if(!connected) {
      Serial.println("TCP connected");
      connected = true;
    }
    
    if(client.connected()) {
      bool command_available;
      if(client.available() > 0) {
      
        char ch = client.read();

    // New improved command handling
        command_available=buildCommand(ch, cmdString);  // build command line
        
    if (command_available && cmdString != "") 
    {
      
      parseCommand(cmdString);  // interpret the command
      //DEBUG_PRINT(" cmd true ");
      //Serial.print("com :");
      //Serial.println(cmdString);
      
    }
    // Serial.write(c);
 
    //Serial.println(cmdString);
      } //while available
      
    } //While connected

    
  } else {
    if(connected) {
      Serial.println("TCP disconnected");
      connected = false;
    }
  }

  
}
