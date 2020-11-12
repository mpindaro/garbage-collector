int I1=2;
int I2=3;
int EA=9;
int I3=4;
int I4=5;
int EB=10;

void setup() {
  digitalWrite(I1,OUTPUT);
  digitalWrite(I2,OUTPUT);
  digitalWrite(EA,OUTPUT);
  digitalWrite(I3,OUTPUT);
  digitalWrite(I4,OUTPUT);
  digitalWrite(EB,OUTPUT);
}

void loop() {
    digitalWrite(I1,HIGH);
    digitalWrite(I2,LOW);
    digitalWrite(EA,HIGH);
    digitalWrite(I3,HIGH);
    digitalWrite(I4,LOW);
    digitalWrite(EB,HIGH);
    delay(5000);
    digitalWrite(EA,LOW);    
    digitalWrite(EB,LOW);    
}
