
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid     = "SKP-GUEST";

const char* server_url = "http://ec2-52-78-61-81.ap-northeast-2.compute.amazonaws.com:8080/restroom";

const char* flour = "/11-";

const char* in = "/in";
const char* out = "/out";

const char room[][2] = {"1", "2", "3"};
const int room_pin[] = {5, 4, 0};
bool room_busy[3] = {false, false, false};
int prev_button_state[3] = {HIGH, HIGH, HIGH};
int press_count[3] = {0, 0, 0};

void setup() {

  pinMode(room_pin[0], INPUT_PULLUP);
  pinMode(room_pin[1], INPUT_PULLUP);
  pinMode(room_pin[2], INPUT_PULLUP);
  
  Serial.begin(115200);
  delay(10);

  Serial.println(WiFi.macAddress());
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
//  WiFi.begin(ssid, password);
  WiFi.begin(ssid);
//  WiFi.begin(ssid, keyIndex, key);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); 
}


void loop() {
  delay(300);

  check_room(0);
  check_room(1);
  check_room(2);
}

void check_room(int index) {
  int button_state = digitalRead(room_pin[index]);
  // prev_button_state 값과 다른 digital input이 들어왔을때
  // count를 1씩 늘려준다 10 count 연속  
  if(button_state != prev_button_state[index]) {
    press_count[index]++;
    Serial.print(index+1);
    Serial.print(" room : ");
    Serial.print(button_state);
    Serial.print(" state / count ");
    Serial.println(press_count[index]);
    if(press_count[index] > 10) {
    //  room_busy[index] = !room_busy[index];
      if(button_state == LOW) {
        room_busy[index] == true;
        Serial.print("room ");
        Serial.print(room[index]);
        Serial.println(" busy!");
        connect_server(room[index], in);
      }
      else {
        room_busy[index] == false;
        Serial.print("room ");
        Serial.print(room[index]);
        Serial.println(" empty!");
        connect_server(room[index], out);
      }
      prev_button_state[index] = button_state;
    }
  }
  // state값이 같으면 count = 0 setting
  else {
    if(press_count[index] > 0) {
      Serial.print(index + 1);
      Serial.println(" room count reset");
    }
    press_count[index] = 0;
  }
}

void connect_server(const char* room, const char* inout) {

  Serial.print("connecting to ");
  char full_url[100];
  strcpy(full_url, server_url);
  strcat(full_url, flour);
  strcat(full_url, room);
  strcat(full_url, inout);
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

