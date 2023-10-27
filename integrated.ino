#include <DFPlayerMini_Fast.h>
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
/* Configuring a serial port for DFPlayer mini */
#if (defined(ARDUINO_AVR_UNO) || defined(ESP8266))
#include <SoftwareSerial.h>
SoftwareSerial softSerial(/*rx =*/4, /*tx =*/5);
#define FPSerial softSerial
#else
#define FPSerial Serial1
#endif

DFPlayerMini_Fast myDFPlayer;

/* For playing a specific digit */
void play_track(uint8_t num)
{
  myDFPlayer.play(num);
  delay(1000);
  while(myDFPlayer.isPlaying());
}

void select_audio(uint8_t num)
{
  switch(num) {
  case 1: play_track(1);
	  break;
  case 2: play_track(2);
	  break;
  case 3: play_track(3);
	  break;
  case 4: play_track(4);
	  break;
  case 5: play_track(5);
	  break;
  case 6: play_track(6);
	  break;
  case 7: play_track(7);
	  break;
  case 8: play_track(8);
	  break;
  case 9: play_track(9);
	  break;
  case 10: play_track(10);
	  break;
  case 11: play_track(11);
	  break;
  case 12: play_track(12);
	  break;
  case 13: play_track(13);
	  break;
  case 14: play_track(14);
	  break;
  case 15: play_track(15);
	  break;
  case 16: play_track(16);
	  break;
  case 17: play_track(17);
	  break;
  case 18: play_track(18);
	  break;
  case 19: play_track(19);
	  break;
  case 20: play_track(20);
	  break;
  case 30: play_track(21);
	  break;
  case 40: play_track(22);
	  break;
  case 50: play_track(23);
	  break;
  case 60: play_track(24);
	  break;
  case 70: play_track(25);
  	break;
  case 80: play_track(26);
	  break;
  case 90: play_track(27);
	  break;
  }
};

void play_denomination(uint8_t n)
{
  switch(n)
  {
    case 1: play_track(29); // Play "thousand"
      break;
    case 2: play_track(28); // Play "hundred"
      break;
    case 3:
    default: play_track(31); // Play "rupees"
      break;
  }
}

/* Break ones and tens into individual digits */
void break_amount(uint8_t val)
{
  uint8_t rem = val % 10;
  uint8_t nearest = (val/10)*10;
  select_audio(nearest);
  if(rem>0)
  select_audio(rem);
}

/* Break the total amount into thousands, hundreds, and tens & ones */
void play_amount(uint32_t amount)
{
 uint8_t ones_tens = (amount % 100);
 uint8_t hundreds = (amount / 100)%10;
 uint8_t thousands = (amount / 1000);

 // Thousands
 if(thousands > 0) {
 if(thousands > 20)
  break_amount(thousands);
 else
  select_audio(thousands);
  play_denomination(1);
 }

 // Hundreds
 if(hundreds>0 && hundreds<=9) {
  select_audio(hundreds);
  play_denomination(2);
 }

 // Tens and ones
 if(ones_tens > 20)
  break_amount(ones_tens);
 else
  select_audio(ones_tens);
 play_denomination(3);
}

int firstline = 0;
int data;

void setup() {
  Serial.begin(9600);

  /* Setup code for GSM module */
  Serial2.begin(9600);
  delay(3000);
 
  /* Setup code for DFPlayerMini */
#if (defined ESP32)
  FPSerial.begin(9600, SERIAL_8N1, /*rx =*/4, /*tx =*/5);
#else
  FPSerial.begin(9600);
#endif

  if (myDFPlayer.begin(FPSerial, true))
    Serial.println("myDFPlayer ready");
  else
    Serial.println("myDFPlayer NOT READY");

  myDFPlayer.volume(30);  // Set maximum volume
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
      uint32_t amount = jsonDoc[l]["amount"];
      String status = jsonDoc[l]["status"];
      if(status=="success")
      play_amount(amount);
	else play_track(33); // Play "Payment failed"
 
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

void updateSerial()
{
  delay(500);
  while (Serial.available())
  {
   Serial2.write(Serial.read()); //Forward what Serial received to Software Serial Port
  }
  while (Serial2.available())
  {
    Serial.write(Serial2.read()); //Forward what Software Serial received to Serial Port
  }
 
}
