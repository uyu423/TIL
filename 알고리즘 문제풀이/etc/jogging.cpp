#include "stdio.h"

struct type {
	int cnt;
};

int main(void) {	
	int t, i;
	struct type same = {0}, big = {0}, less = {0}, *now;
	int fir, tmp, bef;

	scanf("%d", &t);
	for(i = 0; i <= t+1; i++) {
		if(i < t) {
			scanf("%d", &tmp);
		}
		else {
			tmp = fir;
		}

		if(!i) {
			fir = tmp;
			bef = tmp;
			continue;
		}
		if(i == 1) {
			if(bef < tmp){
				now = &big;
			}
			else if(bef > tmp) {
				now = &less;
			}
			else {
				now = &same;
			}
		}
		
		if(bef < tmp) {
			if(now != &big) {
				now->cnt++;
				now = &big;
			}
			else {
			}
		}
		else if(bef > tmp) {
			if(now != &less) {
				now->cnt++;
				now = &less;
			}
			else {
			}
		}
		else {
			if(now != &same) {
				now->cnt++;
				now = &same;
			}
			else {
			}
		}

//	printf("bef : %d\ntmp : %d\n%d %d %d\n", bef, tmp, same.cnt, big.cnt, less.cnt);
		bef = tmp;
	}

	printf("%d %d %d\n", same.cnt, big.cnt, less.cnt);

}
