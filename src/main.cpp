#include <Arduino.h>
//#include <WiFi.h>
#include <WiFiMulti.h>

#include <string> 
#include <WebSocketsClient.h>
#include <creds.h>
// #include <string>
// using namespace std;
//
#define LED_BUILTIN 2

WebSocketsClient wsClient;
creds *credItem = new creds();
WiFiMulti wifiMulti;

void onWSEvent(WStype_t type, uint8_t *payload, size_t length)
{

  Serial.println(type);

  switch (type)
  {
  case WStype_CONNECTED:
    Serial.println("WS Connected");
    //wsClient.sendTXT("HELLLLLO");
    break;
  case WStype_DISCONNECTED:
    Serial.println("WS DISCONNECTed");
    break;
  case WStype_ERROR:
    Serial.println("WS ERROR");
    Serial.printf("payload error", payload);
    break;
  case WStype_TEXT:
    Serial.println("TEXT RECEIVED");
    Serial.printf("TXT", payload);
    break;
  }
}



void setup()
{
  Serial.begin(921600);
  Serial.println("HEY I'M AWAKE");
  pinMode(LED_BUILTIN, OUTPUT);

  wifiMulti.addAP(credItem->SSID, credItem->PASS);

  Serial.print("Connecting");
  while (wifiMulti.run() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(200);
  }

  Serial.println("\nConnected to ");
  Serial.print(WiFi.SSID()); // Tell us what network we're connected to
  Serial.println("IP address:\t");
  Serial.println(WiFi.localIP());

  Serial.println("============ ATTEMPTING WEBSOCKET CONNECTION ===========");
  // wsClient.beginSslWithCA(credItem->HOST, credItem->PORT, credItem->URL, credItem->test_ca_cert, "wss");// !!!!! CERT HERE
  // wsClient.beginSSL(credItem->HOST, credItem->PORT, credItem->URL, "", "wss");
  wsClient.begin(credItem->HOST, credItem->PORT);
  // Serial.println("Say Hello? After wsClientBegin");
  wsClient.onEvent(onWSEvent);
  wsClient.setReconnectInterval(5000);
}

// bool isConnected = false;

void loop()
{

  digitalWrite(LED_BUILTIN, WiFi.status() == WL_CONNECTED);
  wsClient.loop();
  // Serial.println("Loop Now");
  delay(200);

  char buffer [sizeof(int)*8+1];
  int hall=hallRead();


  wsClient.sendTXT(+itoa(hall,buffer,10));
  // Serial.println("Post Loop");
  // wsClient.sendTXT("HELLLLLO");
}