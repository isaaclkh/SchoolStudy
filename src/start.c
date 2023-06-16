#include "../reversi.h"

void startServer(int y1, int x1, int y2, int x2, int row, int col)
{
    char mesg[]="Just a string";
	int row,col;

	mvprintw(row/2,(col-strlen(mesg))/2,"%s",mesg);
	
	mvprintw(row-2,0,"This screen has %d rows and %d columns\n",row,col);
	printw("Try resizing your window(if possible) and then run this program again");
	refresh();
	getch();
	refresh();
}

void startClient(int row, int col)
{

}

void checkSize(int row, int col){
    char widerWindow[] = "You need wider window";
    char heigherWindow[] = "You need heigher window";

    if(row < 28) mvprintw(row / 2, (col - strlen(heigherWindow)) / 2, "%s", heigherWindow);
    else if(col < 69) mvprintw(row / 2, (col - strlen(widerWindow)) / 2, "%s", widerWindow);
    else reversiSetting(5, 5, 21, 45, row, col);
}