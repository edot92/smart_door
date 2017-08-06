void scanTombolDarurat()
{
  // if (digitalRead(btnDarurat1) == 0)
  // {
  //   Serial.println("tombol_darurat_1_di_tekan");
  //   digitalWrite(ledSwPintu1, HIGH);
  //   amanPintu1 = aman;
  //   digitalWrite(pintu1, relayOn);
  //   delay(jedaPowerOnPintu);
  //   digitalWrite(pintu1, relayOff);
  //   kirimLogKeweb("tombol _darurat_1_di_tekan");
  // }
  // if (digitalRead(btnDarurat2) == 0)
  // {
  //   Serial.println("tombol_darurat_2_di_tekan");
  //   digitalWrite(ledSwPintu2, HIGH);
  //   amanPintu2 = aman;
  //   digitalWrite(pintu2, relayOn);
  //   delay(jedaPowerOnPintu);
  //   digitalWrite(pintu2, relayOff);
  //   kirimLogKeweb("tombol_darurat_2_di_tekan");
  // }
}

void scanLimitSwitch()
{
  // Serial.println(digitalRead(swPintu1));
  // Serial.println(digitalRead(swPintu2));
  if (digitalRead(swPintu1) == 0)
  {
    if (amanPintu1 == aman)
    {
      Serial.println("ada pintu1_tertutup");
      amanPintu1 = standby;
      kirimLogKeweb("pintu1_tertutup");
    }
    else
    {
      //ada maling
      digitalWrite(pinBuzzer1, 1);
      Serial.println("ada maling,sistem_mendeteksi_kondisi_tidak_aman");
      Serial.println("tunggu tombol darurat di tekan , buzzer on");
      kirimLogKeweb("sistem_mendeteksi_kondisi_tidak_aman");
      int a = 0;
      while (a == 0)
      {
        digitalWrite(lednya, 1);
        delay(150);
        digitalWrite(lednya, 0);
        delay(150);
        if (digitalRead(btnDarurat1) == 0 || digitalRead(btnDarurat2) == 0)
        {
          a = 1;
        }
      }
      digitalWrite(ledSwPintu1, 0);
      digitalWrite(pinBuzzer1, 0);
      digitalWrite(lednya, 0);
      digitalWrite(pintu1, relayOn);
      delay(jedaPowerOnPintu);
      digitalWrite(pintu1, relayOff);
      Serial.println("tunggu switch terkena untuk masuk, buzzer off");
      // delay(1000);
      while (a == 1)
      {
        if (digitalRead(swPintu1) == 0)
        {
          a = 2;
        }
        digitalWrite(ledSwPintu1, 1);
        delay(200);
        digitalWrite(ledSwPintu1, 0);
        delay(200);
      } // tunggu sw terkena
      // digitalWrite(ledSwPintu1Out, 0);
      Serial.println("kondisi masuk aman melalui tombol darurat");
    }
    digitalWrite(ledSwPintu1, LOW);
  }
  else if (digitalRead(swPintu2) == 0)
  {
    if (amanPintu2 == aman)
    {
      amanPintu2 = standby;
      Serial.println("ada pintu2_tertutup");
      kirimLogKeweb("pintu2_tertutup");
    }
    else
    {
      //ada maling
      digitalWrite(pinBuzzer1, 1);
      kirimLogKeweb("sistem_mendeteksi_kondisi_tidak_aman");
      Serial.println("ada maling,sistem_mendeteksi_kondisi_tidak_aman");
      Serial.println("tunggu tombol darurat di tekan , buzzer on");
      int a = 0;
      while (a == 0)
      {
        digitalWrite(lednya, 1);
        delay(150);
        digitalWrite(lednya, 0);
        delay(150);

        if (digitalRead(btnDarurat1) == 0 || digitalRead(btnDarurat2) == 0)
        {
          a = 1;
        }
      } // tunggu tombol darurat di tekan
      digitalWrite(ledSwPintu2, 0);
      digitalWrite(pinBuzzer1, 0);
      digitalWrite(lednya, 0);
      digitalWrite(pintu2, relayOn);
      delay(jedaPowerOnPintu);
      digitalWrite(pintu2, relayOff);
      Serial.println("tunggu switch terkena untuk masuk , buzzer off");
      while (a == 1)
      {
        if (digitalRead(swPintu2) == 0)
        {
          a = 2;
        }
        digitalWrite(ledSwPintu2, 1);
        delay(200);
        digitalWrite(ledSwPintu2, 0);
        delay(200);
      } // tunggu sw terkena
      digitalWrite(ledSwPintu2, 0);
      Serial.println("kondisi masuk aman melalui tombol darurat");
    }
    digitalWrite(ledSwPintu2, LOW);
  }
}

void scanKeluar()
{
  Serial.println(digitalRead(btnKeluar1));
  Serial.println(digitalRead(btnKeluar2));
  if (digitalRead(btnKeluar1) == 0)
  {
    digitalWrite(ledSwPintu1Out, HIGH);
    digitalWrite(pintu1, relayOn);
    delay(jedaPowerOnPintu);
    digitalWrite(pintu1, relayOff);
    Serial.println("ada pintu_1_terbuka_dari_tombol_keluar");
    Serial.println("ada menunggu limit switch aktif");
    kirimLogKeweb("pintu_1_terbuka_dari_tombol_keluar");
    int x = 0;
    while (x == 0)
    {
      if (digitalRead(swPintu1) == 0)
      {
        x = 1;
      }
    } // tungu pintu ketutup
    digitalWrite(ledSwPintu1Out, LOW);
    delay(1000);
  }
  else if (digitalRead(btnKeluar2) == 0)
  {
    digitalWrite(ledSwPintu2Out, HIGH);
    digitalWrite(pintu2, relayOn);
    delay(jedaPowerOnPintu);
    digitalWrite(pintu2, relayOff);
    Serial.println("ada pintu_2_terbuka_dari_tombol_keluar");
    Serial.println("ada menunggu limit switch aktif");
    kirimLogKeweb("pintu_2_terbuka_dari_tombol_keluar");
    int x = 0;
    while (x == 0)
    {
      if (digitalRead(swPintu2) == 0)
      {
        x = 1;
      }
    } // tungu pintu ketutup
    digitalWrite(ledSwPintu2Out, LOW);
    delay(1000);
  }
}
