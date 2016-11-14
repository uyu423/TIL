/*
 * Baekjoon ACM-ICPC problem 2857
 * https://www.acmicpc.net/problem/2857
 * Corder : Yowu (uyu423@gmail.com || http://luckyyowu.tistory.com)
 * Dev Env : Ubuntu 15.10, gcc no-compile-ops, vim, utf-8
 *
 * try 1 : success
 *
 */
#include <stdio.h>
#include <string.h>
#define MAX 5
typedef enum { false, true } bool;

int main(void) {
	int i, j, len, cnt=0;;
	char str[MAX][11];
	for(i=0; i<MAX; i++) {
		scanf("%s", str[i]);
		len = strlen(str[i]);
		for(j=0; j<len-2; j++) {
			if(str[i][j] == 'F' && str[i][j+1] == 'B' && str[i][j+2] == 'I') {
				printf("%d ", i+1);
				cnt++; break;
			}
		}
	}
	if(!cnt) {
		printf("HE GOT AWAY!\n");
	}
	return 0;
}
