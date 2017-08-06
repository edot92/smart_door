
void olahResponseBukaPintu(const struct UserData *userData)
{
  bool updated = false;
  char noPintu[2];
  int pintu = 0;
  const char *temp1 = userData->control_door1;
  const char *temp2 = userData->control_door2;
  if (strcmp(temp1, "1") >= 0)
  {
    BeepBuzzer();
    delay(100);
    BeepBuzzer();

    updated = true;
    digitalWrite(ledSwPintu1, HIGH);
    strcpy(noPintu, "1");
    digitalWrite(pintu1, relayOn);
    // delay(jedaPowerOnPintu);
    amanPintu1 = aman;
    Serial.println("pintu1_terbuka_dari_web");
    kirimLogKeweb("pintu1_terbuka_dari_web");
    pintu = 1;
  }
  else if (strcmp(temp2, "1") >= 0)
  {
    BeepBuzzer();
    delay(100);
    BeepBuzzer();

    updated = true;
    digitalWrite(ledSwPintu2, HIGH);
    strcpy(noPintu, "2");
    digitalWrite(pintu2, relayOn);
    // delay(jedaPowerOnPintu);
    amanPintu2 = aman;
    Serial.println("pintu2_terbuka_dari_web");
    kirimLogKeweb("pintu2_terbuka_dari_web");
    pintu = 2;
  }
  if (updated == true)
  {
    disconnect();
    if (connect(server))
    {
      char x[100];
      strcpy(x, urlUpdateDoorOpened);
      strcat(x, noPintu);
      if (sendRequest(server, x) && skipResponseHeaders())
      {
      }
    }
    tungguSWTerkena(pintu);
  }
}

void tungguSWTerkena(int pintu)
{
  if (pintu == 1)
  {
    BeepBuzzer();
    while (digitalRead(swPintu1) != 0)
      ;
    {
    } //tunggu di buka
    BeepBuzzer();
    while (digitalRead(swPintu1) != 1)
      ;
    {
    } //tunggu di buka
    BeepBuzzer();
    delay(1000);
    digitalWrite(pintu1, relayOff);
  }
  else if (pintu == 2)
  {
    BeepBuzzer();
    while (digitalRead(swPintu2) != 0)
    {
    } //tunggu di buka
    BeepBuzzer();
    while (digitalRead(swPintu2) != 1)
    {
    } //tunggu di buka
    BeepBuzzer();
    delay(1000);
    digitalWrite(pintu2, relayOff);
  }
}

void BeepBuzzer()
{
  digitalWrite(pinBuzzer1, 1);
  delay(100);
  digitalWrite(pinBuzzer1, 0);
}