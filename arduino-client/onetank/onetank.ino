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

void setup() {
    // NO NEED TO SETUP ANALOG OUTPUT
    pinMode(lftDir, OUTPUT);
    pinMode(rgtDir, OUTPUT);
    digitalWrite(lftDir, HIGH);
    digitalWrite(rgtDir, LOW);
}

void loop() {

    // FORWORD STEP (range from 0 to 255):
    digitalWrite(lftDir, HIGH);
    digitalWrite(rgtDir, LOW);  
    for (int pos = 0 ; pos <= 255; pos += 5) {
        analogWrite(lftMotor, pos);
        analogWrite(rgtMotor, pos);

        //analogWrite(lftMotor, spdMotor);
        //analogWrite(rgtMotor, spdMotor);
        // WAIT FOR MOTOR MOVE
        delay(30);
    }
    delay(1000);

    // BACK STEP (range from 0 to 255):
    digitalWrite(lftDir, LOW);
    digitalWrite(rgtDir, HIGH);
    for (int pos = 0 ; pos <= 255; pos += 5) {
        analogWrite(lftMotor, pos);
        analogWrite(rgtMotor, pos);

        //analogWrite(lftMotor, spdMotor);
        //analogWrite(rgtMotor, spdMotor);
        // WAIT FOR MOTOR MOVE
        delay(30);
    }
    delay(1000);
}
