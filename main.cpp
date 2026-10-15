/*
* Author: Riccardo Bean
* Assignment: Simple 2D Scene
* Date due: 10/05/2026
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.

*/

#include "CS3113/cs3113.h"
#include <cmath>

// Global Constants
constexpr int SCREEN_WIDTH = 1700,
              SCREEN_HEIGHT = 800,
              FPS = 60;

constexpr Vector2 ORIGIN = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
constexpr char BACKGROUND[] = "assets/game/Board.png";
constexpr char PLAYER1[] = "assets/game/Computer.png";
constexpr char PLAYER2[] = "assets/game/Player.png";
constexpr char BALL[] = "assets/game/Ball.png";
constexpr char LIVES[] = "assets/game/HealthUI.png";
constexpr char WELCOME[] = "assets/game/Welcome.png";
constexpr char GOA[] = "assets/game/GOA.png";
constexpr char GOH[] = "assets/game/GOH.png";
constexpr char GO1[] = "assets/game/GO1.png";
constexpr char GO2[] = "assets/game/GO2.png";
constexpr char INSTRUCTIONS[] = "assets/game/Rules.png";
constexpr char DEMON[] = "assets/game/spikes.png";
enum GameStatus { RULES, PLAYING, PAUSED, GAME_OVER };
enum GameMode { AI, MULTI_PLAYER };
enum GameDifficuly { REGULAR, CRAZY };
enum GameWinner { BOT, HUMAN, PLAYER_1, PLAYER_2 };

// Global Variables
AppStatus gAppStatus = RUNNING;
float gPulseTime = 0.0f;
float gPreviousTicks = 0.0f;
GameStatus gGameStatus = PAUSED;
GameMode gGameMode = AI;
GameDifficuly gGameDifficulty = REGULAR;
GameWinner gGameWinner;

// Global Variables - Background
Texture2D gBackground;
Vector2 gBackgroundPosition = ORIGIN;
Vector2 gBackgroundScale = {SCREEN_WIDTH, SCREEN_HEIGHT};
Color gBackgroundColor = WHITE;

// Global Variables - Player1
Texture2D gPlayer1;
Vector2 gPlayer1Position = {100, 400};
Vector2 gPlayer1Scale = {20, 200};

// Global Variables - Player1 Lives
Texture2D gPlayer1Lives;
Vector2 gPlayer1LivesScale = {100, 30};
Vector2 gPlayer1LivesPosition = {SCREEN_WIDTH / 2 - gPlayer1LivesScale.x, gPlayer1LivesScale.y * 2};
int gLives1 = 3;

// Global Variables - Player2
Texture2D gPlayer2;
Vector2 gPlayer2Position = {1590, 400};
Vector2 gPlayer2Scale = {20, 200};

// Global Variables - Player2 Lives
Texture2D gPlayer2Lives;
Vector2 gPlayer2LivesScale = {100, 30};
Vector2 gPlayer2LivesPosition = {SCREEN_WIDTH / 2 + gPlayer2LivesScale.x, gPlayer2LivesScale.y * 2};
int gLives2 = 3;

// Global Variables - Ball
Texture2D gBall;
Vector2 gBallPosition = {800, 400};
Vector2 gBallScale = {30, 30};
float gBallSpeedX, gBallSpeedY;

// Global Variables - ExtraBall1
Texture2D gExtraBall1;
Vector2 gExtraBall1Position = {800, 400};
Vector2 gExtraBall1Scale = {30, 30};
bool gExtraBall1Active = false;
float gExtraBall1SpeedX, gExtraBall1SpeedY;

// Global Variables - ExtraBall2
Texture2D gExtraBall2;
Vector2 gExtraBall2Position = {800, 400};
Vector2 gExtraBall2Scale = {30, 30};
bool gExtraBall2Active = false;
float gExtraBall2SpeedX, gExtraBall2SpeedY;

// Global Variables - ExtraBall3
Texture2D gExtraBall3;
Vector2 gExtraBall3Position = {800, 400};
Vector2 gExtraBall3Scale = {30, 30};
bool gExtraBall3Active = false;
float gExtraBall3SpeedX, gExtraBall3SpeedY;

// Global Variables - Demon Ball
Texture2D gDemon;
Vector2 gDemonScale = {75, 50};
Vector2 gDemonPosition = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
float gDemonSpeedX, gDemonSpeedY;
bool gDemonActive = false;

// Global Variables - Screens
Texture2D gWelcomeScreen;
Vector2 gWelcomeScreenPosition = ORIGIN;
Vector2 gWelcomeScreenScale = {SCREEN_WIDTH, SCREEN_HEIGHT};
Texture2D gGOA;
Texture2D gGOH;
Texture2D gGO1;
Texture2D gGO2;
Texture2D gRulesScreen;

// Global Variables - Crazy Mode
float gCrazyModeTime = 0.0f;
float gNextSpeedIncrease = 5.0f;

// Function Declarations

