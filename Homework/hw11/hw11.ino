// 블루투스 모듈
#include <SoftwareSerial.h>
int blueTx=11; //Tx (보내는핀 설정)
int blueRx=10; //Rx (받는핀 설정)
SoftwareSerial mySerial(blueTx, blueRx); 
// 서보 모터
#include <Servo.h>
Servo servo;
int pos = 90;           // 초기 각도

String myString="";     // 받는 문자열

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  mySerial.write("Enter the up or down\n"); // 초기 스마트폰 출력
  mySerial.write("up = angle + 15\n");
  mySerial.write("down = angle - 15");
  servo.attach(24, 600, 2400);
  servo.write(pos);
  delay(1000);
  servo.detach();
}

void loop() {
  while(mySerial.available())   // 스마트폰에 문자가 입력되면
  {
    char myChar = (char)mySerial.read();
    myString+=myChar;           // 한 글자씩 myString에 저장
    delay(5);                   //수신 문자열 끊김 방지
  }
  if(!myString.equals(""))      // myString에 문자열이 생겼을 때
  {
    if(myString=="up" && pos<180)   // 문자열이 up이고 각도가 180도 미만일 때
    {
      servo.attach(24, 600, 2400);  // 서보모터 각도롤 15도 키움
      for (int i = pos+1; i<=pos+15; ++i){
        servo.write(i);
        delay(15);
      }
      servo.detach();
      pos += 15;                    
      mySerial.write("+15 ");       // 스마트폰에 +15 현재각도 출력
      mySerial.print(pos);
    }
    else if(myString=="down" && pos>0)  // 문자열이 down이고 각도가 0도 초과일 때
    {
      servo.attach(24, 600, 2400);    // 서보모터 각도를 15도 줄임
      for (int i = pos-1; i>=pos-15; --i){
        servo.write(i);
        delay(15);
      }      
      servo.detach();
      pos -= 15;                      
      mySerial.write("-15 ");         // 스마트폰에 -15 현재각도 출력
      mySerial.print(pos);
    }
    else                              // 입력 문자열이 up 또는 down이 아니면 출력
    {
      mySerial.write("wrong operation!!");
    }
    
    myString=""; //myString 변수값 초기화
  }
}
