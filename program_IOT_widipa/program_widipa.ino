#include <LiquidCrystal.h>
#include <EEPROM.h>

#include "DHT.h"
#define PIN_DHT  A7
#define TIPE_DHT DHT11
DHT dht(PIN_DHT, TIPE_DHT);

#include <SoftwareSerial.h>
SoftwareSerial SIM800L(2,3);

//#include <avr/wdt.h> //Watchdog

#define fan 10
#define buzzer 12
#define tombol A4  // Harus Analog
#define suhu1 A0
#define suhu2 A1
#define suhu3 A2
#define suhu4 A3
#define suhu5 A6

//Button
#define CANCEL    (int)(analogRead(tombol)<10)
#define OK        (int)((analogRead(tombol)>239)&&(analogRead(tombol)<250))
#define UP        (int)((analogRead(tombol)>770)&&(analogRead(tombol)<790))
#define DOWN      (int)((analogRead(tombol)>495)&&(analogRead(tombol)<515))

float suhuA;
float suhuB;
float suhuC;
float suhuD;
float suhuE;
int kipas;
int alarm;
int chk;
float lembap;

const int rs = 9, en = 8, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int addr = 0;

//Alamat EEPROM
#define alamatKelembapan 0
#define alamatSuhu       10

//Data EEPROM
#define spkelembapan   EEPROM.read(alamatKelembapan)  
#define spsuhu         EEPROM.read(alamatSuhu)

void setup() 
{
  //wdt_disable();  
  
  dht.begin();
  
  lcd.begin(16, 2);

  lcd.setCursor(0,0);
  lcd.print("    BNDC 2019    ");
  delay(1000);

  lcd.setCursor(3,0);
  lcd.print("WIDIPA UGM");
  delay(1000);
  
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Arduino with SIM800L is ready");
  SIM800L.begin(9600);
  
  pinMode(fan,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(suhu1,INPUT);
  pinMode(suhu2,INPUT);
  pinMode(suhu3,INPUT);
  pinMode(suhu4,INPUT);
  pinMode(suhu5,INPUT);
  
  digitalWrite(fan,LOW);
  digitalWrite(buzzer,LOW);

  //wdt_enable(WDTO_4S);  //Watchdog. Jika program berhenti selama 4s, Arduino akan otomatis direset
}

void loop() 
{
  RUN();
}

