/**********************************************************************
项目名称/Project          : 零基础入门学用物联网
程序名称/Program name     : arduinojson_spiffs_parse
团队/Team                : 太极创客团队 / Taichi-Maker (www.taichi-maker.com)
作者/Author              : CYNO朔
日期/Date（YYYYMMDD）     : 20200303
程序目的/Purpose          : 
演示如何利用arduinojson库分析SPIFFS系统中的config.json文件内容。
 
在测试以下示例程序前，请首先将以下zip文件下载并且解压缩。
解压缩后您将会得到一个JSON文件，该文件含有ESP8266连接WiFi的信息。
请根据您的WiFi环境进行相应调整再将文件上传到ESP8266的闪存根目录下。
 
http://www.taichi-maker.com/wp-content/uploads/2020/04/config.zip
 
ESP8266将会尝试从SPIFFS闪存文件系统中读取连接WiFi所需要的JSON文件，
并且对该文件进行解析然后将解析后的WiFi连接信息应用于程序中，从而实现ESP8266的联网操作。
 
如果您不清楚如何实现这一操作，请参考《零基础入门学用物联网》教程的ESP8266 NodeMCU 闪存文件系统（SPIFFS）</a>部分。
http://www.taichi-maker.com/homepage/esp8266-nodemcu-iot/iot-c/spiffs/
***********************************************************************/
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <FS.h>  
 
// 建立ESP8266WiFiMulti对象
ESP8266WiFiMulti wifiMulti;   
        
void setup(){
  Serial.begin(9600);          
  Serial.println("");
  
  // 启动闪存文件系统
  if(SPIFFS.begin()){                      
    Serial.println("SPIFFS Started.");
  } else {
    Serial.println("SPIFFS Failed to Start.");
  }
 
  // 建立DynamicJsonDocument对象
  const size_t capacity = JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(2) + 60;
  DynamicJsonDocument doc(capacity);
 
  // 从闪存文件系统中读取即将解析的json文件
  File file = SPIFFS.open("/config.json", "r"); 
 
  // 反序列化数据
  deserializeJson(doc, file);
 
  // 获取解析后的数据信息
  const char* wifi_ssid = doc["wifi"]["TP-LINK_46D02C"]; // "taichimaker"
  const char* wifi_password = doc["wifi"]["32416500"]; // "12345678"
 
  // 尝试联网
  wifiMulti.addAP(wifi_ssid, wifi_password);
  wifiMulti.addAP("TP-LINK_46D02C", "32416500"); 
  wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3");
  Serial.println("Connecting ..."); 
 
  int i = 0;  
  while (wifiMulti.run() != WL_CONNECTED) { // 尝试进行wifi连接。
    delay(1000);
    Serial.print(i++); Serial.print(' ');
  }
  
  // WiFi连接成功后将通过串口监视器输出连接成功信息 
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              // WiFi名称
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());           // IP
}
 
void loop(){}
