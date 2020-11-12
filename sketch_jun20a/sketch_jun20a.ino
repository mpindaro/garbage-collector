//motor A connected between A01 and A02
//motor B connected between B01 and B02


#include <AnalogDistanceSensor.h>
#include <DistanceGP2Y0A02YK0F.h>
#include <DistanceSensor.h>

int STBY = 10; //standby

//Sensore
DistanceGP2Y0A02YK0F sensore;
int pinInfra=A5;

//Motor A
int PWMA = 3; //Speed control 
int AIN1 = 9; //Direction
int AIN2 = 8; //Direction

//Motor B
int PWMB = 5; //Speed control
int BIN1 = 11; //Direction
int BIN2 = 12; //Direction

//Distanza ricevuta dai sensori
int distance;

void setup(){
  
   Serial.begin (9600);

  
  pinMode(STBY, OUTPUT);

  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  //Inizializzazione sensore
 sensore.begin(pinInfra);
}

void loop(){



  distance = sensore.getDistanceCentimeter();
  Serial.print("\nDistanza");
  Serial.print(distance);  
  if(distance>50){
    move(1, 255, 0); //motor 1, full speed, left
    move(2, 255, 0); //motor 2, full speed, left
  }
  else{
  move(1, 255, 0); //motor 1, full speed, left
  move(2, 0, 1); //motor 2, full speed, left
    //  stop();
  }
    

  
  

  /*delay(1000); //go for 1 second
  stop(); //stop
  delay(250); //hold for 250ms until move again

  move(1, 128, 0); //motor 1, half speed, right
  move(2, 128, 0); //motor 2, half speed, right

  delay(1000);
  stop();
  delay(250);*/
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
    inPin1 = HIGH;
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
