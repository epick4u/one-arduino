/*  ONE TANK FREE MOVE 
    ---REFERS---
https://www.gitbook.com/book/smartarduino/user-manual-for-2-way-motor-16-way-servos-shield/details
http://www.smartarduino.com/view.php?id=94895
http://playground.arduino.cc/Main/AdafruitMotorShield
http://homediyelectronics.com/projects/arduino/arduinoprogramminghcsr04withinterrupts/?p=4

UNO - ATMega328-compatibles
 */

#include "Arduino.h"
#include <PinChangeInt.h>

#define MOT_SPD_MAX 250
#define MOT_DLY_MAX 10

//MOTOR
#define MOT_LFT	    6      // MOTOR A - PIN 11 POWER 
#define DIR_LFT     7      // MOTOR A - PIN 7  DIRECTION 
#define MOT_RGT     11     // MOTOR B - PIN 6  POWER 
#define DIR_RGT     12     // MOTOR B - PIN 12 DIRECTION 

//SENSOR
/// 초음파 센서
#define TRIG_RGT    2
#define ECHO_RGT    3
#define TRIG_LFT    4
#define ECHO_LFT    5
#define TRIG_BTM    8
#define ECHO_BTM    9
#define UNSET       -1

#define LIMIT_FRONT     25  // CM
#define LIMIT_BOTTOM    14  // CM

void setup();
void loop();
void sensor_dist();
void direction();
void go();
void echo_btm();
void echo_lft();
void echo_rgt();

void turn_rgt();
void move_back();

int MOT_DELAY = MOT_DLY_MAX;  // MOROT DELAY
int MOT_SPD_LFT = MOT_SPD_MAX;  // MOROT SPEED LEFT
int MOT_SPD_RGT = MOT_SPD_MAX;  // MOROT SPEED RIGHT

volatile int stat_btm = LOW;    // DIRECTION STAT BOTTOM
volatile int stat_lft = LOW;    // DIRECTION STAT LEFT
volatile int stat_rgt = LOW;    // DIRECTION STAT RIGHT

volatile int angle_rotate = 0;  // ROTATTION angle to LEFT

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
    digitalWrite(DIR_LFT, HIGH);
    digitalWrite(DIR_RGT, LOW);

    //SENSOR
    pinMode(TRIG_BTM, OUTPUT);
    pinMode(ECHO_BTM, INPUT);
    pinMode(TRIG_LFT, OUTPUT);
    pinMode(ECHO_LFT, INPUT);
    pinMode(TRIG_RGT, OUTPUT);
    pinMode(ECHO_RGT, INPUT);

    //SETUP ISR
    digitalWrite(ECHO_BTM, HIGH);   //the internal pullup resistor for input
    PCintPort::attachInterrupt(ECHO_BTM, echo_btm, CHANGE); 
    digitalWrite(ECHO_LFT, HIGH);   //the internal pullup resistor for input
    PCintPort::attachInterrupt(ECHO_LFT, echo_lft, CHANGE); 
    digitalWrite(ECHO_RGT, HIGH);   //the internal pullup resistor for input
    PCintPort::attachInterrupt(ECHO_RGT, echo_rgt, CHANGE); 

    Serial.begin(9600);
}

void loop() 
{
    sensor_dist();
    direction();
    go();
}

void echo_btm()
{
    switch (digitalRead(ECHO_BTM))
    {
        case HIGH:  //pulse begin
            echo_btm_end = 0;
            echo_btm_beg = micros();
            dist_btm = UNSET;
            break;

        case LOW:   //pulse end
            echo_btm_end = micros();                  
            echo_btm_dur = echo_btm_end - echo_btm_beg;
            dist_btm = ((float)(346 * echo_btm_dur) / 10000) / 2;
            stat_btm = (dist_btm < LIMIT_BOTTOM);
            //Serial.print(dist_btm); Serial.println(" BOTTOM\n");
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
            angle_rotate = dist_lft - dist_rgt;
            break;
    }
}

void echo_rgt()
{
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
            angle_rotate = dist_lft - dist_rgt;
            break;
    }
}

void sensor_dist()
{
    //float duration, distance;
    digitalWrite(TRIG_BTM, HIGH);
    digitalWrite(TRIG_LFT, HIGH);
    digitalWrite(TRIG_RGT, HIGH);
    delay(1);   //min 5us delayMicroseconds(5);
    digitalWrite(TRIG_BTM, LOW);
    digitalWrite(TRIG_LFT, LOW);
    digitalWrite(TRIG_RGT, LOW);

    // ECHO_BTM 이 HIGH를 유지한 시간/2 T=실온25도 가정
    // v * s = (331.5 + 0.60714*T) x t / 2 = 347 * t / 2
    // UNIT : cm, us = 100 /1000000
    // FRONT : BACK

    /**
      duration = pulseIn(ECHO_BTM, HIGH);
      distance = ((float)(346 * duration) / 10000) / 2;
      distance < 15 ? stat_btm = LOW : stat_btm = HIGH; 
      dist_btm = distance;
     */
}

