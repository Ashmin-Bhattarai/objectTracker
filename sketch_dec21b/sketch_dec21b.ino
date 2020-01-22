//#include <SoftwareSerial.h>
#include<Servo.h>
//SoftwareSerial Serial(2, 3); // RX, TX

//Initialize global variables
String bluetoothRead;
unsigned short x, y, area;
unsigned short strLength;
Servo myservo;


void forward();
void back();
void left();
void right();
void stp();



//Configure motor pin
const int motor_in1 = 6; // for one terminal of motor / motor driver
const int motor_in2 = 7;// for another terminal of motor / motor driver
const int servo_sig = 3; // to give signal for servo (PWM pin)
const int motor_pwm = 5; // to control motor speed (PWM pin)


void setup() {

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.println("OpenCV Bot");

  //Setup pins
    pinMode(motor_in1, OUTPUT);
    pinMode(motor_in2, OUTPUT);
    pinMode(servo_sig, OUTPUT);
    pinMode(motor_pwm, OUTPUT);
    
    myservo.attach(servo_sig);
    myservo.write(10);
    delay(15);
  
}

void loop() {
  register byte ndx = 0;
  char commandbuffer[50];

  if (Serial.available() > 0) {
    delay(10);
    while ( Serial.available() && ndx < 50) {
      commandbuffer[ndx++] = Serial.read();
    }

    commandbuffer[ndx] = '\0';
    bluetoothRead = (char*)commandbuffer;
    strLength = bluetoothRead.length();
    //Serial.println(bluetoothRead);

    if (bluetoothRead.substring(0, 1).equals("X")) {
      uint8_t pos, i = 1;

      while (bluetoothRead.substring(i, i + 1) != ("Y")) {
        i++;
      }

      x = bluetoothRead.substring(1, i).toInt();
      //Serial.print("X: ");
      //Serial.println(x);

      pos = i + 1;
      while (bluetoothRead.substring(i, i + 1) != ("A")) {
        i++;
      }

      y = bluetoothRead.substring(pos, i).toInt();
      //Serial.print("Y: ");
      //Serial.println(y);

      area = bluetoothRead.substring(i + 1, strLength).toInt();
      //Serial.print("Area: ");
      //Serial.println(area);


      if (x >= 530 && x <= 800)
      {
        if (area < 10) {
          Serial.println("Forward");
          forward();
        }
        if (area >= 10 && area <= 15) {
          Serial.println("Stop");
          stp();
        }
        if (area > 15) {
          Serial.println("Back");
          back();
        }
      }
      
      if (x < 530) {
        Serial.println("Left");
        left();
      }
      if (x > 800) {
        Serial.println("Right");
        right();
      }
 
    }
  }
  // all data has been sent, and the buffer is empty.
  Serial.flush();
}
/*
void Left() {
  digitalWrite(leftMotorA, LOW);
  digitalWrite(leftMotorB, HIGH);

  digitalWrite(rightMotorA, HIGH);
  digitalWrite(rightMotorB, LOW);
  
}

void Right() {
  digitalWrite(leftMotorA, HIGH);
  digitalWrite(leftMotorB, LOW);

  digitalWrite(rightMotorA, LOW);
  digitalWrite(rightMotorB, HIGH);
}

void Forward() {
  digitalWrite(leftMotorA, HIGH);
  digitalWrite(leftMotorB, LOW);

  digitalWrite(rightMotorA, HIGH);
  digitalWrite(rightMotorB, LOW);
}

void Back() {
  digitalWrite(leftMotorA, LOW);
  digitalWrite(leftMotorB, HIGH);

  digitalWrite(rightMotorA, LOW);
  digitalWrite(rightMotorB, HIGH);
}

void Stop() {
  digitalWrite(leftMotorA, LOW);
  digitalWrite(leftMotorB, LOW);

  digitalWrite(rightMotorA, LOW);
  digitalWrite(rightMotorB, LOW);
}

*/

void forward()
{
  Serial.println("from forward");
  myservo.write(10); // making 10 as straight
  delay(15); 
  analogWrite(motor_pwm, 155);
  digitalWrite(motor_in1, HIGH);
  digitalWrite(motor_in2, LOW);
}

void back()
{
  Serial.println("from back");
  myservo.write(10); // making 60 as straight 
  delay(15);
  analogWrite(motor_pwm, 155);
  digitalWrite(motor_in1, LOW);
  digitalWrite(motor_in2, HIGH);
}

void left()
{
  Serial.println("from left");
  myservo.write(0); // making 40 as left
  delay(15);
  analogWrite(motor_pwm, 155);
  digitalWrite(motor_in1, HIGH);
  digitalWrite(motor_in2, LOW);
}

void right()
{
  Serial.println("from right");
  myservo.write(25); // making 80 as right 
  delay(15);
  analogWrite(motor_pwm, 155);
  digitalWrite(motor_in1, HIGH);
  digitalWrite(motor_in2, LOW);
}

void stp()
{
  Serial.println("from stp");
  myservo.write(10); // making 60 as straight 
  delay(15);
  analogWrite(motor_pwm, 0);
  digitalWrite(motor_in1, LOW);
  digitalWrite(motor_in2, LOW);
}
