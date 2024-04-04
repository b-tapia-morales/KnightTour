#include "knight.h"

int main() {
    int board[N][M] = {0};
    show(board);
    solve(board, 2, 3);
    show(board);
}