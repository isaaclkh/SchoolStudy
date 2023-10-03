#include <stdio.h>

typedef struct{
    int scores[3];
    int sum;
    double avg;
    char grade;
}Student;

void getStudentScores(Student *s);
char grading(double avg);

int main()
{
    Student students[5];
    getStudentScores(students);
}

void getStudentScores(Student *s){
    
    printf("결과예시)\n");

    for (int i = 0; i < 5; i++)
    {
        printf("%d번 : ", i + 1);
        scanf("%d %d %d", &s[i].scores[0], &s[i].scores[1], &s[i].scores[2]);

        s[i].sum = s[i].scores[0] + s[i].scores[1] + s[i].scores[2];
        s[i].avg = s[i].sum / 3.0;
        s[i].grade = grading(s[i].avg);
    }

    for(int i=0; i<5; i++) printf("%d번 총점은 %d, 평균은 %.1f (등급 %c)\n", i+1, s[i].sum, s[i].avg, s[i].grade);
}

char grading(double avg){
    if(90<=avg) return 'A';
    else if(80<=avg) return 'B';
    else if(70<=avg) return 'C';
    else if(60<=avg) return 'D';
    else return 'F';
}