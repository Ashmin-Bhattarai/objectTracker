
#include <Servo.h>

const int motor_in1 = 7; // for one terminal of motor / motor driver
const int motor_in2 = 6;// for another terminal of motor / motor driver
const int servo_sig = 3; // to give signal for servo (PWM pin)
const int motor_pwm = 5; // to control motor speed (PWM pin)

void forward();
void back();
void left();
void right();
void stp();

char data;
int flag = 0;

Servo myservo; //create servo object to control a servo

void setup()
{
    pinMode(motor_in1, OUTPUT);
    pinMode(motor_in2, OUTPUT);
    pinMode(servo_sig, OUTPUT);
    pinMode(motor_pwm, OUTPUT);
    myservo.attach(servo_sig);  // attaches the servo on pin 9 to the servo object
    Serial.begin(9600);
    myservo.write(10);
    delay(15);
}


void loop()
{
    if(Serial.available() > 0)
    {
      data = Serial.read();
      Serial.println(data);
      flag = 0;
    }
    
    if(data == 'f')
    {
      forward();
      if(flag == 0)
      {
         Serial.println("forward");     
         flag = 1; 
      }
    }
    
    else if(data == 'b')
    {
        back();
        if(flag == 0)
        {
            Serial.println("back");
            flag = 1; 
         }
    }

    else if(data == 'l')
    {
        left();
        if(flag == 0)
        {
            Serial.println("left");
            flag = 1; 
        }
    }

   else if(data == 'r')
    {
        right();
        if(flag == 0)
        {
            Serial.println("right");
            flag = 1; 
        }
    }

    else if(data == 's')
    {
        stp();
        if(flag == 0)
        {
          Serial.println("stop");
          flag = 1;
        }
    }
  
}


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
  analogWrite(motor_pwm, 155);
  digitalWrite(motor_in1, LOW);
  digitalWrite(motor_in2, LOW);
}
