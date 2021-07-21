/**********************************************************************
步骤详解：
1. 使用Serial.begin指令启动串口通讯（此操作用于通过串口监视器检查解析结果）
2. 将需要解析的JSON数据文件复制粘贴到ArduinoJson Assistant在线工具
   https://arduinojson.org/v6/assistant/
3. 将Parsing代码复制粘贴到IDE中
4. 从Parsing代码中找到需要解析的数据所对应的const char*
5. 利用as函数需要解析的数据const char*转换为需要的格式
6. 为了代码精简，可删除无需解析的数据所对应的parsing代码部分
***********************************************************************/
#include <ArduinoJson.h>
void setup() {
  Serial.begin(9600);
  const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 2*JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(6) + 240;
  DynamicJsonBuffer jsonBuffer(capacity);

  const char* json = "{\"results\":[{\"location\":{\"id\":\"WW56FQXV5ZHB\",\"name\":\"Xuzhou\",\"country\":\"CN\",\"path\":\"Xuzhou,Xuzhou,Jiangsu,China\",\"timezone\":\"Asia/Shanghai\",\"timezone_offset\":\"+08:00\"},\"now\":{\"text\":\"Overcast\",\"code\":\"9\",\"temperature\":\"27\"},\"last_update\":\"2021-07-21T08:35:00+08:00\"}]}";

  JsonObject& root = jsonBuffer.parseObject(json);

  JsonObject& results_0 = root["results"][0];

  JsonObject& results_0_location = results_0["location"];
  const char* results_0_location_id = results_0_location["id"]; // "WW56FQXV5ZHB"
  const char* results_0_location_name = results_0_location["name"]; // "Xuzhou"
  const char* results_0_location_country = results_0_location["country"]; // "CN"
  const char* results_0_location_path = results_0_location["path"]; // "Xuzhou,Xuzhou,Jiangsu,China"
  const char* results_0_location_timezone = results_0_location["timezone"]; // "Asia/Shanghai"
  const char* results_0_location_timezone_offset = results_0_location["timezone_offset"]; // "+08:00"

  JsonObject& results_0_now = results_0["now"];
  const char* results_0_now_text = results_0_now["text"]; // "Overcast"
  const char* results_0_now_code = results_0_now["code"]; // "9"
  const char* results_0_now_temperature = results_0_now["temperature"]; // "27"

  const char* results_0_last_update = results_0["last_update"]; // "2021-07-21T08:35:00+08:00"

  //常量指针强制类型转换成字符串和整形
  String location_name_String = results_0["location"]["name"].as<String>();
  int now_temperature_int = results_0_now["temperature"].as<int>();

  Serial.println(location_name_String);
  Serial.println(now_temperature_int);
}
 
void loop() {
}
