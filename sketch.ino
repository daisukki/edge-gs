#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET    -1 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define BUZZER 3
#define POT_PIN A0 
void setup() {
  pinMode(BUZZER, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

void loop() {
  int potValue = analogRead(POT_PIN);
  float seaLevel = map(potValue, 0, 1023, 0, 20) / 1000.0;

  display.clearDisplay();
  display.setTextSize(1); 
  display.setTextColor(SSD1306_WHITE); 
  display.setCursor(0,0); 
  display.print("Nivel do Mar: ");
  display.print(seaLevel, 3); 
  display.print("mm");

  if (seaLevel > 0.010) {
    tone(BUZZER, 1000); // kHz
    display.setTextSize(1); 
    display.setCursor(0, 50);
    display.setTextColor(SSD1306_INVERSE); 
    display.print("Nivel do Mar Elevado!");
  } else {
    noTone(BUZZER);
  }

  display.display();
  delay(100); 
}
