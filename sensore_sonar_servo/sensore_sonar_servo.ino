#include <VarSpeedServo.h>

#include <SharpIR.h>

VarSpeedServo servoverticale;
VarSpeedServo servoorizzontale;

int pinservoverticale=A0;
int pinservoorizzontale=A1;

int lastx;
int lasty;

int x;
int y;
int pos=0;

int trigger=20;
long df=0;

//HC RS04 Sensore ultrasuoni
int triggerPort = 7;
int echoPort = 8;
 
void setup() {
 
pinMode( triggerPort, OUTPUT );
pinMode( echoPort, INPUT );
Serial.begin( 9600 );
Serial.println( "Sensore ultrasuoni: ");
servoverticale.attach(pinservoverticale);
servoorizzontale.attach(pinservoorizzontale);

//servoverticale.write(0,255,true);
//servoorizzontale.write(0,255,true);

}
 
void loop() {


//porta bassa l'uscita del trigger
digitalWrite( triggerPort, LOW );
 
//invia un impulso di 10microsec su trigger
digitalWrite( triggerPort, HIGH );
delayMicroseconds( 10 );
digitalWrite( triggerPort, LOW );
 
long duration = pulseIn( echoPort, HIGH );
 
long di = 0.034 * duration / 2;
 
/*Serial.print( "durata: " );
Serial.print( duration );
Serial.print( " , " );
Serial.print( "distanza: " );
*/ 
//dopo 38ms è fuori dalla portata del sensore
//if( duration > 38000 ) Serial.println( "fuori portata");
//else { Serial.print( di ); Serial.println( "cm" );}

if(di<trigger){
  y=0;
  
  
 while(duration<3800){
        pos+=5;
        servoverticale.write(pos);
        digitalWrite( triggerPort, HIGH );
        delayMicroseconds( 10 );
        digitalWrite( triggerPort, LOW );
        long duration = pulseIn( echoPort, HIGH );
        df = 0.034 * duration / 2;
        delay(50);
        
}
float angolo=pos*360/180;
double coseno=cos(angolo);
lasty=sqrt((di*di)+(df*df)-(2*di*df*coseno));
Serial.println(lasty);  
pos=0;  
if(lasty<51){ 
  while(duration<3800){   
      x=0;
      servoorizzontale.write(pos,50);
      digitalWrite( triggerPort, HIGH );
      delayMicroseconds( 10 );
      digitalWrite( triggerPort, LOW );
      long duration = pulseIn( echoPort, HIGH );
      long df = 0.034 * duration / 2;
      delay(50);
}
 float angolo=pos*360/180;
double coseno=cos(angolo);
lastx=sqrt((di*di)+(df*df)-(2*di*df*coseno));
Serial.println(lastx);

}}
//aspetta 1.5 secondi
delay( 1500 );

/*servoverticale.write(0, 150 );
delay ( 3000);
for(int aus = 0; aus < 180; aus ++)
      servoverticale.write(aus,150);
      delay(50);
delay ( 1000 );
for(int aus = 180; aus > 0; aus --)
      servoverticale.write(aus,150);
      delay(50);*/
}

