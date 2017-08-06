

void scanKeluar()
{
  int pintu = 0;
  //  Serial.println(digitalRead(btnKeluar1));
  //  Serial.println(digitalRead(btnKeluar2));
  if (digitalRead(btnKeluar1) == 0)
  {
    BeepBuzzer();
    pintu = 1;
    digitalWrite(ledSwPintu1Out, HIGH);
    digitalWrite(pintu1, relayOn);

    Serial.println("ada pintu_1_terbuka_dari_tombol_keluar");
    Serial.println("ada menunggu limit switch aktif");
    kirimLogKeweb("pintu_1_terbuka_dari_tombol_keluar");
    tungguSWTerkena(pintu);
  }
  else if (digitalRead(btnKeluar2) == 0)
  {
    pintu = 2;
    BeepBuzzer();

    digitalWrite(ledSwPintu2Out, HIGH);
    digitalWrite(pintu2, relayOn);
    // delay(jedaPowerOnPintu);
    // digitalWrite(pintu2, relayOff);
    Serial.println("ada pintu_2_terbuka_dari_tombol_keluar");
    Serial.println("ada menunggu limit switch aktif");
    kirimLogKeweb("pintu_2_terbuka_dari_tombol_keluar");
    tungguSWTerkena(pintu);
  }
}

void scanMaling()
{
  int adaMaling = 0;
  if (digitalRead(swPintu1) == 0)
  {
    kirimLogKeweb("sistem_mendeteksi_kondisi_tidak_aman di pintu 1");
    adaMaling = 1;
  }
  else if (digitalRead(swPintu2) == 0)
  {
    kirimLogKeweb("sistem_mendeteksi_kondisi_tidak_aman di pintu 2");
    adaMaling = 2;
  }
  if (adaMaling != 0)
  {

    int x = 0;
    while (adaMaling != 0)
    {
      BeepBuzzer();
      delay(200);
      if (adaMaling == 1)
      {
        if (digitalRead(btnDarurat1) == 0)
        {
          adaMaling = 0;
          digitalWrite(pintu1, LOW);
          delay(3000);
          tungguSWTerkena(1);
          delay(1000);
        }
      }
      else if (adaMaling == 2)
      {
        if (digitalRead(btnDarurat2) == 0)
        {
          adaMaling = 0;
          digitalWrite(pintu2, LOW);
          delay(3000);
          tungguSWTerkena(2);
          delay(1000);
        }
      }
    }
  }
}