/**********************************************************************
项目名称/Project          : 零基础入门学用物联网
程序名称/Program name     : arduinojosn_2_array
团队/Team                : 太极创客团队 / Taichi-Maker (www.taichi-maker.com)
作者/Author              : CYNO朔
日期/Date（YYYYMMDD）     : 20200424
程序目的/Purpose          : 
此程序用于演示如何使用arduinojson库解析以下json信息，该json包含一个数组，
数组有两个元素，每个元素都是一个对象，每一个对象都有一个数据。
[
  {
    "name": "taichi-maker"
  },
  {
    "website": "www.taichi-maker.com"
  }
]
***********************************************************************/
#include <ArduinoJson.h>
 
void setup() {
  Serial.begin(9600);
 
  // 重点1：DynamicJsonDocument对象
  
  // JSON_ARRAY_SIZE(2)       两个元素的数组J
  // 2*JSON_OBJECT_SIZE(1)    两个JSON对象，各自有一个键值对
  // 60                       余量
  const size_t capacity = JSON_ARRAY_SIZE(2) + 2*JSON_OBJECT_SIZE(1) + 60;
  DynamicJsonDocument doc(capacity);
  
  // 重点2：即将解析的json文件
  String json = "[{\"name\":\"taichi-maker\"},{\"website\":\"www.taichi-maker.com\"}]";
 
  // 重点3：反序列化数据
  deserializeJson(doc, json);
 
 
  String nameStr = doc[0]["name"].as<String>();
  String websiteStr = doc[1]["website"].as<String>();
 
  // 通过串口监视器输出解析后的数据信息
  Serial.print("nameStr = ");Serial.println(nameStr);
  Serial.print("websiteStr = ");Serial.println(websiteStr);
}
 
void loop() {}
