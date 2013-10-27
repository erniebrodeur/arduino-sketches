/*
   This project will page scroll a block of text echoed to the serial input.
*/

#include <LiquidCrystal.h>

// Initialize the library with the pins we're using.
// (Note that you can use different pins if needed.)
// See http://arduino.cc/en/Reference/LiquidCrystal
// for more information:

LiquidCrystal lcd(12,11,5,4,3,2);
String buffer = "Ready.";
String line;
int seek = 0;

void setup()
{
  // column, row
  lcd.begin(16, 2);
  lcd.clear();

  Serial.begin(9600);
}

void loop()
{
  lcd.clear();

  read_input();
  // Write our first line.
  lcd.setCursor(0, 0);
  line = buffer.substring(seek, seek+16);
  lcd.print(line);

  // Write our second line.
  lcd.setCursor(0, 1);
  line = buffer.substring(seek+16, seek+32);
  lcd.print(line);


  // If we are < 32, don't page.
  if (buffer.length() > 32) {
    // Even though we've grabbed 32 characters, we only seek 16.
    // This gives us our text flow effect.  By shifting one line into the next.
    seek += 16;
  }

  // Are we past the end, reset.
  if (seek > buffer.length()) {
    seek = 0;
  }

  // One second per line, kinda fast, might need to be tuned as needed.
  delay(1000);
}

// Did we get new input? if so update our buffer.
void read_input() {
  if (Serial.available()) {
    buffer = "";

    while (Serial.available() > 0) {
      buffer += (char)Serial.read();
    }

    buffer.replace("\n", " ");
    buffer.replace("\r", " ");
    lcd.clear();
    seek = 0;
  }
}
