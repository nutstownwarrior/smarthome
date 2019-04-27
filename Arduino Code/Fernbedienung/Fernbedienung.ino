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
#define WIFI_SSID "Test"
#define WIFI_PASSWORD "Fabian123"

int IRledPin = 0;

void setup() {
  pinMode(IRledPin, OUTPUT);
  Serial.begin(9600);
  digitalWrite(0,LOW);
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
  Firebase.stream("Fabians Zimmer/Fernseher/code");
  delay(1000);
}

void loop() {
  if (Firebase.failed()) {
    Serial.println("streaming error");
    Serial.println(Firebase.error());
  }
  
  if (Firebase.available()) {
     FirebaseObject event = Firebase.readEvent();
     int status = event.getInt("data");
     switch(status){
      case 0:{
        
      }
        break;
      case 1:{
        EinAus();
      }
        break;
      case 2:{
        Zurueck();
      }
        break;
      case 3:{
        Vorwaerts();
      }
        break;
      case 4:{
        Lauter();
      }
        break;
      case 5:{
        Leiser();
      }
        break;
      case 6:{
        Oben();
      }
        break;
      case 7:{
        Links();
      }
        break;
      case 8:{
        Bestaetigen();
      }
        break;
      case 9:{
        Rechts();
      }
        break;
      case 10:{
        Runter();
      }
        break;
      case 11:{
        SmartMenue();
      }
        break;
      case 12:{
        back();
      }
        break;
    }
    Firebase.setInt("Fabians Zimmer/Fernseher/code", 0);
  }
}

void pulseIR(long microsecs) {
  cli();  // this turns off any background interrupts
  while (microsecs > 0) {
    // 38 kHz is about 13 microseconds high and 13 microseconds low
   digitalWrite(IRledPin, HIGH);  // this takes about 3 microseconds to happen
   delayMicroseconds(10);         // hang out for 10 microseconds
   digitalWrite(IRledPin, LOW);   // this also takes about 3 microseconds
   delayMicroseconds(10);         // hang out for 10 microseconds
 
   // so 26 microseconds altogether
   microsecs -= 26;
  }
 
  sei();  // this turns them back on
}

void EinAus(){
  
}

void Zurueck(){
  
}

void Vorwaerts(){
  
}

void Lauter(){
  
}

void Leiser(){
  
}

void Oben(){
  
}

void Links(){
  
}

void Bestaetigen(){
  
}

void Rechts(){
  
}

void Runter(){
  
}

void SmartMenue(){
  
}

void back(){
  
}