// Game functions
void initialise();
void processInput();
void update();
void render();
void shutdown();

// Extra functions
void ResetBall(int ballIndex);
void GameReset();
int GetClosestBall();

// Function Definitions
void ResetBall(int ballIndex) {
    if (ballIndex == 0) {
        gBallPosition = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
        if (GetRandomValue(0, 1) == 0)
            gBallSpeedX = GetRandomValue(-500, -300) * 1.0f;
        else
            gBallSpeedX = GetRandomValue(300, 500) * 1.0f;
        if (GetRandomValue(0, 1) == 0)
            gBallSpeedY = GetRandomValue(-350, -150) * 1.0f;
        else            
            gBallSpeedY = GetRandomValue(150, 350) * 1.0f;
    } else if (ballIndex == 1) {
        gExtraBall1Position = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
        if (GetRandomValue(0, 1) == 0) 
            gExtraBall1SpeedX = GetRandomValue(-500, -300) * 1.0f;
        else 
            gExtraBall1SpeedX = GetRandomValue(300, 500) * 1.0f;
        if (GetRandomValue(0, 1) == 0) 
            gExtraBall1SpeedY = GetRandomValue(-350, -150) * 1.0f;
        else 
            gExtraBall1SpeedY = GetRandomValue(150, 350) * 1.0f;
    } else if (ballIndex == 2) {
        gExtraBall2Position = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
        if (GetRandomValue(0, 1) == 0) 
            gExtraBall2SpeedX = GetRandomValue(-500, -300) * 1.0f;
        else
            gExtraBall2SpeedX = GetRandomValue(300, 500) * 1.0f;
        if (GetRandomValue(0, 1) == 0)
            gExtraBall2SpeedY = GetRandomValue(-350, -150) * 1.0f;
        else 
            gExtraBall2SpeedY = GetRandomValue(150, 350) * 1.0f;
    } else if (ballIndex == 3) {
        gExtraBall3Position = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
        if (GetRandomValue(0, 1) == 0) 
            gExtraBall3SpeedX = GetRandomValue(-500, -300) * 1.0f;
        else 
            gExtraBall3SpeedX = GetRandomValue(300, 500) * 1.0f;
        if (GetRandomValue(0, 1) == 0)
            gExtraBall3SpeedY = GetRandomValue(-350, -150) * 1.0f;
        else
            gExtraBall3SpeedY = GetRandomValue(150, 350) * 1.0f;
    } else if (ballIndex == 4) {
        gDemonPosition = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
        if (gGameMode == MULTI_PLAYER) {
            if (GetRandomValue(0, 1) == 0)
                gDemonSpeedX = GetRandomValue(-800, -600) * 1.0f;
            else
                gDemonSpeedX = GetRandomValue(600, 800) * 1.0f;
            if (GetRandomValue(0, 1) == 0)             
                gDemonSpeedY = GetRandomValue(-800, -600) * 1.0f;
            else
                gDemonSpeedY = GetRandomValue(600, 800) * 1.0f;

        } else {
            gDemonSpeedX = GetRandomValue(-800, -600) * 1.0f;
            gDemonSpeedY = GetRandomValue(600, 800) * 1.0f;
        }
    }
}

void BallBoundaries() {
    
}

void GameReset() {
    gPlayer1Position = {100, 400};
    gPlayer2Position = {1590, 400};
    gPlayer1Scale = {20, 200};
    gPlayer2Scale = {20, 200};
    gCrazyModeTime = 0.0f;
    gNextSpeedIncrease = 5.0f;
    gExtraBall1Active = false;
    gExtraBall2Active = false;
    gExtraBall3Active = false;
    gDemonActive = false;
    gLives1 = 3;
    gLives2 = 3;
}

int GetClosestBall() {
    int closestDistance = gPlayer2Position.x - gBallPosition.x;
    int heightClosestBall = gBallPosition.y;
    if (gExtraBall1Active && gPlayer2Position.x - gExtraBall1Position.x < closestDistance) {
        closestDistance = gPlayer2Position.x - gExtraBall1Position.x;
        heightClosestBall = gExtraBall1Position.y;
    }
    if (gExtraBall2Active && gPlayer2Position.x - gExtraBall2Position.x < closestDistance) {
        closestDistance = gPlayer2Position.x - gExtraBall2Position.x;
        heightClosestBall = gExtraBall2Position.y;
    }
    if (gExtraBall3Active && gPlayer2Position.x - gExtraBall3Position.x < closestDistance) {
        closestDistance = gPlayer2Position.x - gExtraBall3Position.x;
        heightClosestBall = gExtraBall3Position.y;
    }
    return heightClosestBall;
}

