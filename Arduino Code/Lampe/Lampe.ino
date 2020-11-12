#include <ArduinoJson.h>

#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "smart-home-a5e0f.firebaseio.com"
#define FIREBASE_AUTH "6bT8EWgOOjlQjmR3Y01hqsHh96juYui8BhyD2d4H"
#define WIFI_SSID ""
#define WIFI_PASSWORD ""

void setup() {
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  delay(1000);
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.stream("Fabians Zimmer/Testlampe/status");
  delay(1000);
}

int n = 0;

void loop() {
  if (Firebase.failed()) {
    Serial.println("streaming error");
    Serial.println(Firebase.error());
    delay(1000);
  }
  
  if (Firebase.available()) {
     FirebaseObject event = Firebase.readEvent();
     int status = event.getInt("data");
     switch(status){
      case 0:{
        byte open[] = {0xA0, 0x01, 0x00, 0xA1};
        Serial.write(open, sizeof(open));
      }
        break;
      case 1:{
        byte close[] = {0xA0, 0x01, 0x01, 0xA2};
        Serial.write(close, sizeof(close));
      }
        break;
    }
  }
}
