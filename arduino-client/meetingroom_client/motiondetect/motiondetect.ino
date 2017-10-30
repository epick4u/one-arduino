#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

int inputPin = D4;     // 센서 시그널핀
int pirState = LOW;   // 인체감지센서 초기상태
int PIR_val = 0;          // Signal 입력값

long lastUpdateTime = 0;
bool isOccupied = false;
int lowSigCount = 0;

const char* ssid     = "ONE-GUEST";
const char* server_url = "http://onemakers.com:8080/meetingroom";
const char* roomId = "/testRoom";
const char* in = "/in";
const char* out = "/out";

 
void setup()
{
  //pinMode(ledPin, OUTPUT); // LED Output 설정
  pinMode(inputPin, INPUT);    // 센서 Input 설정
  Serial.begin(9600);  // 시리얼 통신 초기화.
  //connectWifi();

  Serial.print("MacAddress : ");
  Serial.println(WiFi.macAddress());
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid);
  //WiFi.begin(ssid, "Arduino12#$");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
 
void loop()
{
  PIR_val = digitalRead(inputPin);     // 센서값 읽기
  
  if (PIR_val == HIGH) {               // 인체감지시
    lastUpdateTime = millis();
    
    if (pirState == LOW) {
        pirState = HIGH;
        
        if (isOccupied == false) {
          isOccupied = true;
          Serial.println("회의실 사용 감지");
          connect_server(roomId, in);
        }
    }
 
  } else {

    if (isOccupied) {
      lowSigCount++;
      Serial.println(lowSigCount);
    }
    
    if (pirState == HIGH) {
        pirState = LOW;
        lowSigCount = 0;
    }

    if (isOccupied && lowSigCount > 100) {
      isOccupied = false;
      lowSigCount = 0;
      Serial.println("회의실 사용 종료");
      connect_server(roomId, out);
    }
  }
  
  delay(500);
}

void connect_server(const char* room, const char* inout) {

  Serial.print("connecting to ");
  char full_url[100];
  strcpy(full_url, server_url);
  strcat(full_url, roomId);
  strcat(full_url, inout);
  Serial.println(full_url);  

  HTTPClient http;
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
