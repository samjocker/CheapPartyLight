#include <SPI.h>
#include "RF24.h"

RF24 rf24(9,8);
const byte addr[] = "1STC";
String msg;
char send_msg[32];
bool button;
int x,y,x_angle,y_angle;

void setup() {
  rf24.begin();
  rf24.setChannel(83);       // 設定頻道編號
  rf24.openWritingPipe(addr); // 設定通道位址
  rf24.setPALevel(RF24_PA_LOW);   // 設定廣播功率
  rf24.setDataRate(RF24_1MBPS); // 設定傳輸速率
  rf24.stopListening();       // 停止偵聽；設定成發射模式
  pinMode(2, INPUT);
}

void loop() {
  x = analogRead(A1);
  y = analogRead(A2);
  button = digitalRead(2);
  
  if (y_angle > 180){
    y_angle = 180;
  }
  else if (y_angle < 0){
    y_angle = 0;
  }
  else if (y > 600){
    y_angle = y_angle+6;
  }
  else if (y < 400){
    y_angle = y_angle-6;
  }
  //--------------
  if (x_angle > 180){
    x_angle = 180;
  }
  else if (x_angle < 0){
    x_angle = 0;
  }
  else if (x > 600){
    x_angle = x_angle+10;
  }
  else if (x < 400){
    x_angle = x_angle-10;
  }
  msg = String(x_angle)+','+String(y_angle)+','+String(button);
  msg.toCharArray(send_msg,32);
  rf24.write(&send_msg, sizeof(send_msg));
  delay(15);

}
