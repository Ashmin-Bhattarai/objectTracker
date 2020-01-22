#include <ibus.h>


//defining ports for motordriver ( L298N )
#define enableLeft 6
#define enableRight  11
#define leftFor  7
#define leftBac  8
#define rightFor 9 
#define rightBac  10 
#define servoControl 3
#define valforsteer 60 // start value for the steering function to kick in. //check value
#define pulse_for_inertia 150 //check value

int16_t channel[10];
int16_t up,side,s_1,s_2;
int16_t turnspeed = 50;  //check value

/*
 * up -> Right Stick (up-down)
 * side -> Right Stick (left-right)
 */
void setup() {
  Serial.begin(115200);
  IBus.begin(Serial);
  pinMode(enableLeft, OUTPUT);
  pinMode(enableRight, OUTPUT);
  pinMode(servoControl, OUTPUT);
  pinMode(leftFor, OUTPUT);
  pinMode(leftBac, OUTPUT);
  pinMode(rightFor, OUTPUT);
  pinMode(rightBac, OUTPUT);
}

void loop() {
/*
   Channel 0 -> Left Stick ( Right - Left)
   Channel 1 -> Left Stick (Up - Down)
   Channel 2 -> Right Stick (Up - Down)
   Channel 3 -> Right Stick (Right - Left)
*/

  dataRead();
  up = map(channel[2],1000,2000,-255,255);
  side = map(channel[0],1000,2000,-255,255);
  
  s_1 = map (channel[6],1000,2000,-255,255);
  s_2 = map (channel [7],1000,2000,-255,255);
  
   // condition for the enablepin voltage; for couple based turning.
  if ( up < 30 && up > -30)
  {
    analogWrite (enableLeft,abs(side));
    analogWrite (enableRight,abs(side));
  }
  // function to check for the necessary conditions
  conditions();
}

void dataRead(){
  IBus.loop();
  for (int i=0;i<10;i++)
  {
    channel[i] = IBus.readChannel(i);
  }
}

void conditions(){
  if (up > 30 && up <= 255)
  {
    
    if ( side > valforsteer && side <= 255)
    {
      Serial.print("Going right steer");
      analogWrite (enableLeft,abs(side));
      analogWrite (enableRight,abs(turnspeed));
      forwards();  // here forwards is used because the motors keep moving in the same direction but at different speeds.
    }
    
    else if (side < -valforsteer && side >= -255)
    {
      Serial.print("Going left steer");
      analogWrite(enableRight,abs(side));
      analogWrite(enableLeft,abs(turnspeed));
      forwards();
      
    }
    else
    {
    analogWrite (enableLeft,abs(up));
    analogWrite (enableRight,abs(up));
      forwards();
    }
  }
  
  else if (up < -30 && up >= -255)
  {
    if ( side > valforsteer && side <= 255)
    {
      Serial.print("Going right steer");
      analogWrite (enableLeft,abs(side));
      analogWrite (enableRight,abs (turnspeed));
      backwards();
    }
    
    else if (side < -valforsteer && side >= -255)
    {
      Serial.print("Going left steer");
      analogWrite(enableRight,abs(side));
      analogWrite(enableLeft,abs (turnspeed));
      backwards();
    }
    else
    {
    analogWrite (enableLeft,abs(up));
    analogWrite (enableRight,abs(up));
      backwards();
    }
  }
  
  if (side > 30 && side <= 255 && up >-50 && up <50) // 50 for correction of Y axis movement ~ adjustment maybe necessary.
  {
    right();
  }
  else if (side < -30 && side >= -255 && up >-50 && up <50)
  {
    left();
  }

    if ((up < 30 && up > -30 && side < 30 && side > -30) || (up > 255 || up < -255 || side > 255 || side < -255)) 
  {
   if (s_1 > 0){
    stop_forwards();
  }
  if ( s_2 > 0){
    stop_backwards();
  }
  else
  {
    stopped();
  }
  }
}

void stop_backwards(){
  analogWrite(enableLeft,255);
  analogWrite(enableRight,255);
  forwards();
  delay(pulse_for_inertia);
  stopped();
  }

void stop_forwards(){
  analogWrite(enableLeft,255);
  analogWrite(enableRight,255);
  backwards();
  delay(pulse_for_inertia);
  stopped();
}

void forwards() {
  Serial.println("Going Forwards");
  digitalWrite(leftFor, HIGH);
  digitalWrite(rightFor, HIGH);
  digitalWrite (leftBac, LOW);
  digitalWrite (rightBac, LOW);
}

void backwards() {
  Serial.println("Going Backwards");
  digitalWrite(leftBac, HIGH);
  digitalWrite(rightBac, HIGH);
  digitalWrite(leftFor, LOW);
  digitalWrite(rightFor, LOW);
}

void left() {
  Serial.println("Going Left");
  digitalWrite (rightFor, HIGH);
  digitalWrite (leftBac, HIGH);
  digitalWrite (rightBac, LOW);
  digitalWrite (leftFor, LOW);
}

void right() {
  Serial.println("Going Right");
  digitalWrite (leftFor, HIGH);
  digitalWrite (rightBac, HIGH);
  digitalWrite (leftBac, LOW);
  digitalWrite (rightFor, LOW);
}

void stopped() {
  Serial.println("Stopped");
  digitalWrite (leftFor, LOW);
  digitalWrite (leftBac, LOW);
  digitalWrite (rightBac, LOW);
  digitalWrite (rightFor, LOW);
}
