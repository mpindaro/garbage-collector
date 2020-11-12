#include <VarSpeedServo.h>


#include <SharpIR.h>

#include <AnalogDistanceSensor.h>
#include <DistanceGP2Y0A02YK0F.h>
#include <DistanceSensor.h>
//b

//Sensore
DistanceGP2Y0A02YK0F sensoreSinistra;
int pinInfraSin=A3;
DistanceGP2Y0A02YK0F sensoreCentrale;
int pinInfraCen=A4;
DistanceGP2Y0A02YK0F sensoreDestra;
int pinInfraDes=A5;


//Motor A
int enableA = 10;
int pinA1 = 2;
int pinA2 = 3;
 
//Motor B
int enableB = 9;
int pinB1 = 4;
int pinB2 = 5;

//define time for run
// in milliseconds
int running = 10000; //10 secons

//Distanza ricevuta dai sensori
int distanceSinistra;
int distanceCentrale;
int distanceDestra;

void setup() {
  // put your setup code here, to run once:
 Serial.begin (9600);
 //configure pin modes
 pinMode (enableA, OUTPUT);
 pinMode (pinA1, OUTPUT);
 pinMode (pinA2, OUTPUT); 
 
 pinMode (enableB, OUTPUT);
 pinMode (pinB1, OUTPUT);
 pinMode (pinB2, OUTPUT); 

 //Inizializzazione sensore
 sensoreSinistra.begin(pinInfraSin);
 sensoreCentrale.begin(pinInfraCen);
 sensoreDestra.begin(pinInfraDes);
 
}

//Defining functions so it's more easy
//motor functions
void motorAforward() {
 digitalWrite (pinA1, HIGH);
 digitalWrite (pinA2, LOW);
}
void motorBforward() {
 digitalWrite (pinB1, LOW);
 digitalWrite (pinB2, HIGH);
}
void motorAbackward() {
 digitalWrite (pinA1, LOW);
 digitalWrite (pinA2, HIGH);
}
void motorBbackward() {
 digitalWrite (pinB1, HIGH);
 digitalWrite (pinB2, LOW);
}
void motorAstop() {
 digitalWrite (pinA1, HIGH);
 digitalWrite (pinA2, HIGH);
}
void motorBstop() {
 digitalWrite (pinB1, HIGH);
 digitalWrite (pinB2, HIGH);
}
void motorAcoast() {
 digitalWrite (pinA1, LOW);
 digitalWrite (pinA2, LOW);
}
void motorBcoast() {
 digitalWrite (pinB1, LOW);
 digitalWrite (pinB2, LOW);
}
void motorAon() {
 digitalWrite (enableA, HIGH);
}
void motorBon() {
 digitalWrite (enableB, HIGH);
}
void motorAoff() {
 digitalWrite (enableA, LOW);
}
void motorBoff() {
 digitalWrite (enableB, LOW);
}
// Movement functions
void avanti (int duration) {
 motorAforward();
 motorBforward();
 //
 
 delay (duration);
}
void indietro (int duration) {
 motorAbackward();
 motorBbackward();
 delay (duration);
}
void sinistra (int duration) {
 motorAforward();
 motorBstop();
 delay (duration);
}
void destra (int duration) {
 motorAstop();
 motorBforward();
 delay (duration);
}
void coast (int duration) {
 motorAcoast();
 motorBcoast();
 delay (duration);
}
void stopMotors(int duration){
  motorAstop();
  motorBstop();
}
void breakRobot (int duration) {
 motorAstop();
 motorBstop();
 //delay (duration);
}
void disableMotors() {
 motorAoff();
 motorBoff();
}
void enableMotors() {
 motorAon();
 motorBon();

}void loop() {

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
    indietro(1500);
    sinistra(500);
  } else if ((!distanceCentrale<45 && distanceSinistra<45 && !distanceDestra<45) || (distanceCentrale<45 && distanceSinistra<45 && !distanceDestra<45)){
        indietro(1500);
       destra(500);   
  }
  else if(!distanceCentrale<45 && distanceSinistra<45 && distanceDestra<45){
        indietro(1500);
       sinistra(500); 
  }else
      avanti(5000);
delay(35);
}
