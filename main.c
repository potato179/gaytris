#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "define.h"
#include <time.h>

#pragma comment(lib, "winmm.lib")

int curX = MAP_W / 2 - 1;
int curY = 0;

int blocks[7][4][4][4] = {
    {
        {0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0}
    },
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0}
    },
    {
        {0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0}
    },
    {
        {0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0}
    },
    {
        {0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0}
    },
    {
        {0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0}
    },
    {
        {0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0}
    }
};

void gotoxy(int x, int y) {
    COORD pos = {
        x, y
    };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void ReSizeConsole(int w, int h) {
    char chTemp[30];
    sprintf(chTemp, "mode con cols=%d lines=%d", w, h);
    system(chTemp);
}

void ClearCursor() {
    CONSOLE_CURSOR_INFO c = {
        0
    };
    c.dwSize = 1;
    c.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), & c);
}

void DisplayStart() {
    while (1) {
        if (_kbhit()) {
            _getch();
            break;
        }
        gotoxy(MAX_X / 2 - 2, MAX_Y / 2);
        printf("Tetris");
        Sleep(500);
        gotoxy(MAX_X / 2 - 2, MAX_Y / 2);
        printf("                   ");
        Sleep(500);
    }
}

void DisplayGameScreen() {
    for (int y = 0; y < MAX_Y; y++) {
        for (int x = 0; x < MAX_X; x += 2) {
            if (x == 0 || y == 0 || x == MAX_X - 2 || y == MAX_Y - 1) {
                gotoxy(x, y);
                printf("★");
            } else {
                gotoxy(x, y);
                printf("  ");
            }

        }
    }
}

void initMap(int( * m)[MAP_W]) {
    for (int y = 0; y < MAP_H; y++) {
        for (int x = 0; x < MAP_W; x++) {
            if (x == 0 || x == MAP_W - 1 || y == MAP_H - 1)
                m[y][x] = WALL;
            else
                m[y][x] = BLANK;
        }
    }
}

void DisplayMap(int( * m)[MAP_W]) {
    for (int y = 0; y < MAP_H; y++) {
        for (int x = 0; x < MAP_W; x++) {
            gotoxy(MARGIN_X + x * 2, y + MARGIN_Y);
            switch (m[y][x]) {
            case BLANK:
                printf(" .");
                break;
            case WALL:
                printf("▩");
                break;
            case ACTIVE_BLOCK:
                printf("■");
                break;
            case INACTIVE_BLOCK:
                printf("□");
                break;
            }
        }
    }
}

void DisplayScore(int sc) {
    gotoxy(MAX_X / 2 + MARGIN_X, MARGIN_Y);
    printf("Score : %2d", sc);
}

void DisplayNextArea() {
    gotoxy(MAX_X / 2 + MARGIN_X, 7);
    printf("┌   Next  ┐"); //문자 공백 3번 Next 공백 2번 문자
    gotoxy(MAX_X / 2 + MARGIN_X, 8);
    printf("│         │"); //막대기 공백 9번 막대기
    gotoxy(MAX_X / 2 + MARGIN_X, 9);
    printf("│         │"); //막대기 공백 9번 막대기
    gotoxy(MAX_X / 2 + MARGIN_X, 10);
    printf("│         │"); //막대기 공백 9번 막대기
    gotoxy(MAX_X / 2 + MARGIN_X, 11);
    printf("│         │"); //막대기 공백 9번 막대기
    gotoxy(MAX_X / 2 + MARGIN_X, 12);
    printf("└─────────┘"); //문자 - 9번 문자
}

void DisplayCurrentBlock(int( * map)[MAP_W], int shape) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (blocks[shape][0][i][j])
                map[curY + i][curX + j] = ACTIVE_BLOCK;
        }
    }
    DisplayMap(map);
}
void DisplayNextBlock(int shape) {
    int x = MAX_X / 2 + MARGIN_X + 2;
    int y = 8;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (blocks[shape][0][i][j]) {
                gotoxy(x + 2 * j, y + i);
                printf("■");
            }
        }
    }
}
void DeleteBlock(int( * map)[MAP_W], int s, int r) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (blocks[s][r][i][j])
                map[curY + i][curX + j] = BLANK;
        }
    }
}
void MoveBlock(int( * map)[MAP_W], int s, int r, int dir) {
    DeleteBlock(map, s, r);
    switch (dir) {
    case LEFT:
        curX--;
        break;
    case RIGHT:
        curX++;
        break;
    case DOWN:
        curY++;
        break;
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (blocks[s][r][i][j])
                map[curY + i][curX + j] = ACTIVE_BLOCK;
        }
    }
    DisplayMap(map);
}
int main() {

    int map[MAP_H][MAP_W] = {
        BLANK
    };
    int score = 0;
    int curShape, nextShape;
    int rotation = 0;

    srand(time(NULL));

    curShape = rand() % 7;
    nextShape = rand() % 7;

    ClearCursor();
    ReSizeConsole(MAX_X, MAX_Y);
    PlaySound(("Tetris_start.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    DisplayGameScreen();
    DisplayStart();
    system("cls");
    PlaySound(NULL, NULL, NULL);

    PlaySound(("Tetris_game.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    initMap(map);
    DisplayMap(map);
    DisplayScore(score);
    DisplayNextArea();

    DisplayCurrentBlock(map, curShape);
    DisplayNextBlock(nextShape);

    while (1) {
        MoveBlock(map, curShape, rotation, DOWN);
        Sleep(10);
    }

    getchar();
}
