
#define SERIAL_HEAD   '<'
#define SERIAL_TAIL   '\n'
#define STICK_SERIAL  Serial1

bool serial_receiving = false;
bool serial_new_data = false;
byte serial_ndx = 0, serial_recv_len = 0;
uint8_t serial_buffer[16];
byte BUTTON1, BUTTON2;
int8_t magnitude, omega;
int16_t angle;

#define CROSS       (BUTTON1>>0)&(0x01)
#define SQUARE      (BUTTON1>>1)&(0x01)
#define CIRCLE      (BUTTON1>>2)&(0x01)
#define TRIANGLE    (BUTTON1>>3)&(0x01)
#define UP          (BUTTON1>>4)&(0x01)
#define DOWN        (BUTTON1>>5)&(0x01)
#define RIGHT       (BUTTON1>>6)&(0x01)
#define LEFT        (BUTTON1>>7)&(0x01)
#define START       (BUTTON2>>0)&(0x01)
#define SELECT      (BUTTON2>>1)&(0x01)
#define L3          (BUTTON2>>2)&(0x01)
#define R3          (BUTTON2>>3)&(0x01)
#define L1          (BUTTON2>>4)&(0x01)
#define R1          (BUTTON2>>5)&(0x01)

void setup() {
  Serial.begin(9600);
  STICK_SERIAL.begin(9600);
}

void loop(){
  serial_receive();
  cekButton();
  
}

void cekButton()
{
  Serial.print("CROSS:");     Serial.print(CROSS);
  Serial.print(" CIRCLE:");   Serial.print(CIRCLE);
  Serial.print(" TRIANGLE:"); Serial.print(TRIANGLE);
  Serial.print(" SQUARE:");   Serial.print(SQUARE);
  Serial.print(" UP:");       Serial.print(UP);
  Serial.print(" DOWN:");     Serial.print(DOWN);
  Serial.print(" RIGHT:");    Serial.print(RIGHT);
  Serial.print(" LEFT:");     Serial.print(LEFT);
  Serial.print(" R1:");       Serial.print(R1);
  Serial.print(" L1:");       Serial.print(L1);
  Serial.print(" R3:");       Serial.print(R3);
  Serial.print(" L3:");       Serial.print(L3);
  Serial.print(" START:");    Serial.print(START);
  Serial.print(" SELECT:");   Serial.println(SELECT);
}



