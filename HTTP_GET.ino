#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

 
const char* ssid = "Devika";
const char* password =  "devika321";

DynamicJsonDocument jsonDoc(500);
  
void setup() {
  
  Serial.begin(115200);
  delay(4000);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  
  Serial.println("Connected to the WiFi network");
}
  
void loop() {
  
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
  
    HTTPClient http;
  
  
    http.begin("https://6e4546ec-e98f-4082-a21d-6a2f0da36c22.mock.pstmn.io/payments/P987654");
    int httpCode = http.GET();                                        //Make the request
  String payload;


    if (httpCode > 0) { //Check for the returning code
  
       payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);

      }
      else {
      Serial.println("Error on HTTP request");
    }
String jsonString=payload;
    DeserializationError error = deserializeJson(jsonDoc, jsonString);

  if (error) {
    Serial.print("Deserialization failed: ");
    Serial.println(error.c_str());
  }

      int amount =jsonDoc["amount"];
      Serial.print("amount: ");
 Serial.println(amount);


    
    http.end(); //Free the resources
  }
  
  delay(10000);
  
}
