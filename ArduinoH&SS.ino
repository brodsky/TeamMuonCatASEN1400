 //Temperature Sensor 1
 int temp1Sensor;
 float temp1SensorVolts;
 float temp1SensorUnits;
 float temp1SensorUnitsC; //var for units in celcius 
 
 //Temperature Sensor 2
 int temp2Sensor;
 float temp2SensorVolts;
 float temp2SensorUnits;
 float temp2SensorUnitsC; //var for units in celcius 
 
 //Humidity Sensor
 int humiditySensor;
 float humiditySensorVolts;
 float humiditySensorUnits;
 
 //Pressure Sensor
 int pressureSensor;
 float pressureSensorVolts;
 float pressureSensorUnits;
 
 
 //Accelerometer
 int sensorX;
 int sensorZ;
 float sensorVoltX;
 float sensorVoltZ;
 float sensorUnitsX;
 float sensorUnitsZ;

 //time
 uint32_t timeStamp = 0;


void setup() {
 pinMode(4, OUTPUT);
 pinMode(5, OUTPUT);
 pinMode(6, OUTPUT);
 pinMode(7, OUTPUT);
 pinMode(9, OUTPUT);

Serial.begin(9600);
Serial.print("TIME,RH,PS,TEMP1,TEMP2,ACCX,ACCZ");
Serial.println();
  
 
}

void loop() {
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(9, LOW);

  timeStamp = millis();
  
  //Temperature sensor 1
  temp1Sensor = analogRead(A0);
  temp1SensorVolts = temp1Sensor*(5.0/1023);
  temp1SensorUnitsC = (temp1SensorVolts - 0.5)/(0.01);
  temp1SensorUnits = (temp1SensorUnitsC*(9.0/5.0)+32);
  
   //Temperature sensor 2
  temp2Sensor = analogRead(A1);
  temp2SensorVolts = temp2Sensor*(5.0/1023);
  temp2SensorUnitsC = (temp2SensorVolts - 0.5)/(0.01);
  temp2SensorUnits = (temp2SensorUnitsC*(9.0/5.0)+32);
  
  //Humidity Sensor
  humiditySensor = analogRead(A2);
  humiditySensorVolts = humiditySensor*(5.0/1023);
  humiditySensorUnits = (((humiditySensorVolts/5.0)-0.16)/0.0062);
  
  //Pressure Sensor
  pressureSensor = analogRead(A3);
  pressureSensorVolts = pressureSensor*(5.0/1023);
  pressureSensorUnits = (pressureSensorVolts-0.5)*(15.0/4.0);
  
  //Accelerometer
  sensorX = analogRead(A4);
  sensorZ = analogRead(A5);
  sensorVoltX = sensorX*(5.0/1023);
  sensorUnitsX = (sensorVoltX-(3.3/2))/(0.330);
  sensorVoltZ = sensorZ*(5.0/1023);
  sensorUnitsZ = (sensorVoltZ-(3.3/2))/(0.330);

  //printing 
  //Time
  Serial.print(timeStamp);
  Serial.print(",");

  //Humidity Sensor
  
  
  Serial.print(humiditySensorUnits,2);
  digitalWrite(6, HIGH);

  //Pressure Sensor
  Serial.print(",");
  Serial.print(pressureSensorUnits,2);
  digitalWrite(7, HIGH);

  //Temp Sensor 1
  Serial.print(",");
  Serial.print(temp1SensorUnits,2);
  digitalWrite(4, HIGH);

  //Temp Sensor 2
  Serial.print(",");
  Serial.print(temp2SensorUnits,2);
  digitalWrite(5, HIGH);

  //Accelerometer
  Serial.print(",");
  Serial.print(sensorUnitsX,3);
  Serial.print(",");
  Serial.print(sensorUnitsZ,3);
  digitalWrite(9, HIGH);

  Serial.println();

  //delay(50);

  

}
