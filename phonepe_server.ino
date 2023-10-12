#include <ArduinoHttpClient.h>
#include <WiFi.h>  // Use the appropriate library for your board

const char* ssid = "kalyanram";
const char* password = "123456789";

WiFiClient wifiClient;
HttpClient http(wifiClient, "mercury-uat.phonepe.com", 443);

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
}

void loop() {
  Serial.println("Sending HTTP GET request");
  http.beginRequest();
  http.get("/enterprise-sandbox/v3/transaction/MT3YG4Z5A/T2310111151597220325757/status");
  http.sendHeader("accept", "application/json");
  http.sendHeader("X-VERIFY", "90443659f151a86831b7502c797c2ee4f3bcf63cbdad141c154effc2aad5c762###1");
  http.endRequest();

  int statusCode = http.responseStatusCode();
  String response = http.responseBody();

  Serial.print("HTTP Status Code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);

  delay(10000);  // Wait for some time before making another request
}