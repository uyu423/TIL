//DateTime : 2013. 11. 27

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const static char base64table[]={'A', 'B', 'C', 'D', 'E', 'F', 'G', 
	'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 
	'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 
	'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 
	'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', 
	'7', '8', '9', '+', '/'};

void binary(int num, int *tmp)
{
	int i=0, j=7;
	int temp[8] = {0, };
	while(num)
	{
		temp[i]=num%2;
		num=num/2;
		i++;
	}
	for(i=0; i<8; i++)
	{
		tmp[j] = temp[i];
		j--;
	}
}

void main()
{
	char str[100];
	int *base64;
	int tmp[8];
	int len, sum=0;
	int i, j=0, cnt=0;
	int binmul = 32;
	int temp, equlcnt=0;
	char complbase[100];

	printf("input str : ");
	scanf("%s",str);
	len = strlen(str);
	base64=(int *)calloc(len*8, sizeof(int));

	for(i=0; i<len; i++)
	{
		binary((int)str[i], tmp);	
		for(j=0; j<8; j++)
		{
			base64[cnt] = tmp[j];
			cnt++;
		}
	}
	cnt=0;
	for(j=0; j<((len*8)/6)+1; j++)
	{
		binmul=32;
		sum=0;
		for(i=0; i<6; i++)
		{
			if(base64[cnt]!=0 && base64[cnt]!=1)
			{	
				equlcnt++;
				continue;
			}
			temp = base64[cnt] * binmul;
			sum = sum + temp;
			binmul = binmul/2;
			cnt++;
		}
		base64[j]=sum;
	}

	cnt=0;
	printf("Base64 encoding : ");
	for(i=0; i<((len*8)/6)+1; i++)
	{
		complbase[cnt]=base64table[base64[i]];
		cnt++;
	}
	for(j=0; j<equlcnt; j=j+2)
	{
		complbase[cnt]='=';
		cnt++;
	}
	complbase[cnt]=NULL;
	puts(complbase);
}
