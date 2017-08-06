void olahResponseBukaPintu(const struct UserData *userData)
{
  bool updated = false;
  char noPintu[2];
  const char *temp1 = userData->control_door1;
  const char *temp2 = userData->control_door2;
  if (strcmp(temp1, "1") >= 0)
  {
    updated = true;
    digitalWrite(ledSwPintu1, HIGH);
    strcpy(noPintu, "1");
    digitalWrite(pintu1, relayOn);
    delay(jedaPowerOnPintu);
    digitalWrite(pintu1, relayOff);
    amanPintu1 = aman;
    Serial.println("pintu1_terbuka_dari_web");
    kirimLogKeweb("pintu1_terbuka_dari_web");
  }
  else if (strcmp(temp2, "1") >= 0)
  {
    updated = true;
    digitalWrite(ledSwPintu2, HIGH);
    strcpy(noPintu, "2");
    digitalWrite(pintu2, relayOn);
    delay(jedaPowerOnPintu);
    digitalWrite(pintu2, relayOff);
    amanPintu2 = aman;
    Serial.println("pintu2_terbuka_dari_web");
    kirimLogKeweb("pintu2_terbuka_dari_web");
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
  }
}
