#include "stdio.h"

int func(int n) {
	if(n==0)	return 0;
	else if(n==1)	return 1;
	else return func(n-1) + func(n-2);
}

void main() {
	int i;
	for(i = 0; i <20; i++)
		printf("%d\n", func(i));
}
