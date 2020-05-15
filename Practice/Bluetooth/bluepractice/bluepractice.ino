#include <SoftwareSerial.h>
#define RX_PIN 3          // HC의 TX에 연결
#define TX_PIN 2          // HC의 RX에 연결
#define SERIAL_BAUD 9600
#define HC_BAUD 9600


SoftwareSerial HCSerial(RX_PIN, TX_PIN);
 
void setup() {
  Serial.begin(SERIAL_BAUD);
  HCSerial.begin(HC_BAUD);
}

unsigned long prevTime = 0;
unsigned long currTime = 0;
int i = 0;
void loop() {
  currTime = millis();
  if(currTime > prevTime+1000){
    HCSerial.write(i);
    Serial.println(i);
    ++i;
    prevTime = currTime;
  }
}
