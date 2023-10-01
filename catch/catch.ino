#include <SPI.h>
#include "RF24.h"
#include <Servo.h>

RF24 rf24(9,8); // CE腳, CSN腳
Servo myservo_x;
Servo myservo_y;

const byte addr[] = "1STC";
const byte pipe = 1;  // 指定通道編號
String msg,x,y,button_get;
int x_angle,y_angle;
bool button;
char get_msg[32];

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void setup() {
  myservo_x.attach(3);
  myservo_y.attach(5);
  Serial.begin(9600);
  rf24.begin();
  rf24.setChannel(83);  // 設定頻道編號
  rf24.setPALevel(RF24_PA_LOW);
  rf24.setDataRate(RF24_1MBPS);
  rf24.openReadingPipe(pipe, addr);  // 開啟通道和位址
  rf24.startListening();  // 開始監聽無線廣播
  Serial.println("nRF24L01 ready!");
}

void loop() {
  if (rf24.available(&pipe)) {
    rf24.read(&get_msg, sizeof(get_msg));
    msg = String(get_msg);
    x = getValue(msg,',',0);
    y = getValue(msg,',',1);
    button_get = getValue(msg,',',2);
    x_angle = x.toInt();
    y_angle = y.toInt();
    myservo_x.write(x_angle);
    myservo_y.write(y_angle);
    Serial.println(y_angle);// 顯示訊息內容 
  }
}
