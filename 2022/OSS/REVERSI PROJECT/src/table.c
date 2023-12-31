#include "../reversi.h"

void reversiSetting(int y1, int x1, int y2, int x2, int row, int col)
{
    int w = x2 - x1;
    int h = y2 - y1;
    char colname[]="  A    B    C    D    E    F    G    H";
    char rowname[]={'1', '2', '3', '4', '5', '6', '7', '8'};

    mvprintw(y1 / 2-1, x1 / 2+3, "**** WELCOME TO REVERSI ****");
    mvprintw(y1 / 2, x1 / 2+3, "opponent has been matched");
    mvprintw(y1 / 2+2, x1 / 2+3,"%s", colname);

    mvhline(y1, x1, ACS_HLINE, w); // first horizontal line
    mvhline(y2, x1, ACS_HLINE, w); // second horizontal line

    mvvline(y1, x1, ACS_VLINE, h); // first vertical line
    mvvline(y1, x2, ACS_VLINE, h); // second vertical line

    for(int i=0; i<8; i++){
        mvprintw(y1 + (h / 8 * i) + 1, x1 / 2+1, "%c", rowname[i]);
    }

    for (int i = 1; i <= 8; i++)
    {
        mvhline(y1 + (h / 8 * i), x1, ACS_HLINE, w);
        mvaddch(y1 + (h / 8 * i), x1, ACS_LTEE);
        mvaddch(y1 + (h / 8 * i), x2, ACS_RTEE);
    }

    for (int i = 1; i <= 8; i++)
    {
        mvvline(y1, x1 + (w / 8 * i), ACS_VLINE, h);
        mvaddch(y1, x1 + (w / 8 * i), ACS_TTEE);
        mvaddch(y2, x1 + (w / 8 * i), ACS_BTEE);
    }

    mvaddch(y1, x1, ACS_ULCORNER);
    mvaddch(y2, x1, ACS_LLCORNER);
    mvaddch(y1, x2, ACS_URCORNER);
    mvaddch(y2, x2, ACS_LRCORNER);
}

void rect(int y1, int x1, int y2, int x2){
    int w = x2 - x1;
    int h = y2 - y1;
    
    mvhline(y1, x1, ACS_HLINE, w); // first horizontal line
    mvhline(y2, x1, ACS_HLINE, w); // second horizontal line

    mvvline(y1, x1, ACS_VLINE, h); // first vertical line
    mvvline(y1, x2, ACS_VLINE, h); // second vertical line

    mvaddch(y1, x1, ACS_ULCORNER);
    mvaddch(y2, x1, ACS_LLCORNER);
    mvaddch(y1, x2, ACS_URCORNER);
    mvaddch(y2, x2, ACS_LRCORNER);
}

void drawing(){
    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLUE);
    init_pair(2, COLOR_RED, COLOR_RED);
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(board[i][j] == 0){ // white rect : blue = server
                attron(COLOR_PAIR(1));
                rect(6 + (j*2), 7 + (i*5), 6+(j*2), 7 + (i*5));
                attroff(COLOR_PAIR(1));
            }
            if(board[i][j] == 1){ // black rect : red = client
                attron(COLOR_PAIR(2));
                rect(6 + (j*2), 7 + (i*5), 6+(j*2), 7 + (i*5));
                attroff(COLOR_PAIR(2));
            }
            if(board[i][j] == 3){
                mvprintw(6 + (j*2), 7 + (i*5), ".");
            }
        }
    }
}