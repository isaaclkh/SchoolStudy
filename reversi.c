#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <ncurses.h>
#include <string.h>

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

int main()
{
    int row, col;
    char widerWindow[] = "You need wider window";
    char heigherWindow[] = "You need heigher window";

    initscr();
    clear();

    getmaxyx(stdscr, row, col);

    if(row < 28) mvprintw(row / 2, (col - strlen(heigherWindow)) / 2, "%s", heigherWindow);

    else if(col < 69) mvprintw(row / 2, (col - strlen(widerWindow)) / 2, "%s", widerWindow);

    else reversiSetting(5, 5, 21, 45, row, col);

    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    curs_set(3);

    int y = 6, x = 7;
    move(y, x);

    refresh();

    int c;
    while ((c = getch()) != KEY_F(1))
    {
        switch (c)
        {
        case KEY_UP:
            if (y > 6)
                y -= 2;
            if (y == 4)
                y = 6;
            break;

        case KEY_DOWN:
            if (y < 22)
                y += 2;
            if (y == 22)
                y = 20;
            break;

        case KEY_LEFT:
            if (x > 7)
                x -= 5;
            if (x == 12)
                x = 7;
            break;

        case KEY_RIGHT:
            if (x < 40)
                x += 5;
            if (x == 45)
                x = 40;
            break;

        default:
            if (isalpha(c))
            {
                printw("%c", c);
            }
            break;
        }

        move(y, x);
        refresh();
    }

    endwin();
    return 0;
}
