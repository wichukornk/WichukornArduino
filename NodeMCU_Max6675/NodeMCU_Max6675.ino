// Example By ArduinoAll.com
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <max6675.h>

//ตั้งค่า wifi
const char* ssid = "3BB_Noomoriginal_2.4GHz"; // ชื่อ
const char* password = "27022528"; // รหัสผ่าน


// ตั้งค่า IFTTT
String event = "wichukorn_test_1"; // ชื่อ event
String key = "iy0EVpMncnVRJ6COgjMGJPNFLtqhcGZv3lUGBlXBoSR"; // Key

// MAX6675
int ktcSO = 12;
int ktcCS = 13;
int ktcCLK = 14;

MAX6675 ktc(ktcCLK, ktcCS, ktcSO);

String sheets = "";
void setup () {
  //สำหรับ esp8266 url ตรง https ให้เปลี่ยนเป็น http
  sheets = "http://maker.ifttt.com/trigger/wichukorn_test_1/with/key/iy0EVpMncnVRJ6COgjMGJPNFLtqhcGZv3lUGBlXBoSR?value1=-1"; // url ที่ส่งค่าลง google sheet

  Serial.begin(115200);
  Serial.println(sheets);
  WiFi.begin(ssid, password);
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  
}

void loop() {
  float DC = ktc.readCelsius();
  String iFTTT = "http://maker.ifttt.com/trigger/wichukorn_test_1/with/key/iy0EVpMncnVRJ6COgjMGJPNFLtqhcGZv3lUGBlXBoSR?value1=";
  String googleSheet = iFTTT + DC;

  if (WiFi.status() == WL_CONNECTED) { //ถ้าเชื่อมต่อสำเร็จ

    HTTPClient http;
    http.begin(googleSheet); //กำหนด url เพื่อเซฟข้อมูลลง google sheets
    int httpCode = http.GET(); //ส่งค่า url

    if (httpCode > 0) { //ถ้าส่งสำเร็จ

      String payload = http.getString();// อ่านค่าผลลัพธ์
      Serial.println(payload);
    }
    http.end(); //ปิดการเชื่อมต่อ

  }

  
  delay(5000); //หน่วงเวลา เซฟข้อมูลทุก 5 วินาที
  
}
