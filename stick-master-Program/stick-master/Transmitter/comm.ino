//** serial comm
void encode_data(){
  // this is where to encode the data received, like the receive event in i2c
  // where serial_buffer[0] is the data type, and the rest is data
  
  byte head = serial_buffer[0];
  if(head == 0x11){
   vib = serial_buffer[1];
  }
}

void serial_receive(){
  while(STICK_SERIAL.available() > 0){
    uint8_t rc = STICK_SERIAL.read();
    
    if(serial_receiving){
      if(rc != SERIAL_TAIL){
        serial_buffer[serial_ndx] = rc;
        serial_ndx++;
      }
      else{
        serial_receiving = false;
        serial_new_data = true;
        serial_recv_len = serial_ndx; serial_ndx = 0;
      }
    }
    else if (rc == SERIAL_HEAD) {
      serial_receiving = true; 
      serial_new_data = false;
    }
  }
  
  if(serial_new_data) {
    encode_data();
    serial_new_data = false;
  }
}

void serial_send_packets(int8_t* data, byte len){
  STICK_SERIAL.write(SERIAL_HEAD);
  for(int i = 0; i < len; i++){
    STICK_SERIAL.write(data[i]);
  }
  STICK_SERIAL.write(SERIAL_TAIL);
}
void serial_send_packets(int16_t* data, byte len){
  STICK_SERIAL.write(SERIAL_HEAD);
  for(int i = 0; i < len; i++){
    serial_send(data[i]);
  }
  STICK_SERIAL.write(SERIAL_TAIL);
}
void serial_send_packets(int32_t* data, byte len){
  STICK_SERIAL.write(SERIAL_HEAD);
  for(int i = 0; i < len; i++){
    serial_send(data[i]);
  }
  STICK_SERIAL.write(SERIAL_TAIL);
}

void serial_send( int16_t data){
  uint8_t buff[2];
  memcpy(buff, &data, sizeof(uint16_t));
  STICK_SERIAL.write(buff, sizeof(int16_t));
}
void serial_send( int32_t data){
  uint8_t buff[4];
  memcpy(buff, &data, sizeof(uint32_t));
  STICK_SERIAL.write(buff, sizeof(int32_t));
}

