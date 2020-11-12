#include <VarSpeedServo.h>


#include <SharpIR.h>

#include <AnalogDistanceSensor.h>
#include <DistanceGP2Y0A02YK0F.h>
#include <DistanceSensor.h>

DistanceGP2Y0A02YK0F sensore;

VarSpeedServo servo;
VarSpeedServo servo2;
VarSpeedServo servo3;

int pinInfra=A0;
int pinServo=2;
int pinServo2=3;
int pinServo3=4;

int y;
int x;
int z;
long int tempo;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
  // pinMode(pinInfra,INPUT);
    servo.attach(pinServo);
 servo.write(0,255,true); // set the intial position of the servo, as fast as possible, wait until done
 servo2.attach(pinServo2);
 servo2.write(180,255,true); // set the intial position of the servo, as fast as possible, wait until done
 servo3.attach(pinServo3);
 servo3.write(0,255,true); // set the intial position of the servo, as fast as possible, wait until done

    
}

void loop() {
  // put your main code here, to run repeatedly:
  y++;
  if(x<90)
  x++;
  z++;
  servo.write(y,100);
  servo2.write(x,100);
  servo3.write(z,100);
  
 
  if(y==180)
    y=0;
  if(z==110)
    z=0;
  Serial.println('x');

 
  
  delay(15
  );

  

  
  
  
}
