#include <NewPing.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C_Hangul.h>
#include <SoftwareSerial.h>

#define SOL_SENSOR   13
#define TRIGGER_PIN  12 
#define ECHO_PIN     11 
#define MAX_DISTANCE 200 
#define BT_RXD 6
#define BT_TXD 5


SoftwareSerial bluetooth(BT_RXD, BT_TXD); 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 
LiquidCrystal_I2C_Hangul lcd(0x27,16,2);
 
void setup() {
  pinMode(SOL_SENSOR, OUTPUT);
  Serial.begin(9600); 
  bluetooth.begin(9600);
  lcd.init();
  lcd.backlight();    
}
 
void loop() {
  char value;

  if (bluetooth.available()){
    value = bluetooth.read();
    Serial.write(value);
    if (value == '1'){
      digitalWrite(SOL_SENSOR, HIGH);
      lcd.setCursor(3, 0);
      lcd.print("Delivered!");
      delay(3000);
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("Waiting...");
      delay(10000);
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Not Delivered");
      digitalWrite(SOL_SENSOR, LOW);
    }
  }

  if (Serial.available()){
    bluetooth.write(Serial.read());
  }

  lcd.setCursor(1, 0);
  lcd.print("Not Delivered");
  
  delay(300);
  lcd.clear();
}
