
/**********************************************************************
项目名称/Project          : 零基础入门学用物联网
程序名称/Program name     : wifiClient_request_basic
团队/Team                : 太极创客团队 / Taichi-Maker (www.taichi-maker.com)
作者/Author              : Dapenson
日期/Date（YYYYMMDD）     : 20200325
程序目的/Purpose          : 
此程序用于演示如何使用esp8266作为互联网客户端向www.example.com网站服务器发送http请求，
并且将网站服务器响应的信息输出在屏幕中
***********************************************************************/
#include <ESP8266WiFi.h>
 
const char* host = "api.seniverse.com"; // 网络服务器地址
const int httpPort = 80;              // http端口80
 
// 设置wifi接入信息(请根据您的WiFi信息进行修改)
const char* ssid = "TP-LINK_46D02C";
const char* password = "32416500";
 
void setup() {
  //初始化串口设置
  Serial.begin(9600);
  Serial.println("");
 
  //设置ESP8266工作模式为无线终端模式
  WiFi.mode(WIFI_STA);
 
  //开始连接wifi
  WiFi.begin(ssid, password);
 
  //等待WiFi连接,连接成功打印IP
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected!");
  
  wifiClientRequest();  
}


 
void loop(){}


 
// 向服务器发送HTTP请求
void wifiClientRequest()
{
  // 建立WiFi客户端对象，对象名称client
  WiFiClient client;    
 
  // 建立字符串，用于HTTP请求
  String httpRequest =  String("GET /v3/weather/now.json?key=SCXC4Mj_0aB96cZup&location=xuzhou&language=en&unit=c") + " HTTP/1.1\r\n" +
                        "Host: " + host + "\r\n" +
                        "Connection: close\r\n" +
                        "\r\n";
  
  // 通过串口输出连接服务器名称以便查阅连接服务器的网址                      
  Serial.print("Connecting to "); 
  Serial.print(host); 
 
  // 连接网络服务器
  if (client.connect(host, httpPort))
  { 
    Serial.println(" Success!");        // 连接成功后串口输出“Success”信息
    
    client.print(httpRequest);          // 向服务器发送HTTP请求
    Serial.println("Sending request: ");// 通过串口输出HTTP请求信息内容以便查阅
    Serial.println(httpRequest);     
    
    // 通过串口输出网络服务器响应信息
    Serial.println("Web Server Response:");  
    //一直接收响应信息，知道没有      
    while (client.connected() || client.available())
    { 
      if (client.available())
      {
        String line = client.readStringUntil('\n');
        Serial.println(line);
      }
    }
    
    client.stop();                      // 断开与服务器的连接
    Serial.print("Disconnected from "); // 并且通过串口输出断开连接信息
    Serial.print(host);
    
  } 
  else
  {    // 如果连接不成功则通过串口输出“连接失败”信息
    Serial.println(" connection failed!");
    client.stop();
  }  
}
