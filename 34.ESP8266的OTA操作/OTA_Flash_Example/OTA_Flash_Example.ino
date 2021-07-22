/**********************************************************************
项目名称/Project          : 零基础入门学用物联网
程序名称/Program name     : OTA_Flash_Example
团队/Team                : 太极创客团队 / Taichi-Maker (www.taichi-maker.com)
作者/Author              : CYNO朔
日期/Date（YYYYMMDD）     : 20200713
程序目的/Purpose          : 
本示例程序用于演示ESP8266的OTA功能。通过本程序，我们将启动ESP8266的OTA程序上传功能。
我们将无需使用连接线将ESP8266与电脑进行连接，而可以使用WiFi对ESP8266上传程序。                  
***********************************************************************/
#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>
#include <Ticker.h>
 
// 闪烁时间间隔(秒)
const int blinkInterval = 1; 
 
// 设置wifi接入信息(请根据您的WiFi信息进行修改)
const char* ssid = "TP-LINK_46D02C";
const char* password = "32416500";
 
Ticker ticker;
 
void setup() {
  Serial.begin(9600);            
  Serial.println("");
  pinMode(LED_BUILTIN, OUTPUT);
 
  ticker.attach(blinkInterval, tickerCount);  // 设置Ticker对象
  
  connectWifi();
 
  // OTA设置并启动
  ArduinoOTA.setHostname("ESP8266");
  ArduinoOTA.setPassword("12345678");
  ArduinoOTA.begin();
  
  Serial.println("OTA ready");
}
void loop() {
  ArduinoOTA.handle();
}
 
// 在Tinker对象控制下，此函数将会定时执行。
void tickerCount(){
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}
 
void connectWifi(){
  //开始连接wifi
  WiFi.begin(ssid, password);
 
  //等待WiFi连接,连接成功打印IP
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected!");  
  Serial.print("IP address:\t");            
  Serial.println(WiFi.localIP());          
}
