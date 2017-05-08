/*  ONE TANK FREE MOVE 
    ---REFERS---
https://www.gitbook.com/book/smartarduino/user-manual-for-2-way-motor-16-way-servos-shield/details
http://www.smartarduino.com/view.php?id=94895
http://playground.arduino.cc/Main/AdafruitMotorShield
http://homediyelectronics.com/projects/arduino/arduinoprogramminghcsr04withinterrupts/?p=4

UNO - ATMega328-compatibles
 */
#include "Arduino.h"

#define MOT_SPD_MAX 250
#define MOT_DLY_MAX 10

//#define DEBUG 1

//#define DBG(msg) Serial.printf( "\tB %d\tL %d\tR %d\tA %d\tT %d\tD %f" , dist_btm, dist_lft, dist_rgt, angle_dst, angle_rot, MOT_DELAY, msg)
#ifdef DEBUG 
#define DBG(msg) {Serial.print("\tB ");Serial.print(dist_btm);\
    Serial.print("\tL ");Serial.print(dist_lft);\
    Serial.print("\tR ");Serial.print(dist_rgt);\
    Serial.print("\tA ");Serial.print(angle_dst);\
    Serial.print("\tT ");Serial.print(angle_rot);\
    Serial.print("D ");Serial.print(MOT_DELAY);\
    Serial.println(msg);\
}
#else
#define DBG
#endif

//MOTOR
#define MOT_LFT	    6      // MOTOR A - PIN 11 POWER 
#define DIR_LFT     7      // MOTOR A - PIN 7  DIRECTION 
#define MOT_RGT     11     // MOTOR B - PIN 6  POWER 
#define DIR_RGT     12     // MOTOR B - PIN 12 DIRECTION 

#define UNSET       -1

#define LIMIT_FRONT     30  // CM
#define LIMIT_BOTTOM    14  // CM
#define LIMIT_DIST      12.0  // CM distance b/w left&right 

//BOARD SPECIFIC
/// 초음파 센서 HC-SR04
#define TRIG_RGT    4
#define ECHO_RGT    5
#define TRIG_LFT    2
#define ECHO_LFT    3
#define TRIG_BTM    8
#define ECHO_BTM    9

#include <PinChangeInt.h>

void setup();
void loop();
void sensor_dist();
void direction();
void go();
void stop(int dummy);
void echo_btm();
void echo_lft();
void echo_rgt();
//void dbg(const char * msg);

void turn(int theta);
void front();
void back();

int MOT_DELAY = MOT_DLY_MAX;  // MOROT DELAY
int MOT_SPD_LFT = MOT_SPD_MAX;  // MOROT SPEED LEFT
int MOT_SPD_RGT = MOT_SPD_MAX;  // MOROT SPEED RIGHT

volatile int stat_btm = LOW;    // DIRECTION STAT BOTTOM
volatile int stat_lft = LOW;    // BLOCK STAT LEFT
volatile int stat_rgt = LOW;    // BLOCK STAT RIGHT

volatile int angle_dst = 0;  // difference LEFT - RIGHT
double angle_rot = 0;// Rotation Angle to right

volatile long echo_btm_beg = 0; // start of echo pulse 
volatile long echo_btm_end = 0; // end of echo pulse 
volatile long echo_btm_dur = 0; // duration of echo pulse 
volatile int dist_btm = UNSET;  // distance of echo pulse 

volatile long echo_lft_beg = 0; // start of echo pulse 
volatile long echo_lft_end = 0; // end of echo pulse 
volatile long echo_lft_dur = 0; // duration of echo pulse 
volatile int dist_lft = UNSET;  // distance of echo pulse 

volatile long echo_rgt_beg = 0; // start of echo pulse 
volatile long echo_rgt_end = 0; // end of echo pulse 
volatile long echo_rgt_dur = 0; // duration of echo pulse 
volatile int dist_rgt = UNSET;  // distance of echo pulse 

void setup() 
{
    // MOTOR NO NEED TO SETUP ANALOG OUTPUT
    pinMode(DIR_LFT, OUTPUT);
    pinMode(DIR_RGT, OUTPUT);
    delay(1);
    digitalWrite(DIR_LFT, LOW);
    digitalWrite(DIR_RGT, HIGH);

    //SENSOR
    pinMode(TRIG_BTM, OUTPUT);
    pinMode(TRIG_LFT, OUTPUT);
    pinMode(TRIG_RGT, OUTPUT);

    //SETUP ISR
    pinMode(ECHO_BTM, INPUT_PULLUP);
    pinMode(ECHO_LFT, INPUT_PULLUP);
    pinMode(ECHO_RGT, INPUT_PULLUP);

    PCintPort::attachInterrupt(ECHO_BTM, echo_btm, CHANGE); 
    PCintPort::attachInterrupt(ECHO_LFT, echo_lft, CHANGE); 
    PCintPort::attachInterrupt(ECHO_RGT, echo_rgt, CHANGE); 
    Serial.begin(9600);
}

