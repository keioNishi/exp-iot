// Program for Arduino version KEIO SD Westlab 2021.3
// Author: Tada Matz, Kanami Yuyama, Hiro West
// 定義

#define RECVINTERVAL 100

#include "wxb.h" // 独自軽量化XBee関数
#include <MsTimer2.h> // タイマー割り込み
MyXBee myxbee;
// メッセージ受信用バッファ
int msglen;

void sendmsg(String message) {
  myxbee.broadcastXBeeData(message);
}

int recvret(0);
void recvmsg(void){
  MsTimer2::stop();
  String receiveStr = myxbee.receiveXBeeData();
  msglen = receiveStr.length();
  if (msglen > 0){ // パケットを受信したサイズを確認
// 受信時の変数代入など簡単な処理を記述する。時間のかかる処理はアウト
    Serial.println(receiveStr);
  }
  MsTimer2::start();
// 受信時の比較的時間のかかる処理はここで記述することができる。
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
  char s[100];
  a = analogRead(2);
  sprintf(s, "/a:%d/", a);
//  Serial.println(s);
  sendmsg(s);
  delay(1000);
}
