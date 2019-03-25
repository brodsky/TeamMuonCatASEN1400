// 25 February 2019
// Code by Andrew Brodsky for Team Muon Cat – ASEN 1400
//
// This program is adapted from: the DS1307_RTC_Demo.ino included 
// in SparkFun's SparkFunDS1307RTC library and released under the MIT License; 
// and the TwoPortReceive example found at https://www.arduino.cc/en/Tutorial/TwoPortReceive, 
// which is in the public domain.

#include <SoftwareSerial.h>
#include <SparkFunDS1307RTC.h> // make sure you have this library installed!
#include <Wire.h>

// Declare our virtual serial connection:
SoftwareSerial masterToSlave(12,13); // RX,TX. Here, we only care about the TX pin.

// Declare our safe-to-read line:
int readLine = 12;

void setup() 
{
  // Use the serial monitor to view time/date output
  Serial.begin(9600);

  while (!Serial) {
  // Wait for hardware serial port to connect. This step is recommended in the TwoPortReceive example.
  }

  // Start our virtual serial port:
  masterToSlave.begin(9600);

  // Set pinmode for readLine to PULLUP. When the slave wants a timestamp from the RTC, it will 
  //  pull this line low and wait for the master to respond.
  pinMode(readLine, INPUT_PULLUP);

  // Initialize the SparkFun RTC library
  rtc.begin();

}


// For ease of copying and pasting this code into other sketches, the main loop has been modularized.
void loop() {
  
  // Call rtc.update() to get the latest date/time values for all the library's return functions.
  rtc.update();
  
  serialPrintTime();
  sendTime();
    
}

void serialPrintTime(){ // Prints the time and date to the serial monitor.
    
  // Print hour
  Serial.print(String(rtc.hour()) + ":");
  
  // Print leading '0' for minute if necessary
  if (rtc.minute() < 10) Serial.print('0');
  // Print minute
  Serial.print(String(rtc.minute()) + ":"); 

  // Print leading '0' for second if necessary
  if (rtc.second() < 10) Serial.print('0');
  // Print second
  Serial.print(String(rtc.second()));

  Serial.print(" "); // add space before date
  // print the full date! (in day/month/year format)
  Serial.println(String(rtc.date()) + "/" + String(rtc.month()) + "/" + String(rtc.year()) + " ");
  
}

void sendTime(){   // If the slave Arduino wants the time, then send it over.
  
  if(digitalRead(readLine)==0){ // slave has pulled readLine low
    
  // Send hour
  masterToSlave.print(String(rtc.hour()) + ":");
  
  // Send leading '0' for minute if necessary
  if (rtc.minute() < 10) masterToSlave.print('0');
  // Send minute
  masterToSlave.print(String(rtc.minute()) + ":"); 

  // Send leading '0' for second if necessary
  if (rtc.second() < 10) masterToSlave.print('0');
  // Send second
  masterToSlave.print(String(rtc.second()));

  masterToSlave.print(" "); // add space before date
  // Send the full date! (in day/month/year format)
  masterToSlave.print(String(rtc.date()) + "/" + String(rtc.month()) + "/" + String(rtc.year()) + " ");

  // Send the terminator character. This is how the slave knows the transmission has ended.
  masterToSlave.print("#");

  }
    
}
