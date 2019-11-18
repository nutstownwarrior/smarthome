#include <ArduinoJson.h>
#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>
#include <ESP8266WiFi.h>
#include <ESP8266Ping.h>

#define FIREBASE_HOST "smart-home-a5e0f.firebaseio.com"
#define FIREBASE_AUTH "6bT8EWgOOjlQjmR3Y01hqsHh96juYui8BhyD2d4H"
#define WIFI_SSID "Shome"
#define WIFI_PASSWORD "ghjzv23.!?@2019"

int n = 0;
bool button = false;
int lampstat = 0;

void setup() {
  Serial.begin(9600,SERIAL_8N1,SERIAL_TX_ONLY);
  pinMode(0 ,OUTPUT);
  digitalWrite(0 , LOW);
  pinMode(3 ,INPUT);
  // connect to wifi.
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while ((WiFi.status() != WL_CONNECTED)  || !Ping.ping("www.google.de")) {
    delay(500);
  }  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.stream("Fabians Zimmer/Testlampe/status");
  delay(1000);
}

void loop() {
  if (Firebase.failed()) {
    Serial.println(Firebase.error());
  }
  
  if (Firebase.available()) {
     FirebaseObject event = Firebase.readEvent();
     lampstat = event.getInt("data");
     switch(lampstat){
      case 0:{
        digitalWrite(0,LOW);
      }
        break;
      case 1:{
        digitalWrite(0,HIGH);
      }
        break;
    }
  }
  else{
    delay(1000);
  }
  delay(100);
  lever();
  yield();
}


void lever(){
  if((digitalRead(3) == HIGH) && (!button)){
    if(lampstat == 1){
        digitalWrite(0,LOW);
        Firebase.setFloat("Fabians Zimmer/Testlampe/status", 0);
      }
      else{
        digitalWrite(0,HIGH);
        Firebase.setFloat("Fabians Zimmer/Testlampe/status", 1);
      }
      button = true;
  }
  else if((digitalRead(3) == LOW) && button){
    if(lampstat == 1){
        digitalWrite(0,LOW);
        Firebase.setFloat("Fabians Zimmer/Testlampe/status", 0);
      }
      else{
        digitalWrite(0,HIGH);
        Firebase.setFloat("Fabians Zimmer/Testlampe/status", 1);
      }
    button = false;
  }
}
