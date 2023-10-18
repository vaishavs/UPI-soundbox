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
  
   //http.begin("https://api.phonepe.com/apis/hermes/pg/v1/status/M1LBOW56CH3A/QTRAVEL00010002"); //Specify the URL
    //http.begin("https://api.genderize.io/?name=devika");
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



 /* int postId = jsonDoc["postId"];
  int id = jsonDoc["id"];
  String name = jsonDoc["name"];
  String email = jsonDoc["email"];
  String body = jsonDoc["body"];*/
  
      int amount =jsonDoc["amount"];
      Serial.print("amount: ");
 Serial.println(amount);

 /* Serial.println("Deserialized JSON Data:");
  Serial.print("postId: ");
 Serial.println(postId);
  Serial.print("id: ");
  Serial.println(id);
  Serial.print("name: ");
  Serial.println(name);
  Serial.print("email: ");
  Serial.println(email);
  Serial.print("body: ");
  Serial.println(body);*/
    
    http.end(); //Free the resources
  }
  
  delay(10000);
  
}