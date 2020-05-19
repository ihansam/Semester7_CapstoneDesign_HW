#include <LiquidCrystal_I2C.h>    // LCD 라이브러리
LiquidCrystal_I2C lcd(0x27,16,2);

// Pin map
const int redPin = 9;   
const int greenPin = 10;
const int bluePin = 11;
const int XPin = A1;
const int YPin = A0;
const int switchPin = 4;

// LED 색(꺼짐,파랑,빨강,초록,노랑,흰색, 꺼짐) 열거형과, 그에 대한 RGB 값, 모니터에 출력할 string
enum color {BLUE, RED, GREEN, YELLOW, WHITE, LED_OFF};
int colorRGB[6][3] = {{0,0,255}, {255,0,0}, {0,127,0}, {255,127,0}, {255,255,255}, {0,0,0}};
char showstate[6][15] = {"UP: blue", "DOWN: red", "RIGHT: green",\
                        "LEFT: yellow", "MIDDLE: white", "PUSHED: OFF"};

void setup()
{
  Serial.begin(9600);
  lcd.init();                         // LCD 초기화
  lcd.backlight();
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(switchPin, INPUT_PULLUP);   // 스위치 핀: 내부 풀업 입력
}

bool READjoystick(int &x, int &y) // 조이스틱 센서 값을 읽어
{                                 // x, y 값을 저장하고
  x = analogRead(XPin);           // 스틱이 눌렸는지 여부를 반환하는 함수
  y = analogRead(YPin);
  return digitalRead(switchPin); // 누른 상태일 때 false 반환
}

void PRINTjoy(int x, int y)       // 조이스틱 좌표를 받아
{                                 // 모니터와 LCD에 출력하는 함수
  Serial.print("X = ");
  Serial.print(x);
  Serial.print(", Y = ");
  Serial.print(y);
  lcd.clear();                    // 화면 지우기
  lcd.setCursor(0, 0);            // 윗줄 x좌표 출력
  lcd.print("X = ");        
  lcd.print(x);          
  lcd.setCursor(0, 1);            // 아래줄 y좌표 출력
  lcd.print("Y = ");    
  lcd.print(y);
}

void LEDcontrol(int x, int y, bool sel)
{
  int idx;                        // x, y, sel에 따라 LED를 제어하기 위한 index
  if (sel){                       // 버튼이 눌리지 않았다면
    if(x<300) idx = BLUE;
    else if(x>700) idx = RED;
    else{
      if(y<300) idx = GREEN;
      else if(y>700) idx = YELLOW;
      else idx = WHITE;
    }
  }
  else idx = LED_OFF;             // 버튼이 눌렸다면

  analogWrite(redPin, colorRGB[idx][0]);    // idx에 따른 LED 색 제어
  analogWrite(greenPin, colorRGB[idx][1]);
  analogWrite(bluePin, colorRGB[idx][2]);
  Serial.print("\t");
  Serial.println(showstate[idx]);           // idx에 따른 현재 상태 모니터에 출력
}

void loop() {
  int x, y;
  bool sel = READjoystick(x, y);  // 조이스틱 좌표를 읽고 버튼 눌림 여부를 확인한다
  PRINTjoy(x, y);                 // 좌표를 모니터와 LCD에 출력한다
  LEDcontrol(x, y, sel);          // 조이스틱 좌표와 눌림 여부에 따라 LED 색을 제어한다

  delay(200);
}