void initialise() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong");

    gBackground = LoadTexture(BACKGROUND);
    gPlayer1 = LoadTexture(PLAYER1);
    gPlayer1Lives = LoadTexture(LIVES);
    gPlayer2 = LoadTexture(PLAYER2);
    gPlayer2Lives = LoadTexture(LIVES);
    gBall = LoadTexture(BALL);
    gExtraBall1 = LoadTexture(BALL);
    gExtraBall2 = LoadTexture(BALL);
    gExtraBall3 = LoadTexture(BALL);
    gWelcomeScreen = LoadTexture(WELCOME);
    gGOA = LoadTexture(GOA);
    gGOH = LoadTexture(GOH);
    gGO1 = LoadTexture(GO1);
    gGO2 = LoadTexture(GO2);
    gRulesScreen = LoadTexture(INSTRUCTIONS);
    gDemon = LoadTexture(DEMON);
    ResetBall(0);

    SetTargetFPS(FPS);
}

void processInput() {
    if (WindowShouldClose() && !IsKeyPressed(KEY_ESCAPE)) gAppStatus = TERMINATED;
    if (gGameStatus == PLAYING) {
        if (IsKeyPressed(KEY_ESCAPE)) gGameStatus = PAUSED;
        if (IsKeyDown(KEY_W) && gPlayer1Position.y > gPlayer1Scale.y / 2) gPlayer1Position.y -= 5.0f;
        if (IsKeyDown(KEY_S) && gPlayer1Position.y < SCREEN_HEIGHT - gPlayer1Scale.y / 2) gPlayer1Position.y += 5.0f;
        if (IsKeyDown(KEY_UP) && gPlayer2Position.y > gPlayer2Scale.y / 2 && gGameMode == MULTI_PLAYER) gPlayer2Position.y -= 5.0f;
        if (IsKeyDown(KEY_DOWN) && gPlayer2Position.y < SCREEN_HEIGHT - gPlayer2Scale.y / 2 && gGameMode == MULTI_PLAYER) gPlayer2Position.y += 5.0f;
        if (IsKeyPressed(KEY_T)) {
            if (gGameMode == AI) 
                gGameMode = MULTI_PLAYER;
            else
                gGameMode = AI; 
        }
        if (IsKeyPressed(KEY_R)) {
            ResetBall(0);
            GameReset();
            gGameStatus = PLAYING;
        }
        if (IsKeyPressed(KEY_ONE)) {
            ResetBall(1);
            gExtraBall1Active = true;
        }
        if (IsKeyPressed(KEY_TWO)) {
            ResetBall(1);
            ResetBall(2);
            gExtraBall1Active = true;
            gExtraBall2Active = true;
        }
        if (IsKeyPressed(KEY_THREE)) {
            ResetBall(1);
            ResetBall(2);
            ResetBall(3);
            gExtraBall1Active = true;
            gExtraBall2Active = true;
            gExtraBall3Active = true;
        }
        if (IsKeyPressed(KEY_P)) {
            gGameStatus = PAUSED;
        }
    } else if (gGameStatus == PAUSED) {
        if (IsKeyPressed(KEY_ESCAPE)) gAppStatus = TERMINATED;
        if (IsKeyPressed(KEY_ONE)) {
            gGameStatus = RULES;
        }
        if (IsKeyPressed(KEY_TWO)) {
            ResetBall(0);
            GameReset();
            gGameMode = MULTI_PLAYER;
            gGameStatus = PLAYING;
        }
        if (IsKeyPressed(KEY_THREE)) {
            ResetBall(0);
            GameReset();
            gGameMode = AI;
            gGameStatus = PLAYING;
        }
        if (IsKeyPressed(KEY_FOUR)) {
            ResetBall(0);
            GameReset();
            gGameDifficulty = CRAZY;
            gGameStatus = PLAYING;
        }
    } else if (gGameStatus == GAME_OVER) {
        if (IsKeyPressed(KEY_R)) {
            ResetBall(0);
            GameReset();
            gGameStatus = PLAYING;
        } 
        if (IsKeyPressed(KEY_M)) {
            gGameStatus = PAUSED;
        }
    } else if (gGameStatus == RULES) {
        if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_M)) {
            gGameStatus = PAUSED;
        }
    }
}

