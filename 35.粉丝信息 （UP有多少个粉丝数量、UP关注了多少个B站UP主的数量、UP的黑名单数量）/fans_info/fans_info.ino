/**********************************************************************
项目名称/Project          : 零基础入门学用物联网
程序名称/Program name     : fans_info
团队/Team                : 太极创客团队 / Taichi-Maker (www.taichi-maker.com)
作者/Author              : CYNO朔
日期/Date（YYYYMMDD）     : 20200614
程序目的/Purpose          : 
通过ESP8266获取哔哩哔哩用户的粉丝信息（UP有多少个粉丝数量、UP关注了多少个B站UP主的数量、
UP的黑名单数量）。                             
***********************************************************************/
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>

const char* ssid     = "TP-LINK_46D02C";       // 连接WiFi名（此处使用taichimaker为示例）
                                            // 请将您需要连接的WiFi名填入引号中
const char* password = "32416500";          // 连接WiFi密码（此处使用12345678为示例）
                                            // 请将您需要连接的WiFi密码填入引号中
 
const char* host = "api.bilibili.com";     // 将要连接的服务器地址  
const int httpPort = 80;                   // 将要连接的服务器端口      

String mid = "44471237";                  // 哔哩哔哩用户id

void setup(){
  Serial.begin(9600);          
  Serial.println("");
  
  // 连接WiFi
  connectWiFi();
  ArduinoOTA.setHostname("ESP8266");
  ArduinoOTA.setPassword("12345678");
  ArduinoOTA.begin();
  
  Serial.println("OTA ready");
}
 
void loop(){
  // 建立哔哩哔哩API请求资源地址
  String reqRes = "/x/relation/stat?vmid=" + mid 
                   +"&type=json";

  // 向哔哩哔哩API服务器服务器请求信息并对信息进行解析
  httpRequest(reqRes);
  delay(3000);
}
 
// 向服务器请求信息并对信息进行解析
void httpRequest(String reqRes){
  WiFiClient client;

  // 建立http请求信息
  String httpRequest = String("GET ") + reqRes + " HTTP/1.1\r\n" + 
                              "Host: " + host + "\r\n" + 
                              "Connection: close\r\n\r\n";
  Serial.println(""); 
  Serial.print("Connecting to "); Serial.print(host);

  // 尝试连接服务器
  if (client.connect(host, 80))
  {
    Serial.println(" Success!");
 
    // 向服务器发送http请求信息
    client.print(httpRequest);
    Serial.println("Sending request: ");
    Serial.println(httpRequest);  
 
    // 获取并显示服务器响应状态行 
    String status_response = client.readStringUntil('\n');
    Serial.print("status_response: ");
    Serial.println(status_response);
 
    // 使用find跳过HTTP响应头
    if (client.find("\r\n\r\n")) 
    {
      Serial.println("Found Header End. Start Parsing.");
    }
    
    // 利用ArduinoJson库解析响应信息
     parseInfo(client); 
  } 
  else 
  {
    Serial.println(" connection failed!");
  }   
  //断开客户端与服务器连接工作
  client.stop(); 
}

// 连接WiFi
void connectWiFi(){
  WiFi.begin(ssid, password);                  // 启动网络连接
  Serial.print("Connecting to ");              // 串口监视器输出网络连接信息
  Serial.print(ssid); Serial.println(" ...");  // 告知用户NodeMCU正在尝试WiFi连接
  
  int i = 0;                                   // 这一段程序语句用于检查WiFi是否连接成功
  while (WiFi.status() != WL_CONNECTED) {      // WiFi.status()函数的返回值是由NodeMCU的WiFi连接状态所决定的。 
    delay(1000);                               // 如果WiFi连接成功则返回值为WL_CONNECTED                       
    Serial.print(i++); Serial.print(' ');      // 此处通过While循环让NodeMCU每隔一秒钟检查一次WiFi.status()函数返回值
  }                                            // 同时NodeMCU将通过串口监视器输出连接时长读秒。
                                               // 这个读秒是通过变量i每隔一秒自加1来实现的。                                              
  Serial.println("");                          // WiFi连接成功后
  Serial.println("Connection established!");   // NodeMCU将通过串口监视器输出"连接成功"信息。
  Serial.print("IP address:    ");             // 同时还将输出NodeMCU的IP地址。这一功能是通过调用
  Serial.println(WiFi.localIP());              // WiFi.localIP()函数来实现的。该函数的返回值即NodeMCU的IP地址。  
}

// 利用ArduinoJson库解析响应信息
void parseInfo(WiFiClient client)
{
  const size_t capacity = JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + 70;
  DynamicJsonDocument doc(capacity);
  
  deserializeJson(doc, client);
  
  int code = doc["code"]; 
  const char* message = doc["message"]; 
  int ttl = doc["ttl"]; 
  
  JsonObject data = doc["data"];
  long data_mid = data["mid"];
  int data_following = data["following"];
  int data_whisper = data["whisper"];
  int data_black = data["black"];
  int data_follower = data["follower"];
  
  Serial.println("=======================");
  Serial.print("Fen Si: ");              // 串口监视器输出粉丝数量
  Serial.println(data_follower);
  Serial.print("Guan Zhu: ");            // 串口监视器输出关注数量
  Serial.println(data_following);  
  Serial.print("Hei Ming Dan = ");       // 串口监视器输黑名单里的数量
  Serial.println(data_black);    
  Serial.print("=======================");
}
