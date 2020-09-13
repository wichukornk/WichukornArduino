// Example By ArduinoAll.com
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

//ตั้งค่า wifi
const char* ssid = ""; // ชื่อ
const char* password = ""; // รหัสผ่าน


// ตั้งค่า IFTTT
String event = "test"; // ชื่อ event
String key = "cd86zJCvok4e2-kXzGtrk"; // Key

String sheets = "";
void setup () {
  //สำหรับ esp8266 url ตรง https ให้เปลี่ยนเป็น http
  sheets = "http://maker.ifttt.com/trigger/test/with/key/cd86zJCvok4e2-kXzGtrkw?value1=123"; // url ที่ส่งค่าลง google sheet

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

  if (WiFi.status() == WL_CONNECTED) { //ถ้าเชื่อมต่อสำเร็จ

    HTTPClient http;
    http.begin(sheets); //กำหนด url เพื่อเซฟข้อมูลลง google sheets
    int httpCode = http.GET(); //ส่งค่า url

    if (httpCode > 0) { //ถ้าส่งสำเร็จ

      String payload = http.getString();// อ่านค่าผลลัพธ์
      Serial.println(payload);
    }
    http.end(); //ปิดการเชื่อมต่อ

  }
  delay(5000); //หน่วงเวลา เซฟข้อมูลทุก 5 วินาที
}
