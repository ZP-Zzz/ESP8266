// For a connection via I2C using the Arduino Wire include:
#include <Wire.h>               // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Wire.h"        // legacy: #include "SSD1306.h"

#include "images.h"


// Initialize the OLED display using Arduino Wire:
   SSD1306Wire display(0x3c, D3, D5);  // ADDRESS, SDA, SCL 

int counter = 1;

void setup() {
  
  // 初始化UI也会初始化显示
  display.init();
}



void drawFontFaceDemo() 
{
    // Font Demo1
    display.setTextAlignment(TEXT_ALIGN_LEFT);  //文本左对齐
    display.setFont(ArialMT_Plain_10);  //字号，10号
    display.drawString(0, 0, "Hello world");
    display.setFont(ArialMT_Plain_16);  //字号，16号
    display.drawString(0, 10, "Hello world");
    display.setFont(ArialMT_Plain_24);  //字号，24号
    display.drawString(0, 26, "Hello world");
}


void drawTextAlignmentDemo()
{
    // Text alignment demo
    display.setFont(ArialMT_Plain_10); //字号，10号
    display.drawString(0, 0, "123");
    display.drawString(10, 10, "456");
    display.drawString(90, 20, "789");
}


// 在给定位置画一个像素
void drawRectDemo() {
      
    // 画一个叉×
    for (int i = 0; i < 10; i++)
    {
      display.setPixel(i, i);
      display.setPixel(10 - i, i);
    }
    // 画矩形
    display.drawRect(12, 12, 20, 20);

    // 填充矩形
    display.fillRect(14, 14, 17, 17);

    // 水平画一条线
    display.drawHorizontalLine(0, 40, 20);

    // 垂直画一条线
    display.drawVerticalLine(40, 0, 20);
}

//画圆
void drawCircleDemo() {
  for (int i=1; i < 8; i++) {
    display.setColor(WHITE);
    display.drawCircle(32, 32, i*3);
    if (i % 2 == 0) 
    {
      display.setColor(BLACK);
    }
    display.fillCircle(96, 32, 32 - i* 3);
  }
}


//画进度条
void drawProgressBarDemo() 
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

}


void drawImageDemo() 
{
    display.drawXbm(34, 14, WiFi_Logo_width, WiFi_Logo_height, WiFi_Logo_bits);
}


void loop() 
{
  
  // 清除显示
  display.clear();
  drawFontFaceDemo();
  display.display();
  delay(1000);


  display.clear();
  drawTextAlignmentDemo();
  display.display();
  delay(1000);

  display.clear();
  drawRectDemo();
  display.display();
  delay(1000);

  display.clear();
  drawCircleDemo();
  display.display();
  delay(1000);
 
  drawProgressBarDemo();

  display.clear();
  drawImageDemo();
  display.display();
  delay(1000);
}
