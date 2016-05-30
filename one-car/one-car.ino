#include <Servo.h>

// 서보 모터 컨트롤
Servo myservo;
int SLEFT = 160;
int SRIGHT = 20;
int SMOTOR = 9;
int SDELAY = 500;
// 초음파 센서
int TRIG = A0;
int ECHO = A1;

int ENA = 5;
int ENB = 6;

//모터A 컨트롤
int IN1 = 3;
int IN2 = 2;

//모터B 컨트롤
int IN3 = 12;
int IN4 = 13;

// 속도
int SPEED = 255;
int TURN_DELAY = 300;
int GO_DELAY = 100;

void setup() {
 Serial.begin(9600);
 //  pinMode(upButton, INPUT);
 //  pinMode(downButton, INPUT);
 pinMode(TRIG, OUTPUT);
 pinMode(ECHO, INPUT);
 pinMode(IN1, OUTPUT);
 pinMode(IN2, OUTPUT);
 pinMode(IN3, OUTPUT);
 pinMode(IN4, OUTPUT);
 analogWrite(ENA, SPEED);
 analogWrite(ENB, SPEED);

 myservo.attach(SMOTOR);  // attaches the servo on pin 9 to the servo object

}

bool search() {
  //0~60 = LEFT
  //60~180 = RIGHT
  Serial.println("Searching Start...");
  
  myservo.write(SLEFT); //Search LFET
  delay(SDELAY);  
  unsigned int LD_MAX = getDistance();
  Serial.println(LD_MAX);
  myservo.write(SRIGHT); //Search RIGHT  
  delay(SDELAY);
  unsigned int RD_MAX = getDistance();
  Serial.println(RD_MAX);
  
  myservo.write(90); //Search LFET
  delay(SDELAY);
  return (RD_MAX > LD_MAX);//TEST
}


void loop() {

 unsigned int distance = getDistance();
 Serial.println(distance);
 if (distance < 15)
 {
   stopAllMotor();
   bool is_right = search();
   if ( is_right == true ) //right
   {
    Serial.println("Turn right");
    turnRight();
   }
   else //left
   {
    Serial.println("Turn left"); // left
    turnLeft();
   }
   delay(TURN_DELAY);//turn delay
 }
 else {
   bothMotorStart();
   Serial.println("go ahead");
   delay(GO_DELAY);
 }

}

/*
 void speedUp()
 {
 if(SPEED != 255)
 {
   SPEED += 5;
 }
 }

 void speedDown()
 {
 if(SPEED != 0)
 {
   SPEED -= 5;
 }
 }
*/

void trig(void)
{
 digitalWrite(TRIG, HIGH);
 delay(10);
 digitalWrite(TRIG, LOW);
}

unsigned long echo(void)
{
 while (digitalRead(ECHO) == LOW);
 unsigned long start_time = micros();
 while (digitalRead(ECHO) == HIGH);
 return micros() - start_time;
}

unsigned long getDistance(void)
{
 trig();
 unsigned long echo_time = echo();
 //Serial.println(echo_time);
 return echo_time * 17 / 1000;
}

//모터A,B 정회전
void bothMotorStart()
{
 digitalWrite(IN1, HIGH);
 digitalWrite(IN2, LOW);
 digitalWrite(IN3, HIGH);
 digitalWrite(IN4, LOW);
}

//모터A,B Stop
void stopAllMotor()
{
 digitalWrite(IN1, LOW);
 digitalWrite(IN2, LOW);
 digitalWrite(IN3, LOW);
 digitalWrite(IN4, LOW);
}

//모터A 역회전, 모터B 정회전
void turnLeft()
{
 digitalWrite(IN1, LOW);
 digitalWrite(IN2, HIGH);
 digitalWrite(IN3, HIGH);
 digitalWrite(IN4, LOW);
}

//모터A 정회전, 모터B 역회전
void turnRight()
{
 digitalWrite(IN1, HIGH);
 digitalWrite(IN2, LOW);
 digitalWrite(IN3, LOW);
 digitalWrite(IN4, HIGH);
}
