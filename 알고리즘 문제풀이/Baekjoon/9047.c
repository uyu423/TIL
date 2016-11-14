/*
* ProjectName : Baekjoon Algorithm Problem 9047 - 6174
* Corder : YoWu (uyu423@gamil.com / http://luckyyowu.tistory.com)
* Organiz. : Catholic Univ. of Korea
* Major : Computer Science
* Minor : Infomation System Engineering
* DateTime	: 2015.4.28 00:01
* Develop OS : CentOS Linux 6.6 x86 (kernel 2.6.32-504)
* PorgramLang : C (Library Model : POSIX)
* TextEditor : VIM - Vi IMproved 7.2
* Encording : UTF-8 (Linux Basic)
* Compiler	: GCC 4.4.7
*/

/*
* ** Try Status **
* try 01 : runtime error (num < 1000 exception)
* try 02 : incorrect value (cnt == 1 error (input 1476))
* try 03 : incorrect value (because print debug function;;)
* try 04 : success
*/

#include <stdio.h>
#include <stdlib.h> /* qsort() */

/* quick sort function */
int smallOrder(const void *a, const void *b) {
	return (*(char *)a - *(char *)b);
}
int bigOrder(const void *a, const void *b) {
	return (*(char *)b - *(char *)a);
}

/* recursion function */
int func(int num, int cnt) {
	char bigNum[5], smallNum[5];
	sprintf(bigNum, "%d", num);
	sprintf(smallNum, "%d", num);
	qsort(bigNum, 4, sizeof(char), bigOrder);
	qsort(smallNum, 4, sizeof(char), smallOrder);
	num = atoi(bigNum) - atoi(smallNum);
	if (num == 6174) {
		return cnt;
	}
	else {
		if (num < 1000) num *= 10;	//999 -> 9990
		return func(num, cnt + 1);
	}
}

/* main function */
int main(void) {
	int t, num, cnt;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &num);
		printf("%d\n", (num == 6174 ? 0 : func(num, 1)));
	}
}
