/*
 * PIR Triggered LED Fader V2
 */
 
#define fadePin 3//PWM Pin on ATtiny85
#define pirPin 7 //Input Pin on ATtiny85
#define maxOn 252 //must be multiple of upSpeed
#define minOn 0
#define upSpeed 6 //multiples of x to remove flashes
#define downSpeed 2
#define waitOn 15000 //how many milliseconds to remain on

int pirState = LOW;
int stateCheck = LOW;
int fadeVal = 0;

void setup()
{
  pinMode(fadePin, OUTPUT);
  pinMode(pirPin, INPUT);
  analogWrite(fadePin, fadeVal); //at fadeVal
  
  //Serial.begin(9600); //for debugging
}

void fadeUp()//should always fade all the way up
{
  while(fadeVal < maxOn)
  {
    analogWrite(fadePin, fadeVal);
    fadeVal += upSpeed;
    //Serial.print("fadeVal = ");
    //Serial.println(fadeVal);
    delay(30);
  }
  fadeVal = maxOn;
  analogWrite(fadePin, fadeVal);//must be done outside or flashes at max
  //Serial.print("fadeVal = ");
  //Serial.println(fadeVal);
}

void fadeDown()//can be partially 'interupted' by only doing on interation at a time
{
  if(fadeVal > minOn)
  { 
    analogWrite(fadePin, fadeVal);
    fadeVal -= downSpeed;
    //Serial.print("fadeVal = ");
    //Serial.println(fadeVal);
    delay(30);
  }
  else
  {
    fadeVal = minOn;
    analogWrite(fadePin, minOn);//to turn the lights all the way to minOn
  } //might be a better way to do this, not sure, want to just have the arduino in low power and not constanly sending
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
      delay(waitOn); //minimum on time
      //Serial.println("Motion");
    }
  }
  else
  {
    //fadeout here
    if(pirState == HIGH)
    {
      //fadeDown();
      pirState = LOW;
      //Serial.println("Motion ended");
    }
    fadeDown();
  }
} 


