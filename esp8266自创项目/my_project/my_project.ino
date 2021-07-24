#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "SSD1306Wire.h" 
#include <Wire.h> 
#include <Ticker.h> 
#include <ArduinoJson.h>

#define WiFi_Logo_width 60
#define WiFi_Logo_height 36
const uint8_t WiFi_Logo_bits[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xFF, 0x07, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xE0, 0xFF, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF,
  0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0xFF, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xFE, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
  0xFF, 0x03, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
  0x00, 0xFF, 0xFF, 0xFF, 0x07, 0xC0, 0x83, 0x01, 0x80, 0xFF, 0xFF, 0xFF,
  0x01, 0x00, 0x07, 0x00, 0xC0, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x0C, 0x00,
  0xC0, 0xFF, 0xFF, 0x7C, 0x00, 0x60, 0x0C, 0x00, 0xC0, 0x31, 0x46, 0x7C,
  0xFC, 0x77, 0x08, 0x00, 0xE0, 0x23, 0xC6, 0x3C, 0xFC, 0x67, 0x18, 0x00,
  0xE0, 0x23, 0xE4, 0x3F, 0x1C, 0x00, 0x18, 0x00, 0xE0, 0x23, 0x60, 0x3C,
  0x1C, 0x70, 0x18, 0x00, 0xE0, 0x03, 0x60, 0x3C, 0x1C, 0x70, 0x18, 0x00,
  0xE0, 0x07, 0x60, 0x3C, 0xFC, 0x73, 0x18, 0x00, 0xE0, 0x87, 0x70, 0x3C,
  0xFC, 0x73, 0x18, 0x00, 0xE0, 0x87, 0x70, 0x3C, 0x1C, 0x70, 0x18, 0x00,
  0xE0, 0x87, 0x70, 0x3C, 0x1C, 0x70, 0x18, 0x00, 0xE0, 0x8F, 0x71, 0x3C,
  0x1C, 0x70, 0x18, 0x00, 0xC0, 0xFF, 0xFF, 0x3F, 0x00, 0x00, 0x08, 0x00,
  0xC0, 0xFF, 0xFF, 0x1F, 0x00, 0x00, 0x0C, 0x00, 0x80, 0xFF, 0xFF, 0x1F,
  0x00, 0x00, 0x06, 0x00, 0x80, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x07, 0x00,
  0x00, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0xF8, 0xFF, 0xFF,
  0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0x01, 0x00, 0x00,
  0x00, 0x00, 0xFC, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF,
  0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0x1F, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x80, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  };






SSD1306Wire display(0x3c, D3, D5);  //SDA, SCL 

const char *ssid     = "TP-LINK_46D02C";
const char *password = "32416500";

const char* host = "api.seniverse.com";     // 将要连接的服务器地址  
const int httpPort = 80;                    // 将要连接的服务器端口 

// 心知天气HTTP请求所需信息
String reqUserKey = "SY7PlK2gea4ynluag";   // 私钥
String reqLocation = "Xuzhou";            // 城市
String reqUnit = "c";                      // 摄氏/华氏

//存放天气/温度
String results_0_now_text_str; 
int results_0_now_temperature_int;  


WiFiUDP ntpUDP;
Ticker ticker1;// 建立Ticker用于实现定时功能
Ticker ticker2;

NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 60*60*8, 30*60*1000);

int i=0;
int counter = 1;                            
int counter2 = 1;  
                  

void setup()
{

  Serial.begin(9600);
  display.init();
  
  connectWiFi();
  
  timeClient.begin();
    
  ticker1.attach(1, timeupdate);
  ticker2.attach(1, count);
}


void count()
{
  i++;
  if(i==31)
  {
    i=0;
  }
  
}



void loop() 
{

  timeClient.update();

 
  String reqRes = "/v3/weather/now.json?key=" + reqUserKey +    // 建立心知天气API当前天气请求资源地址
                  + "&location=" + reqLocation + 
                  "&language=en&unit=" +reqUnit;
                  
  if(i==0)
  {
    httpRequest(reqRes); // 向心知天气服务器服务器请求信息并对信息进行解析 
  }              
   
  showoled();   // oled显示时间和天气

}



