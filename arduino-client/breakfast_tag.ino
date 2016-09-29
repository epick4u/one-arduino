#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid     = "SKP-GUEST";
const char* server_url = "http://ec2-52-78-61-81.ap-northeast-2.compute.amazonaws.com:8080/breakfast/recipient/";

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

void tag(char* tagId) {
  char full_url[200];
  strcpy(full_url, server_url);
  strcat(full_url, tagId);
  Serial.println(full_url);

  HTTPClient http;
  const int httpPort = 80;
  
  http.begin(full_url);

  // start connection and send HTTP header
  int httpCode = http.GET();

  // httpCode will be negative on error
  if(httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] Result Code: %d\n", httpCode);

      // file found at server
      if(httpCode == HTTP_CODE_OK) {
          String payload = http.getString();
          Serial.println(payload);
      }
  } else {
      Serial.printf("[HTTP] failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end(); 
}