void update() {
    float ticks = GetTime();
    float deltaTime = ticks - gPreviousTicks;
    gPreviousTicks = ticks;
    // Delta time to make the pulse look exactly the same on every computer
    gPulseTime += 1.0f * deltaTime;
    if (gGameStatus == PLAYING) {
        gBallPosition.x += gBallSpeedX * deltaTime;
        gBallPosition.y += gBallSpeedY * deltaTime;

        if (gExtraBall1Active) {
            gExtraBall1Position.x += gExtraBall1SpeedX * deltaTime;
            gExtraBall1Position.y += gExtraBall1SpeedY * deltaTime;
        }
        if (gExtraBall2Active) {
            gExtraBall2Position.x += gExtraBall2SpeedX * deltaTime;
            gExtraBall2Position.y += gExtraBall2SpeedY * deltaTime;
        }
        if (gExtraBall3Active) {
            gExtraBall3Position.x += gExtraBall3SpeedX * deltaTime;
            gExtraBall3Position.y += gExtraBall3SpeedY * deltaTime;
        }
        if (gDemonActive) {
            gDemonPosition.x += gDemonSpeedX * deltaTime;
            gDemonPosition.y += gDemonSpeedY * deltaTime;
        }

        if (gGameMode == AI) {
            int closestBall = GetClosestBall();
            if (closestBall < gPlayer2Position.y && gPlayer2Position.y > gPlayer2Scale.y / 2) {
                gPlayer2Position.y -= 5.0f;
            }
            if (closestBall > gPlayer2Position.y && gPlayer2Position.y < SCREEN_HEIGHT - gPlayer2Scale.y / 2) {
                gPlayer2Position.y += 5.0f;
            }
        }

        if (gGameDifficulty == CRAZY) {
            gCrazyModeTime += deltaTime;
            if (gCrazyModeTime >= gNextSpeedIncrease) {
                gBallSpeedX *= 1.2f;
                gBallSpeedY *= 1.2f;
                gExtraBall1SpeedX *= 1.2f;
                gExtraBall1SpeedY *= 1.2f;
                gExtraBall2SpeedX *= 1.2f;
                gExtraBall2SpeedY *= 1.2f;
                gExtraBall3SpeedX *= 1.2f;
                gExtraBall3SpeedY *= 1.2f;

                gNextSpeedIncrease += 5.0f;
            }

            if (gCrazyModeTime >= 10.0f) {
                gPlayer1Scale.y = 150.0f;
                if (gGameMode == MULTI_PLAYER)
                    gPlayer2Scale.y = 150.0f;
            }

            if (gCrazyModeTime >= 15.0f && !gDemonActive) {
                ResetBall(4);
                gDemonActive = true;
            }

            if (gCrazyModeTime >= 20.0f) {
                gPlayer1Scale.y = 110.0f;
                if (gGameMode == AI)
                    gPlayer2Scale.y = 150.0f;
                else if (gGameMode == MULTI_PLAYER)
                    gPlayer2Scale.y = 110.0f;
                if (!gExtraBall1Active) {
                    ResetBall(1);
                    gExtraBall1Active = true;
                }
            }

            if (gCrazyModeTime >= 30.0f) {
                gPlayer1Scale.y = 70.0f;
                if (gGameMode == AI)
                    gPlayer2Scale.y = 110.0f;
                else if (gGameMode == MULTI_PLAYER)
                    gPlayer2Scale.y = 70.0f;
            }
        }

        if (gBallPosition.x < gPlayer1Position.x - gPlayer1Scale.x * 2) {
            ResetBall(0);
            gLives1--;
        }
        if (gBallPosition.x > gPlayer2Position.x + gPlayer2Scale.x * 2) {
            ResetBall(0);
            gLives2--;
        }

        if (gExtraBall1Active) {
            if (gExtraBall1Position.x < gPlayer1Position.x - gPlayer1Scale.x * 2) {
                ResetBall(1);
                gLives1--;
            }
            if (gExtraBall1Position.x > gPlayer2Position.x + gPlayer2Scale.x * 2) {
                ResetBall(1);
                gLives2--;
            }
        }
        if (gExtraBall2Active) {
            if (gExtraBall2Position.x < gPlayer1Position.x - gPlayer1Scale.x * 2) {
                ResetBall(2);
                gLives1--;
            }
            if (gExtraBall2Position.x > gPlayer2Position.x + gPlayer2Scale.x * 2) {
                ResetBall(2);
                gLives2--;
            }
        }
        if (gExtraBall3Active) {
            if (gExtraBall3Position.x < gPlayer1Position.x - gPlayer1Scale.x * 2) {
                ResetBall(3);
                gLives1--;
            }
            if (gExtraBall3Position.x > gPlayer2Position.x + gPlayer2Scale.x * 2) {
                ResetBall(3);
                gLives2--;
            }
        }
        if (gDemonActive) {
            if (gDemonPosition.x < gPlayer1Position.x - gPlayer1Scale.x * 2) {
                ResetBall(4);
                gLives1 = 3;
            }
            if (gDemonPosition.x > gPlayer2Position.x + gPlayer2Scale.x * 2) {
                ResetBall(4);
                gLives2 = 3;
            }
        }
        

        if (gBallPosition.y < gBallScale.y / 2) {
            gBallPosition.y = gBallScale.y / 2;
            gBallSpeedY = -gBallSpeedY;
        } 
        if (gBallPosition.y > SCREEN_HEIGHT - gBallScale.y / 2) {
            gBallPosition.y = SCREEN_HEIGHT - gBallScale.y / 2;
            gBallSpeedY = -gBallSpeedY;
        }

        if (gExtraBall1Active) {
            if (gExtraBall1Position.y < gExtraBall1Scale.y / 2) {
                gExtraBall1Position.y = gExtraBall1Scale.y / 2;
                gExtraBall1SpeedY = -gExtraBall1SpeedY;
            } 
            if (gExtraBall1Position.y > SCREEN_HEIGHT - gExtraBall1Scale.y / 2) {
                gExtraBall1Position.y = SCREEN_HEIGHT - gExtraBall1Scale.y / 2;
                gExtraBall1SpeedY = -gExtraBall1SpeedY;
            }
        }
        if (gExtraBall2Active) {
            if (gExtraBall2Position.y < gExtraBall2Scale.y / 2) {
                gExtraBall2Position.y = gExtraBall2Scale.y / 2;
                gExtraBall2SpeedY = -gExtraBall2SpeedY;
            }
            if (gExtraBall2Position.y > SCREEN_HEIGHT - gExtraBall2Scale.y / 2) {
                gExtraBall2Position.y = SCREEN_HEIGHT - gExtraBall2Scale.y / 2;
                gExtraBall2SpeedY = -gExtraBall2SpeedY;
            }
        }
        if (gExtraBall3Active) {
            if (gExtraBall3Position.y < gExtraBall3Scale.y / 2) {
                gExtraBall3Position.y = gExtraBall3Scale.y / 2;
                gExtraBall3SpeedY = -gExtraBall3SpeedY;
            }
            if (gExtraBall3Position.y > SCREEN_HEIGHT - gExtraBall3Scale.y / 2) {
                gExtraBall3Position.y = SCREEN_HEIGHT - gExtraBall3Scale.y / 2;
                gExtraBall3SpeedY = -gExtraBall3SpeedY;
            }
        }

        if (gDemonActive) {
            if (gDemonPosition.y < gDemonScale.y / 2) {
                gDemonPosition.y = gDemonScale.y / 2;
                gDemonSpeedY = -gDemonSpeedY;
            }
            if (gDemonPosition.y > SCREEN_HEIGHT - gDemonScale.y / 2) {
                gDemonPosition.y = SCREEN_HEIGHT - gDemonScale.y / 2;
                gDemonSpeedY = -gDemonSpeedY;
            }
        }

        
        if (gBallPosition.x < gPlayer1Position.x + gPlayer1Scale.x / 2 && 
            gBallPosition.x > gPlayer1Position.x - gPlayer1Scale.x / 2 &&
            gBallPosition.y < gPlayer1Position.y + gPlayer1Scale.y / 2 && 
            gBallPosition.y > gPlayer1Position.y - gPlayer1Scale.y / 2) {
            gBallPosition.x = gPlayer1Position.x + gPlayer1Scale.x / 2 + gBallScale.x / 2;
            gBallSpeedX = -gBallSpeedX;
        }

        if (gExtraBall1Active) {
            if (gExtraBall1Position.x < gPlayer1Position.x + gPlayer1Scale.x / 2 && 
                gExtraBall1Position.x > gPlayer1Position.x - gPlayer1Scale.x / 2 &&
                gExtraBall1Position.y < gPlayer1Position.y + gPlayer1Scale.y / 2 && 
                gExtraBall1Position.y > gPlayer1Position.y - gPlayer1Scale.y / 2) {
                gExtraBall1Position.x = gPlayer1Position.x + gPlayer1Scale.x / 2 + gExtraBall1Scale.x / 2;
                gExtraBall1SpeedX = -gExtraBall1SpeedX;
            }
        }
        if (gExtraBall2Active) {
            if (gExtraBall2Position.x < gPlayer1Position.x + gPlayer1Scale.x / 2 && 
                gExtraBall2Position.x > gPlayer1Position.x - gPlayer1Scale.x / 2 &&
                gExtraBall2Position.y < gPlayer1Position.y + gPlayer1Scale.y / 2 && 
                gExtraBall2Position.y > gPlayer1Position.y - gPlayer1Scale.y / 2) {
                gExtraBall2Position.x = gPlayer1Position.x + gPlayer1Scale.x / 2 + gExtraBall2Scale.x / 2;
                gExtraBall2SpeedX = -gExtraBall2SpeedX;
            }
        }
        if (gExtraBall3Active) {
            if (gExtraBall3Position.x < gPlayer1Position.x + gPlayer1Scale.x / 2 && 
                gExtraBall3Position.x > gPlayer1Position.x - gPlayer1Scale.x / 2 &&
                gExtraBall3Position.y < gPlayer1Position.y + gPlayer1Scale.y / 2 && 
                gExtraBall3Position.y > gPlayer1Position.y - gPlayer1Scale.y / 2) {
                gExtraBall3Position.x = gPlayer1Position.x + gPlayer1Scale.x / 2 + gExtraBall3Scale.x / 2;
                gExtraBall3SpeedX = -gExtraBall3SpeedX;
            }
        }
        if (gDemonActive) {
            if (gDemonPosition.x < gPlayer1Position.x + gPlayer1Scale.x / 2 && 
                gDemonPosition.x > gPlayer1Position.x - gPlayer1Scale.x / 2 &&
                gDemonPosition.y < gPlayer1Position.y + gPlayer1Scale.y / 2 && 
                gDemonPosition.y > gPlayer1Position.y - gPlayer1Scale.y / 2) {
                gDemonPosition.x = gPlayer1Position.x + gPlayer1Scale.x / 2 + gDemonScale.x / 2;
                gLives1 = 0;
            }
        }
            
        if (gBallPosition.x < gPlayer2Position.x + gPlayer2Scale.x / 2 &&
            gBallPosition.x > gPlayer2Position.x - gPlayer2Scale.x / 2 &&
            gBallPosition.y < gPlayer2Position.y + gPlayer2Scale.y / 2 &&
            gBallPosition.y > gPlayer2Position.y - gPlayer2Scale.y / 2) {
            gBallPosition.x = gPlayer2Position.x - gPlayer2Scale.x / 2 - gBallScale.x / 2;
            gBallSpeedX = -gBallSpeedX;
        }
        if (gExtraBall1Active) {
            if (gExtraBall1Position.x < gPlayer2Position.x + gPlayer2Scale.x / 2 &&
                gExtraBall1Position.x > gPlayer2Position.x - gPlayer2Scale.x / 2 &&
                gExtraBall1Position.y < gPlayer2Position.y + gPlayer2Scale.y / 2 &&
                gExtraBall1Position.y > gPlayer2Position.y - gPlayer2Scale.y / 2) {
                gExtraBall1Position.x = gPlayer2Position.x - gPlayer2Scale.x / 2 - gExtraBall1Scale.x / 2;
                gExtraBall1SpeedX = -gExtraBall1SpeedX;
            }
        }
        if (gExtraBall2Active) {
            if (gExtraBall2Position.x < gPlayer2Position.x + gPlayer2Scale.x / 2 &&
                gExtraBall2Position.x > gPlayer2Position.x - gPlayer2Scale.x / 2 &&
                gExtraBall2Position.y < gPlayer2Position.y + gPlayer2Scale.y / 2 &&
                gExtraBall2Position.y > gPlayer2Position.y - gPlayer2Scale.y / 2) {
                gExtraBall2Position.x = gPlayer2Position.x - gPlayer2Scale.x / 2 - gExtraBall2Scale.x / 2;
                gExtraBall2SpeedX = -gExtraBall2SpeedX;
            }
        }
        if (gExtraBall3Active) {
            if (gExtraBall3Position.x < gPlayer2Position.x + gPlayer2Scale.x / 2 &&
                gExtraBall3Position.x > gPlayer2Position.x - gPlayer2Scale.x / 2 &&
                gExtraBall3Position.y < gPlayer2Position.y + gPlayer2Scale.y / 2 &&
                gExtraBall3Position.y > gPlayer2Position.y - gPlayer2Scale.y / 2) {
                gExtraBall3Position.x = gPlayer2Position.x - gPlayer2Scale.x / 2 - gExtraBall3Scale.x / 2;
                gExtraBall3SpeedX = -gExtraBall3SpeedX;
            }
        }
        if (gDemonActive) {
            if (gDemonPosition.x < gPlayer2Position.x + gPlayer2Scale.x / 2 &&
                gDemonPosition.x > gPlayer2Position.x - gPlayer2Scale.x / 2 &&
                gDemonPosition.y < gPlayer2Position.y + gPlayer2Scale.y / 2 &&
                gDemonPosition.y > gPlayer2Position.y - gPlayer2Scale.y / 2) {
                gDemonPosition.x = gPlayer2Position.x - gPlayer2Scale.x / 2 - gDemonScale.x / 2;
                gLives2 = 0;
            }
        }

        if (gLives1 <= 0) {
            gGameStatus = GAME_OVER;
            if (gGameMode == MULTI_PLAYER) gGameWinner = PLAYER_2;
            else gGameWinner = BOT;
        }
        if (gLives2 <= 0) {
            gGameStatus = GAME_OVER;
            if (gGameMode == MULTI_PLAYER) gGameWinner = PLAYER_1;
            else gGameWinner = HUMAN;
        }

    } else if (gGameStatus == GAME_OVER) {
        gBallSpeedX = 0.0f;
        gBallSpeedY = 0.0f;
        gExtraBall1SpeedX = 0.0f;
        gExtraBall1SpeedY = 0.0f;
        gExtraBall2SpeedX = 0.0f;
        gExtraBall2SpeedY = 0.0f;
        gExtraBall3SpeedX = 0.0f;
        gExtraBall3SpeedY = 0.0f;
        gBallPosition = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
        gExtraBall1Position = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
        gExtraBall2Position = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
        gExtraBall3Position = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
        gExtraBall1Active = false;
        gExtraBall2Active = false;
        gExtraBall3Active = false;
    }
    
    

}

