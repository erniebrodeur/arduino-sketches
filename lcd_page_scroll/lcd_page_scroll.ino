
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

  // If we've passed the end of our buffer, lets restart.
  if (seek > buffer.length()) {
    seek = 0;
  }


  lcd.clear();
  lcd.setCursor(0, 0);
  line = buffer.substring(seek, seek+16);
  lcd.print(line);

  lcd.setCursor(0, 1);
  line = buffer.substring(seek+16, seek+32);
  lcd.print(line);

  // Even though we've grabbed 32 characters, we only seek 16.
  // This gives us our text flow effect.

  if (buffer.length() > 32) {
    seek += 16;
  }

  delay(1000);
}
