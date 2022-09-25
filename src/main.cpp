#include <Arduino.h>
#include <WiFi.h>
#include <WebSocketsClient.h>
#include <creds.h>
// #include <string>
// using namespace std;
//
#define LED_BUILTIN 2


WebSocketsClient wsClient;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(921600);
  Serial.println("HEY I'M AWAKE");
  creds* credItem= new creds();
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
  }

  if (WiFi.status() != WL_CONNECTED)
  {
    isConnected = false;
    Serial.println("Connecting...!");
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(1000);
  }

  Serial.println(hallRead());

  Serial.println(credItem->SSID);
  delay(500);

  // delay(1000);

  // Serial.println("Hey from Loops");
  // delay(1000);
  // digitalWrite(LED_BUILTIN, LOW);

  // digitalWrite(LED_BUILTIN, WiFi.status()==WL_CONNECTED);
  // Serial.println("Loop!");

  // Serial.println(WiFi.localIP());

  // put your main code here, to run repeatedly:
}