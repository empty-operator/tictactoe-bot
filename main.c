#include <stdio.h>
#include <stdlib.h>
#include "windows.h"
#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)
#define PAUSE 5000
#define EMPTY ' '
#define USER 'X'
#define BOT 'O'

int minimax(int board[][3], int isUserTurn);
void initBoard(int board[][3]);
void printBoard(int board[][3]);
int checkBoard(int board[][3]);
void userMove(int board[][3]);
void botMove(int board[][3]);
int endGame(int board[][3]);
int isFull(int board[][3]);

int main() {
    SMALL_RECT windowSize = {0 , 0 , 30 , 10};
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);
    system("chcp 65001");
    int board[3][3];
    initBoard(board);
    printBoard(board);
    while (1) {
        userMove(board);
        printBoard(board);
        if (endGame(board)) {
            Sleep(PAUSE);
            exit(0);
        }
        botMove(board);
        printBoard(board);
        if (endGame(board)) {
            Sleep(PAUSE);
            exit(0);
        }
    }
}

void initBoard(int board[][3]) {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            board[j][i] = EMPTY;
}

void printBoard(int board[][3]) {
    system("cls");
    printf_s("\n ╔═══╦═══╦═══╗\n");
    for (int i = 0; i < 3; ++i) {
        printf_s(" ║");
        for (int j = 0; j < 3; ++j)
            printf_s(" %c ║", board[j][i]);
        if (i != 2)
            printf_s("\n ╠═══╬═══╬═══╣\n");
    }
    printf_s("\n ╚═══╩═══╩═══╝\n");
}

void userMove(int board[][3]) {
    int x, y;
    do {
        printf_s("\nEnter coordinates: ");
        scanf_s("%d%d", &x, &y);
    } while (board[y - 1][x - 1] != EMPTY);
    board[y - 1][x - 1] = USER;
}

void botMove(int board[][3]) {
    int x, y, score, bestScore = -10;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j) {
            if (board[j][i] == EMPTY) {
                board[j][i] = BOT;
                score = minimax(board, 1);
                board[j][i] = EMPTY;
                if (score > bestScore) {
                    bestScore = score;
                    x = i; y = j;
                }
            }
        }
    board[y][x] = BOT;
}

int minimax(int board[][3], int isUserTurn) {
    switch (checkBoard(board)) {
        case BOT:
            return 1;
        case 1:
            return 0;
        case USER:
            return -1;
    }
    int score;
    if (isUserTurn) {
        score = 10;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j) {
                if (board[j][i] == EMPTY) {
                    board[j][i] = USER;
                    score = MIN(score, minimax(board, 0));
                    board[j][i] = EMPTY;
                }
            }
    } else {
        score = -10;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j) {
                if (board[j][i] == EMPTY) {
                    board[j][i] = BOT;
                    score = MAX(score, minimax(board, 1));
                    board[j][i] = EMPTY;
                }
            }
    }
    return score;
}

int endGame(int board[][3]) {
    switch (checkBoard(board)) {
        case USER:
            printf_s("\nYou won!");
            return 1;
        case 1:
            printf_s("\nDraw.");
            return 1;
        case BOT:
            printf_s("\nGame over!");
            return 1;
        default:
            return 0;
    }
}

int isFull(int board[][3]) {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[j][i] == EMPTY)
                return 0;
    return 1;
}

int checkBoard(int board[][3]) {
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return board[i][0];
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) return board[0][i];
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) return board[0][2];
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) return board[0][0];
    return isFull(board);
}
