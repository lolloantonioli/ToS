#ifndef __GAME__
#define __GAME__

#define INITIAL_TIME 8000
#define LEVEL_FACTOR 100
#define SLEEP_TIMEOUT 10000
#define FADE_STEP 30
#define FADE_DELAY 15

enum State {
    WAITING,
    SLEEPING,
    PLAYING,
    WAITING_ANSWER,
    GAME_OVER
};

extern State gameState;

void changeState(State state);
void initializeGame();
void handleWaitingState();
void handleSleepingState();
void handlePlayingState();
void handleWaitingAnswerState();
void handleGameOverState();
void updateFading();
void updateDifficultyLevel();
void shuffleNumbers();
void checkButtonInput();
bool checkAnswer();
void turnOffGreenLeds();

#endif