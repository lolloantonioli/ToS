#include "pins.h"
#include "game.h"
#include "display.h"

void wakeUp();

void setup() {
    Serial.begin(9600);
    randomSeed(analogRead(A1));
    
    pinMode(LED_PIN, OUTPUT);
    pinMode(LED_PIN1, OUTPUT);
    pinMode(LED_PIN2, OUTPUT);
    pinMode(LED_PIN3, OUTPUT);
    pinMode(LED_PIN4, OUTPUT);
    pinMode(BUTTON_PIN1, INPUT);
    pinMode(BUTTON_PIN2, INPUT);
    pinMode(BUTTON_PIN3, INPUT);
    pinMode(BUTTON_PIN4, INPUT);
    
    attachInterrupt(digitalPinToInterrupt(2), wakeUp, RISING);
    
    initializeLcd();
    initializeGame();
}

void loop() {
    switch (gameState) {
        case WAITING:
            handleWaitingState();
            break;
        case SLEEPING:
            handleSleepingState();
            break;
        case PLAYING:
            handlePlayingState();
            break;
        case WAITING_ANSWER:
            handleWaitingAnswerState();
            break;
        case GAME_OVER:
            handleGameOverState();
            break;
    }
}

void wakeUp() {}