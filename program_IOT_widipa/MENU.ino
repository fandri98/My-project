void MENU() {
  int select = 1;
  lcd.clear();
  digitalWrite(fan,HIGH);
  while (1)
  {
    //wdt_reset(); //Jika tidak direset selama 4s, Arduino akan direset
    
    switch (select) {
      case 0:
        select = 2;
        break;
      case 1:
        lcd.setCursor(3, 0);
        lcd.print("WIDIPA UGM");
        lcd.setCursor(0, 1);
        lcd.print(">RUN");
        lcd.setCursor(9, 1);
        lcd.print("SETTING");
        break;
      case 2:
        lcd.setCursor(3, 0);
        lcd.print("WIDIPA UGM");
        lcd.setCursor(0, 1);
        lcd.print("RUN");
        lcd.setCursor(9, 1);
        lcd.print(">SETTING");
        break;
      case 3:
        select = 1;
        break;
    }

    //Untuk Ganti Menu
    if (UP)
    {
      delay(200);
      select--;
    }
    else if (DOWN)
    {
      delay(200);
      select++;
    }

    //Untuk Masuk RUN atau Setting
    if (OK && select == 1)
    {
      delay(200);
      RUN();
    }
    else if (OK && select == 2)
    {
      delay(200);
      SETTING();
    }
  }
}


