#include <stdio.h>

int main(void) {
	double a,b;
	scanf("%lf %lf", &a, &b);
	printf("%.20lf", a/b);
	return 0;
}
