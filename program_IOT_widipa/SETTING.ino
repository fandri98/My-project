void SETTING() 
{
  digitalWrite(fan,HIGH);
  int set = 1;
  lcd.clear();
  
  while (1)
  {
    //wdt_reset(); //Jika tidak direset selama 4s, Arduino akan direset
    
    switch (set)
    {
      case 0:
        set = 2;
        break;
      case 1:
        lcd.setCursor(3, 0);
        lcd.print("SETTING");
        lcd.setCursor(0, 1);
        lcd.print(">SUHU");
        lcd.setCursor(8, 1);
        lcd.print("LEMBAPAN");
        break;
      case 2:
        lcd.setCursor(3, 0);
        lcd.print("SETTING");
        lcd.setCursor(0, 1);
        lcd.print("SUHU");
        lcd.setCursor(8, 1);
        lcd.print(">LEMBAPAN");
        break;
      case 3:
        set = 1;
        break;
    }

    //Ganti Setting
    if (UP)
    {
      delay(200);
      set--;
    }
    else if (DOWN)
    {
      delay(200);
      set++;
    }

    //Masuk ke salah satu setting
    if (OK && set == 1)
    {
      delay(200);
      settingSuhu();
    }
    else if (OK && set == 2)
    {
      delay(200);
      settingKelembapan();
    }
    else if (CANCEL) //Kembali ke menu
    {
      delay(200);
      MENU();
    }
  }
}

void settingSuhu()
{
  char text[20];
  int16_t suhuSementara = spsuhu;
  lcd.clear();

  while (1)
  {
    //wdt_reset(); //Jika tidak direset selama 4s, Arduino akan direset
    
    lcd.setCursor(0, 0);
    lcd.print("SP Suhu:");
    lcd.setCursor(0, 1);
    sprintf(text, "%4d ", suhuSementara);
    lcd.print(text);

    if (DOWN) {
      delay(200); lcd.clear();
      suhuSementara -= 1;
    }
    if (UP) {
      delay(200); lcd.clear();
      suhuSementara += 1;
    }


    if (CANCEL) {
      delay(200);
      suhuSementara = constrain(suhuSementara, 0, 255);  //Beri batas nilai karena 1 byte hanya bisa 0-255

      EEPROM.write(alamatSuhu, suhuSementara); delay(100);

      lcd.clear();
      lcd.setCursor(10, 0);
      lcd.print("saved");
      delay(350);
      SETTING(); //Kembali ke setting
    }
  }
}

void settingKelembapan()
{
  char text[20];
  int16_t kelembapanSementara = spkelembapan;
  lcd.clear();

  while (1)
  {
    //wdt_reset(); //Jika tidak direset selama 4s, Arduino akan direset
    
    lcd.setCursor(0, 0);
    lcd.print(" SP Kelembapan:");
    lcd.setCursor(0, 1);
    sprintf(text, "%4d ", kelembapanSementara);
    lcd.print(text);

    if (DOWN) {
      delay(200); lcd.clear();
      kelembapanSementara -= 1;
    }
    if (UP) {
      delay(200); lcd.clear();
      kelembapanSementara += 1;
    }


    if (CANCEL) {
      delay(200);
      kelembapanSementara = constrain(kelembapanSementara, 0, 255);  //Beri batas nilai karena 1 byte hanya bisa 0-255

      EEPROM.write(alamatKelembapan, kelembapanSementara); delay(100);  //Simpan ke EEPROM

      lcd.clear();
      lcd.setCursor(10, 0);
      lcd.print("saved");
      delay(350);
      SETTING(); //Kembali ke setting
    }
  }
}

