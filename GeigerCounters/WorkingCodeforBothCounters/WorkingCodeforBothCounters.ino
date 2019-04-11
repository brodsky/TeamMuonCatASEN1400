///　Digital I/O PIN Settings　///
int counter1SignPin = 2; 
int counter1NoisePin = 4;

int counter2SignPin = 10; 
int counter2NoisePin = 8; 

const double alpha = 53.032; // cpm = uSv x alpha

float counter1Rad = 0;
float counter2Rad = 0;

int tempC1 = 0;
int tempC2 = 0;


int counter1SignCount = 0; //Counter for Radiation Pulse
int counter2SignCount = 0;
int counter1NoiseCount = 0; //Counter for Noise Pulse
int counter2NoiseCount = 0;

int counter1SignOn = 0; //Lock flag for Radiation Pulse
int counter2SignOn = 0;
int counter1NoiseOn = 0; //Lock flag for Noise Puls
int counter2NoiseOn = 0;

int index = 0;
int counter1CPM=0;
int counter2CPM=0;
unsigned int  mult;

int muonCount = 0;
int muonCPM = 0;

#define AVG_PERIOD  15000
#define ONE_MINUTE  60000

void setup()
{
  //Serial setup
  //9600bps
  Serial.begin(9600);

  //PIN setting for Radiation Pulse
  pinMode(counter1SignPin, INPUT);
  digitalWrite(counter1SignPin, HIGH);
  pinMode(counter2SignPin, INPUT);
  digitalWrite(counter2SignPin, HIGH);

  //PIN setting for Noise Pulse
  pinMode(counter1NoisePin, INPUT);
  digitalWrite(counter1NoisePin, HIGH);
   pinMode(counter2NoisePin, INPUT);
  digitalWrite(counter2NoisePin, HIGH);

  //CSV-formatting for serial output (substitute , for _)
  Serial.println("Time(ms),C1_Sign, C1_CPM, C1_uSv, C2_Sign, C2_CPM, C2_uSv MuonCount, muonCPM");
  mult = ONE_MINUTE/AVG_PERIOD;

 
}

void loop()
{
  static unsigned long then;
  unsigned long now = millis();
  // Raw data of Radiation Pulse: Not-detected -> High, Detected -> Low
  int counter1Sign = digitalRead(counter1SignPin);
  int counter2Sign = digitalRead(counter2SignPin);

  // Raw data of Noise Pulse: Not-detected -> Low, Detected -> High
  int counter1Noise = digitalRead(counter1NoisePin);
  int counter2Noise = digitalRead(counter2NoisePin);

  //Radiation Pulse normally keeps low for about 100[usec]
  if (counter1Sign == 0 && counter1SignOn == 0)
  { 
    counter1SignOn = 1;
    counter1SignCount++;
    tempC1 = 1;
    
  } else if (counter1Sign == 1 && counter1SignOn == 1) {
    counter1SignOn = 0;
  }

  //Noise Pulse normally keeps high for about 100[usec]
  if (counter1Noise == 1 && counter1NoiseOn == 0)
  { 
    counter1NoiseOn = 1;
    counter1NoiseCount++;
  } else if (counter1Noise == 0 && counter1NoiseOn == 1) {
    counter1NoiseOn = 0;
  }

  
  //Radiation Pulse normally keeps low for about 100[usec]
  if (counter2Sign == 0 && counter2SignOn == 0)
  { 
    counter2SignOn = 1;
    counter2SignCount++;
    tempC2 = 1;
  } else if (counter2Sign == 1 && counter2SignOn == 1) {
    counter2SignOn = 0;
  }

  //Noise Pulse normally keeps high for about 100[usec]
  if (counter2Noise == 1 && counter2NoiseOn == 0)
  { 
    counter2NoiseOn = 1;
    counter2NoiseCount++;
  } else if (counter2Noise == 0 && counter2NoiseOn == 1) {
    counter2NoiseOn = 0;
  }

  if(tempC1 == 1 && tempC1 == tempC2){
    if(counter1NoiseCount == 0 && counter2NoiseCount == 0){
    muonCount++;
    }
  }
  tempC1 = 0;
  tempC2 = 0;
 
   if (now-then > AVG_PERIOD) {
      then = now;
      Serial.print(now);
      Serial.print(",");
  
      if (counter1NoiseCount == 0)
        {
           counter1CPM = counter1SignCount * mult;
           counter1Rad = counter1CPM/alpha;
      Serial.print(counter1SignCount);
      Serial.print(",");
      Serial.print(counter1CPM);
        Serial.print(",");
        Serial.print(counter1Rad);
        Serial.print(",");
        
    
        }
        else{
          Serial.print("0");
        Serial.print(",");
        Serial.print("0");
          Serial.print(",");
            Serial.print("0.0");
          Serial.print(",");
        }
       if(counter2NoiseCount == 0){
          counter2CPM = counter2SignCount * mult;
           counter2Rad = counter2CPM/alpha;
          Serial.print(counter2SignCount);
          Serial.print(",");
          Serial.print(counter2CPM);
            Serial.print(",");
              Serial.print(counter2Rad);
        Serial.print(",");
        
       }
       else{
         Serial.print("0");
        Serial.print(",");
        Serial.print("0");
          Serial.print(",");
          Serial.print("0.0");
          Serial.print(",");
        
       }
       
        muonCPM = muonCount * mult;

        Serial.print(muonCount);
        Serial.print(",");
        Serial.println(muonCPM);
       
       

    //Initialization for next 10000 loops
   
    counter1SignCount = 0;
    counter2SignCount = 0;
    counter1NoiseCount = 0;
    counter2NoiseCount = 0;
    counter1CPM = 0;
    counter2CPM = 0;
    muonCount = 0;
    muonCPM = 0;
   
  }
}