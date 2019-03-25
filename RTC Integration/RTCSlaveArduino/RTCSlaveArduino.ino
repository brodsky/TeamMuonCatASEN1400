// 25 February 2019
// Code by Andrew Brodsky for Team Muon Cat – ASEN 1400
//
// This program is adapted from: the TwoPortReceive example found 
// at https://www.arduino.cc/en/Tutorial/TwoPortReceive, 
// which is in the public domain.

#include <SoftwareSerial.h>

// Declare our virtual serial connection:
SoftwareSerial masterToSlave(7,6); // RX, TX. Here, we only care about RX.

// Declare our safe-to-read line:
int readLine = 4;

// Declare global vars:
String incomingSerial;

void setup() 
{
  // We'll use the serial monitor to view time/date output
  Serial.begin(9600);

  while (!Serial) {
  // Wait for hardware serial port to connect. This step is recommended in the TwoPortReceive example.
  }

  // Start our virtual serial port:
  masterToSlave.begin(9600);

  // Set pinmode for the read line. When the slave wants a timestamp from the master, it will pull readLine low
  // and wait for the master to respond.
  pinMode(readLine, OUTPUT);
  digitalWrite(readLine, HIGH);

}


// For ease of copying and pasting this code into other sketches, the main loop has been modularized.
void loop() {
  
  receiveTime();
  serialPrintTime();

}

void receiveTime(){ // Request and record the time from the master Arduino.
  
  // First, pull readLine low.
  digitalWrite(readLine, LOW);

  // Wait until the master notices our request and sends something:
  while(masterToSlave.available()==0);

  // After that, read data from the serial buffer until a "#" character is found,
  // which marks the end of the transmission from the master.
  incomingSerial = masterToSlave.readStringUntil('#');

  // Set readLine back to high:
  digitalWrite(readLine, HIGH);
}

void serialPrintTime(){ // Print the recorded time to the serial monitor.
    
Serial.println(incomingSerial);
  
}
