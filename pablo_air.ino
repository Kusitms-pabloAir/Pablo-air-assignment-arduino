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

      while(1){
        int dist = sonar.ping_cm();
        if (dist <= 5 && dist != 0){
          lcd.setCursor(3, 0);
          lcd.print("Delivered!");
          delay(1000);
          lcd.clear();
        } 
        else {
          lcd.setCursor(6, 0);
          lcd.print("Done!");
          delay(3000);
          lcd.clear();
          lcd.setCursor(1, 0);
          lcd.print("Not Delivered");
          digitalWrite(SOL_SENSOR, LOW);
          break;
        }
      }
    }
    
  }

  if (Serial.available()){
    bluetooth.write(Serial.read());
  }

  int dist = sonar.ping_cm();

  if (dist <= 25 && dist != 0) {
    lcd.setCursor(3, 0);
    lcd.print("Delivered!");
  }
  else {
    lcd.setCursor(1, 0);
    lcd.print("Not Delivered");
  }
  
  delay(300);
  lcd.clear();
}
