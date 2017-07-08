/*
BCN3D Moveo
This code is to control the BCN3D moveo with a bunch of analog joysticks.

It is designed to run on an arduino mega.

Written by Michael Eagan
 */
  const int SpeedDivider = 70;

//Input from Joysticks  
  const int Input0 = A0; 
  const int Input1 = A1; 
  const int Input2 = A2;
  const int Input3 = A3; 
  const int Input4 = A4; 
  const int Input5 = A5; 
  const int SERVO = 13; 

//Stepper Controls  
int Step0 = 45;
int Step1 = 47;
int Step2 = 49;
int Step3 = 51;
int Step4 = 53;
int Dir0 = 44;
int Dir1 = 46;
int Dir2 = 48;
int Dir3 = 50;
int Dir4 = 52;

int Max0 = 43; 
int Min0 = 42;
int Max1 = 41; 
int Min1 = 40;
int Max2 = 39; 
int Min2 = 38;
int Max3 = 37; 
int Min3 = 36;
int Max4 = 35; 
int Min4 = 34;


//Temp Storage Variables
  int Speed0;
  int Speed1;
  int Speed2;
  int Speed3;
  int Speed4;
  int Center0;
  int Center1;
  int Center2;
  int Center3;
  int Center4;
  int CAL = 100;                  //This figure stores the width of the "no movement" zone.

  
//Time Variables
  unsigned long previousMicros;
  unsigned long previousMicros0;
  unsigned long previousMicros1;
  unsigned long previousMicros2;
  unsigned long previousMicros3;
  unsigned long previousMicros4;
  
int GetDir(int A, int Center) //Set direction function.
{
    if(A>=Center+5){
    return HIGH;
  }
  if(A<=Center - 5){
    return LOW;
  
  }
}

int CALandConvert(int A, int Cal, int Center, int Dir, int Max, int Min)                          //Calibration function, also converts to a direct number, the further from 512, the lower the number.
{ int Distance = Center - 512;
  if (Max == LOW && Dir == HIGH){         //Check to see if you're trying to move forwards and if you're already as "forward" as you can be
    return 10000;  //Set the stepper to hold (never stepping)
  }
  if (Min == LOW && Dir == LOW){          //Check to see if you're trying to move backwards and if you're already as "backward" as you can be
    return 10000;  //Set the stepper to hold (never stepping)
  }
  if(A<=Center+Cal && A>=Center-Cal){     //Check to see if the value of the joystick is within the "dead" zone. This prevents it from moving while you're trying to keep it at zero.
    return 10000;                         //Set the stepper to hold (never stepping)
  }

  if(A>=Center+Cal){                      //Check to see if the value is greater than the center position (plus whatver cal is set to)
  return 1024-A + Distance;               //Do a bit of math to convert the value to a "time". The lower this value is, the more often the stepper is stepped. (lower value = faster movement)
  
  }
  if(A<=Center-Cal){                        
    if (A - Distance <=0){                //There's a possibility that the value can go negative because of the center position. 
      return 1;                           //this prevents it from feeding a negative number to the main loop, which could cause issues.
    }
  else{return A - Distance;               //The lower this value is, the more often the stepper is stepped. (lower value = faster movement)
  }
  }
  
}
  

void setup() {

  //Set all the pinmodes
  pinMode(Step0, OUTPUT);
  pinMode(Step1, OUTPUT);
  pinMode(Step2, OUTPUT);
  pinMode(Step3, OUTPUT);
  pinMode(Step4, OUTPUT);
  pinMode(Dir0, OUTPUT);
  pinMode(Dir1, OUTPUT);
  pinMode(Dir2, OUTPUT);
  pinMode(Dir3, OUTPUT);
  pinMode(Dir4, OUTPUT);
  pinMode(Input0, INPUT);
  pinMode(Input1, INPUT);
  pinMode(Input2, INPUT);
  pinMode(Input3, INPUT);
  pinMode(Input4, INPUT);
  pinMode(Input5, INPUT);

  delay(1000); //Delay to let power stabilize



  //Finding where the joystick's resting point is
  Center0 = analogRead(Input0);
  Center1 = analogRead(Input1);
  Center2 = analogRead(Input2);
  Center3 = analogRead(Input3);
  Center4 = analogRead(Input4);

  
  //Serial.begin(9600);

}

// the loop function runs over and over again forever
void loop() {

  unsigned long currentMicros = micros();
if(currentMicros - previousMicros > 50000) {                         //only run every 50ms
  
  //Set direction on each axis.
  digitalWrite(Dir0, GetDir(analogRead(Input0), Center0));
  digitalWrite(Dir1, GetDir(analogRead(Input1), Center1));
  digitalWrite(Dir2, GetDir(analogRead(Input2), Center2));
  digitalWrite(Dir3, GetDir(analogRead(Input3), Center3));
  digitalWrite(Dir4, GetDir(analogRead(Input4), Center4));

  //Set the speed value (how often it triggers while looping)
  Speed0 = CALandConvert(analogRead(Input0), CAL, Center0, digitalRead(Dir0), digitalRead(Max0), digitalRead(Min0));
  Speed1 = CALandConvert(analogRead(Input1), CAL, Center1, digitalRead(Dir1), digitalRead(Max1), digitalRead(Min1));
  Speed2 = CALandConvert(analogRead(Input2), CAL, Center2, digitalRead(Dir2), digitalRead(Max2), digitalRead(Min2));
  Speed3 = CALandConvert(analogRead(Input3), CAL, Center3, digitalRead(Dir3), digitalRead(Max3), digitalRead(Min3));
  Speed4 = CALandConvert(analogRead(Input4), CAL, Center4, digitalRead(Dir4), digitalRead(Max4), digitalRead(Min4));
  analogWrite(SERVO, map(analogRead(Input5), 0, 1024, 0, 255));
  //Reset the compare variable for the micros counter
  previousMicros = currentMicros;

  //check if endstops are hit

  

  }
 if(currentMicros - previousMicros0 > Speed0 && Speed0 < 1024) {
      digitalWrite(Step0, HIGH); 
      delayMicroseconds(7);
      digitalWrite(Step0, LOW);
      previousMicros0 = currentMicros;
}
    if(currentMicros - previousMicros1 > Speed1 && Speed1 < 1024) {
      digitalWrite(Step1, HIGH); 
      delayMicroseconds(7);
      digitalWrite(Step1, LOW);
      previousMicros1 = currentMicros;
}
   if(currentMicros - previousMicros2 > Speed2 && Speed2 < 1024) {
      digitalWrite(Step2, HIGH); 
      delayMicroseconds(7);
      digitalWrite(Step2, LOW);
      previousMicros2 = currentMicros;
}
   if(currentMicros - previousMicros3 > Speed3 && Speed3 < 1024) {
      digitalWrite(Step3, HIGH); 
      delayMicroseconds(7);
      digitalWrite(Step3, LOW);
      previousMicros3 = currentMicros;
}
   if(currentMicros - previousMicros4 > Speed4 && Speed4 < 1024) {
      digitalWrite(Step4, HIGH); 
      delayMicroseconds(7);
      digitalWrite(Step4, LOW);
      previousMicros4 = currentMicros;
}
   delayMicroseconds(SpeedDivider);
  
}
