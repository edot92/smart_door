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
  Serial.print("status_door1 = ");
  Serial.println(userData->status_door1);
  Serial.print("status_door2 = ");
  Serial.println(userData->status_door2);
  Serial.print("control_door1 = ");
  Serial.println(userData->control_door1);
  Serial.print("control_door2 = ");
  Serial.println(userData->control_door2);
}

// Close the connection with the HTTP server
void disconnect()
{
  //  Serial.println("Disconnect");
  client.stop();
  //  client.flush();
}

// Pause for a 1 minute
void wait()
{
  //  Serial.println("Wait 60 seconds");
  //  delay(60000);
  //  Serial.println("jeda 2 detik");
  // delay(2000);
}
