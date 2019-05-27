#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include <math.h>
#include <SoftwareSerial.h>

#define DHTPIN 7
#define DHTTYPE DHT11

byte degreeChar[] = {
  B01000,
  B10100,
  B01000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

const int ledPin = 3;
const int light = A1;
const int RxD = 6;
const int TxD = 7;

double lightn = 0;
char val = '1';
int lightIntens = 0;
int currentIntens = 0;

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial bt(RxD, TxD); // rx, tx Cia gali tekti pakeisti

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(light,INPUT);
  dht.begin();
  lcd.init();           // initialize the lcd 
  lcd.backlight();
  lcd.noBlink();
  bt.begin(9600);
  Serial.println("Inicijavimas baigtas.");
}


void loop()
{
  delay(50);
  lightn = analogRead(light) / 100.0; // Nuskaitomas sviesos sensorius
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  
  if(bt.available())         //check if there's any data sent from the remote bluetooth shield
  {
    recvChar = blueToothSerial.read();
    Serial.print(recvChar);
  }
  if(Serial.available())                  //check if there's any data sent from the local serial terminal, you can add the other applications here
  {
    recvChar  = Serial.read();
    blueToothSerial.print(recvChar);
}

if(val == '0'){
  analogWrite(ledPin, 0);
}
  
  // ---------------------- Pagal apšvietimą -------------------
  if (val == '1')
  {
    double intens = ((-1)*pow((1.7*(double)lightn), 2)+1.7*(double)lightn+(double)256);
    lightIntens = (int)intens;
} else if (val == '2')
{
  Serial.print(t);
}
  //----------------- Rankinis valdymas --------------------
else if (val == '3')
{
  lightIntens = 0;
}
else if (val == '4')
{
  lightIntens = 64;
}
else if (val == '5')
{
  lightIntens = 128;
}
else if (val == '6')
{
  lightIntens = 192;
}
else if (val == '7')
{
  lightIntens = 255;
}
if((int)lightIntens < (int)40){
  lightIntens = 0;
  currentIntens = 0;
}
if((int)lightIntens >= (int)256){
  lightIntens = 255;
  currentIntens = 255;
}
  if(lightIntens < currentIntens -5){
  currentIntens -= 5;
  }
  else if(lightIntens > currentIntens +5){
  currentIntens += 5;
  }
  SetIntensity(currentIntens);
  
  lcd.createChar(0, degreeChar);
  lcd.setCursor(0,0);
  lcd.print("T:");
  lcd.print(t, 1);
  lcd.write(0);
  lcd.print("C ");
  lcd.setCursor(0,1);
  lcd.print("I:");
  lcd.print(lightn);
  lcd.setCursor(10,0);
  lcd.print("H:");
  lcd.print(round(h));
  lcd.print("% ");
  lcd.setCursor(14,1);
  lcd.print(" ");
  lcd.setCursor(10,1);
  lcd.print("L:");
  lcd.print(currentIntens/2.55, 0);
  lcd.print("% ");
  Serial.print(String(t) + " " + String(currentIntens));
  
  delay(200);
}

void SetIntensity(int value){
  analogWrite(ledPin, value);
}
