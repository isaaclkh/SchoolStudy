#include <stdio.h>

char grading(double avg);
void printing(int *sumPrint, double *avgPrint, char *letter);

int main()
{
    int scores[5][3] = {0}, sum[5]={0};
    char grade[5] = {0};
    double avg[5] = {0};

    printf("결과예시)\n");

    for(int i=0; i<5; i++){
        printf("%d번 : ", i+1);
        scanf("%d %d %d", &scores[i][0], &scores[i][1], &scores[i][2]);
        
        sum[i] = scores[i][0] + scores[i][1] + scores[i][2];
        avg[i] = sum[i] / 3.0;
        grade[i] = grading(avg[i]);
    }

    printing(sum, avg, grade);
}

char grading(double avg){
    if(90<=avg) return 'A';
    else if(80<=avg) return 'B';
    else if(70<=avg) return 'C';
    else if(60<=avg) return 'D';
    else return 'F';
}

void printing(int *sumPrint, double *avgPrint, char *letter){
    for(int i=0; i<5; i++){
        printf("%d번 총점은 %d, 평균은 %.1f (등급 %c)\n", i+1, sumPrint[i], avgPrint[i], letter[i]);
    }
}