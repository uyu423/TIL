/*
 *  Baekjoon ACM-ICPC problem 5502 펠린드롬
 *  https://www.acmicpc.net/problem/5502
 *  Corder : Yowu (uyu423@gmail.com || http://luckyyowu.tistory.com)
 *  Dev Env : Ubuntu 16.04, gcc no-compile-ops, vim, utf-8
 *  
 *  try 01 : runtime error
 *  try 02 : trying chaging matrix array using calloc -> runtime error
 *  try 03 : what the fucking runtime error
 *  try 04 : remove fflush, debugFunc. but Inavild Answers.
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
	int a = matrix[mRow - 1][mCol];
	int b = matrix[mRow][mCol - 1];
	int c = matrix[mRow - 1][mRow - 1];
	if(rev[col] == str[row]) {
		if(a > b && a > c) { matrix[mRow][mCol] = a + 1; }
		else if(b > a && b > c) { matrix[mRow][mCol] = b + 1; }
		else { matrix[mRow][mCol] = c + 1; }
	}
	else {
		if(a > b && a > c) { matrix[mRow][mCol] = a; }
		else if(b > a && b > c) { matrix[mRow][mCol] = b; }
		else { matrix[mRow][mCol] = c; }
	}
}

int main(void) {
	int t, i, j;
	scanf("%d", &t);
	scanf("%s", str);
	myStrrev(str, rev);
	for(i=0; i<t; i++) {
		for(j=0; j<t; j++) {
			checkMatrix(i, j);
		}
	}
	printf("%d\n" ,t - matrix[t][t]);

	return 0;
}
