#include <math.h>

#define TO_DEG    57.29577951308
#define TO_RAD    0.01745329252

#define SERIAL_HEAD   '<'
#define SERIAL_TAIL   '\n'
#define STICK_SERIAL  Serial1

bool serial_receiving = false;
bool serial_new_data = false;
byte serial_ndx = 0, serial_recv_len = 0;
uint8_t serial_buffer[16];

#define BUTTON_A_PIN  A5
#define BUTTON_B_PIN  A4
#define START_PIN     8
#define SELECT_PIN    7
#define L3_PIN        13
#define R3_PIN        6
#define L1_PIN        11
#define R1_PIN        12
#define LX_PIN        A1
#define RX_PIN        A3
#define LY_PIN        A0
#define RY_PIN        A2

#define CROSS         (int)(analogRead(BUTTON_A_PIN)<10)
#define SQUARE        (int)((analogRead(BUTTON_A_PIN)>239)&&(analogRead(BUTTON_A_PIN)<250))
#define CIRCLE        (int)((analogRead(BUTTON_A_PIN)>770)&&(analogRead(BUTTON_A_PIN)<790))
#define TRIANGLE      (int)((analogRead(BUTTON_A_PIN)>495)&&(analogRead(BUTTON_A_PIN)<515))
#define ATAS          (int)((analogRead(BUTTON_B_PIN)>495)&&(analogRead(BUTTON_B_PIN)<515))
#define BAWAH         (int)(analogRead(BUTTON_B_PIN)< 10)
#define KANAN         (int)((analogRead(BUTTON_B_PIN)>770)&&(analogRead(BUTTON_B_PIN)<790))
#define KIRI          (int)((analogRead(BUTTON_B_PIN)>239)&&(analogRead(BUTTON_B_PIN)<250))
#define START         !digitalRead(START_PIN)
#define SELECT        !digitalRead(SELECT_PIN)
#define L3            !digitalRead(L3_PIN)
#define R3            !digitalRead(R3_PIN)
#define L1            !digitalRead(L1_PIN)
#define R1            !digitalRead(R1_PIN)
#define LX_RAW        analogRead(LX_PIN)
#define RX_RAW        analogRead(RX_PIN)
#define LY_RAW        analogRead(LY_PIN)
#define RY_RAW        analogRead(RY_PIN)
#define LX            map(LX_RAW,0,1023,-127,127)
#define RX            map(RX_RAW,0,1023,-127,127)
#define LY            map(LY_RAW,0,1023,-127,127)
#define RY            map(RY_RAW,0,1023,-127,127)
#define ARAH          (KANAN||KIRI||ATAS||BAWAH)

#define BUTTON1       CROSS+(SQUARE*2)+(CIRCLE*4)+(TRIANGLE*8)+(ATAS*16)+(BAWAH*32)+(KANAN*64)+(KIRI*128)
#define BUTTON2       START|(SELECT<<1)|(L3<<2)|(R3<<3)|(L1<<4)|(R1<<5)

float angle, magnitude, omega;
int8_t angle0, angle1, angle2, omg, mag;
int8_t lastBUTTON1, lastBUTTON2, lastOmega, lastMagnitude;
int16_t lastAngle;

uint8_t vib = 0;

unsigned long now = 0;

void setup() 
{  
  Serial.begin(38400);
  STICK_SERIAL.begin(9600);

  pinMode(START_PIN,  INPUT_PULLUP);
  pinMode(SELECT_PIN, INPUT_PULLUP);
  pinMode(L3_PIN,     INPUT_PULLUP);
  pinMode(R3_PIN,     INPUT_PULLUP);
  pinMode(L1_PIN,     INPUT_PULLUP);
  pinMode(R1_PIN,     INPUT_PULLUP);
}

void loop()
{
  //Serial.print(BUTTON1);Serial.print("  "); Serial.println(BUTTON2);
  //cekButton();
  calcParam();
  sendData();
  delay(10);
}

void calcParam()
{
  if (ARAH) magnitude = 100;
  
  if (KANAN) angle = 0;
  else if (ATAS) angle = 90;
  else if (KIRI) angle = 180;
  else if (BAWAH) angle = -90;
  else if (ATAS && KANAN) angle = 45;
  else if (KANAN && BAWAH) angle = 135;
  else if (BAWAH && KIRI) angle = -135;
  else if (KIRI && ATAS) angle = -45;
  else angle = 0;

  if (LX != 0 || LY != 0) 
  {
    magnitude = abs((sqrt(LX * LX + LY * LY) * 100 / 127));
    magnitude = constrain(magnitude, 0, 100);
    angle = (atan2((float)LY, (float)LX) * TO_DEG);
  }
      
  if(RX != 0) omega = (float)(RX*100.0)/127.0;
}

void sendData()
{
  angle0 = (int16_t) angle;
  angle1 = (int8_t)  (angle0);
  angle2 = (int8_t)  (angle0>>8);
  mag    = (int8_t)  (magnitude);
  omg    = (int8_t)  omega;
  
  
  if(millis()-now >= 50){

    if(BUTTON1 != lastBUTTON1 || BUTTON2 != lastBUTTON2 || angle0 != lastAngle || mag != lastMagnitude || omg != lastOmega )
    {
//      int8_t data[6] = {button1, button2, (int8_t) magnitude,
//                        ((int16_t) angle >> 8) & 0xFF, ((int16_t) angle) & 0xFF, 
//                        (int8_t) omega};
//
//      send_data(ADDRESS, data, 6);

      int8_t data[7] = {0x10, BUTTON1, BUTTON2, angle1, angle2, mag, omg};
      serial_send_packets( data, 7);
    
      lastBUTTON1    = BUTTON1;
      lastBUTTON2    = BUTTON2;
      lastAngle      = angle0;
      lastMagnitude  = mag;
      lastOmega      = omg;

      Serial.println("Sent");
    }
  
    now = millis();
  }

}

void cekButton()
{
  Serial.print("CROSS:");     Serial.print(CROSS);
  Serial.print(" CIRCLE:");   Serial.print(CIRCLE);
  Serial.print(" TRIANGLE:"); Serial.print(TRIANGLE);
  Serial.print(" SQUARE:");   Serial.print(SQUARE);
  Serial.print(" UP:");       Serial.print(ATAS);
  Serial.print(" DOWN:");     Serial.print(BAWAH);
  Serial.print(" RIGHT:");    Serial.print(KANAN);
  Serial.print(" LEFT:");     Serial.print(KIRI);
  Serial.print(" R1:");       Serial.print(R1);
  Serial.print(" L1:");       Serial.print(L1);
  Serial.print(" R3:");       Serial.print(R3);
  Serial.print(" L3:");       Serial.print(L3);
  Serial.print(" START:");    Serial.print(START);
  Serial.print(" SELECT:");   Serial.print(SELECT);
//  Serial.print(" LX:");       Serial.print(LX);
//  Serial.print(" LY:");       Serial.print(LY);
//  Serial.print(" RX:");       Serial.print(RX);
//  Serial.print(" RY:");       Serial.print(RY);
  Serial.print(" Agl:");      Serial.print(angle);
  Serial.print(" Mag:");      Serial.print(magnitude);
  Serial.print(" Omg:");      Serial.println(omega);
}
