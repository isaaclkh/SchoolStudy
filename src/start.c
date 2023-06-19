#include "../reversi.h"

void checkSize(int row, int col){
    char widerWindow[] = "You need wider window";
    char heigherWindow[] = "You need heigher window";

    if(row < 28) mvprintw(row / 2, (col - strlen(heigherWindow)) / 2, "%s", heigherWindow);
    else if(col < 69) mvprintw(row / 2, (col - strlen(widerWindow)) / 2, "%s", widerWindow);
    else reversiSetting(5, 5, 21, 45, row, col);
}

void initial(){
    memset(board, 2, sizeof(board));
    // board[col][row]
    board[3][3] = 1; // client
    board[4][3] = 0; // server
    board[3][4] = 0;
    board[4][4] = 1;
    scores[0] = 2;
    scores[1] = 2;

    mark_playable_positions();
}