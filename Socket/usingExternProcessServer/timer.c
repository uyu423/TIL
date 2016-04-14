#include <stdio.h>
#include <time.h>

int main(void) {
	struct tm *t;
	time_t timer;
	
	timer = time(NULL);
	t = localtime(&timer);

	printf("현재 시스템의 시간은 %d년 %d월 %d일 %d시 %d분 %d초입니다.\n",t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);

	return 0;
}
