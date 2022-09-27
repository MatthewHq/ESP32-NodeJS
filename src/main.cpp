#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>

#include <WebSocketsClient.h>
#include <creds.h>
// #include <string>
// using namespace std;
//
#define LED_BUILTIN 2

WebSocketsClient wsClient;
creds *credItem = new creds();
bool socketDone = false;

void onWSEvent(WStype_t type, uint8_t *payload, size_t length)
{
  Serial.println(type);
  switch (type)
  {
  case WStype_CONNECTED:
    Serial.println("WS Connected");
    socketDone = true;
    break;
  case WStype_DISCONNECTED:
    Serial.println("WS DISCONNECTed");
    socketDone = false;
    break;
  case WStype_ERROR:
    Serial.println("WS ERROR");
    Serial.printf("payload error", payload);
    break;
  }
}

WiFiMulti wifiMulti;

void setup()
{
 
  Serial.begin(921600);
  Serial.print("HEY I'M AWAKE|||");
  Serial.print(credItem->test_ca_cert);
  Serial.println("|||END CA CERT PRINT");
  pinMode(LED_BUILTIN, OUTPUT);

  wifiMulti.addAP(credItem->SSID, credItem->PASS);

  while (wifiMulti.run() != WL_CONNECTED)
  {
    delay(100);
  }
  
  Serial.println("Connected to ");
  Serial.print(WiFi.SSID()); // Tell us what network we're connected to
  Serial.println("IP address:\t");
  Serial.println(WiFi.localIP());

  Serial.println("============ ATTEMPTING SSL CONNECTION ===========");
  wsClient.beginSslWithCA(credItem->HOST, credItem->PORT, credItem->URL, credItem->test_ca_cert, "wss");
  wsClient.onEvent(onWSEvent);
}

// bool isConnected = false;

void loop()
{

  digitalWrite(LED_BUILTIN, WiFi.status() == WL_CONNECTED);
  // if (WiFi.status() == WL_CONNECTED && !isConnected)
  // {
  // Serial.println("Connected to WiFi!");
  // digitalWrite(LED_BUILTIN, HIGH);
  // isConnected = true;

  // if (!socketDone)
  // {

  // void WebSocketsClient::beginSslWithCA(const char * host, uint16_t port, const char * url, const char * CA_cert, const char * protocol) {
  // begin(host, port, url, protocol);
  //  wsClient.beginSSL(credItem->HOST, credItem->PORT, credItem->URL, "", "wss");

  // Serial.println("BEGINSSL...!");
  // }
  // }

  // if (WiFi.status() != WL_CONNECTED)
  // {
  //   isConnected = false;
  //   Serial.println("Connecting...!");
  //   digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

  //   delay(1000);
  // }

  // if (socketDone)
  // {
  wsClient.loop();
  // wsClient.onEvent(onWSEvent);
  // }
  // else
  // {
  // wsClient.beginSslWithCA(credItem->HOST, credItem->PORT, credItem->URL, credItem->CA, "wss");
  // Serial.println("BEGINSSL...!");
  // }
  Serial.println(hallRead());

  // Serial.println(credItem->SSID);
  delay(2000);

  // delay(1000);

  // Serial.println("Hey from Loops");
  // delay(1000);
  // digitalWrite(LED_BUILTIN, LOW);

  // digitalWrite(LED_BUILTIN, WiFi.status()==WL_CONNECTED);
  // Serial.println("Loop!");

  // Serial.println(WiFi.localIP());

  // put your main code here, to run repeatedly:
}