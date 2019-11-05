#include <ArduinoJson.h>

#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>

//
// Copyright 2015 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// FirebaseDemo_ESP8266 is a sample that demo the different functions
// of the FirebaseArduino API.

#include <ESP8266WiFi.h>

// Set these to run example.
#define FIREBASE_HOST "smart-home-a5e0f.firebaseio.com"
#define FIREBASE_AUTH "6bT8EWgOOjlQjmR3Y01hqsHh96juYui8BhyD2d4H"
#define WIFI_SSID "shome"
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
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.stream("Fabians Zimmer/Sofalampe/status");
  delay(1000);
}

void loop() {
  retry();
  if (Firebase.failed()) {
    Serial.println("streaming error");
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
  //lever();
}


void lever(){
  if((digitalRead(3) == HIGH) && (!button)){
    if(lampstat == 1){
        digitalWrite(0,LOW);
        Firebase.setFloat("Fabians Zimmer/Sofalampe/status", 0);
      }
      else{
        digitalWrite(0,HIGH);
        Firebase.setFloat("Fabians Zimmer/Sofalampe/status", 1);
      }
      button = true;
  }
  else if((digitalRead(3) == LOW) && button){
    if(lampstat == 1){
        digitalWrite(0,LOW);
        Firebase.setFloat("Fabians Zimmer/Sofalampe/status", 0);
      }
      else{
        digitalWrite(0,HIGH);
        Firebase.setFloat("Fabians Zimmer/Sofalampe/status", 1);
      }
    button = false;
  }
}

void retry(){
  int wifi_retry = 0;
  while(WiFi.status() != WL_CONNECTED && wifi_retry < 5 ) {
      wifi_retry++;
      Serial.println("WiFi not connected. Try to reconnect");
      WiFi.disconnect();
      WiFi.mode(WIFI_OFF);
      WiFi.mode(WIFI_STA);
      WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
      delay(100);
  }
  if(wifi_retry >= 5) {
      Serial.println("\nReboot");
      ESP.restart();
  }
}
