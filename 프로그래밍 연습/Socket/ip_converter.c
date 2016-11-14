#include "stdio.h"
#include "netinet/in.h"
//inet_pton, inet_ntop 함수가 포함된 헤더파일

void main(int argc, char *argv[])
{
		struct in_addr addr;
		//2진수 IP 주소의 저장을 위한 구조체 사용
		char buf[20];
		//10진수 IP 주소의 저장을 위한 임시 변수
		
		printf("demical IP addr : %s\n", argv[1]);
		//입력받은 10진수 IP 주소를 명시
		
		inet_pton(AF_INET, argv[1], &addr.s_addr);
		printf("inet_pton(%s) : 0x%x\n", argv[1], addr.s_addr);
		//입력받은 값을 2진수 IP주소로 변환하여 addr 구조체에 저장

		inet_ntop(AF_INET, &addr.s_addr, buf, sizeof(buf));
		printf("inet_ntop(0x%x) = %s\n", addr.s_addr, buf);
		//addr 구조체의 2진수 IP주소 값을 10진수로 변환하여 buf에 sizeof(buf)만큼 저장
}
