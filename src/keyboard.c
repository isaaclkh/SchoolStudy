#include "../reversi.h"

void keyBoardMoving(int *y, int *x){
    int c;

    while ((c = getch()) != '\n')
    {
        switch (c)
        {
        case KEY_UP:
            if (*y > 6)
                *y -= 2;
            if (*y == 4)
                *y = 6;
            break;

        case KEY_DOWN:
            if (*y < 22)
                *y += 2;
            if (*y == 22)
                *y = 20;
            break;

        case KEY_LEFT:
            if (*x > 7)
                *x -= 5;
            if (*x == 12)
                *x = 7;
            break;

        case KEY_RIGHT:
            if (*x < 40)
                *x += 5;
            if (*x == 45)
                *x = 40;
            break;

        default:
            break;
        }

        move(*y, *x);
        refresh();
    }
}