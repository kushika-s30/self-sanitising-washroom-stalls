#include <Servo.h>
int triggerpin1 = 9;
int echopin1 = 10;
int triggerpin2 = 11;
int echopin2= 12;


int door_status = 0;
int autolock=0;
int finished=0;

Servo myservo;

void setup() 
{
  Serial.begin(9600);
  myservo.attach(8);
  myservo.write(0);
  pinMode(triggerpin1, OUTPUT);
  pinMode(echopin1, INPUT);
  pinMode(triggerpin2, OUTPUT);
  pinMode(echopin2, INPUT);
  
}

void loop() 
{                 
    
    long cm1,cm2;
    cm1 =ultrasonic(triggerpin1,echopin1);
    cm2 =ultrasonic(triggerpin2,echopin2);
    delay(1000);
//-----------------------------------------------------------    
  if(cm1<10)
  { 
    delay(1000);
    if((door_status==0))
       {
       myservo.write(90);                 
       Serial.println("OPEN NOW");
       autolock=1;
       door_status=1;
      }
   
  }
  
  if(cm2<10)
  {
    delay(1000);
    if((door_status==1))
     {
       myservo.write(90);                 
       Serial.println("YOU CAN LEAVE NOW!");
       finished=1;
       autolock=1;
       door_status=0;  
       
    }
  }


 if(autolock==1)
  {

    if(finished==1)
      {
        delay(5000);
        myservo.write(-90);
        Serial.println("EMPTY");
        finished=0;
      }
      else
       {
        delay(5000);
        myservo.write(-90);
        Serial.println("OCCUPIED"); 
       }
       
     autolock=0;
  }
  
 
}


int ultrasonic(int trigger, int echo)
{
  long duration,distance;
  digitalWrite(trigger,HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigger, LOW);
  duration=pulseIn(echo, HIGH);
  distance =(duration/2)/29.1;
  return distance;
 
}
