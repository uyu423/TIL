/*
 * ProjectName : Baekjoon Algorithm Problem 9009
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
 * try 01 : runtime error (fixed line 76) 
 * 		- before : if(fiboEndValue < num)
 * 		- after : if(fiboEndValue <= num)
 * try 02 : success
 */

#include <stdio.h>

typedef struct __Store {
	int arr[50];
	int cnt;
} store;

store fibo;
store ans;
int fiboEndValue = 0;

/* first fibo table len = 2 */
int makeFiboTable(int max) {
	int i;
	for(i = fibo.cnt; fibo.arr[i-1] <= max; i++) {
		fibo.arr[i] = fibo.arr[i-1] + fibo.arr[i-2];
	}
	fiboEndValue = fibo.arr[i-1];
	return i;
}

/* fibo table value debug function */
void printFiboTable() {
	int i;
	for(i=0; i<fibo.cnt; i++) {
		printf("Fibo.arr[%d] : %d\n", i, fibo.arr[i]);
	}
	return;
}

/* find value into fiboTable and store AnsArr */
/* if you will be imporve program's performance, try binary search */
int findValue(int num) {
	int i;
	int val;
	for(i=0; i<fibo.cnt; i++) {
		if(fibo.arr[i] > num) {
			return fibo.arr[i-1];
		}
	}
	return -1;
}

int main(void) {
	int num;
	int i, t;
	fibo.arr[0] = 0;
	fibo.arr[1] = 1;
	fibo.cnt = 2;
	scanf("%d", &t);
	while(t--) {
		ans.cnt = 0;
		scanf("%d", &num);
		if(fiboEndValue <= num) {
			fibo.cnt = makeFiboTable(num);
		}
//		printFiboTable();	//debug for print fibo.arr 
//		printf("toString\nfibo.cnt = %d\tnum = %d\tfiboEndValue = %d\n", fibo.cnt, num, fiboEndValue);	//debug for main vals
		while(num) {
			ans.arr[ans.cnt] = findValue(num);
			if(ans.arr[ans.cnt] == -1) {
				printf("ans.arr[ans.cnt] = %d\n", ans.arr[ans.cnt]);
				perror("\t** Error Handling(findValue()) : ");
				return 1;
			}
			num -= ans.arr[ans.cnt++];
		}
		for(i = ans.cnt-1; i>=0; i--) {
			printf("%d ", ans.arr[i]);
		}
		putchar('\n');
	}
}
