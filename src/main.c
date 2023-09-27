#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "console.h"

static int mapSize[2] = {80, 25};
static int playerPosition[2] = {0, 0};
static int fruitPosition[2] = {0, 0};
static int playerScore = 0;
static int gameOver = 0;

/**
 * @brief Set the direction (left, right, up, down) that the snake will move
 * 0 = >
 * 1 = <
 * 2 = ^
 * 3 = v
 */
static int movingDirection = 0;

void UpdateMovementAndDirection() {
    if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
        movingDirection = 1;
    } else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
        movingDirection = 0;
    } else if (GetAsyncKeyState(VK_UP) & 0x8000) {
        movingDirection = 2;
    } else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
        movingDirection = 3;
    }

    if (movingDirection == 0) {
        playerPosition[0] += 1;
    } else if (movingDirection == 1) {
        playerPosition[0] -= 1;
    } else if (movingDirection == 2) {
        playerPosition[1] -= 1;
    } else if (movingDirection == 3) {
        playerPosition[1] += 1;
    }
}

void DrawMap() {
    ConsoleDrawWCharAt(L"┌", 0, 1);
    ConsoleDrawWCharAt(L"┐", mapSize[0], 1);

    for (int x=1; x < mapSize[0]; x++) {
        ConsoleDrawWCharAt(L"─", x, 1);
    }

    for (int y=2; y < mapSize[1]; y++) {
        if (y == 3) {
            ConsoleDrawWCharAt(L"├", 0, y);
            ConsoleDrawWCharAt(L"┤", mapSize[0], y);
            continue;
        }
        ConsoleDrawWCharAt(L"│", 0, y);
        ConsoleDrawWCharAt(L"│", mapSize[0], y);
    }

    for (int x=1; x < mapSize[0]; x++) {
        ConsoleDrawWCharAt(L"─", x, 3);
    }

    for (int x=1; x < mapSize[0]; x++) {
        ConsoleDrawWCharAt(L"─", x, mapSize[1]);
    }

    ConsoleDrawWCharAt(L"└", 0, mapSize[1]);
    ConsoleDrawWCharAt(L"┘", mapSize[0], mapSize[1]);

    // draw head
    ConsoleDrawWCharAt(L"□", 1 + playerPosition[0], 4 + playerPosition[1]);
    ConsoleDrawWCharAt(L"●", 1 + fruitPosition[0], 4 + fruitPosition[1]);
}

int CheckGameOver() {
    if (playerPosition[0] < 0 || playerPosition[0] >= mapSize[0] - 1) {
        return 1;
    }

    if (playerPosition[1] < 0 || playerPosition[1] >= mapSize[1] - 4) {
        return 1;
    }

    return 0;
}

void UpdateScoreBoard() {
    wchar_t numStr[20];
    swprintf(numStr, sizeof(numStr) / sizeof(numStr[0]), L"%d", playerScore);

    wchar_t resultStr[70];

    if (gameOver == 0) {
        wcscpy(resultStr, L"Snake Game | Score: ");
    } else {
        wcscpy(resultStr, L"Snake Game | Game Over | Score: ");
    }
    
    wcscat(resultStr, numStr);

    ConsoleDrawTextAt(resultStr, 2, 2);
}


void ResetFruitPosition() {
    ConsoleClearAt(1 + fruitPosition[0], 4 + fruitPosition[1]);

    srand((unsigned)time(NULL));

    fruitPosition[0] = (rand() % mapSize[0] - 1);
    fruitPosition[1] = (rand() % mapSize[1] - 4);
}

void UpdateIfPlayerCollidedWithFruit() {
    if (playerPosition[0] == fruitPosition[0] && playerPosition[1] == fruitPosition[1]) {
        playerScore++;

        ResetFruitPosition();
        UpdateScoreBoard();
    }
}

int main()
{
    ConsoleClear();
    ResetFruitPosition();
    UpdateScoreBoard();

    while(1) {
        ConsoleClearAt(1 + playerPosition[0], 4 + playerPosition[1]);

        UpdateIfPlayerCollidedWithFruit();
        UpdateMovementAndDirection();

        if (CheckGameOver() == 1) {
            gameOver = 1;
            UpdateScoreBoard();
            break;
        }

        DrawMap();
        
        Sleep(50);
    }

    return 0;
}
