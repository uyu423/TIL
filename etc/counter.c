/*
 * invaildCounter.c
 *
 *  Created on: 2014. 10. 8.
 *      Author: YoWu (uyu423@gmail.com)
 *         IDE: Eclipse Luna (gcc 4.8.2)
 */

#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"

int main(void) {
	int halflife2;				//input value
	int gordon = 1, freeman = 0;
	int gordon_freeman = 0;

	int bbaru;					//temp value
	int combine = 10;			//combine = combine * 10;
	int smg1[10];			//save array value by halflife2
	int ar2 = 0;					//smg1 counter

	int i = 0;

	scanf("%d", &halflife2);
	bbaru = halflife2;

	//input halflife2 to smg1 array
	while (bbaru) {
		smg1[i] = bbaru % combine;
		bbaru = bbaru / combine;
		ar2++;
		i++;
	}

	//calculate
	for (i = 0; i < ar2; i++) {
		if (smg1[i] >= 4) {
			gordon_freeman = gordon_freeman + gordon + (freeman * (smg1[i] - 1));
		} else {
			gordon_freeman = gordon_freeman + (freeman * smg1[i]);
		}
		freeman = gordon + (freeman * 9);
		gordon = gordon * 10;
	}

	printf("%d\n", halflife2 - gordon_freeman);

	return 0;
}

