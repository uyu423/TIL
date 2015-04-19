/*
 * ProjectName : Baekjoon Algorithm Problem 1026
 * Corder : YoWu (uyu423@gamil.com / http://luckyyowu.tistory.com)
 * Organiz. : Catholic Univ. of Korea
 * Major : Computer Science
 * Minor : Infomation System Engineering
 * DateTime	: 2015.4.20 06:55
 * Develop OS : CentOS Linux 6.6 x86 (kernel 2.6.32-504)
 * PorgramLang : C (Library Model : POSIX)
 * TextEditor : VIM - Vi IMproved 7.2
 * Encording : UTF-8 (Linux Basic)
 * Compiler	: GCC 4.4.7
 */

#include <stdio.h>
#include <stdlib.h>

int A[50], B[50];

/* quick sort function : 1 2 3 4 5 */
int compare(const void *a, const void *b) {
	return ( *(int *)a - *(int *)b);
}

/* quick sort function : 5 4 3 2 1 */
int compare2(const void *a, const void *b) {
	return ( *(int *)b - *(int *)a);
}

/* A[0] * B[0] + ... + A[n-1] * B[n-1] */
int calc(int max) {
	int i, sum = 0;
	for(i=0; i<max; i++) {
		sum += A[i] * B[i];
	}
	printf("%d\n", sum);
	return;
}

int main(void) {
	int max;
	int i;
	scanf("%d", &max);
	for(i=0; i<max; i++) {
		scanf("%d", &A[i]);
	}
	for(i=0; i<max; i++) {
		scanf("%d", &B[i]);
	}
	qsort(A, max, sizeof(int), compare);
	qsort(B, max, sizeof(int), compare2);
	calc(max);
	return 0;
}
