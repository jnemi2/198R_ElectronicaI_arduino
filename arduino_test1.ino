#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#define TRIG 8
#define ECHO 9
#define N_SAMPLES 5
#define SERVO 6
#define MAX_DEGREE 180
#define MULTIPLIER 5
#define delimeter "|"

LiquidCrystal_I2C lcd(0x27,16,2);

float getDistance();
float measure();
int degree;
int direction;
Servo servo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  servo.attach(SERVO);
  servo.write(0);
  degree = 0;
  direction = 1;
  
}

void loop() {
  // put your main code here, to run repeatedly:
  degree = degree + MULTIPLIER*direction;
  servo.write(degree);
  if (degree >= MAX_DEGREE || degree <= 0)
      direction = -direction;
  float distance = measure();
  lcd.clear();
  Serial.print(-degree);
  Serial.print(delimeter);
  Serial.println((int)distance);
  lcd.print("Ang. ");
  lcd.print(degree);
  lcd.cursor(0,1);
  lcd.print("Dist ");
  lcd.print(distance);
  
  //delay(100);
}

float measure(){
  float distance = 0;
  for (int i = 0; i < N_SAMPLES; i++){
    distance += getDistance();
    delay(100);
  }
  distance = distance / N_SAMPLES;
  return distance;
}

float getDistance(){
  float echoTime;
  float calculatedDistance = -1;

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  echoTime = pulseIn(ECHO, HIGH);

  calculatedDistance = echoTime / 58.0;

  return calculatedDistance;
}
