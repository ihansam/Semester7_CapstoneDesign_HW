#include <Servo.h>
Servo servo;
void setup()
{
servo.attach(24, 600, 2400);
//1000,1500 으로 변경해보기
}
void loop()
{
  int pos;
  servo.write(0);
  delay(1000);
  servo.write(35);
  delay(1000);
  servo.write(60);
  delay(1000);
  servo.write(90);
  delay(1000);
  servo.write(120);
  delay(1000);
  servo.write(150);
  delay(1000);
  servo.write(180);
  delay(1000);
  servo.write(90);
  delay(1000);
  servo.write(0);
  delay(1000);
  
  
}
