/*
*	ProjectName	: Baekjoon Algorithm Problem 1051 - 숫자 정사각형
*	Corder 		: YoWu (uyu423@gamil.com / http://luckyyowu.tistory.com)
*	Organiz.	: Catholic Univ. of Korea
*	Major		: Computer Science (Minor : Infomation System Eng)
*	DateTime	: 2015.06.02 19:33
*	Develop OS	: CentOS Linux 6.6 x86 (kernel 2.6.32-504)
*	PorgramLang	: C (Library Model : POSIX)
*	TextEditor	: VIM - Vi IMproved 7.2
*	Encording	: UTF-8 (Linux Basic)
*	Compiler	: GCC 4.4.7
*/

/*
* ** Try Status **
* try 01 : success (oh yeah)
*/

#include <stdio.h>
#include <math.h>	//sqrt()

char table[1000][1000];
int hei, wid;	//max table height, max table width;
int ans = 1;	//answer variable

void makeTable() {	//input table values
	int i, j;
	for (i = 0; i<hei; i++) {
		for (j = 0; j<wid; j++) {
			scanf("%c", &table[i][j]);
			if (table[i][j] == '\n') j--;
		}
	}
}

void search(int thisHei, int thisWid) {
	int addVal = sqrt(ans);
	while (thisHei + addVal < hei || thisWid + addVal < wid) {
		if (table[thisHei][thisWid] == table[thisHei + addVal][thisWid + addVal] &&
			table[thisHei][thisWid] == table[thisHei + addVal][thisWid] &&
			table[thisHei][thisWid] == table[thisHei][thisWid + addVal]) {
			ans = (addVal + 1) * (addVal + 1);	//addValue = 2 -> lineLength = 3;
		}
		addVal++;
	}
}

void solve() {
	int i, j;
	for (i = 0; i<hei; i++) {
		for (j = 0; j<wid; j++) {
			search(i, j);
		}
	}
}

int main(void) {
	scanf("%d %d", &hei, &wid);
	makeTable();
	solve();
	printf("%d\n", ans);
	return 0;
}
