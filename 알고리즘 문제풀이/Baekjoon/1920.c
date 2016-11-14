/*
 *	ProjectName	: Baekjoon Algorithm Problem 1920 - 수 찾기
 *	Corder 		: YoWu (uyu423@gamil.com / http://luckyyowu.tistory.com)
 *	Organiz.	: Catholic Univ. of Korea
 *	Major		: Computer Science (Minor : Infomation System Eng)
 *	DateTime	: 2015.4.30 15:38
 *	Develop OS	: CentOS Linux 6.6 x86 (kernel 2.6.32-504)
 *	PorgramLang	: C (Library Model : POSIX)
 *	TextEditor	: VIM - Vi IMproved 7.2
 *	Encording	: UTF-8 (Linux Basic)
 *	Compiler	: GCC 4.4.7
 */
 
/*
* ** Try Status **
* try 01 : incorrect value (?)
* try 02 : incorrect value (because compare funtion overflow)
* try 03 : success (fixed compare function ref. https://www.acmicpc.net/wiki/c/qsort)
*/
 
#include <stdio.h>
#include <stdlib.h>

typedef enum { false, true } bool;
int n, m;
int arrN[100000];

/* qsort compare function (caution : integer overflow) */
int compare(const void *arg1, const void *arg2) {
	  return *(int *)arg1 > *(int *) arg2 ? 1 : *(int *)arg1 < *(int *)arg2 ? -1 : 0;
}

/* binary search function. recursion */
bool Bsearch(int goal, int st, int ed) {
	int now = (st + ed) / 2;
	if(st > ed)	return false;
	if(arrN[now] > goal) 		return Bsearch(goal, st, now - 1);
	else if(arrN[now] < goal)	return Bsearch(goal, now + 1, ed);
	else return true;
}

int main(void) {
	int i, num;
	scanf("%d", &n);
	for(i=0; i<n; i++) {
		scanf("%d", &arrN[i]);
	}
	qsort(arrN, n, sizeof(int), compare);
	scanf("%d", &m);
	for(i=0; i<m; i++) {
		scanf("%d", &num);
		printf("%d\n", (int)Bsearch(num, 0, n - 1));
	}
}
