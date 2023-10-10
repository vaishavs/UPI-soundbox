#include <DFPlayerMini_Fast.h>
char mess[500];
char mess1[100];
int i=0,j=0;
// DF Mini player
#if (defined(ARDUINO_AVR_UNO) || defined(ESP8266))   // Using a soft serial port
#include <SoftwareSerial.h>
SoftwareSerial softSerial(/*rx =*/4, /*tx =*/5);
#define FPSerial softSerial
#else
#define FPSerial Serial1
#endif
DFPlayerMini_Fast myDFPlayer;
// GSM 

void play_track(uint8_t num)
{
  myDFPlayer.play(num);
  delay(1000);
  myDFPlayer.isPlaying();
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
    case 1: play_track(29); // thousand
      break;
    case 2: play_track(28); // hundred
      break;
    case 3:
    default: play_track(31); // rupees
      break;
  }
}

void break_amount(uint8_t val)
{
  uint8_t rem = val % 10;
  uint8_t nearest = (val/10)*10;
  select_audio(nearest);
  if(rem>0)
  select_audio(rem);
}

void play_amount(uint32_t amount)
{
 uint8_t ones_tens = (amount % 100);
 uint8_t hundreds = (amount / 100)%10;
 uint8_t thousands = (amount / 1000);
 delay(2000);
 play_track(30); // You have received

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
void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  delay(3000);
  
 /* Setup code for DFPlayerMini */
#if (defined ESP32)
  FPSerial.begin(9600, SERIAL_8N1, /*rx =*/4, /*tx =*/5);
#else
  FPSerial.begin(9600);
#endif
  
  if (myDFPlayer.begin(FPSerial, true))
    Serial.println("myDFPlayer Player ready");
  else
    Serial.println("myDFPlayer Player NOT READY");

  myDFPlayer.volume(30);  //Set volume value. From 0 to 30
test_sim800_module();
 RECEIVE_SMS();
  /* GSM module setup code */
}
void loop() {
  //send_SMS();
 RECEIVE_SMS();
  updateSerial();
 //uint32_t prev_amount, amount = 87056;

  //play_amount(amount);

  //prev_amount = amount;
}
void test_sim800_module()
{
  Serial.println("AT");
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
}
void updateSerial_val()
{
  delay(500);
  while (Serial2.available())
  {
    //delay(3);
    mess[j]=Serial2.read();//Forward what Software Serial received to Serial Port
    j++;
  }
  j=0;
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
void text_extract(String s)
{

    char a[30]="Rs.";

    char b[10];

    int i=0,j=0,l=0;

    while(s[i]!='\0')

    {

        if(s[i]==a[j])

        {

            if(s[i+1]==a[j+1])

            {

                if(s[i+2]==a[j+2])

                {

                    for(int k=i+3;s[k]!=' ';k++)

                    {

                        b[l]=s[k];
                         Serial.println(b[l]);
                        l++;

                    }
                    b[l]='\0';
                    Serial.println("debug");
                    Serial.println(b);
                  int data = atoi(b);
                  Serial.println(data);
                  play_amount(data);
                }

            }

        }

        i++;

    }

 

}


void RECEIVE_SMS()
{
  int k=0;
  char mob[11];
   while (!(Serial2.available()));
  Serial2.print("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial_val();
  Serial2.print("AT+CNMI=1,2,0,0,0");
  Serial.println("1");
  Serial.println(mess);
  for(k=12;k<=21;k++){
    mob[k-12]=mess[k];
   Serial.print(mess[k]);}
   mob[10]='\0';
   Serial.println("start");
    Serial.println(mob);
   Serial.println("check");
  Serial.println("done");
  if(!(strcmp(mob,"8838528218"))){
  text_extract(mess);}
  Serial.println("Message Received");
  Serial2.write(26);
  
}