#include <Arduino.h>
#include <WiFi.h>
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
  switch (type)
  {
  case WStype_CONNECTED:
    Serial.println("WS Connected");
    socketDone = true;
    break;
  case WStype_DISCONNECTED:
    Serial.println("WS Connected");
    socketDone = false;
    break;
  case WStype_ERROR:
    Serial.println("WS ERROR");
    Serial.printf("payload error", payload);
    break;
  }
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(921600);
  Serial.println("HEY I'M AWAKE");

  WiFi.begin(credItem->SSID, credItem->PASS);

  // Serial.println(WiFi.localIP());
  // Serial.println(hallRead());
}

bool isConnected = false;

void loop()
{

  if (WiFi.status() == WL_CONNECTED && !isConnected)
  {
    Serial.println("Connected!");
    digitalWrite(LED_BUILTIN, HIGH);
    isConnected = true;

    if (!socketDone)
    {
      wsClient.beginSSL(credItem->HOST, credItem->PORT, credItem->URL, "", "wss");
      Serial.println("BEGINSSL...!");
    }
  }

  if (WiFi.status() != WL_CONNECTED)
  {
    isConnected = false;
    Serial.println("Connecting...!");
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

    delay(1000);
  }

  if (socketDone)
  {
    wsClient.loop();
    wsClient.onEvent(onWSEvent);
  }
  else
  {
    wsClient.beginSSL(credItem->HOST, credItem->PORT, credItem->URL, "", "wss");
    Serial.println("BEGINSSL...!");
  }
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