/*  ONE TANK FREE MOVE 
    ---REFERS---
https://www.gitbook.com/book/smartarduino/user-manual-for-2-way-motor-16-way-servos-shield/details
http://www.smartarduino.com/view.php?id=94895
http://playground.arduino.cc/Main/AdafruitMotorShield
*/

#include "Arduino.h"

#define MOT_SPD_MAX 200

void setup();
void loop();
int sensor_dist();
void direction();
void go();

const int MOT_LFT   = 6;      // MOTOR A - PIN 11 POWER 
const int DIR_LFT   = 7;      // MOTOR A - PIN 7  DIRECTION 
const int MOT_RGT   = 11;     // MOTOR B - PIN 6  POWER 
const int DIR_RGT   = 12;     // MOTOR B - PIN 12 DIRECTION 

int MOT_SPD_LFT     = MOT_SPD_MAX;    // MOROT SPEED LEFT
int MOT_SPD_RGT     = MOT_SPD_MAX;    // MOROT SPEED RIGHT


// 초음파 센서
const int TRIG_LFT = 2;
const int ECHO_LFT = 3;
const int TRIG_RGT = 4;
const int ECHO_RGT = 5;
const int TRIG_BTM = 8;
const int ECHO_BTM = 9;
int stat_btm = LOW;
int stat_lft = LOW;
int stat_rgt = LOW;

int dist_lft = 0;
int dist_rgt = 0;

void setup() 
{
    Serial.begin(9600);

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
}

void loop() 
{
    sensor_dist();
    direction();
    go();
}

int sensor_dist()
{
    float duration, distance;
    digitalWrite(TRIG_BTM, HIGH);
    digitalWrite(TRIG_LFT, HIGH);
    digitalWrite(TRIG_RGT, HIGH);
    delay(10);
    digitalWrite(TRIG_BTM, LOW);
    digitalWrite(TRIG_LFT, LOW);
    digitalWrite(TRIG_RGT, LOW);

    // ECHO_BTM 이 HIGH를 유지한 시간을 저장 한다.
    // FRONT : BACK
    duration = pulseIn(ECHO_BTM, HIGH);
    distance = ((float)(340 * duration) / 10000) / 2;
    distance < 15 ? stat_btm = LOW : stat_btm = HIGH; 

    //LEFT Dicision
    duration = pulseIn(ECHO_LFT, HIGH);
    distance = ((float)(340 * duration) / 10000) / 2;
    distance < 15 ? stat_lft = LOW : stat_lft = HIGH; 
    dist_lft = distance;

    //Right Dicision
    duration = pulseIn(ECHO_RGT, HIGH);
    distance = ((float)(340 * duration) / 10000) / 2;
    distance < 15 ? stat_rgt = LOW : stat_rgt = HIGH; 
    dist_rgt = distance;

    //시리얼모니터에 Echo가 HIGH인 시간 및 거리를 표시해준다.
    //Serial.print("Duration:");
    //Serial.print(duration);
    //Serial.print("\nDIstance:");
    Serial.print(dist_lft);
    Serial.println("LFT\n");
    Serial.print(dist_lft);
    Serial.println("RGT\n");
    //delay(10);
    return distance;
}

void direction()
{

    //INIT SPEED
    MOT_SPD_LFT = MOT_SPD_RGT = MOT_SPD_MAX;

    if (stat_btm) {
        //FRONT
        digitalWrite(DIR_LFT, LOW);
        digitalWrite(DIR_RGT, HIGH);
    } else {
        //BACK
        digitalWrite(DIR_LFT, HIGH);
        digitalWrite(DIR_RGT, LOW);
    }

    if (stat_lft) {
        //LEFT BLOCK
        digitalWrite(DIR_LFT, HIGH);
        digitalWrite(DIR_RGT, HIGH);
        MOT_SPD_LFT = MOT_SPD_MAX/2;
    }

    if (stat_rgt) {
        //RIGHT BLOCK
        digitalWrite(DIR_LFT, LOW);
        digitalWrite(DIR_RGT, LOW);
        MOT_SPD_RGT = MOT_SPD_MAX/2;
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
    delay(5);
}
