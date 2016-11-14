/*
 *  ProjectName : Baekjoon Algorithm Problem 8979 (올림픽)
 *  Corder      : YoWu (uyu423@gamil.com / http://luckyyowu.tistory.com)
 *  Organiz.    : Catholic Univ. of Korea
 *  Major       : Computer Science (Minor : Infomation System Eng)
 *  DateTime    : 2015.4.23 (YoWu's 24th BirthDay) 05:05
 *  Develop OS  : CentOS Linux 6.6 x86 (kernel 2.6.32-504)
 *  PorgramLang : C (Library Model : POSIX)
 *  TextEditor  : VIM - Vi IMproved 7.2
 *  Encording   : UTF-8 (Linux Basic)
 *  Compiler    : GCC 4.4.7
 */

#include <stdio.h>

/* Country Information Saving Sturct Definition */
typedef struct {
    int gold;
    int silver;
    int bronze;
} country;

/* calc country[sel]'s rank and return rank number */
int calcRank(int sel, country *cou, int max) {
    int i, rank = 1;
    for(i=1; i<=max; i++) {
        if(cou[sel].gold < cou[i].gold) rank++;
        else if(cou[sel].gold == cou[i].gold && cou[sel].silver < cou[i].silver)    rank++;
        else if(cou[sel].gold == cou[i].gold && cou[sel].silver == cou[i].silver && cou[sel].bronze < cou[i].bronze)    rank++;
        else continue;
    }   
    return rank;
}

int main(void) {
    country cou[1001];
    int tmp, maxCon, selCon, i;
    scanf("%d %d", &maxCon, &selCon);
    for(i=0; i<maxCon; i++) {
        scanf("%d", &tmp);
        scanf("%d %d %d", &cou[tmp].gold, &cou[tmp].silver, &cou[tmp].bronze);
    }   
    printf("%d\n", calcRank(selCon, cou, maxCon));
    return 0;
}
