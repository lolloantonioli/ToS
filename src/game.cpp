#include <avr/sleep.h>
#include <LiquidCrystal_I2C.h>
#include "Arduino.h"
#include "game.h"
#include "display.h"
#include "pins.h"

extern LiquidCrystal_I2C lcd;
State gameState;
int score;
int numbers[4] = {1, 2, 3, 4};
int totalTime;
int currentLevel;
int factor;
long enteredTime;
long answeringTime;
int currIntensity;
int fadeAmount;
int count;
int answer[4];

void changeState(State state) {
    gameState = state;
}

void initializeGame() {
    changeState(WAITING);
    score = 0;
    totalTime = INITIAL_TIME;
    currentLevel = 0;
    factor = LEVEL_FACTOR;
    currIntensity = 0;
    fadeAmount = FADE_STEP;
    enteredTime = millis();
}

void handleWaitingState() {
    updateDifficultyLevel();
    updateFading();
    displayWelcomeMessage();
    
    if (digitalRead(BUTTON_PIN1) == HIGH) {
        digitalWrite(LED_PIN1, HIGH);
      	delay(300);
        digitalWrite(LED_PIN1, LOW);
      	digitalWrite(LED_PIN, LOW);
        changeState(PLAYING);
        displayGameStart();
    }
    
    if (millis() - enteredTime >= SLEEP_TIMEOUT) {
        changeState(SLEEPING);
        digitalWrite(LED_PIN, LOW);
    }
}

void handleSleepingState() {
    lcd.clear();
    lcd.noBacklight();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();
    
    if (digitalRead(BUTTON_PIN1) == HIGH) {
        changeState(WAITING);
        lcd.backlight();
        enteredTime = millis();
        sleep_disable();
        digitalWrite(LED_PIN1, HIGH);
        delay(200);
        digitalWrite(LED_PIN1, LOW);
    }
}

void handlePlayingState() {
    digitalWrite(LED_PIN, LOW);
    turnOffGreenLeds();
    
    shuffleNumbers();
    displaySequence();
    
    changeState(WAITING_ANSWER);
    lcd.clear();
    count = 0;
    answeringTime = millis();
}

void handleWaitingAnswerState() {
    if (millis() - answeringTime > totalTime) {
        changeState(GAME_OVER);
        return;
    }
    
    if (count < 4) {
        checkButtonInput();
    } else {
        turnOffGreenLeds();
        if (checkAnswer()) {
            totalTime -= factor;
            score++;
            displayScore(score);
            delay(1000);
            changeState(PLAYING);
        } else {
            changeState(GAME_OVER);
        }
    }
}

void handleGameOverState() {
    turnOffGreenLeds();
    
    digitalWrite(LED_PIN, HIGH);
    delay(2000);
    digitalWrite(LED_PIN, LOW);
    
    displayGameOver();
    delay(10000);

    initializeGame();
}

void updateFading() {
    analogWrite(LED_PIN, currIntensity);
    currIntensity += fadeAmount;
    
    if (currIntensity == 0 || currIntensity == 255) {
        fadeAmount = -fadeAmount;
    }
    
    delay(FADE_DELAY);
}

void updateDifficultyLevel() {
    int newLevel = analogRead(POT_PIN) / 256;
    
    if (newLevel != currentLevel) {
        currentLevel = newLevel;
        factor = (newLevel + 1) * LEVEL_FACTOR;
    }
}

void shuffleNumbers() {
    for (int i = 3; i > 0; i--) {
        int j = random(0, i + 1);
        int temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
    }
}

void checkButtonInput() {
    int buttonPins[] = {BUTTON_PIN1, BUTTON_PIN2, BUTTON_PIN3, BUTTON_PIN4};
    int ledPins[] = {LED_PIN1, LED_PIN2, LED_PIN3, LED_PIN4};
    
    for (int i = 0; i < 4; i++) {
        if (digitalRead(buttonPins[i]) == HIGH) {
            digitalWrite(ledPins[i], HIGH);
            answer[count] = i + 1;
            count++;
            delay(200);
        } else {
            digitalWrite(ledPins[i], LOW);
        }
    }
}

bool checkAnswer() {
    for (int i = 0; i < 4; i++) {
        if (numbers[i] != answer[i]) {
            return false;
        }
    }
    return true;
}

void turnOffGreenLeds() {
    digitalWrite(LED_PIN1, LOW);
    digitalWrite(LED_PIN2, LOW);
    digitalWrite(LED_PIN3, LOW);
    digitalWrite(LED_PIN4, LOW);
}