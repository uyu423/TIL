/*
 *	Corder : Yu Yongwoo (uyu423@gmail.com / CUK CSIE '10)
 *	Ubuntu 15.10 (x64 / Linux Kernel 4.2.0)
 *	GNU Compiler Colletion 5.2.1 Compile Options -O2 -DNDEBUG
 *	Vi IMproved 7.4, File Character Encoding UTF-8
 */ 

#include <stdio.h>
#define VALMAX	20001
#define INTMAX	2100000000
#define BALLNUM	3
typedef enum { MAX, MIN } compare;

int tow[4][VALMAX];

void initTowByBall1(int n) { while(n--) tow[1][n+1] = n+1; }
int compareValue(compare mode, int a, int b);
void calcTowByBallN(int n, int f);

int main(void) {
	int i, n;
	tow[2][1] = tow[3][1] = 1;	//init static value
	tow[2][2] = tow[3][2] = 2;
	scanf("%d", &n);
	initTowByBall1(n);
	for(i=2; i<=BALLNUM; i++) calcTowByBallN(n, i); 
	printf("%d\n", tow[BALLNUM][n]);

	return 0;
}

int compareValue(compare mode, int a, int b) { 
	switch(mode) { 
		case MAX : return a > b ? a : b; 
		case MIN : return b > a ? a : b; 
	} 
}	

void calcTowByBallN(int n, int f) {
	int i, j, max, min;
	for(i=3; i<=n; i++) {
		min = INTMAX;
		for(j=1; j<=i; j++) {
			max = compareValue(MAX, tow[f][i-j], tow[f-1][j-1]) + 1;
			min = compareValue(MIN, max, min);
		}
		tow[f][i] = min;
	}
}
