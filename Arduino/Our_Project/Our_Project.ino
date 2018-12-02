
#include <LiquidCrystal.h>
#include <SimpleDHT.h>
#include "Heat_Index.hpp"
#include "MQ2.h"
#include "MQ9.h"
#define DHTPIN 2
#define ANALOG1 A0
#define ANALOG2 A5
#define LED1 4

const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

SimpleDHT11 dht11(DHTPIN);
MQ2 mq2(ANALOG1);
MQ9 mq9(ANALOG2);
Heat_Index hi;

void setup() {
  pinMode(LED1,OUTPUT);
  lcd.begin(16, 2);
}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("Results:");
  delay(3000);

  byte temperature = 0;
  byte humidity = 0;
  
  dht11.read(&temperature, &humidity, NULL);
  float smoke_sensor = mq2.read(false);
  float gas_sensor = mq9.read(false);

  if (isnan(humidity) || isnan(temperature) || isnan(gas_sensor) || isnan(smoke_sensor)) {
    lcd.setCursor(0,1);
    lcd.println("Failed to read!");
    delay(3000);
    lcd.clear();
    delay(3000);
  }
  else{
    float fahrenheit = 1.8 * temperature + 32;
    float heat_index = hi.computeHeatIndex(fahrenheit, humidity);
    lcd.setCursor(0,1);
    lcd.print("                      ");
    lcd.setCursor(0,1);
    lcd.print("Humidity: ");
    lcd.print(humidity);
    lcd.print("%");
    delay(3000);

    delay(3000);
    lcd.setCursor(0,1);
    lcd.print("                      ");
    lcd.setCursor(0,1);
    lcd.print("Fahrenheit: ");
    lcd.print(fahrenheit);
    lcd.print(" *F");

    delay(3000);
    lcd.setCursor(0,1);
    lcd.print("                      ");
    lcd.setCursor(0,1);
    lcd.print("Heat index: ");
    lcd.print(heat_index);
    lcd.print(" *F ");
    
    if ( heat_index < 80 ){
      digitalWrite(LED1, HIGH);
      delay(9000);
      digitalWrite(LED1, LOW);
    }
    else if ( heat_index >= 80 && heat_index <= 89 ){
      for ( int i = 0; i < 3; i++ ){
        digitalWrite(LED1, HIGH);
        delay(1500);
        digitalWrite(LED1, LOW);
        delay(1500);
      }
    }
    else if ( heat_index >= 90 && heat_index <= 104 ){
      for ( int i = 0; i < 9; i++ ){
        digitalWrite(LED1, HIGH);
        delay(500);
        digitalWrite(LED1, LOW);
        delay(500);
      }
    }
    else if ( heat_index >= 105 && heat_index <= 129 ){
      for ( int i = 0; i < 30; i++ ){
        digitalWrite(LED1, HIGH);
        delay(150);
        digitalWrite(LED1, LOW);
        delay(150);
      }
    }
    else{
      for ( int i = 0; i < 90; i++ ){
        digitalWrite(LED1, HIGH);
        delay(50);
        digitalWrite(LED1, LOW);
        delay(50);
      }
    }

    lcd.setCursor(0,1);
    lcd.print("                      ");
    lcd.setCursor(0,1);
    lcd.print("Smoke: ");
    lcd.print(smoke_sensor);
    lcd.print(" ppm");

    if ( smoke_sensor < 50 ){
      digitalWrite(LED1, HIGH);
      delay(9000);
      digitalWrite(LED1, LOW);
    }
    else if ( smoke_sensor >= 51 && smoke_sensor <= 100 ){
      for ( int i = 0; i < 3; i++ ){
        digitalWrite(LED1, HIGH);
        delay(1500);
        digitalWrite(LED1, LOW);
        delay(1500);
      }
    }
    else if ( smoke_sensor >= 101 && smoke_sensor <= 150 ){
      for ( int i = 0; i < 9; i++ ){
        digitalWrite(LED1, HIGH);
        delay(500);
        digitalWrite(LED1, LOW);
        delay(500);
      }
    }
    else{
      for ( int i = 0; i < 90; i++ ){
        digitalWrite(LED1, HIGH);
        delay(50);
        digitalWrite(LED1, LOW);
        delay(50);
      }
    }
  
    delay(3000);
    lcd.setCursor(0,1);
    lcd.print("                      ");
    lcd.setCursor(0,1);
    lcd.print("Gas: ");
    lcd.print(gas_sensor);
    lcd.print(" ppm");

    if ( gas_sensor < 50 ){
      digitalWrite(LED1, HIGH);
      delay(9000);
      digitalWrite(LED1, LOW);
    }
    else if ( gas_sensor >= 50 && gas_sensor <= 100 ){
      for ( int i = 0; i < 3; i++ ){
        digitalWrite(LED1, HIGH);
        delay(500);
        digitalWrite(LED1, LOW);
        delay(500);
      }
    }
    else{
      for ( int i = 0; i < 90; i++ ){
        digitalWrite(LED1, HIGH);
        delay(50);
        digitalWrite(LED1, LOW);
        delay(50);
      }
    }
    
    delay(3000);
    lcd.clear();
  }
  
}
