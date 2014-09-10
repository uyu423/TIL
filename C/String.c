//cording by YoWu (uyu423@gmail.com
//동적할당을 사용한 입력받은 문자열 뒤집는 프로그램

#include "stdio.h"
#include "string.h"

char **fuck;

void mirror(char *str) {
		int max = strlen(str);
		int i;
		for(i = max; i>=0; i--) {
				putchar(str[i]);
		}
		putchar('\n');
}

void allocate(int num) {
	int i;
	fuck = (char **)calloc(num, sizeof(char *));
	for(i = 0; i < num; i++) {
			fuck[i] = (char *)calloc(20, sizeof(char *));
			scanf("%s", fuck[i]);
			mirror(fuck[i]);
	}
}

int main(void) {
	int num;
	scanf("%d", &num);
	allocate(num);

	return 0;
}
