/*
* ProjectName : Baekjoon Algorithm Problem 10757 - Big Number
* Corder : YoWu (uyu423@gamil.com / http://luckyyowu.tistory.com)
* Organiz. : Catholic Univ. of Korea
* Major : Computer Science
* Minor : Infomation System Engineering
* DateTime	: 2015.4.29 15:43
* Develop OS : Windows 8.1 Embedded Industry (x86)
* PorgramLang : C (Library Model : POSIX)
* TextEditor : VIM - Vi IMproved 7.2
* Encording : UTF-8 (Linux Basic)
* Compiler	: GCC 4.4.7
*/

/*
* ** Try Status **
* try 01 : incorrect value (?)
* try 02 : incorrect value (???????)
* try 03 : incorrect value (make and copy debug source)
* try 04 : success
*/

#include <stdio.h>
#include <string.h>

typedef enum { false, true } bool;
typedef struct {
	char num[100001];
	int st;
} bigNum;

bigNum big1, big2, res;

int parseInt(char num) { return num - '0'; }

int main(void) {
	int i, tmp;
	bool flag = false;
	scanf("%s", big1.num);
	scanf("%s", big2.num);
	big1.st = strlen(big1.num);
	big2.st = strlen(big2.num);
	res.st = 0;
	for (i = (big1.st > big2.st ? big1.st : big2.st); i > 0; i--) {
		if (!big2.st && big1.st)	tmp = parseInt(big1.num[--big1.st]);
		else if (!big1.st && big2.st)	tmp = parseInt(big2.num[--big2.st]);
		else if (big1.st && big2.st)	tmp = parseInt(big1.num[--big1.st]) + parseInt(big2.num[--big2.st]);
		else {
			tmp = 0;
		}
		if (flag) {
			flag = false;
			tmp++;
		}
		if (tmp > 9) {
			flag = true;
			tmp = tmp % 10;
			if (!big1.st && !big2.st) i++;
		}
		sprintf(&res.num[res.st++], "%d", tmp);
	}
	for (i = res.st - 1; i >= 0; i--) {
		printf("%c", res.num[i]);
	}
	putchar('\n');
	
	return 0;
}
