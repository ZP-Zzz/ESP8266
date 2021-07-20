/**********************************************************************
项目名称/Project          : 零基础入门学用物联网
程序名称/Program name     : stream_readString
团队/Team                : 太极创客团队 / Taichi-Maker (www.taichi-maker.com)
作者/Author              : CYNO朔
日期/Date（YYYYMMDD）     : 20200308
程序目的/Purpose          : 
Stream类用于处理字符数据流或二进制数据流。Stream类是不能被直接调用的。
然而当我们使用基于Stream类的库时，都会调用Stream中的内容。
 
以下Arduino库及相应库中的类都是基于Stream类所实现的。
 库                  类
Serial              Serial
SoftwareSerial    SoftwareSerial
Ehternet          EthernetClient
ESP8266FS         File
SD                File
Wire              Wire
GSM               GSMClient
WifiClient        WiFiClient
WiFiServer        WiFiServer
WiFiUDP           WiFiUDP
WiFiClientSecure  WiFiClientSecure
 
此程序使用Serial库来演示Stream类中的available()以及
readString函数的使用方法。
available函数将会返回开发板所接收到的stream中等待读取的字节数。
readString函数将读取stream中的字符并存储到字符中。
***********************************************************************/
 
void setup() {
  // 启动串口通讯
  Serial.begin(9600); 
  Serial.println();
}
 
void loop() {  
  if (Serial.available()){                    // 当串口接收到信息后
    String serialData = Serial.readString();  // 将接收到的信息使用readString()存储于serialData变量
    Serial.print(serialData);                 // 以便查看serialData变量的信息
  }
}
