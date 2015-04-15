/*
 *	ProjectName	: Baekjoon Algorithm Problem 9012
 *	Corder 		: YoWu (uyu423@gamil.com / http://luckyyowu.tistory.com)
 *	Organiz.	: Catholic Univ. of Korea
 *	Major		: Computer Science (Minor : Infomation System Eng)
 *	DateTime	: 2015.4.15 13:14
 *	Develop OS	: CentOS Linux 6.6 x86 (kernel 2.6.32-504)
 *	PorgramLang	: C (Library Model : POSIX)
 *	TextEditor	: VIM - Vi IMproved 7.2
 *	Encording	: UTF-8 (Linux Basic)
 *	Compiler	: GCC 4.4.7
 */

#include <stdio.h>
#include <string.h>

//typedef enum { false, true } bool;
typedef struct __stackManager {
	int top;
} stackMgr;

void stackPush(stackMgr *stmgr) {
	stmgr->top++;
}

bool stackPop(stackMgr *stmgr) {
	stmgr->top--;
	if((stmgr->top) < 0) {
		return false;
	}
	return true;
}

int main(void) {
	int cnt;
	char buf[100];
	int i;
	bool stat = true;
	stackMgr stmgr;
	stmgr.top = 0;
	scanf("%d", &cnt);
	while(cnt--) {
		scanf("%s", buf);
//		printf("buf len : %d\n", strlen(buf)); //Debug : buf's length
		for(i = 0 ; i < strlen(buf); i++) {
			if(buf[i] == '(') {
				stackPush(&stmgr);
			}
			else if(buf[i] == ')') {
				stat = stackPop(&stmgr);
			}
			if(stat == false)	break;
		}
//		printf("stat : %d stack top : %d\n", stat, stmgr.top);	//Debug : stat, stack top value
		if(stat == false || stmgr.top != 0) {
			printf("NO\n");
		}
		else printf("YES\n");
		stmgr.top = 0;
		stat = true;
	}
	return 0;
}
