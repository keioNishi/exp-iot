/*
   wxb.cpp
   Author: Tada Matz, Hiro West, WestLab
   Comment: Methods of MyXBee class
*/

#include "wxb.h"

MyXBee::MyXBee() {
  xbee = XBee();
  //receive
  response = XBeeResponse();
  rx = ZBRxResponse(); // create reusable response objects for responses we expect to handle
}

void MyXBee::init(Stream &serial) {
  xbee.setSerial(serial); //for UNO
  //send
  //  txAddrHSB = 0x0013A200; // fixed
  //  txAddrLSB = 0x40B0A672; // Get it from X-CTU
  txAddrHSB = 0x0;
  txAddrLSB = 0x0;
}

void MyXBee::broadcastXBeeData(String payload) {
  uint8_t temppayload[payload.length()];
  for (int i = 0; i < (int)payload.length(); i++) {
    temppayload[i] = payload.charAt(i);
  }
  Serial.println(F("Send ZbTx"));
  txAddr64 = XBeeAddress64(txAddrHSB, txAddrLSB);
  txRequest = ZBTxRequest(txAddr64, temppayload, sizeof(temppayload));
  xbee.send(txRequest);
}

void MyXBee::sendXBeeData(uint32_t txAddr, String payload) {
  uint8_t temppayload[payload.length()];
  for (int i = 0; i < (int)payload.length(); i++) {
    temppayload[i] = payload.charAt(i);
  }
  Serial.println(F("Send ZbTx"));
  txAddr64 = XBeeAddress64(txAddrHSB, txAddr);
  txRequest = ZBTxRequest(txAddr64, temppayload, sizeof(temppayload));
  xbee.send(txRequest);
}

String MyXBee::receiveXBeeData() {
  xbee.readPacket();

  if (xbee.getResponse().isAvailable()) {    // got something
    if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {      // got a zb rx packet
      //      Serial.print("got zb rx packet >>> ");
      //      //put on receive LED
      //      digitalWrite(RECEIVE_LED_PIN, HIGH);
      //      receiveLedPreviousMillis = millis();
      // now fill our zb rx class
      xbee.getResponse().getZBRxResponse(rx);

      //parsing data(payload) should be explored more
      String returnStr = "";
      for (int i = 0; i < rx.getDataLength(); i++) {
        returnStr += (char)rx.getData(i);
      }
      return returnStr;

      //      //printing packet info
      //      //remote source address
      //      Serial.print(rx.getRemoteAddress64().getMsb(), HEX);//data type of return value is uint32_t
      //      Serial.print(",");
      //      Serial.print(rx.getRemoteAddress64().getLsb(), HEX);//data type of return value is uint32_t
      //      Serial.print(",");
      //      //data(payload) length
      //      Serial.print(rx.getDataLength());
      //      Serial.print(",");
      //      Serial.println("");
      //      for (int i = 0; i < rx.getDataLength(); i++) Serial.print((char)receivePayload[i]);
      //      Serial.println("");
    }
  }
  return "";
}