void render() {
    BeginDrawing();
    ClearBackground(gBackgroundColor);
    // Texture Area
    

    Rectangle backgroundTextureArea = {
        // Top left corner
        0.0f,
        0.0f,

        // How large of a rectangle, starting from 0,0 do we want to slice
        static_cast<float>(gBackground.width),
        static_cast<float>(gBackground.height),

    };

    Rectangle player1TextureArea = {
        0.0f,
        0.0f,

        static_cast<float>(gPlayer1.width),
        static_cast<float>(gPlayer1.height),
    };

    Rectangle player1LivesTextureArea = {
        0.0f,
        (3 - gLives1) * 2.0f * gPlayer1Lives.height / 7.0f,

        static_cast<float>(gPlayer1Lives.width),
        static_cast<float>(gPlayer1Lives.height / 7.0f),
    };

    Rectangle player2TextureArea = {
        0.0f,
        0.0f,

        static_cast<float>(gPlayer2.width),
        static_cast<float>(gPlayer2.height),
    };

    Rectangle player2LivesTextureArea = {
        0.0f,
        (3 - gLives2) * 2.0f * gPlayer2Lives.height / 7.0f,

        static_cast<float>(gPlayer2Lives.width),
        static_cast<float>(gPlayer2Lives.height / 7.0f),
    };

    Rectangle ballTextureArea = {
        0.0f,
        0.0f,

        static_cast<float>(gBall.width),
        static_cast<float>(gBall.height),
    };

    Rectangle extraBall1TextureArea = {
        0.0f,
        0.0f,

        static_cast<float>(gExtraBall1.width),
        static_cast<float>(gExtraBall1.height),
    };

    Rectangle extraBall2TextureArea = {
        0.0f,
        0.0f,

        static_cast<float>(gExtraBall2.width),
        static_cast<float>(gExtraBall2.height),
    };

    Rectangle extraBall3TextureArea = {
        0.0f,
        0.0f,

        static_cast<float>(gExtraBall3.width),
        static_cast<float>(gExtraBall3.height),
    };
    Rectangle welcomeScreenTextureArea = {
        0.0f,
        0.0f,
        static_cast<float>(gWelcomeScreen.width),
        static_cast<float>(gWelcomeScreen.height),
    };
    Rectangle demonTextureArea = {
        0.0f,
        0.0f,
        static_cast<float>(gDemon.width),
        static_cast<float>(gDemon.height),
    };
    

    // Destination Area
    Rectangle backgroundDestinationArea = {
        // where we want our rectangle to start being drawn
        gBackgroundPosition.x, gBackgroundPosition.y,

        // how big do we want it to be on our screen / scale
        gBackgroundScale.x * 2, gBackgroundScale.y * 2
    };
    Rectangle player1DestinationArea = {
        gPlayer1Position.x, gPlayer1Position.y,

        gPlayer1Scale.x, gPlayer1Scale.y
    };
    Rectangle player1LivesDestinationArea = {
        gPlayer1LivesPosition.x, gPlayer1LivesPosition.y,

        gPlayer1LivesScale.x, gPlayer1LivesScale.y
    };
    Rectangle player2DestinationArea = {
        gPlayer2Position.x, gPlayer2Position.y,

        gPlayer2Scale.x, gPlayer2Scale.y
    };
    Rectangle player2LivesDestinationArea = {
        gPlayer2LivesPosition.x, gPlayer2LivesPosition.y,

        gPlayer2LivesScale.x, gPlayer2LivesScale.y
    };
    Rectangle ballDestinationArea = {
        gBallPosition.x, gBallPosition.y,

        gBallScale.x, gBallScale.y
    };

    Rectangle extraBall1DestinationArea = {
        gExtraBall1Position.x, gExtraBall1Position.y,

        gExtraBall1Scale.x, gExtraBall1Scale.y
    };

    Rectangle extraBall2DestinationArea = {
        gExtraBall2Position.x, gExtraBall2Position.y,

        gExtraBall2Scale.x, gExtraBall2Scale.y
    };

    Rectangle extraBall3DestinationArea = {
        gExtraBall3Position.x, gExtraBall3Position.y,

        gExtraBall3Scale.x, gExtraBall3Scale.y
    };

    Rectangle welcomeScreenDestinationArea = {
        gWelcomeScreenPosition.x, gWelcomeScreenPosition.y,

        gWelcomeScreenScale.x, gWelcomeScreenScale.y
    };

    Rectangle demonDestinationArea = {
        gDemonPosition.x, gDemonPosition.y,

        gDemonScale.x, gDemonScale.y
    };


    // Origin Offset
    Vector2 backgroundOriginOffset = {
        gBackgroundScale.x, gBackgroundScale.y
    };

    Vector2 player1OriginOffset = {
        gPlayer1Scale.x / 2, gPlayer1Scale.y / 2
    };
    Vector2 player1LivesOriginOffset = {
        gPlayer1LivesScale.x / 2, gPlayer1LivesScale.y / 2
    };
    Vector2 player2OriginOffset = {
        gPlayer2Scale.x / 2, gPlayer2Scale.y / 2
    };
    Vector2 player2LivesOriginOffset = {
        gPlayer2LivesScale.x / 2, gPlayer2LivesScale.y / 2
    };
    Vector2 ballOriginOffset = {
        gBallScale.x / 2, gBallScale.y / 2
    };

    Vector2 extraBall1OriginOffset = {
        gExtraBall1Scale.x / 2, gExtraBall1Scale.y / 2
    };
    Vector2 extraBall2OriginOffset = {
        gExtraBall2Scale.x / 2, gExtraBall2Scale.y / 2
    };
    Vector2 extraBall3OriginOffset = {
        gExtraBall3Scale.x / 2, gExtraBall3Scale.y / 2
    };
    Vector2 welcomeScreenOriginOffset = {
        gWelcomeScreenScale.x / 2, gWelcomeScreenScale.y / 2
    };
    Vector2 demonOriginOffset = {
        gDemonScale.x / 2, gDemonScale.y / 2
    };

    // Draw the textures
    if (gGameStatus == PLAYING) {
        DrawTexturePro(gBackground, backgroundTextureArea, backgroundDestinationArea, backgroundOriginOffset, 0.0f, BLUE);
        DrawTexturePro(gPlayer1, player1TextureArea, player1DestinationArea, player1OriginOffset, 0.0f, WHITE);
        DrawTexturePro(gPlayer1Lives, player1LivesTextureArea, player1LivesDestinationArea, player1LivesOriginOffset, 0.0f, RED);
        DrawTexturePro(gPlayer2, player2TextureArea, player2DestinationArea, player2OriginOffset, 0.0f, WHITE);
        DrawTexturePro(gPlayer2Lives, player2LivesTextureArea, player2LivesDestinationArea, player2LivesOriginOffset, 0.0f, RED);
        DrawTexturePro(gBall, ballTextureArea, ballDestinationArea, ballOriginOffset, 0.0f, WHITE);
        if (gExtraBall1Active) {
            DrawTexturePro(gExtraBall1, extraBall1TextureArea, extraBall1DestinationArea, extraBall1OriginOffset, 0.0f, WHITE);
        }
        if (gExtraBall2Active) {
            DrawTexturePro(gExtraBall2, extraBall2TextureArea, extraBall2DestinationArea, extraBall2OriginOffset, 0.0f, WHITE);
        }
        if (gExtraBall3Active) {
            DrawTexturePro(gExtraBall3, extraBall3TextureArea, extraBall3DestinationArea, extraBall3OriginOffset, 0.0f, WHITE);
        }
        if (gGameDifficulty == CRAZY && gDemonActive)
            DrawTexturePro(gDemon, demonTextureArea, demonDestinationArea, demonOriginOffset, 0.0f, WHITE);
    } else if (gGameStatus == PAUSED) {
        DrawTexturePro(gWelcomeScreen, welcomeScreenTextureArea, welcomeScreenDestinationArea, welcomeScreenOriginOffset, 0.0f, WHITE);
    } else if (gGameStatus == GAME_OVER) {
        if (gGameWinner == BOT) DrawTexturePro(gGOA, welcomeScreenTextureArea, welcomeScreenDestinationArea, welcomeScreenOriginOffset, 0.0f, WHITE);
        if (gGameWinner == HUMAN) DrawTexturePro(gGOH, welcomeScreenTextureArea, welcomeScreenDestinationArea, welcomeScreenOriginOffset, 0.0f, WHITE);
        if (gGameWinner == PLAYER_1) DrawTexturePro(gGO1, welcomeScreenTextureArea, welcomeScreenDestinationArea, welcomeScreenOriginOffset, 0.0f, WHITE);
        if (gGameWinner == PLAYER_2) DrawTexturePro(gGO2, welcomeScreenTextureArea, welcomeScreenDestinationArea, welcomeScreenOriginOffset, 0.0f, WHITE);
    } else if (gGameStatus == RULES) {
        DrawTexturePro(gRulesScreen, welcomeScreenTextureArea, welcomeScreenDestinationArea, welcomeScreenOriginOffset, 0.0f, WHITE);
    } 



    EndDrawing();
}

void shutdown() {
    CloseWindow();
    UnloadTexture(gBackground);
    UnloadTexture(gPlayer1);
    UnloadTexture(gPlayer1Lives);
    UnloadTexture(gPlayer2);
    UnloadTexture(gPlayer2Lives);
    UnloadTexture(gBall);
    UnloadTexture(gExtraBall1);
    UnloadTexture(gExtraBall2);
    UnloadTexture(gExtraBall3);
    UnloadTexture(gWelcomeScreen);
    UnloadTexture(gGOA);
    UnloadTexture(gGOH);
    UnloadTexture(gGO1);
    UnloadTexture(gGO2);
    UnloadTexture(gRulesScreen);
    UnloadTexture(gDemon);
}

int main(void) {
    initialise();

    while (gAppStatus == RUNNING) {
        processInput();
        update();
        render();
    }

    shutdown();

    return 0;
}
