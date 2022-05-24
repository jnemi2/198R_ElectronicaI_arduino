#include <LiquidCrystal_I2C.h>
#define TRIG 8
#define ECHO 9
#define N_SAMPLES 5

LiquidCrystal_I2C lcd(0x27,16,2);

float getDistance();
float measure();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  float distance = measure();
  lcd.clear();
  Serial.print(distance);
  Serial.print("\n");
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
  float echoTime;           //variable to store the time it takes for a ping to bounce off an object
  float calculatedDistance = -1; //variable to store the distance calculated from the echo time

  //send out an ultrasonic pulse that's 10ms long
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  echoTime = pulseIn(ECHO, HIGH); //use the pulsein command to see how long it takes for the
                                     //pulse to bounce back to the sensor

  calculatedDistance = echoTime / 58.0; //calculate the distance of the object that reflected the pulse (half the bounce time multiplied by the speed of sound)

  return calculatedDistance; //send back the distance that was calculated
}
