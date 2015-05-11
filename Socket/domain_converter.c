#include "stdio.h"
#include "netinet/in.h"
#include "netdb.h"
//hostent 구조체와 gethostname 함수 포함 헤더

void main(int argc, char *argv[])
{
		struct hostent *host;
		struct in_addr addr;

		int i;
		char buf[20];
		
		host = gethostname(argv[1]);
		if(!host) 
		{
				printf("gethostbyname fail\n");
				exit(0);
		}

		printf("호스트 이름 :%s\n", host->h_name);
		printf("호스트 주소타입 번호 : %d\n", host->h_addrtype);
		printf("호스트 주소의 길이 : %d\n", host->h_length);
		for(i=0; host->h_addr_list[i]; i++) 
		{
				memcpy(&addr.s_addr, host->h_addr_list[i], sizeof(addr.s_addr));
				inet_ntop(AF_INET, &addr, buf, sizeof(buf));
				printf("IP 주소(%d 번째) : %s", i+1, buf);
		}
		for(i=0; host->h_aliases[i]; i++)
		{
				printf("호스트 별명(%d 번째) : %s", i+1, host->h_aliases[i]);
		}
}
