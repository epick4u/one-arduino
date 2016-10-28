#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SPI.h>
#include "MFRC522.h"


void dump_byte_array(byte *buffer, byte bufferSize);

/* wiring the MFRC522 to ESP8266 (ESP-12)
RST     = GPIO15
SDA(SS) = GPIO2 
MOSI    = GPIO13
MISO    = GPIO12
SCK     = GPIO14
GND     = GND
3.3V    = 3.3V
*/

const char* ssid     = "SKP-GUEST";
const char* server_url = "http://ec2-52-78-61-81.ap-northeast-2.compute.amazonaws.com:8080/breakfast/recipient/";

#define RST_PIN  15 // RST-PIN für RC522 - RFID - SPI - Modul GPIO15 
#define SS_PIN  2  // SDA-PIN für RC522 - RFID - SPI - Modul GPIO2
#define SPK_PIN 5  // GPIO5

const char *ssid =  "yourSSID";     // change according to your Network - cannot be longer than 32 characters!
const char *pass =  "yourPASSWORD"; // change according to your Network

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance

void setup() {
  Serial.begin(9600);    // Initialize serial communications
  delay(250);
  Serial.println(F("Re Booting...."));
  
  SPI.begin();           // Init SPI bus
  mfrc522.PCD_Init();    // Init MFRC522
  
  WiFi.begin(ssid, pass);
  
  int retries = 0;
  while ((WiFi.status() != WL_CONNECTED) && (retries < 10)) {
    retries++;
    delay(500);
    Serial.print(".");
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(F("WiFi connected"));
  }
  
  Serial.println(F("Ready!"));
  Serial.println(F("======================================================")); 
  Serial.println(F("Scan for Card and print UID:"));
}

void loop() { 
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    delay(50);
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    delay(50);
    return;
  }
  // Show some details of the PICC (that is: the tag/card)
  Serial.print(F("Card UID:"));
  dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
  Serial.println();
  tone(SPK_PIN,2400,150);//500: 음의 높낮이(주파수), 1000: 음의 지속시간(1초)
  delay(500);
  //tone(SPK_PIN,1500,150);  //500: 음의 높낮이(주파수), 1000: 음의 지속시간(1초)
}

// Helper routine to dump a byte array as hex values to Serial
void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
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

