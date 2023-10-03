#include <stdio.h>
#include <stdlib.h>

void pp(int *x, int *y){

    printf("*x : %d *y : %d\n", *x, *y);
    printf("x : %d y : %d\n", x, y);
    
    if(*x>5) *x+=2;
    else *x-=2;
    
    if(*y>5) *y-=2;
    else *y+=2;

}

int main(){
    int x, y;

    scanf("%d %d", &x, &y);
    pp(&x, &y);

    printf("x: %d\ny:%d\n", x ,y);
}

