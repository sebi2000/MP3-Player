#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLLFzo-3Yd"
#define BLYNK_DEVICE_NAME "LedSwitch"
#define BLYNK_AUTH_TOKEN "uFuMRP1bL6ZY4ZFsaS0Zcl5Q4gGrXfRL"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "uFuMRP1bL6ZY4ZFsaS0Zcl5Q4gGrXfRL";
//blynkbl
int current = 1;

void playCurrent(){
  Serial.print("INTRA");
  if(current == 1)
      digitalWrite(D1, HIGH);
  else if(current == 2)
      digitalWrite(D2, HIGH);
  else digitalWrite(D3, HIGH);
}

void stopCurrent(){
  if(current == 1)
      digitalWrite(D1, LOW);
  else if(current == 2)
      digitalWrite(D2, LOW);
  else digitalWrite(D3, LOW);
}

//Get the button value
//BLYNK_WRITE(V0) {
//  Serial.print("Param: ");
//  Serial.print(param.asStr());
//  digitalWrite(D0, param.asInt());
//}

BLYNK_WRITE(V1) {
  Serial.print("Param: ");
  Serial.print(param.asStr());
  Serial.print("Current: ");
  Serial.print(current);

  String action = param.asStr();

  if (action == "play") {
    playCurrent();
  }
  if (action == "stop") {
    stopCurrent();
  }
  if (action == "next") {
    if(current == 3){
      digitalWrite(D3, LOW);
      current = 1;
    }
    else if(current == 2){
      digitalWrite(D2, LOW);
      current ++;
    }
    else {
      digitalWrite(D1, LOW);
      current ++;
    }
    playCurrent();
  }
  if (action == "prev") {
    if(current == 1){
      current = 3;
      digitalWrite(D1, LOW);
    }
    else if(current == 2){
      digitalWrite(D2, LOW);
      current --;
    }
    else {
      digitalWrite(D3, LOW);
        current --;
    }
    playCurrent();
  }
}

void setup() {
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  
  Serial.begin(9600);
  Serial.print("NodeMCU IP Address:");
  Serial.print(WiFi.localIP());
  
//  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  Blynk.config(auth, "blynk.cloud", 80);
}

void loop() {
  //Run the Blynk library
  Blynk.run();
}
