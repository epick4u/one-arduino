/*  ONE TANK FREE MOVE 
    ---REFERS---
https://www.gitbook.com/book/smartarduino/user-manual-for-2-way-motor-16-way-servos-shield/details
http://www.smartarduino.com/view.php?id=94895
http://playground.arduino.cc/Main/AdafruitMotorShield
 */

int lftMotor  = 6;      // MOTOR A - PIN 11 POWER 
int lftDir    = 7;      // MOTOR A - PIN 7  DIRECTION 
int rgtMotor  = 11;     // MOTOR B - PIN 6  POWER 
int rgtDir    = 12;     // MOTOR B - PIN 12 DIRECTION 

int spdMotor  = 200;    // MOROT SPEED STEP 5


// 초음파 센서
int TRIG = 8;
int ECHO = 9;

void setup() 
{
    Serial.begin(9600);

    // MOTOR NO NEED TO SETUP ANALOG OUTPUT
    pinMode(lftDir, OUTPUT);
    pinMode(rgtDir, OUTPUT);
    digitalWrite(lftDir, HIGH);
    digitalWrite(rgtDir, LOW);

    //SENSOR
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);

}

void loop() 
{
    if ( dist_short() < 15 ) 
        front();
    else
        back();
}

int dist_short()
{
    float duration, distance;
    digitalWrite(TRIG, HIGH);
    delay(10);
    digitalWrite(TRIG, LOW);

    // ECHO 이 HIGH를 유지한 시간을 저장 한다.
    duration = pulseIn(ECHO, HIGH);
    // HIGH 였을 때 시간(초음파가 보냈다가 다시 들어온 시간)을 가지고 거리를 계산 한다.
    // 340은 초당 초음파(소리)의 속도, 10000은 밀리세컨드를 세컨드로, 왕복거리이므로 2로 나눠준다.
    distance = ((float)(340 * duration) / 10000) / 2;

    //시리얼모니터에 Echo가 HIGH인 시간 및 거리를 표시해준다.
    //Serial.print("Duration:");
    //Serial.print(duration);
    //Serial.print("\nDIstance:");
    //Serial.print(distance);
    //Serial.println("cm\n");
    delay(10);
    return distance;
}

void go()
{
    for (int pos = 0 ; pos <= 225; pos += 5) {
        analogWrite(lftMotor, pos);
        analogWrite(rgtMotor, pos);

        //analogWrite(lftMotor, spdMotor);
        //analogWrite(rgtMotor, spdMotor);
        // WAIT FOR MOTOR MOVE
        delay(5);
    }
    //delay(5);
}

void front()
{
    // FORWORD STEP (range from 0 to 255):
    digitalWrite(lftDir, HIGH);
    digitalWrite(rgtDir, LOW);
    go();
}

void back()
{
    // BACK STEP (range from 0 to 255):
    digitalWrite(lftDir, LOW);
    digitalWrite(rgtDir, HIGH);
    go();
}

void right()
{
}

void left()
{
}
