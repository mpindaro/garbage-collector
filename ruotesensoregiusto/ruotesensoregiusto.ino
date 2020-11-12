#include <Servo.h>

//motor A connected between A01 and A02
//motor B connected between B01 and B02


#include <AnalogDistanceSensor.h>
#include <DistanceGP2Y0A02YK0F.h>
#include <DistanceSensor.h>

int pinSTBY = 10; //standby

//Sensore sinistra
DistanceGP2Y0A02YK0F sensoreSinistra; 
int pinInfraSinistra=A5;

//Sensore centrale
DistanceGP2Y0A02YK0F sensoreCentrale; 
int pinInfraCentrale=A4;

//Sensore destra
DistanceGP2Y0A02YK0F sensoreDestra; 
int pinInfraDestra=A3;

//Motor A
int PWMA = 3; //Speed control 
int AIN1 = 9; //Direction
int AIN2 = 8; //Direction

//standby
int STBY;

//Motor B
int PWMB = 5; //Speed control
int BIN1 = 11; //Direction
int BIN2 = 12; //Direction

static boolean turnCW=0;
static boolean turnCCW=1;
static boolean motor1=1;
static boolean motor2=2;
boolean libero=3;

//Distanza ricevuta dal sensore sinistro
int distanceSinistra;

//Distanza ricevuta dal sensore centrale
int distanceCentrale;

//Distanza ricevuta dal sensore destro
int distanceDestra;

void motorDrive(boolean motorNumber, boolean motorDirection, int motorSpeed){
  boolean pinIn1;
  if(motorDirection== turnCW)
    pinIn1=HIGH;
  else
   pinIn1=LOW;
  if(motorNumber== motor1){
    digitalWrite(AIN1, pinIn1);
    digitalWrite(AIN2, pinIn1);
    analogWrite(PWMA, motorSpeed);
  }else{
    digitalWrite(BIN1, pinIn1);
    digitalWrite(BIN2, pinIn1);
    analogWrite(PWMB, motorSpeed);
  }
  digitalWrite(pinSTBY, HIGH);
}
void motorStop(boolean motorNumber){
  if(motorNumber== motor1){
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
  }else{
     digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
  }
}
void setup(){
  
   Serial.begin (9600);

  
  pinMode(pinSTBY, OUTPUT);

  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  //Inizializzazione sensore
 sensoreSinistra.begin(pinInfraSinistra);
 
 //Inizializzazione sensore
 sensoreCentrale.begin(pinInfraCentrale);
 
 //Inizializzazione sensore
 sensoreDestra.begin(pinInfraDestra);
}

void loop(){



  distanceSinistra = sensoreSinistra.getDistanceCentimeter();
  distanceCentrale = sensoreCentrale.getDistanceCentimeter();
  distanceDestra = sensoreDestra.getDistanceCentimeter();
  
  Serial.print("\nDistanza Sinistra");
  Serial.print(distanceSinistra);
  Serial.print("\nDistanza Centrale");
  Serial.print(distanceCentrale);
  Serial.print("\nDistanza Destra");
  Serial.print(distanceDestra);
  if((distanceCentrale<45 && distanceSinistra<45 && distanceDestra<45) || (distanceCentrale<45 && !distanceSinistra<45 && !distanceDestra<45) || (!distanceCentrale<45 && !distanceSinistra<45 && distanceDestra<45) || (distanceCentrale<45 && !distanceSinistra<45 && distanceDestra<45)){
   
    motorDrive(2, turnCCW, 255); //motor, direction, speed
    motorDrive(1, turnCCW, 255); 
    motorStop(1);
    motorDrive(2,turnCW,255);
  }
  else if ((!distanceCentrale<45 && distanceSinistra<45 && !distanceDestra<45) || (distanceCentrale<45 && distanceSinistra<45 && !distanceDestra<45)){
    motorDrive(2, turnCCW, 255); //motor, direction, speed
    motorDrive(1, turnCCW, 255); 
    motorStop(2);
    motorDrive(1,turnCW,255);
    //  stop();
  }
  else if(!distanceCentrale<45 && distanceSinistra<45 && distanceDestra<45){
     stop();
     motorDrive(2, turnCCW, 255); 
    motorDrive(1, turnCCW, 255); 
    motorStop(2);
    motorDrive(1,turnCW,255);
  }
    else {
       motorDrive(1, turnCW, 255); 
       motorDrive(2, turnCW, 255); 
    
    }

    delay(500);

}


void move(int motor, int speed, int direction){
//Move specific motor at speed and direction
//motor: 0 for B 1 for A
//speed: 0 is off, and 255 is full speed
//direction: 0 clockwise, 1 counter-clockwise

  digitalWrite(STBY, HIGH); //disable standby

  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if(direction == 1){
    inPin1 = LOW;
    inPin2 = LOW;
  }else if(direction==0){
    inPin1 = HIGH;
    inPin2 = HIGH;
  }

  if(motor == 1){
    digitalWrite(AIN1, inPin1);
    digitalWrite(AIN2, inPin2);
    analogWrite(PWMA, speed);
  }else{
    digitalWrite(BIN1, inPin1);
    digitalWrite(BIN2, inPin2);
    analogWrite(PWMB, speed);
  }
}

void stop(){
//enable standby  
  digitalWrite(STBY, LOW); 
}