void loop() 
{
    sensor_dist();
    //STOP WHEN NO SENSOR ERROR //INTERRUPT Defense ifelse
    if ( stat_lft == UNSET || stat_rgt == UNSET || stat_btm == UNSET ) {
        return;
    } else {
        direction();
        go();
    }

    //TEST
    //DBG("HELLOOO");
    //delay(1000);

    //stop(3000);
    //front();
    //stop(3000);
    //back();
    //stop(3000);

    //turn(20);
    //go();
    //stop(3000);
    //turn(-20);
    //go();
    //stop(3000);
}

void echo_btm()
{
    switch (digitalRead(ECHO_BTM))
    {
        case HIGH:  //pulse begin
            echo_btm_end = 0;
            dist_btm = stat_btm = UNSET;
            echo_btm_beg = micros();
            break;

        case LOW:   //pulse end
            echo_btm_end = micros();                  
            echo_btm_dur = echo_btm_end - echo_btm_beg;
            dist_btm = ((float)(346 * echo_btm_dur) / 10000) / 2;
            stat_btm = (dist_btm > LIMIT_BOTTOM);
            break;
    }
}

void echo_lft()
{
    switch (digitalRead(ECHO_LFT))
    {
        case HIGH:  //pulse begin
            echo_lft_end = 0;
            dist_lft = stat_lft = UNSET;
            echo_lft_beg = micros();
            break;
        case LOW:   //pulse end
            echo_lft_end = micros();                  
            echo_lft_dur = echo_lft_end - echo_lft_beg;
            dist_lft = ((float)(346 * echo_lft_dur) / 10000) / 2;
            stat_lft = (dist_lft < LIMIT_FRONT);
            angle_dst = (dist_lft - dist_rgt);
            break;
    }
}

void echo_rgt() {
    switch (digitalRead(ECHO_RGT))
    {
        case HIGH:  //pulse begin
            echo_rgt_end = 0;
            dist_rgt = stat_rgt = UNSET;
            echo_rgt_beg = micros();
            break;
        case LOW:   //pulse end
            echo_rgt_end = micros();                  
            echo_rgt_dur = echo_rgt_end - echo_rgt_beg;
            dist_rgt = ((float)(346 * echo_rgt_dur) / 10000) / 2;
            stat_rgt = (dist_rgt < LIMIT_FRONT);
            angle_dst = (dist_lft - dist_rgt);
            break;
    }
}

void sensor_dist()
{
    //LOW>HIGH>LOW
    digitalWrite(TRIG_BTM, LOW);
    digitalWrite(TRIG_LFT, LOW);
    digitalWrite(TRIG_RGT, LOW);
    delay(2);   //min 5us delayMicroseconds(5);
    digitalWrite(TRIG_BTM, HIGH);
    digitalWrite(TRIG_LFT, HIGH);
    digitalWrite(TRIG_RGT, HIGH);
    delay(2);   //min 10us delayMicroseconds(5);
    digitalWrite(TRIG_BTM, LOW);
    digitalWrite(TRIG_LFT, LOW);
    digitalWrite(TRIG_RGT, LOW);
}

void direction()
{
    //INIT SPEED
    MOT_SPD_LFT = MOT_SPD_RGT = MOT_SPD_MAX;
    MOT_DELAY = MOT_DLY_MAX;
    angle_rot = 0;//Rotation 0

    //PRIORITY 역주행 > 회전
    // 역주행
    if ( stat_btm > 0 ) {            
        //BOTTOM EMPTY & BACKWARD
        digitalWrite(DIR_LFT, HIGH);
        digitalWrite(DIR_RGT, LOW);
        DBG(" BOTTOM EMPTY & BACKWARD");
        MOT_DELAY = MOT_DLY_MAX*120;//1 SEC BACK RIGHT TURN
        MOT_SPD_LFT = MOT_SPD_MAX*0.8;
        MOT_SPD_RGT = MOT_SPD_MAX*0.2;
        return;//Immediate move
    }

    angle_rot = atan(angle_dst/LIMIT_DIST)*180.0/M_PI;
    // TODO : 반사주행 : 180-2*angle = 2*(90-theta)
    if ( stat_lft > 0 && stat_rgt > 0 ) {
        angle_rot > 0 ? turn(180-2*angle_rot) : turn(-1*(180+2*angle_rot));
        return;
    }

    // TODO 평행주행 : 90-angle
    // turn to longer distance, HIGH = BLOCK, LOW = OPEN
    //angle_rot > 0 ? turn(angle_dst,90-angle_rot) : turn(angle_dst,90+angle_rot);
    if ( stat_lft > 0 ) {
        turn(-20);
        return;
    }

    if ( stat_rgt > 0 ) {
        turn(20);
        return;
    }

    if ( stat_btm == 0 ) {
        //BOTTOM OK & FORWARD
        digitalWrite(DIR_LFT, LOW);
        digitalWrite(DIR_RGT, HIGH);
        //DBG(" \tFORWARD\n");
    } 

}


