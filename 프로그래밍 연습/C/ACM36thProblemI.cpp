#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int arr[1000000];

int compare(const void * a, const void * b)
{
	return (*(int*)a - *(int*)b);
}

int main(void) {
	int t, n, k;
	int min = 98461687;
	int cnt = 1;
	int thisVal;
	//scanf("%d", &t);

		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d", &arr[i]);
		}
		scanf("%d", &k);
		qsort(arr, n, sizeof(int), compare);
		/* for (int i = 0; i < n; i++)
			printf("%d ", arr[i]); */
		for (int i = 0; i < n; i++) {
			for (int j = i+1; j < n; j++) {
				thisVal = (arr[i] + arr[j]) - k;
				if (min > abs(thisVal)) {
					min = abs(thisVal);
					cnt = 1;
				}
				else if (min == abs(thisVal)) {
					cnt++;
				}
				else if (min < thisVal) {
					break;
				}
				else
				{
					continue;
				}
			}
		}
		printf("%d\n", cnt);
}
