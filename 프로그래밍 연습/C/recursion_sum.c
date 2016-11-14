#include "stdio.h"

#define MAX 10

int arr[MAX] = {1,2,3,4,5,6,7,8,9};

int sum(int st, int ed) { 
		if(st == ed) {
				return arr[st];
		}
		else return sum(st, ed-1) + arr[ed];
}

void main() {
	printf("sum : %d\n", sum(0, MAX-1));
}
