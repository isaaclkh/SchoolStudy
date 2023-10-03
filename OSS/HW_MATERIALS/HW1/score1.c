#include <stdio.h>

int main(){
    int one[3], two[3], three[3], four[3], five[3], sum1, sum2, sum3, sum4, sum5;
    char a, b, c, d, e;
    double z, q, r, s, t;

    printf("결과예시)\n");
    
    printf("1번 : ");
    scanf("%d %d %d", &one[0], &one[1], &one[2]);
    printf("2번 : ");
    scanf("%d %d %d", &two[0], &two[1], &two[2]);
    printf("3번 : ");
    scanf("%d %d %d", &three[0], &three[1], &three[2]);
    printf("4번 : ");
    scanf("%d %d %d", &four[0], &four[1], &four[2]);
    printf("5번 : ");
    scanf("%d %d %d", &five[0], &five[1], &five[2]);

    sum1 = one[0] + one[1] + one[2];
    sum2 = two[0] + two[1] + two[2];
    sum3 = three[0] + three[1] + three[2];
    sum4 = four[0] + four[1] + four[2];
    sum5 = five[0] + five[1] + five[2];

    z = sum1/3.0;
    q = sum2/3.0;
    r = sum3/3.0;
    s = sum4/3.0;
    t = sum5/3.0;

    if(90<=z) a = 'A';
    if(80<=z && z<90)a = 'B';
    if(70<=z && z<80) a = 'C';
    if(60<=z && z<70) a = 'D';
    if(z<60.0) a = 'F';

    if(90<=q) b = 'A';
    if(80<=q && q<90)b = 'B';
    if(70<=q && q<80) b = 'C';
    if(60<=q && q<70) b = 'D';
    if(q<60) b = 'F';

    if(90<=r) c = 'A';
    if(80<=r && r<90)c = 'B';
    if(70<=r && r<80) c = 'C';
    if(60<=r && r<70) c = 'D';
    if(r<60) c = 'F';

    if(90<=s) d = 'A';
    if(80<=s && s<90)d = 'B';
    if(70<=s && s<80) d = 'C';
    if(60<=s && s<70) d = 'D';
    if(s<60) d = 'F';

    if(90<=t) e = 'A';
    if(80<=t && t<90)e = 'B';
    if(70<=t && t<80) e = 'C';
    if(60<=t && t<70) e = 'D';
    if(t<60) e = 'F';

    printf("1번 총점은 %d, 평균은 %.1f (등급 %c)\n", sum1, z, a);
    printf("2번 총점은 %d, 평균은 %.1f (등급 %c)\n", sum2, q, b);
    printf("3번 총점은 %d, 평균은 %.1f (등급 %c)\n", sum3, r, c);
    printf("4번 총점은 %d, 평균은 %.1f (등급 %c)\n", sum4, s, d);
    printf("5번 총점은 %d, 평균은 %.1f (등급 %c)\n", sum5, t, e);
}