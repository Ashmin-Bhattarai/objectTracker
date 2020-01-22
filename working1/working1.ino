
#include<Servo.h>


//Initialize global variables
int count = 0;
String bluetoothRead;
unsigned short x, y, area;
unsigned short strLength;
Servo myservo;


void forward(int, int);
void back(int, int);
void dir(int, int);
//void right(int, int);
void stp();



//Configure motor pin
const int motor_in1 = 7; // for one terminal of motor / motor driver
const int motor_in2 = 6;// for another terminal of motor / motor driver
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
    myservo.write(18);
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

        //Serial.println(x);

        if (y >= 700) 
        {
          Serial.println("Stop");
          if(count == 0)
          {
              back(x, y);
              count = 1;   
          }
         stp();
        }
      else if (x >= 670 && x <= 1117)
      {
        if (y < 700) 
        {
          Serial.println("Forward");
          forward(x, y);
          count = 0;
        }
        
        //if (area > 15) {
          //Serial.println("Back");
          //back();
        //}
      }  
      else if (x < 670 && y < 700) {
        Serial.println("Left");
        dir(x, y);
        count = 0;
      }
      else if (x > 1117 && y < 700) {
        Serial.println("Right");
        dir(x, y);
        count = 0;
      }
      /////
      
 
    }
  }
  
  // all data has been sent, and the buffer is empty.
  Serial.flush();
}

void forward(int a, int b)
{
  Serial.println("from forward");
  a = map(a, 50, 1800, 0, 30);
  Serial.println(a);
  myservo.write(a); // making 10 as straight
  delay(15);
  b = map(b, 150, 1000, 200, 50);
  Serial.println(b);
  analogWrite(motor_pwm, b);
  digitalWrite(motor_in1, HIGH);
  digitalWrite(motor_in2, LOW);
}

void back(int a, int b)
{
  Serial.println("from back");
  //a = map(a, 50, 1800, 0, 30);
  //Serial.println(a);
  //myservo.write(a); // making 60 as straight 
  //delay(15);
  //b = map(b, 150, 1000, 100, 200);
  analogWrite(motor_pwm, 175);
  digitalWrite(motor_in1, LOW);
  digitalWrite(motor_in2, HIGH);
  delay(250);
}

void dir(int a, int b)
{
  Serial.println("from left");
  a = map(a, 50, 1800, 0, 30);
  Serial.println(a);
  myservo.write(a); // making 40 as left
  delay(15);
  b = map(b, 150, 1000, 200, 50);
  Serial.println(b);
  analogWrite(motor_pwm, b);
  digitalWrite(motor_in1, HIGH);
  digitalWrite(motor_in2, LOW);
}
/*
void right(int a, int b)
{
  Serial.println("from right");
  myservo.write(25); // making 80 as right 
  delay(15);
  analogWrite(motor_pwm, 155);
  digitalWrite(motor_in1, HIGH);
  digitalWrite(motor_in2, LOW);
}
*/
void stp()
{
  Serial.println("from stp");
  //a = map(a, 50, 1800, 0, 30);
  //myservo.write(10); // making 60 as straight 
  //delay(15);
  analogWrite(motor_pwm, 125);
  digitalWrite(motor_in1, LOW);
  digitalWrite(motor_in2, LOW);
}
