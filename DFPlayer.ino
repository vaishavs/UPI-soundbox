#include <DFPlayerMini_Fast.h>

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

void setup()
{ 
  /* Setup code for DFPlayerMini */
#if (defined ESP32)
  FPSerial.begin(9600, SERIAL_8N1, /*rx =*/4, /*tx =*/5);
#else
  FPSerial.begin(9600);
#endif
  
  Serial.begin(115200);

  Serial.println();

  if (myDFPlayer.begin(FPSerial, true))
    Serial.println("myDFPlayer Player ready");
  else
    Serial.println("myDFPlayer Player NOT READY");

  myDFPlayer.volume(30);  //Set volume value. From 0 to 30

  /* GSM module setup code */
}

void loop()
{
  uint32_t prev_amount, amount = 87056;
  
  // If button press
  play_amount(amount);
  
  prev_amount = amount;
}
