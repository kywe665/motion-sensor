const int ledPin = 13;
const int sensorPin = 0;
const int speakerPin = 9;
const int minFrequency = 1; //1ms cycles = 500Hz
const int maxFrequency = 10; //10ms cycles = 50Hz

long prevLedBlink = 0;
long prevSpeaker = 0;
long prevAvg = 0;
int prevSensor = 0;
int ledState = LOW;
int speakerState = LOW;
int avgLight = 0;
int avgInterval = 2000;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(speakerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();
  int sensorRead = analogRead(sensorPin);
  int rate = map(sensorRead, 200, 800, minFrequency, maxFrequency);
  if(currentMillis - prevLedBlink > sensorRead){
    prevLedBlink = currentMillis;
    toggleLed();
  }
  //Serial.println("current: "+sensorRead);
  if(currentMillis - prevAvg > avgInterval){
    avgLight = (prevSensor+sensorRead)/2;
    prevAvg = currentMillis;
  }
  Serial.println(abs(avgLight-sensorRead));
  if(abs(avgLight - sensorRead) > 50){
    if(currentMillis - prevSpeaker > 1){
      prevSpeaker = currentMillis;
      pulseSpeaker();
    }
  }
  prevSensor = sensorRead;
}

void toggleLed() {
  if(ledState == LOW){
    ledState = HIGH;
  }
  else{
    ledState = LOW;
  }
  digitalWrite(ledPin, ledState);
}
void pulseSpeaker() {
  if(speakerState == LOW){
    speakerState = HIGH;
  }
  else{
    speakerState = LOW;
  }
  digitalWrite(speakerPin, speakerState);
}

