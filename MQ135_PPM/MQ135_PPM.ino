// Project 02: MQ135 Gas Sensor Alarm
// Equipment: Arduino Uno, MQ135, Buzzer, LED light, LCD 16x2

//----------------------------------------------  include all libraries

#include <LiquidCrystal.h>
#include <MQUnifiedsensor.h>
#include <MQ135.h>
#include <Wire.h>

//----------------------------------------------  Define all pins
int MQ135pin = A0;
int BuzzerPin = 7;
int red = 5, green = 6;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

//----------------------------------------------  Define all commands order
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
MQ135 gasSensor = MQ135(MQ135pin);


void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);                                // set up the LCD's number of columns and rows:

}

void loop() {

  lcd.setCursor(0, 0);
  lcd.print("MQ135(PPM) Proje");

  int gasValue = analogRead(MQ135pin);             // Get gas values
  float CO2 = gasSensor.getPPM();                  // Get Co2 Values   

  //-------------------------------------------- Ptint to serial monitor
  Serial.println("MQ135(PPM) Project");
  Serial.print("Gas Content");
  Serial.print(gasValue);
  Serial.print(" PPM");
  delay(500);
                              

  //-------------------------------------------- Set some alarm when gas get higher than 270 ppm
  if (gasValue > 270) {

    lcd.clear();
    digitalWrite(BuzzerPin, HIGH);
    delay(50);
    digitalWrite(red, HIGH);
    delay(50);
    digitalWrite(BuzzerPin, LOW);
    delay(50);
    digitalWrite(red, LOW);
    delay(50);

    //-------------------------------------------- Print to LCD display
    lcd.setCursor(0, 0);
    lcd.print("  Weather Status  ");
    delay(500);

    lcd.setCursor(0, 0);
    lcd.print("Gas Content");
    lcd.setCursor(0, 1);
    lcd.print("    ");
    lcd.print(gasValue);
    lcd.print(" PPM");
    delay(500);

    lcd.setCursor(0, 0);
    lcd.print("CO2 Content");
    lcd.setCursor(0, 1);
    lcd.print("    ");
    lcd.print(CO2);
    lcd.print(" PPM");
    delay(500);
    
    lcd.setCursor(0, 0);
    lcd.print("   Bad Weather  ");
    lcd.setCursor(0, 1);
    lcd.print("    Check it!   ");
    delay(500);

    digitalWrite(green, LOW);
  }

  //---------------------------------------------- Cooldown alarm when everthings good
  else {

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Weather Status  ");
    delay(500);

    lcd.setCursor(0, 0);
    lcd.print("Gas Content");
    lcd.setCursor(0, 1);
    lcd.print("    ");
    lcd.print(gasValue);
    lcd.print(" PPM");
    delay(500);

    lcd.setCursor(0, 0);
    lcd.print("CO2 Content");
    lcd.setCursor(0, 1);
    lcd.print("    ");
    lcd.print(CO2);
    lcd.print(" PPM");
    delay(500);

    digitalWrite(BuzzerPin, LOW);
    digitalWrite(red, LOW);
    
    digitalWrite(green, HIGH);
    delay(500);
    digitalWrite(green, LOW);
    delay(500);
  }
}
