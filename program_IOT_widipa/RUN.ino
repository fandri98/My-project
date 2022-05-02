
//Variabel untuk Kirim SMS tiap 10 jam
int detik=0, menit=0, jam=0;

void RUN() {
  lcd.clear();
  unsigned long now = 0;
  digitalWrite(fan,HIGH);
  while (1)
  {
    if(millis()-now>1000)  //Sudah 1 detik
    {
      detik++;
      now = millis();
    }
    if(detik>59)  //Sudah 1 menit
    {
      menit++;
      detik = 0;
    }
    if(menit>59)  //Sudah 1 jam
    {
      jam++;
      menit = 0;
    }
    if(jam==8)  //Sudah 8 jam
    {
      SIM800L.write("AT+CMGF=1\r\n");
      delay(1000);
      SIM800L.write("AT+CMGS=\087834708958\"\r\n");
      delay(1000);
      SIM800L.write("Proses Pengeringan Gabah Anda Sudah Lebih Dari 10 jam, harap segera diperiksa. Matur sukma:)");    //Kirim SMS
      digitalWrite(buzzer, HIGH);       //Buzzer Nyala
      delay(10000);
      jam = 0;
    }
 
    
    //wdt_reset(); //Jika tidak direset selama 4s, Arduino akan direset
    
    lembap = analogRead(A7);
    lembap = (lembap/1024)*10;
    lcd.setCursor(12, 1);
    delay(500);
    lcd.print(lembap,1);

    suhuA = analogRead(suhu1);//nilai adc sensor
    suhuA = (suhuA / 1024) * 5000; //konversi analog jadi milivolt
    suhuA = suhuA / 10; //konversi derajat celcius dengan persamaan 1 derajat / 10 milivolt
    lcd.setCursor(0, 0);
    delay(500);
    lcd.print(suhuA,1);

    suhuB = analogRead(suhu2);//nilai adc sensor
    suhuB = (suhuB / 1024) * 5000; //konversi analog jadi milivolt
    suhuB = suhuB / 10; //konversi derajat celcius dengan persamaan 1 derajat / 10 milivolt
    lcd.setCursor(0, 1);
    delay(100);
    lcd.print(suhuB,1);

    suhuC = analogRead(suhu3);//nilai adc sensor
    suhuC = (suhuC / 1024) * 5000; //konversi analog jadi milivolt
    suhuC = suhuC / 10; //konversi derajat celcius dengan persamaan 1 derajat / 10 milivolt
    lcd.setCursor(6, 0);
    delay(100);
    lcd.print(suhuC,1);

    suhuD = analogRead(suhu4);//nilai adc sensor
    suhuD = (suhuD / 1024) * 5000; //konversi analog jadi milivolt
    suhuD = suhuD / 10; //konversi derajat celcius dengan persamaan 1 derajat / 10 milivolt
    lcd.setCursor(6, 1);
    delay(100);
    lcd.print(suhuD,1);

    suhuE = analogRead(suhu5);//nilai adc sensor
    suhuE = (suhuE / 1024) * 5000; //konversi analog jadi milivolt
    suhuE = suhuE / 10; //konversi derajat celcius dengan persamaan 1 derajat / 10 milivolt
    lcd.setCursor(12, 0);
    delay(100);
    lcd.print(suhuE,1);
//    
//    if ((suhuA > spsuhu) && (suhuB > spsuhu) && (suhuC > spsuhu) && (suhuD > spsuhu) && (suhuE > spsuhu) && (lembap <= spkelembapan))
//    {
//      digitalWrite(fan, HIGH);
//      digitalWrite(buzzer, LOW);
//      SIM800L.write("kipas hidup");
//      SIM800L.write((char)26);
//    }
//    else if ((suhuA < spsuhu) && (suhuB < spsuhu) && (suhuC < spsuhu) && (suhuD < spsuhu) && (suhuE < spsuhu) && (lembap >= spkelembapan))
//    {
//      digitalWrite(fan, LOW);
//      digitalWrite(buzzer, HIGH);
//      SIM800L.write("kipas mati");
//      SIM800L.write((char)26);
//    }

    if (CANCEL) //Kembali ke menu awal
    {
      delay(200);
      MENU();
    }
  }
}