void stop(int dummy)
{
    analogWrite(MOT_LFT, LOW);
    analogWrite(MOT_RGT, LOW);
    delay(dummy);
}
void go()
{
    //GEARED LOOP
    //for (int pos = 0 ; pos <= 225; pos += 5) {
    //analogWrite(MOT_LFT, pos);
    //analogWrite(MOT_RGT, pos);

#ifndef DEBUG
    analogWrite(MOT_LFT, MOT_SPD_LFT);
    analogWrite(MOT_RGT, MOT_SPD_RGT);
#endif
    delay(MOT_DELAY);
}

void front()
{
    digitalWrite(DIR_LFT, LOW);
    digitalWrite(DIR_RGT, HIGH);
    delay(100);
    analogWrite(MOT_LFT, MOT_SPD_MAX);
    analogWrite(MOT_RGT, MOT_SPD_MAX);
    delay(1000);
}

void back()
{
    digitalWrite(DIR_LFT, HIGH);
    digitalWrite(DIR_RGT, LOW);
    delay(100);
    analogWrite(MOT_LFT, MOT_SPD_MAX);
    analogWrite(MOT_RGT, MOT_SPD_MAX);
    delay(1000);
}

//theta 0~360
void turn(int theta)
{
    if ( theta == 0 ) {
        DBG(" TURN ZERO");
        return;
    }

    if ( theta > 0 ) {
        //TURN TO LEFT
        MOT_DELAY=theta*10;
        digitalWrite(DIR_LFT, HIGH);
        digitalWrite(DIR_RGT, HIGH);
        MOT_SPD_LFT = MOT_SPD_MAX*0.8;
        MOT_SPD_RGT = MOT_SPD_MAX*0.6;
        DBG(" GO LEFT");
    } else {
        //TURN TO RIGHT
        MOT_DELAY=theta*-10;
        digitalWrite(DIR_LFT, LOW);
        digitalWrite(DIR_RGT, LOW);
        MOT_SPD_LFT = MOT_SPD_MAX*0.6;
        MOT_SPD_RGT = MOT_SPD_MAX*0.8;
        DBG(" GO RIGHT");
    }

    if ( MOT_DELAY > 3000 ) MOT_DELAY = 3000;
}
/*
  void dbg(const char * msg)
  {
#ifdef DEBUG_MODE
Serial.print("\tB ");Serial.print(dist_btm); 
Serial.print("\tL ");Serial.print(dist_lft); 
Serial.print("\tR ");Serial.print(dist_rgt); 
Serial.print("\tA ");Serial.print(angle_dst); 
Serial.print("\tT ");Serial.print(angle_rot); 
Serial.print("D ");Serial.print(MOT_DELAY); 
Serial.println(msg);
#endif
}
 */

/* multiple pulse in not working example...
 * no working code !!

// ECHO_BTM 이 HIGH를 유지한 시간/2 T=실온25도 가정
// v * s = (331.5 + 0.60714*T) x t / 2 = 347 * t / 2
// UNIT : cm, us = 100 /1000000

void echo()
{
digitalWrite(TRIG_BTM, LOW);
digitalWrite(TRIG_LFT, LOW);
digitalWrite(TRIG_RGT, LOW);
delay(1);   //min 5us delayMicroseconds(5);
digitalWrite(TRIG_BTM, HIGH);
digitalWrite(TRIG_LFT, HIGH);
digitalWrite(TRIG_RGT, HIGH);
delay(1);   //min 10us delayMicroseconds(5);
digitalWrite(TRIG_BTM, LOW);
digitalWrite(TRIG_LFT, LOW);
digitalWrite(TRIG_RGT, LOW);

dist_btm = UNSET;
echo_btm_dur = pulseIn(ECHO_BTM, HIGH);
dist_btm = ((float)(346 * echo_btm_dur) / 10000) / 2;
stat_btm = (dist_btm < LIMIT_BOTTOM);
Serial.print(dist_btm); 
//Serial.println(" BOTTOM\n");

dist_lft = UNSET;
echo_lft_dur = pulseIn(ECHO_LFT, HIGH);
dist_lft = ((float)(346 * echo_lft_dur) / 10000) / 2;
stat_lft = (dist_lft < LIMIT_FRONT);
Serial.print(dist_lft); 
Serial.println(" LEFT \n");

dist_rgt = UNSET;
echo_rgt_dur = pulseIn(ECHO_RGT, HIGH);
dist_rgt = ((float)(346 * echo_rgt_dur) / 10000) / 2;
stat_rgt = (dist_rgt < LIMIT_FRONT);
Serial.print(dist_rgt); 
Serial.println(" RIGHT \n");
}
 */
