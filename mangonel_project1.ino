#include <math.h> 
#include <LiquidCrystal.h>
#include <Servo.h>
#define DB4 9
#define DB5 10
#define DB6 11
#define DB7 12
#define E 8
#define RS 7
Servo servo;
LiquidCrystal LCD(RS, E, DB4, DB5, DB6, DB7);
void setup()
{
  LCD.begin(16,2);
  servo.attach(4);
}
long cal(int trig, int echo)
{
  pinMode(trig, OUTPUT);
  digitalWrite(3, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(3, LOW);
  pinMode(2, INPUT); 
  return pulseIn(2, HIGH); 
}
void loop()
{ 
  //VerticalDistance(vd), HorizontalDistance(hd)
  //Calculating Angle
  long time = cal(6,5);
  double vd = 0.01723 * time; 
  double hd = 30; 
  double ang = vd / hd;
  double angle = atan(ang); 
  double degrees = angle * 180 / M_PI;  
  
  servo.write(degrees);
  
  //Calculating Range
  long dur = cal(3,2);
  double Range = 0.01723 * dur;
  Serial.print(Range);
  Serial.print("\n");
  
  //Calculating Velocity
  double actangle = 2 * angle;
  double sine = sin(actangle);
  double con = 9.81 * Range / sine;
  double v = sqrt(con);
  Serial.print(v);
  Serial.print("\n");
  
  //On the screen
  LCD.print("Mangonel Project");
  delay(1500);
  LCD.clear();
  LCD.print("Velocity: ");
  LCD.print(v);
  delay(1500);
  LCD.clear();
  
  LCD.print("Angle: ");
  LCD.print(degrees);
  delay(1500);
  LCD.clear();
  
  LCD.print("Distance: ");
  LCD.print(Range);
  delay(3500);
  LCD.clear();
  
}