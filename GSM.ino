// GSM interfacing code
void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  delay(3000);
  test_sim800_module();
 RECEIVE_SMS();
}
void loop() {
 // send_SMS();
  RECEIVE_SMS();
  updateSerial();
}
void test_sim800_module()
{
  Serial.println("AT"); //test is successful, it will back to OK
  updateSerial();
  Serial.println();
  Serial2.println("AT+CSQ"); //Signal quality test, value range is 0-31
  updateSerial();
  Serial2.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
  updateSerial();
  Serial2.println("AT+CREG?"); ////Check whether it has registered in the network
  updateSerial();
  Serial2.println("ATI");//manufacturer specific information about the device
  updateSerial();
 // Serial2.println("AT+CBC");
 // updateSerial();
}
void updateSerial()
{
  delay(500);
  while (Serial.available())
  {
    Serial2.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while (Serial2.available())
  {
    Serial.write(Serial2.read());//Forward what Software Serial received to Serial Port
  }
}

void send_SMS()
{
  Serial2.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  Serial2.println("AT+CMGR=\"+919629055521\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  Serial2.print("hi ANBURAJ"); //text content
  updateSerial();
  Serial.println();
  Serial.println("Message sent");
  Serial2.write(26);
}
void RECEIVE_SMS()
{
   while (!(Serial2.available()));
  Serial2.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  Serial2.println("AT+CNMI=1,2,0,0,0");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  //Serial2.print("hi saravanan"); //text content
  updateSerial();
  Serial.println();
  Serial.println("Message Received");
  Serial2.write(26);

}
