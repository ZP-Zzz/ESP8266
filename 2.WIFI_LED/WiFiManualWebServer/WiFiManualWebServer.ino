/*
    This sketch demonstrates how to set up a simple HTTP-like server.
    The server will set a GPIO pin depending on the request
      http://server_ip/gpio/0 will set the GPIO2 low,
      http://server_ip/gpio/1 will set the GPIO2 high
    server_ip is the IP address of the ESP8266 module, will be
    printed to Serial when the module is connected.
*/

#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "TP-LINK_46D02C"
#define STAPSK  "32416500"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

WiFiServer server(80);//开启扳子的port 80

void setup() 
{
  Serial.begin(115200);

  // prepare LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 0); //准备信号灯，并设置不亮

  // Connect to WiFi network
  Serial.println();  //打印空格
  Serial.println();  //打印空格
  Serial.print(F("Connecting to "));
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);   // 设置ESP8266为无线终端模式
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println();
  Serial.println(F("WiFi connected"));

  // Start the server
  server.begin();
  Serial.println(F("Server started"));

  Serial.println(WiFi.localIP());  //打印出扳子的IP
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) 
  {
    return;
  }
  Serial.println(F("new client"));

  client.setTimeout(5000); // default is 1000

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(F("request: "));
  Serial.println(req);

  // Match the request
  int val;
  if (req.indexOf(F("/gpio/0")) != -1) 
  {
    val = 0;
  } 
  else if (req.indexOf(F("/gpio/1")) != -1) 
  {
    val = 1;
  } 
  else 
  {
    Serial.println(F("invalid request"));
    val = digitalRead(LED_BUILTIN);
  }

  digitalWrite(LED_BUILTIN, val);

  while (client.available()) 
  {
   client.read();
  }

  // Send the response to the client
  // it is OK for multiple small client.print/write,
  // because nagle algorithm will group them into one single packet
  client.print(F("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now "));
  client.print((val) ? F("high") : F("low"));
  client.print(F("<br><br>Click <a href='http://"));
  client.print(WiFi.localIP());
  client.print(F("/gpio/1'>here</a> to switch LED GPIO on, or <a href='http://"));
  client.print(WiFi.localIP());
  client.print(F("/gpio/0'>here</a> to switch LED GPIO off.</html>"));

  // The client will actually be *flushed* then disconnected
  // when the function returns and 'client' object is destroyed (out-of-scope)
  // flush = ensure written data are received by the other side
  Serial.println(F("Disconnecting from client"));
}
