//Testing the DC Motors
//Define Pins
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
boolean play;
void setup() {
 Serial.begin (9600);
 //configure pin modes
 pinMode (enableA, OUTPUT);
 pinMode (pinA1, OUTPUT);
 pinMode (pinA2, OUTPUT); 
 
 pinMode (enableB, OUTPUT);
 pinMode (pinB1, OUTPUT);
 pinMode (pinB2, OUTPUT); 
 
 play = true;
 
}

void loop(){
   digitalWrite (pinA1, HIGH);
    digitalWrite (pinA2, LOW);
 digitalWrite (pinB1, LOW);
 digitalWrite (pinB2, HIGH);
}