void direction()
{
    //STOP WHEN NO SENSOR ERROR
    if ( stat_lft == UNSET || stat_rgt == UNSET || stat_btm == UNSET )
        return;

    //Serial.print("\tBTM: ");
    //Serial.print(dist_btm);
    //Serial.print("\tLFT: ");
    //Serial.print(dist_lft);
    //Serial.print("\tRGT: ");
    //Serial.print(dist_rgt);
    //Serial.print("\n");

    //INIT SPEED
    MOT_SPD_LFT = MOT_SPD_RGT = MOT_SPD_MAX;
    MOT_DELAY = MOT_DLY_MAX;

    //PRIORITY BOTTOM-BACK > BLOCK-ROTATE
    if (!stat_btm) {            
        //BOTTOM EMPTY & BACKWARD
        digitalWrite(DIR_LFT, LOW);
        digitalWrite(DIR_RGT, HIGH);
        //Serial.println(" BOTTOM EMPTY & BACKWARD\n");
        MOT_DELAY = MOT_DLY_MAX*100;//1 SEC BACK & TURN
        move_back();//100ms back
        turn_rgt();//100ms turn
        return;//Immediate move
    }

    //BOTH BLOCK! rotate to longer distance 
    //HIGH = BLOCK, LOW = OPEN
    if ( stat_lft &&  stat_rgt ) {
        if ( angle_rotate > 0 ) {
            //RIGHT BLOCK & ROTATE TO LEFT
            digitalWrite(DIR_LFT, HIGH);
            digitalWrite(DIR_RGT, HIGH);
            MOT_SPD_LFT = MOT_SPD_MAX*0.8;
            MOT_SPD_RGT = MOT_SPD_MAX*0.6;
            //Serial.println(" BOTH BLOCK & ROTATE TO LEFT\n");
        }else {
            //LEFT BLOCK & ROTATE TO RIGHT
            digitalWrite(DIR_LFT, LOW);
            digitalWrite(DIR_RGT, LOW);
            MOT_SPD_LFT = MOT_SPD_MAX*0.6;
            MOT_SPD_RGT = MOT_SPD_MAX*0.8;
            //Serial.println(" BOTH BLOCK & ROTATE TO RIGHT\n");
        }
        return;
    }

    //TODO: diff lft-rgt and decide
    if (stat_lft) {
        //LEFT BLOCK & ROTATE TO RIGHT
        digitalWrite(DIR_LFT, LOW);
        digitalWrite(DIR_RGT, LOW);
        MOT_SPD_LFT = MOT_SPD_MAX*0.6;
        MOT_SPD_RGT = MOT_SPD_MAX*0.8;
        //Serial.println(" LEFT BLOCK\n");
        return;
    } else if (stat_rgt) {     
        //RIGHT BLOCK & ROTATE TO LEFT
        digitalWrite(DIR_LFT, HIGH);
        digitalWrite(DIR_RGT, HIGH);
        MOT_SPD_LFT = MOT_SPD_MAX*0.8;
        MOT_SPD_RGT = MOT_SPD_MAX*0.6;
        //Serial.println(" RIGHT BLOCK\n");
        return;
    }

    if (stat_btm) {
        //BOTTOM OK & FORWARD
        digitalWrite(DIR_LFT, HIGH);
        digitalWrite(DIR_RGT, LOW);
        //Serial.println(" BOTTOM OK & FORWARD\n");
    } 

}

void go()
{
    //for (int pos = 0 ; pos <= 225; pos += 5) {
    //analogWrite(MOT_LFT, pos);
    //analogWrite(MOT_RGT, pos);

    // WAIT FOR MOTOR MOVE
    //delay(5);
    //}

    analogWrite(MOT_LFT, MOT_SPD_LFT);
    analogWrite(MOT_RGT, MOT_SPD_RGT);
    if ( (stat_lft || stat_rgt) 
    && (angle_rotate < LIMIT_FRONT && angle_rotate > -1*LIMIT_FRONT) 
    && (stat_btm > 0)
    ) 
    {  
        ( angle_rotate > 0 ) ? delay(angle_rotate*2) : delay(angle_rotate*-2);
    }
    delay(MOT_DELAY);
}

void move_back()
{
    analogWrite(MOT_LFT, MOT_SPD_LFT);
    analogWrite(MOT_RGT, MOT_SPD_RGT);
    delay(MOT_DELAY);
    //Serial.println(" TURN RIGHT\n");
}

void turn_rgt()
{
    //TURN TO RIGHT
    digitalWrite(DIR_LFT, LOW);
    digitalWrite(DIR_RGT, LOW);
    MOT_SPD_LFT = MOT_SPD_MAX*0.6;
    MOT_SPD_RGT = MOT_SPD_MAX*0.8;

    analogWrite(MOT_LFT, MOT_SPD_LFT);
    analogWrite(MOT_RGT, MOT_SPD_RGT);
    delay(MOT_DELAY);
    //Serial.println(" TURN RIGHT\n");
}
