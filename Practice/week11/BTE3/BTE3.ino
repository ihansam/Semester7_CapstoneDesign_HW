#include <SoftwareSerial.h>
//시리얼 통신 라이브러리 호출
int blueTx=11; //Tx (보내는핀 설정)
int blueRx=10; //Rx (받는핀 설정)
SoftwareSerial mySerial(blueTx, blueRx); 
String myString=""; //받는 문자열
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600); //블루투스 시리얼
  pinMode(13, OUTPUT); 
}
void loop() {

  while(mySerial.available())
  {
    char myChar = (char)mySerial.read();
    //mySerial int형식의 값을 char형식으로 변환
    myString+=myChar;
    delay(5); //수신 문자열 끊김 방지
  }
  if(!myString.equals(""))
  {
    Serial.println("input value: "+myString);
    if(myString.equals("on")) 
    {
      digitalWrite(13, HIGH); //LED ON
      Serial.println("ON!");
    }
    else if(myString=="off")
    {
      digitalWrite(13, LOW); //LED OFF
      Serial.println("OFF!");
    }
    else Serial.println("?");
    
    myString=""; //myString 변수값 초기화
  }

  
}
