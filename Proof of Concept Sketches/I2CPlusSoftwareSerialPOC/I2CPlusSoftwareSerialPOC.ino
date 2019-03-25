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

// Declare our virtual serial connections:
SoftwareSerial topCounter(2,3);
SoftwareSerial midCounter(4,5);
SoftwareSerial botCounter(6,7);

// Declare some global vars:
unsigned long startTime = 0;
int cycles = 0;

String topVal;
String midVal;
String botVal;

void setup() 
{
  // Use the serial monitor to view time/date output
  Serial.begin(9600);

  while (!Serial) {
  // Wait for hardware serial port to connect. This step is recommended in the TwoPortReceive example.
  }

  // Start our virtual serial ports
  topCounter.begin(9600);
  midCounter.begin(9600);
  botCounter.begin(9600);
  
  // Initialize the RTC library
  rtc.begin();

  // Wait a full second (reasoning explained below)
  delay(1000);
}

void loop() 
{

  // Recall that we waited for a full second in setup; this ensures that this if statement will be triggered during the
  // first run through loop(). The statement measures how many loops the Arduino is able to do in 1 second.
  if((millis()-startTime)>=1000){

    // Output how many cycles the Arduino was able to do in 1 second:
    Serial.println();
    Serial.println();
    Serial.println( String( "Cycles: "+String(cycles) ) );
    Serial.println();
    Serial.println();

    // Reset the cycle counter and start time:
    cycles = 0;
    startTime = millis(); // get the time
  }

  // Listen on all of the virtual serial ports and get the first byte that comes in (should be a 1 or 
  // a 0, depending on whether or not a particle was detected).
  topCounter.listen();
  topVal = topCounter.read();

  midCounter.listen();
  midVal = midCounter.read();

  botCounter.listen();
  botVal = botCounter.read();

  Serial.print(String(topVal+", "+midVal+", "+botVal+"; "));
  
  // Call rtc.update() to get the latest date/time values for all the library's return functions.
  rtc.update();

  // Print the time and date to the serial monitor:
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

  // Increment the number of cycles and do it all again!
  cycles += 1;
  
}
