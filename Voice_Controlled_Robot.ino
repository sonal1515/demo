#include<SoftwareSerial.h>
#include <TimerOne.h>

#define IN1 8   //leftWheel 1
#define IN2 9   //leftwheel 2
#define IN3 10  //rightwheel 1
#define IN4 11  //rightwheel 2
#define SPD 6

SoftwareSerial mySerial(2,3); //RX,TX
String String1,String2,String3;
int spacepos,distance;

int rotation=5;
unsigned int counter=0;

void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  Timer1.initialize(1000000); //set timer for 1 second
  attachInterrupt(SPD,count1,RISING)
  Timer1.attachInterrupt(timerIsr); //enable timer
  mySerial.begin(9600);

}

void loop() {
  while(mySerial.available() >0)
  {
      String1 = mySerial.readStringUntil('\n');
      spacepos = String1.indexOf(' ');

      if(spacepos!=-1)
      {
          String2 = String1.substring(spacepos + 1);
          String3 = String1.substring(0,spacepos - 1);
          distance = String3.toInt();
          t=delay_time(distance);
    
          switch (String2)
          {
            case 'forward' :
                forward();
                delay(t);
                break;
            case 'reverse' :
                reverse();
                delay(t);
                break;
            case 'left' :
                left();
                delay(t);
                break;
            case 'right' :
                right();
                delay(t);
                break;
          }
      }
      else if(String1 == "stop")
                  stoprobot();
      else
          Serial.println("Invalid Input");
  }
}

void forward() //function to move robot forward
{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW); 
  
}
void reverse() //function to move robot backwards
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
   
}
void left() //function to move robot to right
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW); 
}
void right() //function to move robot to right
{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW); 
}
void stoprobot() //function to stop robot when called
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW); 
}

void count1() //counts from speed sensor 
{ 
  counter++; // increases counter by 1
}

int delay_time(int dist)
{
  int x=(dist/(10*rotation));//assuming the circumference of bot wheel as 10 cm
  return(x*1000);
} 

void timerIsr()
{
  Timer1.detachInterrupt(); //stop timer
  rotation=(counter/20);//rotation gives RPS value because the encoder wheel has 20 holes in it
  counter=0; //reset counter to 0
  Timer1.attachInterrupt(timerIsr); //enable timer
}
