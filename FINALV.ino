#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <NewPing.h>
#include <math.h>

const int trigPin = 6;
const int echoPin = 7; 
const int emptyDistance = 24; 

LiquidCrystal_I2C lcd(0x27, 16, 2);
NewPing sonar(trigPin, echoPin, 500);

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  float distance = sonar.convert_cm(sonar.ping_median(50));
  float waterPercentage = ((emptyDistance - distance) / emptyDistance) * 100;
  bool isValid = waterPercentage <= 100 && waterPercentage >= 0;

  lcd.clear();
  lcd.setCursor(0, 0);

  Serial.print("Distance: ");
  Serial.println(distance);

  Serial.println(emptyDistance - distance);
  Serial.println(emptyDistance);

  if (!isValid) {
    lcd.print("Fill Me Up!");
    lcd.setCursor(0, 1);
    lcd.print("Container Empty!");
  } else {
    Serial.print("Water Percentage: ");
    Serial.println(waterPercentage);

    lcd.print("Water Percentage:");
    lcd.setCursor(0, 1);
    lcd.print(waterPercentage);
    lcd.print("%");
  }

  delay(1000);
}
