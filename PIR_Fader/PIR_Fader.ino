/*
 * PIR Triggered LED Fader
 */
 
#define fadePin 0 //PWM Pin on ATtiny85
#define pirPin 2 //Input Pin on ATtiny85

int pirState = LOW;
int stateCheck = LOW;

void setup()
{
  pinMode(fadePin, OUTPUT);
  pinMode(pirPin, INPUT);
  analogWrite(fadePin, 0); //start off
  
  //Serial.begin(9600);
}

void fadeUp()
{
  for(int val = 0; val <= 255; val+=5)
  {
    analogWrite(fadePin, val);
    delay(30);
  }
}

void fadeDown()
{
  for(int val = 255; val >= 0; val -=5)
  {
    analogWrite(fadePin, val);
    delay(30);
  }
}

void loop()
{
  stateCheck = digitalRead(pirPin);
  if(stateCheck == HIGH)
  {
    if(pirState == LOW)
    {
      fadeUp();
      pirState = HIGH;
      //delay(5000); //minimum on time
      //Serial.println("Motion");
    }
  }
  else
  {
    //fadeout here
    if(pirState == HIGH)
    {
      fadeDown();
      pirState = LOW;
      //Serial.println("Motion ended");
    }
  }
} 
