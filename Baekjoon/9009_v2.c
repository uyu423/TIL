/*
 * ProjectName : Baekjoon Algorithm Problem 9009 version 2 (feat. vyujing)
 * Corder : YoWu (uyu423@gamil.com / http://luckyyowu.tistory.com)
 * Organiz. : Catholic Univ. of Korea
 * Major : Computer Science
 * Minor : Infomation System Engineering
 * DateTime	: 2015.4.20 02:17
 * Develop OS : CentOS Linux 6.6 x86 (kernel 2.6.32-504)
 * PorgramLang : C (Library Model : POSIX)
 * TextEditor : VIM - Vi IMproved 7.2
 * Encording : UTF-8 (Linux Basic)
 * Compiler	: GCC 4.4.7
 */

/*
 * ** Try Status **
 * Try 01 : Success
 */

#include <stdio.h>

int fiboTable[50] = {0 ,1};
int fiboLen = 2;

/* make fiboTable, first fiboLen = 2 */
/* if not exist fibo value, make new fibo value */
int makeFiboTable(int max) {
	int i;
	for(i = fiboLen; fiboTable[i-1] <= max; i++) {
		fiboTable[i] = fiboTable[i-1] + fiboTable[i-2];
	}
	return i;
}

/* findValue recursion version (feat. vyujing) */
/* sibal gi ga mak hee ne zz */
void findValue(int num) {
	int i;
	if(num == 0) {
		return;
	}
	for(i=1; i<=fiboLen; i++) {
		if(fiboTable[i] > num) {
			findValue(num - fiboTable[i-1]);
			printf("%d ", fiboTable[i-1]);
			break;
		}
	}
}

int main(void) {
	int num;
	int i, t;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &num);
		if(fiboTable[fiboLen] <= num) {
			fiboLen = makeFiboTable(num);
		}
		findValue(num);
		putchar('\n');
	}
}
