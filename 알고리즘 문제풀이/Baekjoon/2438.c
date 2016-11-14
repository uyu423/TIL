/*
* ProjectName : Baekjoon Algorithm Problem 10757 - 별찍기1
* Corder : YoWu (uyu423@gamil.com / http://luckyyowu.tistory.com)
* Organiz. : Catholic Univ. of Korea
* Major : Computer Science
* Minor : Infomation System Engineering
* DateTime	: 2015.4.29 15:54
* Develop OS :  CentOS Linux 6.6 x86 (kernel 2.6.32-504)
* PorgramLang : C (Library Model : POSIX)
* TextEditor : VIM - Vi IMproved 7.2
* Encording : UTF-8 (Linux Basic)
* Compiler	: GCC 4.4.7
*/

/*
* ** Try Status **
* try 01 : success
*/

#include <stdio.h>

int main(void) {
	int i, j, n;
	scanf("%d", &n);
	for(i=1;i<=n;i++) {
		for(j=0;j<i;j++) {
			putchar('*');
		}
		putchar('\n');
	}
	return 0;
}
