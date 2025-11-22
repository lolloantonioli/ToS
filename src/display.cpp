#include <LiquidCrystal_I2C.h>
#include "Arduino.h"
#include "display.h"
#include "pins.h"

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);
extern int score;
extern int numbers[4];

void initializeLcd() {
    lcd.init();
    lcd.backlight();
}

void displayWelcomeMessage() {
    lcd.setCursor(0, 0);
    lcd.print("Welcome to TOS!");
    lcd.setCursor(0, 1);
    lcd.print("Press B1 to Start");
}

void displayScore(int score) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("GOOD! SCORE: ");
    lcd.print(score);
}

void displayGameStart() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("GO!");
    delay(2000);
}

void displaySequence() {
    lcd.clear();
    for (int i = 0; i < 4; i++) {
        lcd.setCursor(i, 0);
        lcd.print(numbers[i]);
    }
    delay(3000);
}

void displayGameOver() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("GAME OVER!");
    lcd.setCursor(0, 1);
    lcd.print("Score: ");
    lcd.print(score);
}