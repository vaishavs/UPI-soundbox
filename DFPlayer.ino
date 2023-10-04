#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"

// DF Mini player
#if (defined(ARDUINO_AVR_UNO) || defined(ESP8266))   // Using a soft serial port
#define FPSerial Serial
#else
#define FPSerial Serial1
#endif

DFRobotDFPlayerMini myDFPlayer;

// GSM 

void select_audio(uint8_t num)
{
  switch(num) {
  case 1: myDFPlayer.play(1);  //Play the first mp3
	  break;
  case 2: myDFPlayer.play(2);  //Play the next mp3
	  break;
  case 3: myDFPlayer.play(3);
	  break;
  case 4: myDFPlayer.play(4);
	  break;
  case 5: myDFPlayer.play(5);
	  break;
  case 6: myDFPlayer.play(6);
	  break;
  case 7: myDFPlayer.play(7);
	  break;
  case 8: myDFPlayer.play(8);
	  break;
  case 9: myDFPlayer.play(9);
	  break;
  case 10: myDFPlayer.play(10);
	  break;
  case 11: myDFPlayer.play(11);
	  break;
  case 12: myDFPlayer.play(12);
	  break;
  case 13: myDFPlayer.play(13);
	  break;
  case 14: myDFPlayer.play(14);
	  break;
  case 15: myDFPlayer.play(15);
	  break;
  case 16: myDFPlayer.play(16);
	  break;
  case 17: myDFPlayer.play(17);
	  break;
  case 18: myDFPlayer.play(18);
	  break;
  case 19: myDFPlayer.play(19);
	  break;
  case 20: myDFPlayer.play(20);
	  break;
  case 30: myDFPlayer.play(21);
	  break;
  case 40: myDFPlayer.play(22);
	  break;
  case 50: myDFPlayer.play(23);
	  break;
  case 60: myDFPlayer.play(24);
	  break;
  case 70: myDFPlayer.play(25);
  	break;
  case 80: myDFPlayer.play(26);
	  break;
  case 90: myDFPlayer.play(27);
	  break;
  }
};

void play_denomination(uint8_t n)
{
  switch(n)
  {
    case 1: myDFPlayer.play(29); // thousand
      break;
    case 2: myDFPlayer.play(28); // hundred
      break;
    case 3:
    default: myDFPlayer.play(31); // rupees
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

void play_amount(int amount)
{
 uint8_t ones_tens = (amount % 100);
 uint8_t hundreds = (amount / 100);
 uint8_t thousands = (amount / 1000);
 myDFPlayer.play(30); // You have received

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
  FPSerial.begin(9600, SERIAL_8N1, /*rx1 =*/3, /*tx1 =*/1);

  // Use serial to communicate with mp3.
  if (!myDFPlayer.begin(FPSerial, /*isACK = */true, /*doReset = */true)) {  
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
  }

  Serial.begin(9600);
  myDFPlayer.volume(30);  //Set volume value. From 0 to 30

  /* GSM module setup code */
}

void loop()
{
  int prev_amount, amount;
  // play_amount(amount);
  FPSerial.println("Hello from DFPlayerMini!\n");
  
  // If button press
  // play_amount(prev_amount);
  prev_amount = amount;
}
