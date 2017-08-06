#include <ArduinoJson.h>
#include <Ethernet.h>
#include <SPI.h>
const char *server = "192.168.137.1"; // server's address
int jedaPowerOnPintu = 8000;
int pinBuzzer1 = 24;
int pinBuzzer2 = 25;
int pintu1 = 26;
int pintu2 = 27;
int btnDarurat1 = A8;
int swPintu1 = A9;
int btnKeluar1 = A14;
int btnDarurat2 = A11;
int swPintu2 = A12;
int btnKeluar2 = A13;
int lednya = 13;
int ledInternet = 7;
int ledSwPintu1 = 44;
int ledSwPintu2 = 45;
int ledSwPintu1Out = 46;
int ledSwPintu2Out = 47;
// int relayOn = 0;
// int relayOff = 1;
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
const unsigned long HTTP_TIMEOUT = 10000;                               // max respone time from server
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
int portWeb = 8080;
// fill in your Domain Name Server address here:
IPAddress myDns(192, 168, 137, 1);

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
  Serial.println("membaca perintah buka pintu dari server dan membaca kondisi tidak aman");
  if (connect(server))
  {
    if (sendRequest(server, urlGetLastValue) && skipResponseHeaders())
    {
      UserData userData;
      if (readReponseContent(&userData))
      {
        printUserData(&userData);
        olahResponseBukaPintu(&userData);
      }
    }
  }
  disconnect();
  scanTombolDarurat();
  scanLimitSwitch();
  scanKeluar();
  client.flush();
  wait();
}

// Initialize Serial port
void initSerial()
{
  Serial.begin(BAUD_RATE);
  // while (!Serial)
  // {
  //   ; // wait for serial port to initialize
  // }
  Serial.println("Serial ready");
}

// Initialize Ethernet library
void initEthernet()
{
  //  byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
  //  if (!Ethernet.begin(mac)) {
  //    Serial.println("Failed to configure Ethernet");
  //    return;
  //  }
  //  Serial.println("Ethernet ready");
  //  delay(1000);
  // start the Ethernet connection using a fixed IP address and DNS server:
  Ethernet.begin(mac, ip, myDns);
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
}
// Open connection to the HTTP server
bool connect(const char *hostName)
{
  //  Serial.print("Connect to ");
  //  Serial.println(hostName);

  bool ok = client.connect(hostName, portWeb);

  //  Serial.println(ok ? "Connected" : "Connection Failed!");
  if (ok)
  {
    digitalWrite(ledInternet, HIGH);
  }
  else
  {
    digitalWrite(ledInternet, LOW);
  }
  return ok;
}

// Send the HTTP GET request to the server
bool sendRequest(const char *host,
                 const char *dataUrl)
{
  //  Serial.print("GET ");
  //  Serial.println(dataUrl);

  client.print("GET ");
  client.print(dataUrl);
  client.println(" HTTP/1.1");
  client.print("Host: ");
  client.println(host);
  client.println("Connection: close");
  client.println();

  return true;
}

// Skip HTTP headers so that we are at the beginning of the response's body
bool skipResponseHeaders()
{
  // HTTP headers end with an empty line
  char endOfHeaders[] = "\r\n\r\n";

  client.setTimeout(HTTP_TIMEOUT);
  bool ok = client.find(endOfHeaders);

  if (!ok)
  {
    Serial.println("No response or invalid response!");
  }

  return ok;
}

// Parse the JSON from the input string and extract the interesting values
// Here is the JSON we need to parse

//    "status_door1": "1",
//    "status_door2": "0",
//    "control_door1": "1",
//    "control_door2": "1",

bool readReponseContent(struct UserData *userData)
{
  // Compute optimal size of the JSON buffer according to what we need to parse.
  // This is only required if you use StaticJsonBuffer.
  const size_t BUFFER_SIZE =
      JSON_OBJECT_SIZE(4) // the root object has 4 elements
      //      + JSON_OBJECT_SIZE(7)  // the "data" object has 7 elements
      + MAX_CONTENT_SIZE; // additional space for strings

  // Allocate a temporary memory pool
  DynamicJsonBuffer jsonBuffer(BUFFER_SIZE);

  JsonObject &root = jsonBuffer.parseObject(client);

  if (!root.success())
  {
    Serial.println("JSON parsing failed!");
    return false;
  }

  strcpy(userData->status_door1, root["status_door1"]);
  strcpy(userData->status_door2, root["status_door2"]);
  strcpy(userData->control_door1, root["control_door1"]);
  strcpy(userData->control_door2, root["control_door2"]);

  return true;
}

// Print the data extracted from the JSON
void printUserData(const struct UserData *userData)
{
  //  Serial.print("status_door1 = ");
  //  Serial.println(userData -> status_door1);
  //  Serial.print("status_door2 = ");
  //  Serial.println(userData -> status_door2);
  //  Serial.print("control_door1 = ");
  //  Serial.println(userData -> control_door1);
  //  Serial.print("control_door2 = ");
  //  Serial.println(userData -> control_door2);
}

// Close the connection with the HTTP server
void disconnect()
{
  //  Serial.println("Disconnect");
  client.stop();
  client.flush();
}

// Pause for a 1 minute
void wait()
{
  //  Serial.println("Wait 60 seconds");
  //  delay(60000);
  //  Serial.println("jeda 2 detik");
  // delay(2000);
}
