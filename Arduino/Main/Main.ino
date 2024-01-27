#include "WebServer.h"
#include <WiFi.h>
#include <SPI.h>

// Define Serial2 pins
#define RXD2 33
#define TXD2 4

// Create server and client objects
WebServer webServer;
WiFiServer wifiServer(100);
WiFiClient wifiClient;

// Global variables for state management
bool isConnected = false;
String readBuffer = "";
String sendBuffer = "";

void setup()
{
  // Initialize serial communications
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  // Start web server and WiFi server
  webServer.start();
  wifiServer.begin();

  // Print WiFi status
  printWifiStatus();
}

void loop()
{
  // Main loop to handle commands
  handleClient();
}

void handleClient()
{
  if (!isConnected)
  {
    connectClient();
  }
  else
  {
    processClientData();
  }
  delay(100);
}

void connectClient()
{
  wifiClient = wifiServer.available();
  if (wifiClient)
  {
    Serial.println("Got a client!");
    if (wifiClient.connected())
    {
      Serial.println("Client is connected.");
      isConnected = true;
    }
    else
    {
      Serial.println("Client not connected.");
      wifiClient.stop();
    }
  }
}

void processClientData()
{
  if (wifiClient.connected())
  {
    readAndForwardData();
    sendSerial2Data();
  }
  else
  {
    Serial.println("Client is gone.");
    wifiClient.stop();
    isConnected = false;
  }
}

void readAndForwardData()
{
  while (wifiClient.available())
  {
    char c = wifiClient.read();
    handleCharacterRead(c);
  }
}

void handleCharacterRead(char c)
{
  if (c == '{')
  {
    readBuffer = "";
  }
  readBuffer += c;
  if (c == '}')
  {
    Serial.println(readBuffer);
    Serial2.print(readBuffer);
    readBuffer = "";
  }
}

void sendSerial2Data()
{
  while (Serial2.available())
  {
    char c = Serial2.read();
    sendBuffer += c;
    if (c == '}')
    {
      wifiClient.print(sendBuffer);
      Serial.print(sendBuffer);
      sendBuffer = "";
    }
  }
}

void printWifiStatus()
{
  // Print WiFi connection details
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI): ");
  Serial.print(rssi);
  Serial.println(" dBm");
}
