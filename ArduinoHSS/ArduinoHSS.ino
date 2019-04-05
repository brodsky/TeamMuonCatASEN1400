 //Temperature Sensor 1
 const byte temp1Pin = A0;
 const int greenTemp1On = 5;
 int temp1Sensor;
 float temp1SensorVolts;
 float temp1SensorUnits;
 float temp1SensorUnitsC; //var for units in celcius 
 
 //Temperature Sensor 2
 const byte temp2Pin = A1;
 //const int Temp2On = 4;
 int temp2Sensor;
 float temp2SensorVolts;
 float temp2SensorUnits;
 float temp2SensorUnitsC; //var for units in celcius 
 
 //Humidity Sensor
 const byte humidityPin = A2;
 const int blueHumidityOn = 6; 
 int humiditySensor;
 float humiditySensorVolts;
 float humiditySensorUnits;
 
 //Pressure Sensor
 const byte pressurePin = A3;
 const int redPressureOn = 7;
 int pressureSensor;
 float pressureSensorVolts;
 float pressureSensorUnits;
 
 
 //Accelerometer
 const byte accelXPin = A4;
 const byte accelZPin = A5;
 const int yellowAccelOn = 9;
 int sensorX;
 int sensorZ;
 float sensorVoltX;
 float sensorVoltZ;
 float sensorUnitsX;
 float sensorUnitsZ;

 //time
 uint32_t timeStamp = 0;


 //heater
 const int heaterPin = 10;
 int failSafe = 0;
 



void setup() {
 //pinMode(4, OUTPUT);
 pinMode(greenTemp1On, OUTPUT);
 pinMode(blueHumidityOn, OUTPUT);
 pinMode(redPressureOn, OUTPUT);
 pinMode(yellowAccelOn, OUTPUT);
 pinMode(heaterPin, OUTPUT);

Serial.begin(9600);
Serial.print("New Data Run...");
Serial.println();
Serial.print("TIME,RH,PS,TEMP1,TEMP2,ACCX,ACCZ");
Serial.println();

  
 
}

void loop() {
  //digitalWrite(4, LOW);
  //digitalWrite(greenTemp1On, LOW);
  //digitalWrite(blueHumidityOn, LOW);
  //digitalWrite(redPressureOn, LOW);
  //digitalWrite(yellowAccelOn, LOW);

  timeStamp = millis();
  
  //Temperature sensor 1
  temp1Sensor = analogRead(temp1Pin);
  temp1SensorVolts = temp1Sensor*(5.0/1023);
  temp1SensorUnitsC = (temp1SensorVolts - 0.5)/(0.01);
  temp1SensorUnits = (temp1SensorUnitsC*(9.0/5.0)+32)-2.12903; //2.12903 for bias
  
   //Temperature sensor 2
  temp2Sensor = analogRead(temp2Pin);
  temp2SensorVolts = temp2Sensor*(5.0/1023);
  temp2SensorUnitsC = (temp2SensorVolts - 0.5)/(0.01);
  temp2SensorUnits = (temp2SensorUnitsC*(9.0/5.0)+32)+2.39003; //2.39003 for bias
  
  //Humidity Sensor
  humiditySensor = analogRead(humidityPin);
  humiditySensorVolts = humiditySensor*(5.0/1023);
  humiditySensorUnits = (((humiditySensorVolts/5.0)-0.16)/0.0062);
  
  //Pressure Sensor
  pressureSensor = analogRead(pressurePin);
  pressureSensorVolts = pressureSensor*(5.0/1023);
  pressureSensorUnits = (pressureSensorVolts-0.5)*(15.0/4.0)+0.03471; //0.03471 for bias
  
  //Accelerometer
  sensorX = analogRead(accelXPin);
  sensorZ = analogRead(accelZPin);
  sensorVoltX = sensorX*(5.0/1023);
  sensorUnitsX = (sensorVoltX-(3.3/2))/(0.330)+0.0976; //0.08279 for bias
  sensorVoltZ = sensorZ*(5.0/1023);
  sensorUnitsZ = (sensorVoltZ-(3.3/2))/(0.330)+0.07565-.02962; //0.07565 for bias




  //heater 
analogWrite(heaterPin, 255);
//  if(failSafe != 1){
//    if(temp1SensorUnitsC < -15){//failsafe case
//      analogWrite(heaterPin, 255);
//      failSafe = 1;
//    }
//  else if(temp1SensorUnitsC <= 15 && temp1SensorUnitsC > 10){
//      analogWrite(heaterPin, 25);
//    }
//    else if(temp1SensorUnitsC <= 10 && temp1SensorUnitsC > 5){
//      analogWrite(heaterPin, 75);
//    }
//    else if(temp1SensorUnitsC <= 5 && temp1SensorUnitsC > 0){
//      analogWrite(heaterPin, 150);
//    }
//
//    else if(temp1SensorUnitsC <= 0 && temp1SensorUnitsC > -15){
//      analogWrite(heaterPin, 255);
//    }
// }
//
//  //makes sure it wont get too hot 
//  if(temp1SensorUnitsC > 30 && failSafe == 1){
//    failSafe = 0;
//  }

  //printing 
  //Time
 Serial.print(timeStamp);
 Serial.print(",");

  //Humidity Sensor
  
  
  Serial.print(humiditySensorUnits,5);
  digitalWrite(blueHumidityOn, HIGH);

  //Pressure Sensor
  Serial.print(",");
  Serial.print(pressureSensorUnits,5);
  digitalWrite(redPressureOn, HIGH);

  //Temp Sensor 1
  Serial.print(",");
  Serial.print(temp1SensorUnits,5);
  digitalWrite(greenTemp1On, HIGH);

  //Temp Sensor 2
  Serial.print(",");
  Serial.print(temp2SensorUnits,5);
  //digitalWrite(4, HIGH);

  //Accelerometer
  Serial.print(",");
  Serial.print(sensorUnitsX,5);
  Serial.print(",");
  Serial.print(sensorUnitsZ,5);
  digitalWrite(yellowAccelOn, HIGH);

  Serial.println();

  delay(100);

  

}
