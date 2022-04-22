// Program for Arduino version KEIO SD Westlab 2021.3
// Author: Tada Matz, Kanami Yuyama, Hiro West
// 定義
#define ARD_LED 13
#define RECVINTERVAL 50

#include "source.h" // 独自軽量化XBee関数
#include <MsTimer2.h> // タイマー割り込み
MyXBee myxbee;
// メッセージ受信用バッファ
String message;
int msglen;

void sendmsg(String message) {
  myxbee.broadcastXBeeData(message);
}

int recvret(0);
void recvmsg(void){
  String receiveStr = myxbee.receiveXBeeData();
  MsTimer2::stop();
  if(msglen > 0){
    // 重複割り込み発生
    Serial.println("ERR:Duplicated RECV Interrupt");
  }
  msglen = receiveStr.length();
  if (msglen > 0){ // パケットを受信した
    int messagelen = receiveStr.substring(0, 3).toInt();
    int loc = 3;
    message = receiveStr.substring(loc, loc+messagelen);
// 受信時の変数代入など簡単な処理を記述する。時間のかかる処理はアウト
  
// ここまで
  }
  MsTimer2::start();
// 受信時の比較的時間のかかる処理はここで記述することができる。
  if(msglen > 0){
//    message;
  }
  
// ここまで
}

void setup() {
  Serial.begin(9600);
  myxbee.init(Serial);
  pinMode(ARD_LED, OUTPUT);
  MsTimer2::set(RECVINTERVAL, recvmsg); // タイマー割り込みをかける
  MsTimer2::start();
  pinMode(2, INPUT);
}

void loop() {
  int a;
  String s;
  a = analogRead(2);
  s = "/"+String(a)+"/";
  Serial.println(s);
  sendmsg(s);
  delay(1000);
}
