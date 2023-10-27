#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <string.h>
  int l=0;
  int id=0;
 // int currentid=0;
const char* ssid = "ESP32";
const char* password =  "esp32esp32";
 
DynamicJsonDocument jsonDoc(1000);
  
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
  
    http.begin("http://192.168.198.31:4000/transactions"); //Specify the URL
    int httpCode = http.GET();                                        //Make the request
  String payload;
 
    if (httpCode > 0) { //Check for the returning code
  
       payload = http.getString();
       // Serial.println(httpCode);
        //Serial.println(payload);
 
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
      id = jsonDoc[l]["id"];
      
       if(id!=0)
       {
        id = jsonDoc[l]["id"];
       Serial.println(id);
      String name = jsonDoc[l]["name"];
      String amount = jsonDoc[l]["amount"];
      String status = jsonDoc[l]["status"];
 
 
  Serial.println("Deserialized JSON Data:");
  Serial.print("id: ");
  Serial.println(id);
  Serial.print("name: ");
  Serial.println(name);
  Serial.print("amount: ");
  Serial.println(amount);
  Serial.print("status: ");
  Serial.println(status);
   l++;
   Serial.println(l);
  }
   
   
    http.end(); //Free the resources
  }
  
  delay(10000);
  
}