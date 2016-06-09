/*
 *  Baekjoon ACM-ICPC problem 5502 펠린드롬
 *  https://www.acmicpc.net/problem/5502
 *  Corder : Yowu (uyu423@gmail.com || http://luckyyowu.tistory.com)
 *  Dev Env : Ubuntu 16.04, gcc no-compile-ops, vim, utf-8
 *  
 *  try 01 : success?
 */
#include <stdio.h>
#include <string.h>
#define MAX 5001

int matrix[MAX][MAX];
char str[MAX], rev[MAX];

char myStrrev(char *origin, char *target) { //linux system haven't strrev function
	int i, j;
	target[strlen(origin)] = '\0';
	for(i=0, j=strlen(origin) - 1; j>=0; i++, j--) {
		target[j] = origin[i];	
	}
}

void checkMatrix(int col, int row) {
	int mCol = col + 1, mRow = row + 1;
	if(rev[col] == str[row]) {
		matrix[mRow][mCol] = (matrix[mRow - 1][mCol] > matrix[mRow][mCol - 1]) ? matrix[mRow - 1][mCol] + 1 : matrix[mRow][mCol - 1] + 1;
	}
	else {
		matrix[mRow][mCol] = (matrix[mRow - 1][mCol] > matrix[mRow][mCol - 1]) ? matrix[mRow - 1][mCol] : matrix[mRow][mCol - 1];
	}
}

void printForDebug(int t) {
	int i, j;
	for(i=0; i<=t; i++) {
		for(j=0; j<=t; j++) {
			printf("%3d", matrix[i][j]);
		}
		putchar('\n');
	}
}

int main(void) {
	int t, i, j;
	scanf("%d", &t);
	fflush(stdin);
	scanf("%s", str);
	myStrrev(str, rev);
//	printf("%s | %s\n", str, rev);
	for(i=0; i<t; i++) {
		for(j=0; j<t; j++) {
			checkMatrix(i, j);
		}
	}
//	printForDebug(t);
	printf("%d\n" ,t - matrix[t+1][t+1]);

	return 0;
}