void connectWiFi()
{
  WiFi.begin(ssid, password);                  // 启动网络连接
  
  display.clear();
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 0, "Connecting to Wifi...");
  display.drawString(0, 20, String(ssid));
  display.display();

  delay(4500);
  if(WiFi.status() == WL_CONNECTED)
  {
    display.clear();   
    display.drawString(0, 0, "Connection established!");    
    display.drawString(0,20, "IP address:");                                                               
    display.drawString(10,35, WiFi.localIP().toString());  
    display.display();
    delay(1000);
  }
  else
  {
     display.clear();
     display.drawString(0, 0, "connection timed out!");
     display.display();
     delay(2000);
  }
}                                      



//利用中断一直获取时间
void timeupdate()
{
  timeClient.update();
}



void showoled()
{

  while(counter)
  {
    display.clear();
    // 绘制进度条
    display.drawProgressBar(0, 32, 120, 10, counter); //(x,y,进度条长度,进度条宽度,  )
    // 将百分比绘制为字符串
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.drawString(64, 15, String(counter) + "%");
    counter++;
    display.display();
    if(counter==100)
    {counter=0;}        //只显示一次，因为counter=0进不去了
    delay(10);
  }
  while(counter2)
  {
    display.clear();
    display.drawXbm(34, 14, WiFi_Logo_width, WiFi_Logo_height, WiFi_Logo_bits);
    display.display();
    delay(1500);
    counter2=0;    
  }
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(5, 0, "Now time");
  display.drawString(49, 0, ":");
  display.drawString(55,0, String(timeClient.getHours()));
  display.drawString(67,0, ":");
  display.drawString(73,0,String(timeClient.getMinutes()));
  display.drawString(85, 0, ":");
  display.drawString(90, 0,String(timeClient.getSeconds())); 
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 15, "location");
  display.drawString(60, 15, ":");
  display.drawString(67, 15, reqLocation);
  display.drawString(0, 30, "weather");
  display.drawString(60, 30, ":");
  display.drawString(67, 30, results_0_now_text_str);
  display.drawString(0, 47, "temperature");
  display.drawString(88, 47, ":"); 
  display.drawString(93, 47, String(results_0_now_temperature_int));
  display.drawString(112, 47,"°");
  display.drawString(117, 47,"C");
  
  display.display();
   
  
}






void httpRequest(String reqRes)
{
  WiFiClient client;
 // 建立http请求信息
  String httpRequest = String("GET ") + reqRes + " HTTP/1.1\r\n" + 
                              "Host: " + host + "\r\n" + 
                              "Connection: close\r\n\r\n";

  // 尝试连接服务器
  if (client.connect(host, 80))
  {
    Serial.println(" Success!");
    
    // 向服务器发送http请求信息
    client.print(httpRequest); 
    delay(400);    
    // 使用find跳过HTTP响应头
    if (client.find("\r\n\r\n"))
    {
      Serial.println("Found Header End. Start Parsing.");
    }
    
    // 利用ArduinoJson库解析心知天气响应信息
    parseInfo(client); 
  } 
  else 
  {
    Serial.println(" connection failed!");
  }   
  //断开客户端与服务器连接工作
  client.stop(); 
}


// 利用ArduinoJson库解析心知天气响应信息
void parseInfo(WiFiClient client){
  const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 2*JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(6) + 230;
  DynamicJsonDocument doc(capacity);
  
  deserializeJson(doc, client);
  
  JsonObject results_0 = doc["results"][0];
  
  JsonObject results_0_now = results_0["now"];
  const char* results_0_now_text = results_0_now["text"]; // "Sunny"
  const char* results_0_now_temperature = results_0_now["temperature"]; // "32"
  
  const char* results_0_last_update = results_0["last_update"]; // "2020-06-02T14:40:00+08:00" 
 
   // 通过串口监视器显示以上信息
  results_0_now_text_str = results_0_now["text"].as<String>(); 
  results_0_now_temperature_int = results_0_now["temperature"].as<int>(); 
  String results_0_last_update_str = results_0["last_update"].as<String>(); 
 
  Serial.println(F("======Weahter Now======="));
  Serial.print(F("Weather Now: "));
  Serial.println(results_0_now_text_str);
  Serial.print(F("Temperature: "));
  Serial.println(results_0_now_temperature_int);
  Serial.print(F("Last Update: "));
  Serial.println(results_0_last_update_str);
  Serial.println(F("========================"));


}  
