

int pinDo=8;
int pinRe=9;
int pinMi=10;
int pinFa=10;
int pinSol=10;
int pinLa=10;

int buzzer=13;

int doo;
int re;
int mi;
int fa;
int sol;
int la;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(pinDo, INPUT);
    pinMode(pinRe, INPUT);
    pinMode(pinMi, INPUT);
    pinMode(pinFa, INPUT);
    pinMode(pinSol, INPUT);
    pinMode(pinLa, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  doo=digitalRead(pinDo);
  re=digitalRead(pinRe);
  mi=digitalRead(pinMi);
  fa=digitalRead(pinFa);
  sol=digitalRead(pinSol);
  la=digitalRead(pinLa);
  
  if(doo==1)
      tone(buzzer,262);
  if(re==1)
    tone(buzzer,294);

  if(mi==1)
    tone(buzzer,330);
  if(fa==1)
    tone(buzzer,349);
  if(sol==1)
    tone(buzzer,392);
  if(la==1)
    tone(buzzer,440);
    
}
