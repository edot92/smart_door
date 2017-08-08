#include <ArduinoJson.h>
#include <Ethernet.h>
#include <SPI.h>
char serverOffile = "192.168.137.1";
char serveronline = "ilma.smartdoor.karyateknologi.com ";
int portOffline = 10007;
int portOnline = 80;
char server[40] = "";
int portWeb = 0;
// const char *server = "192.168.137.1"; // server's address
// int portWeb = 10007;
// const char *server = "ilma.smartdoor.karyateknologi.com";
// int portWeb = 80;
int jedaPowerOnPintu = 4000;
const unsigned long HTTP_TIMEOUT = 5000; // max respone time from server
int sensorPin = A0;                      // select the input pin for the potentiometer
int ledPin = 17;                         // select the pin for the LED
int sensorValue = 0;                     // variable to store the value coming from the sensor
int pinBuzzer1 = 24;
int pinBuzzer2 = 25;
int pintu1 = 26;
int pintu2 = 27;
int btnDarurat1 = A8;
int swPintu1 = A13;  // A9
int btnKeluar1 = A9; //A14
int btnDarurat2 = A11;
int swPintu2 = A12;
int btnKeluar2 = A14;
int lednya = 13;
int ledInternet = 7;
int ledSwPintu1 = 44;
int ledSwPintu2 = 45;
int ledSwPintu1Out = 46;
int ledSwPintu2Out = 47;
int selectServerLokal = A0;
int selectServerOnline = A1;
int ledSelectServer = 13;
// update value
int adaMaling = 2;
int aman = 1;
int standby = 0;
int amanPintu1 = standby;
int amanPintu2 = standby;
EthernetClient client;
int relayOn = 0;
int relayOff = 1;
const char *urlGetLastValue = "/v1/mikro/getlastvalue";
const char *urlUpdateDoorOpened = "/v1/mikro/updateclosealldoor?door="; // http urlGetLastValue
const char *urlUpdateLog = "/v1/mikro/updatelogalat?log=";              // http log alat update
const unsigned long BAUD_RATE = 9600;                                   // serial connection speed
const size_t MAX_CONTENT_SIZE = 512;                                    // max size of the HTTP response
// assign a MAC address for the ethernet controller.
// fill in your address here:
byte mac[] = {
    0xDE,
    0xAD,
    0xBE,
    0xEF,
    0xFE,
    0xED};
// fill in an available IP address on your network here,
// for manual configuration:
IPAddress ip(192, 168, 137, 177);

// fill in your Domain Name Server address here:
//IPAddress myDns(192, 168, 137, 1);

struct UserData
{
  char status_door1[5];
  char status_door2[5];
  char control_door1[5];
  char control_door2[5];
};

// ARDUINO entry point #1: runs once when you press reset or power the board
void setup()
{
  initSerial();
  initEthernet();
  initPinMikro();
}

// ARDUINO entry point #2: runs over and over again forever
void loop()
{
  Serial.flush();
  if (connect(server))
  {
    Serial.println("membaca perintah buka pintu dari server dan membaca kondisi tidak aman");

    if (sendRequest(server, urlGetLastValue) && skipResponseHeaders())
    {
      UserData userData;
      if (readReponseContent(&userData))
      {
        printUserData(&userData);
        (&userData);
        olahResponseBukaPintu(&userData);
      }
    }
  }
  disconnect();
  // scanTombolDarurat();
  scanKeluar();
  scanMaling();
  //  client.flush();
  wait();
}

// Initialize Serial port
void initSerial()
{
  Serial.begin(BAUD_RATE);
  Serial.println("Serial ready");
}

// Initialize Ethernet library
void initEthernet()
{
  //  byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
  // if (!Ethernet.begin(mac))
  // {
  Serial.println("Failed to configure DHCP, SET TO STATIC");
  Ethernet.begin(mac, ip);
  // }
  Serial.println("Ethernet ready");
  //  delay(1000);
  // start the Ethernet connection using a fixed IP address and DNS server:

  // print the Ethernet board/shield's IP address:
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
  delay(2000);
}
void initPinMikro()
{
  delay(1000);
  pinMode(pinBuzzer1, OUTPUT);
  pinMode(pinBuzzer2, OUTPUT);
  pinMode(pintu1, OUTPUT);
  pinMode(pintu2, OUTPUT);
  pinMode(ledInternet, OUTPUT);
  pinMode(ledSwPintu1, OUTPUT);
  pinMode(ledSwPintu2, OUTPUT);
  pinMode(ledSwPintu1Out, OUTPUT);
  pinMode(ledSwPintu2Out, OUTPUT);
  for (int x = 0; x < 2; x++)
  {
    digitalWrite(pintu1, relayOn);
    digitalWrite(pintu2, relayOn);
    digitalWrite(pinBuzzer2, HIGH);
    digitalWrite(lednya, HIGH);
    digitalWrite(ledInternet, HIGH);
    digitalWrite(ledSwPintu1, HIGH);
    digitalWrite(ledSwPintu2, HIGH);
    digitalWrite(ledSwPintu1Out, HIGH);
    digitalWrite(ledSwPintu2Out, HIGH);
    delay(1000);
    digitalWrite(pintu1, relayOff);
    digitalWrite(pintu2, relayOff);
    digitalWrite(pinBuzzer2, LOW);
    digitalWrite(lednya, LOW);
    digitalWrite(ledInternet, LOW);
    digitalWrite(ledSwPintu1, LOW);
    digitalWrite(ledSwPintu2, LOW);
    digitalWrite(ledSwPintu1Out, LOW);
    digitalWrite(ledSwPintu2Out, LOW);
    delay(1000);
  }

  pinMode(btnDarurat1, INPUT_PULLUP);
  pinMode(swPintu1, INPUT_PULLUP);
  pinMode(btnKeluar1, INPUT_PULLUP);
  pinMode(btnDarurat2, INPUT_PULLUP);
  pinMode(swPintu2, INPUT_PULLUP);
  pinMode(btnKeluar2, INPUT_PULLUP);
  pinMode(selectServerLokal, INPUT_PULLUP);
  pinMode(selectServerOnline, INPUT_PULLUP);
  if (digitalRead(selectServerLokal) == 0)
  {
    digitalWrite(ledSelectServer, 1);
    strcpy(server, serverOffile);
    portWeb = portOffline;
  }
  else if (digitalRead(selectServerLokal) == 0)
  {
    digitalWrite(ledSelectServer, 0);
    strcpy(server, serveronline);
    portWeb = portOnline;
  }

else
{
  digitalWrite(ledSelectServer, 1);
  strcpy(server, serverOffile);
  portWeb = portOffline;
}

}

