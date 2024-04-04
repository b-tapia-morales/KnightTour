#include <stdbool.h>
#include <stdio.h>

#ifndef KNIGHT_H
#define KNIGHT_H

#endif //KNIGHT_H

#define N 6
#define M N
#define MOVES 8

const int xMoves[MOVES] = {-2, -1, +1, +2, +2, +1, -1, -2};
const int yMoves[MOVES] = {+1, +2, +2, +1, -1, -2, -2, -1};

bool coordinatesAreValid(int, int);

bool spaceIsUnmarked(int [N][M], int, int);

void markSpace(int [N][M], int, int, int);

void unmarkSpace(int [N][M], int, int);

bool isFinished(int);

bool isUnsolvable(int, int);

void moveForward(int *x, int *y, int *index, int *counter, int nextX, int nextY);

void previousSpace(int [N][M], int *, int *, int *, int *);

bool solve(int[N][M], int x, int y);

void drawLine();

void show(int [N][M]);

bool coordinatesAreValid(int x, int y) {
    return (x >= 0 && x < N) && (y >= 0 && y < M);
}

bool spaceIsUnmarked(int board[N][M], int x, int y) {
    return board[x][y] == 0;
}

void markSpace(int board[N][M], int x, int y, int counter) {
    board[x][y] = counter;
}

void unmarkSpace(int board[N][M], int x, int y) {
    board[x][y] = 0;
}

bool isFinished(int counter) {
    return counter == N * M;
}

bool isUnsolvable(int index, int counter) {
    return counter == 1 && index >= (MOVES - 1);
}

void moveForward(int *x, int *y, int *index, int *counter, int nextX, int nextY) {
    *x = nextX;
    *y = nextY;
    *index = 0;
    *counter += 1;
}

void previousSpace(int board[N][M], int *x, int *y, int *index, int *counter) {
    *counter -= 2;
    for (int i = 0; i < MOVES; i++) {
        int prevX = *x + xMoves[i];
        int prevY = *y + yMoves[i];
        if (board[prevX][prevY] == *counter) {
            const int n = MOVES / 2;
            *x = prevX;
            *y = prevY;
            *index = (i + n) % MOVES + 1;
            *counter += 1;
            return;
        }
    }
}

void drawLine() {
    for (int i = 0; i < M; i++) {
        printf("+----");
    }
    printf("+\n");
}

void show(int board[N][M]) {
    fflush(stdout);
    drawLine();
    for (int i = 0; i < N; i++) {
        fflush(stdout);
        for (int j = 0; j < M; j++) {
            printf("| %2d ", board[i][j]);
        }
        printf("|\n");
        drawLine();
    }
    printf("\n");
}


bool solve(int board[N][M], int x, int y) {
    markSpace(board, x, y, 1);
    int index = 0;
    int counter = 2;
    while (true) {
        int nextX = x + xMoves[index];
        int nextY = y + yMoves[index];
        if (coordinatesAreValid(nextX, nextY) && spaceIsUnmarked(board, nextX, nextY)) {
            markSpace(board, nextX, nextY, counter);
            if (isFinished(counter)) {
                return true;
            }
            moveForward(&x, &y, &index, &counter, nextX, nextY);
        } else {
            index += 1;
            if (isUnsolvable(index, counter)) {
                return false;
            }
            if (index >= MOVES) {
                unmarkSpace(board, x, y);
                previousSpace(board, &x, &y, &index, &counter);
            }
        }
    }
}