int counterASign;
int counterBSign;
int counterBNoise;
int counterANoise;

const int counterASignPin = 2;
const int counterANoisePin = 3;
const int counterBSignPin = 5;
const int counterBNoisePin = 6;

int signA;
int noiseA;
int signB;
int noiseB;

int counterACheck= 0;
int counterBCheck= 0;
int counterACPM = 0;
int counterBCPM = 0;

int i=0;

int muonCount = 0;
int muonCPM = 0;

 //time
 uint32_t timeStamp = 0;
 unsigned long t = 0;
 uint32_t startTime = 0;
 
void setup() {
  Serial.begin(9600);
  pinMode(counterANoisePin, INPUT);
  pinMode(counterASignPin, INPUT);  
  pinMode(counterBNoisePin, INPUT);
  pinMode(counterBSignPin, INPUT);

  digitalWrite(counterANoisePin, HIGH);
  digitalWrite(counterASignPin, HIGH);
  digitalWrite(counterBNoisePin, HIGH);
  digitalWrite(counterBSignPin, HIGH);
  Serial.print("New Data Entry");

 // Serial.print("TIME,SIGNA,NOISEA,SIGNB,NOISEB")
 Serial.print("Time,counterACPM,counterBCPM,muonCPM,noiseA,noiseB");
  Serial.println();
  
}

void loop() {

  timeStamp = millis();
  startTime = millis();

  while(i < 30){
    counterACheck = digitalRead(counterASignPin);
    counterBCheck = digitalRead(counterBSignPin);
    if(counterACheck > 0){
      signA++;
    }
    if (counterBCheck > 0){
      signB++;
    }
    if(counterACheck > 0 && counterBCheck >0){
      muonCount++;
    }
    i = millis();
    i = i - startTime;
    i = i/1000;
    t = millis();
    t = t/1000;    
  }
  counterACPM = signA*2;
  counterBCPM = signB*2;
  muonCPM = muonCount*2;
  
 // signA = digitalRead(counterASignPin);
  noiseA = digitalRead(counterANoisePin);
  //signB = digitalRead(counterBSignPin);
  noiseB = digitalRead(counterBNoisePin);


  Serial.print(timeStamp);
  Serial.print(",");
  Serial.print(counterACPM);
  Serial.print(",");
  Serial.print(counterBCPM);
  Serial.print(",");
  Serial.print(muonCPM);
 Serial.print(",");
 Serial.print(noiseA);
 Serial.print(",");
 Serial.print(noiseB);
  Serial.println();
}
