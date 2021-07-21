/**********************************************************************
项目名称/Project          : 零基础入门学用物联网
程序名称/Program name     : arduinojosn_1_object
团队/Team                : 太极创客团队 / Taichi-Maker (www.taichi-maker.com)
作者/Author              : CYNO朔
日期/Date（YYYYMMDD）     : 20200424
程序目的/Purpose          : 
此程序用于演示如何使用arduinojson库解析以下json信息。该json包含一个对象，
对象中有一个数据。
{
  "name": "taichi-maker",
  "number": 1
}
***********************************************************************/
#include <ArduinoJson.h>

void setup() {
  Serial.begin(9600);
  Serial.println("");

  // 重点1：DynamicJsonDocument对象   size_t = unsigned long
  const size_t capacity = JSON_OBJECT_SIZE(2) + 30;  //含有两个键值对，30是余量
  DynamicJsonDocument doc(capacity);

  // 重点2：即将解析的json文件
  String json = "{\"name\":\"taichi-maker\",\"number\":1}";
  
  // 重点3：反序列化数据
  deserializeJson(doc, json);  //解析，并放在doc里

  // 重点4：获取解析后的数据信息
  String nameStr = doc["name"].as<String>();  //转换成字符串型
  int numberInt = doc["number"].as<int>();    //转换成整形型

  // 通过串口监视器输出解析后的数据信息
  Serial.print("nameStr = ");Serial.println(nameStr);
  Serial.print("numberInt = ");Serial.println(numberInt);
}

void loop() {}
