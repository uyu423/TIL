/*
* ProjectName : Baekjoon Algorithm Problem 10757 - Big Number (Debug Source)
* Corder : YoWu (uyu423@gamil.com / http://luckyyowu.tistory.com)
* Organiz. : Catholic Univ. of Korea
* Major : Computer Science
* Minor : Infomation System Engineering
* DateTime	: 2015.4.29 15:39
* Develop OS : Windows 8.1 Embedded Industry (x86)
* PorgramLang : C (Library Model : POSIX)
* TextEditor : VIM - Vi IMproved 7.2
* Encording : UTF-8 (Linux Basic)
* Compiler	: GCC 4.4.7
*/

#include <stdio.h>
#include <string.h>

typedef enum { false, true } bool;
typedef struct {
	char num[100001];
	int st;
} bigNum;

bigNum big1, big2, res, ans;

int parseInt(char num) { return num - '0'; }

void realMain(char *num1, char *num2) {
	int i, tmp;
	bool flag = false;
//	scanf("%s", big1.num);
//	scanf("%s", big2.num);
	strcpy(big1.num, num1);
	strcpy(big2.num, num2);
	big1.st = strlen(big1.num);
	big2.st = strlen(big2.num);
	res.st = 0;
	ans.st = 0;
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
		ans.num[ans.st++] = res.num[i];
	}
	ans.num[ans.st] = '\0';
//	printf("%s\n", ans.num);
}

int judge(int sum) {
	char tmp[100001];
	sprintf(tmp, "%d", sum);
	if (strcmp(ans.num, tmp) != 0) {
		printf("%s + %s = %s\tYou : %s Fuck!\n", big1.num, big2.num, tmp, ans.num);
		return 1;
	}
	else {
		printf("%s + %s = %s\tYou : %s OK!\n", big1.num, big2.num, tmp, ans.num);
		return 0;
	}
}

int main(void) {
	char num1[100001], num2[100001];
	int i, j;
	srand(time(NULL));
	while (1) {
		sprintf(num1, "%d", rand());
		sprintf(num2, "%d", rand());
		realMain(num1, num2);
		if (judge(atoi(num1) + atoi(num2))) {
			break;
		}
	}
	
	return 0;
}
