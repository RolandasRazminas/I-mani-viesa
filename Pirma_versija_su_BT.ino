#include <SoftwareSerial.h>

const int light = A1;
const int temp = A0;
int ledPin = 3;
float lightn = 0;
double tempn = 0;
char val = '5';

SoftwareSerial bt(7, 6); // rx, tx Cia gali tekti pakeisti


void setup()
{
  Serial.begin(9600);
  bt.begin(9600);
  Serial.println("Prisijunge");
  pinMode(ledPin,OUTPUT);
  pinMode(light,INPUT);
  pinMode(temp,INPUT);
}

void loop ()
{
  lightn = analogRead(light) / 100; // Nuskaitomas sviesos sensorius
  tempn = (analogRead(temp) * 114.4)/1024; // Nuskaitomas temperaturos sensorius
 // digitalWrite(13, HIGH); // sets the digital pin 13 on
   // analogWrite(ledPin, 255);
   // delay(2000);
   // analogWrite(ledPin, 0);
   // delay(2000);
   // analogWrite(ledPin, 128);
   // delay(2000);
  //  analogWrite(ledPin, 192);
  //  delay(2000);
  //  analogWrite(ledPin, 64);
  //  delay(2000);
   // Serial.println("Praejo visos stadijos");
    //  digitalWrite(13, LOW);  // sets the digital pin 13 off
                          //Bt testavimui
    if(bt.available() > 0)
    {
          val = bt.read();
    }
    Serial.print(val);
    Serial.print("   ");
    Serial.print(tempn);
    Serial.print("   ");
    Serial.print(lightn);
    Serial.println("");
    delay(500);
    //----------------------------------------Pagal sviesa-------------------------------
if (val == '1') //
{
  if (lightn < 4 && lightn > 0)
  {
    analogWrite(ledPin, 255);
  }
  if (lightn < 6 && lightn > 4)
  {
    analogWrite(ledPin, 192);
  }
  if(lightn < 8 && lightn > 6)
  {
    analogWrite(ledPin, 128);
  }
  if (lightn < 10 && lightn > 8)
  {
    analogWrite(ledPin, 64);
  }
  if ( lightn > 10)
  {
  analogWrite(ledPin, 0);
  }
}
//--------------------------Pagal temperatura`-------------------------------------
if (val == '2') // voltai yra konvertuojami i temperetaura ir issiunciami i susieta bt itaisa.  T(C)=(vout(mv)-500)/10
{
  float t = ((tempn * 1000) - 500 ) / 10; 
  bt.print(t);
}
//``````````````````````````````Rankinis valdimas``````````````````````````````````````
if (val == '3')
{
  analogWrite(ledPin, 0);
}
if (val == '4')
{
  analogWrite(ledPin, 64);
}
if (val == '5')
{
  analogWrite(ledPin, 128);
}
if (val == '6')
{
  analogWrite(ledPin, 192);
}
if (val == '7')
{
  analogWrite(ledPin, 255);
}
}
