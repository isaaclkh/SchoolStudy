#include "../reversi.h"

void checkSize(int row, int col){
    char widerWindow[] = "You need wider window";
    char heigherWindow[] = "You need heigher window";

    if(row < 28) mvprintw(row / 2, (col - strlen(heigherWindow)) / 2, "%s", heigherWindow);
    else if(col < 69) mvprintw(row / 2, (col - strlen(widerWindow)) / 2, "%s", widerWindow);
    else reversiSetting(5, 5, 21, 45, row, col);
}

void initial(){
    // board[col][row]
    board[3][3] = 2; // client
    board[4][3] = 1; // server
    board[3][4] = 1;
    board[4][4] = 2;
}