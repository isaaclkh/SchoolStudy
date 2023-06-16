#include "../reversi.h"

void reversiSetting(int y1, int x1, int y2, int x2, int row, int col)
{
    int w = x2 - x1;
    int h = y2 - y1;

    mvprintw(y1 / 2-1, x1 / 2+3, "**** WELCOME TO REVERSI ****");
    mvprintw(y1 / 2, x1 / 2+3, "opponent has been matched");
    mvprintw(y1 / 2+1, x1 / 2+3, "You : black stone");
    mvprintw(y1 / 2+2, x1 / 2+3, "Opponent : white stone");

    mvhline(y1, x1, ACS_HLINE, w); // first horizontal line
    mvhline(y2, x1, ACS_HLINE, w); // second horizontal line

    mvvline(y1, x1, ACS_VLINE, h); // first vertical line
    mvvline(y1, x2, ACS_VLINE, h); // second vertical line

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