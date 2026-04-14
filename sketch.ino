#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2
#define DHTTYPE DHT22 
#define RED_PIN 9
#define GREEN_PIN 10
#define BLUE_PIN 11
#define BUZZER_PIN 8

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);

  dht.begin();
  lcd.begin(16, 2);
  lcd.backlight();

  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  float temp = dht.readTemperature();

  // Display on LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print(" C   ");

  // Display on Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" C");

  // RGB and Buzzer Logic
  if (temp < 35) {
    setColor(0, 0, 255); // Blue
    Serial.println("Color: Blue");
    noTone(BUZZER_PIN); // Buzzer OFF
  } else if (temp == 35) {
    setColor(0, 255, 0); // Green
    Serial.println("Color: Green");
    noTone(BUZZER_PIN); // Buzzer OFF
  } else if (temp > 35) {
    setColor(255, 0, 0); // Red
    Serial.println("Color: Red");
    tone(BUZZER_PIN, 1000); // Buzzer ON with tone
  }

  delay(1000);
}

// Adjusted for common anode RGB LED: invert PWM values
void setColor(int r, int g, int b) {
  analogWrite(RED_PIN, 255 - r);
  analogWrite(GREEN_PIN, 255 - g);
  analogWrite(BLUE_PIN, 255 - b);
}
