

void kirimLogKeweb(char *paramLog)
{
  disconnect();
  if (connect(server))
  {
    char x[100];
    strcpy(x, urlUpdateLog);
    strcat(x, paramLog);
    if (sendRequest(server, x) && skipResponseHeaders())
    {
    }
    delay(2000);
    while (client.available() > 0)
    {
      char a = (client.read());
      a = 0;
    }
  }
  else
  {

    Serial.println("ga konek");
  }
}
