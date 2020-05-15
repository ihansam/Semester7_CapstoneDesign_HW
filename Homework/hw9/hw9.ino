#include <DHT.h>                  // 온습도센서 라이브러리
#include <LiquidCrystal_I2C.h>    // LCD 라이브러리
#define DHTPIN 2                  // 센서 핀
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27,16,2);

float temp;                       // 전역변수 온도, 습도
float humi;
const int redPin = 9;             // LED pin map
const int greenPin = 10;
const int bluePin = 11;

// 온도에 따른 LED 색에 대한 RGB 값 (파랑->초록->노랑->빨강. 센서 오류시 흰색)
int colorRGB[5][3] = {{0, 0, 255}, {0, 127, 0}, {255, 127, 0}, {255, 0, 0}, {255, 255, 255}};
// LCD에 출력할 LED 색의 이름
char colorNAME[5][7] = {"BLUE", "GREEN", "YELLOW", "RED", "WHITE"};

// 온습도 값을 읽어 모니터에 출력하는 함수
void readNprint(float &t, float &h)
{
  t = dht.readTemperature();    // 참조자를 통해 하나의 함수로
  h = dht.readHumidity();       // 온도, 습도 값 업데이트
  Serial.print("Humidity: ");   // 시리얼 모니터에 각각 출력
  Serial.print(humi); Serial.print(" %\t");
  Serial.print("Temperature: "); Serial.print(temp); Serial.println(" °C");
}

// 온도에 따라 color 인덱스를 리턴하는 함수
// 온도가 22도미만/22도이상25도미만/25도이상28도미만/28도이상/nan일 때,
// color index 0부터 4를 return (각각 파/초/노/빨/흰)
int tempTOled (float t)
{
  if(isnan(t)) return 4;    // exception handling
  else return constrain(t-19.0, 0.0, 9.0)/3;
}

// color 인덱스를 받아 LCD 화면에 온도와 색깔을 출력하는 함수
void printLCD(int idx){
  lcd.clear();              // 화면 지우기
  lcd.setCursor(0, 0);      // 윗줄 첫글자로 커서 이동
  lcd.print("Temp = ");     // 온도 출력
  lcd.print(temp);          
  lcd.setCursor(0, 1);      // 아래줄 첫글자로 커서 이동
  lcd.print("Color : ");    // 색깔 출력
  lcd.print(colorNAME[idx]);
}

void setup()
{
  lcd.init();               // LCD 초기화
  lcd.backlight();
  Serial.begin(9600);  
}

void loop()
{
  readNprint(temp, humi);                         // 온습도 센서 값을 읽는다
  int colorIdx = tempTOled(temp);                 // 온도에 따른 color index를 받아온다
  printLCD(colorIdx);                             // color index에 맞게 LCD를 표시하고,
  analogWrite(redPin, colorRGB[colorIdx][0]);     // LED 색을 출력한다
  analogWrite(greenPin, colorRGB[colorIdx][1]);
  analogWrite(bluePin, colorRGB[colorIdx][2]);
  delay(1000);
}
