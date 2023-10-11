int firstline = 0;
void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  delay(3000);
  test_sim800_module();
  receive_SMS();
}
void loop() { 

 if (Serial2.available() > 0)
  {
    String mpm = Serial2.readStringUntil('\n');
    Serial.println(mpm);
    int mpmlen = mpm.length();
    Serial.println(mpmlen);
    int prev_index_val = 0, current_index_val = 0;
    if (firstline == 1)
    {
      current_index_val = mpm.indexOf("Rs.", prev_index_val);
     String one_at_a_time_str1 = mpm.substring(current_index_val + 3, current_index_val + 10);
      Serial.print(one_at_a_time_str1);
      Serial.println(".");
       int data = one_at_a_time_str1.toInt();
      Serial.println(data);
      firstline = 0;
    }
    if (mpm.startsWith("+CMT: \"+918220090759\""))
    {
      current_index_val = mpm.indexOf(',', prev_index_val);
      prev_index_val = current_index_val + 1;
      current_index_val = mpm.indexOf(',', prev_index_val);
      prev_index_val = current_index_val + 1;
      current_index_val = mpm.indexOf(',', prev_index_val);
      prev_index_val = current_index_val + 1;
      String one_at_a_time_str = mpm.substring(prev_index_val, prev_index_val + 5);
      Serial.println(one_at_a_time_str);
      firstline = 1;
      delay(100);
    }
    //    Serial.write(Serial2.read());
  }
  if (Serial.available() > 0)
    Serial2.write(Serial.read());
		  
}
void test_sim800_module()
{
  Serial2.println("AT");
  updateSerial();
  Serial.println();
  Serial2.println("AT+CSQ");
  updateSerial();
  Serial2.println("AT+CCID");
  updateSerial();
  Serial2.println("AT+CREG?");
  updateSerial();
  Serial2.println("ATI");
  updateSerial();
  Serial2.println("AT+CBC");
  updateSerial();
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
  //Serial.println(mess1);
  //Serial.println(mess2);
}
void send_SMS()
{
  Serial2.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  Serial2.println("AT+CMGS=\"+919804049270\"");// phone number to sms
  updateSerial();
Serial.println();
  Serial.println("Message Sent");
  Serial2.write(26);
}
void receive_SMS()
{
   Serial2.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  Serial2.println("AT+CNMI=1,2,0,0,0");
  updateSerial();
  Serial.println();
  Serial.println("Message RECEIVED");
  Serial2.write(26);
}