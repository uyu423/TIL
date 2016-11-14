#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"
//필요한 헤더 상단부 선언

#define BUF_LEN 512
//주고가는 데이터의 크기를 기본 512 byte로 설정

int main(int argc, char **argv)
{
		char buffer[BUF_LEN], temp[BUF_LEN];
		struct sockaddr_in server_addr, client_addr;
		int server_fd, client_fd, file_fd;
		int len, msg_size;
		int cnt=0, i = 0, j = 0;

		char method[10];	//메소드 값이 들어간다
		char path[100];		//경로가 들어간다.
		char filename[20];	//파일명이 들어간다.
		char protocol[10];	//프로토콜 값이 들어간다.

		if(argc != 2) {
				printf("usage : %s [port]\n", argv[0]);
				exit(0);
		}

		if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		{
				printf("WEB_Server : Can't open stream socket.\n");
				exit(0);
		}
		memset(&server_addr, 0x00, sizeof(server_addr));

		server_addr.sin_family = AF_INET;
		server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
		server_addr.sin_port = htons(atoi(argv[1]));

		if(bind(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
		{
				printf("WEB_Server : Can't bind local address or port.\n");
				exit(0);
		}

		if(listen(server_fd, 10) < 0)
		{
				printf("WEB_Server : Can't listening connect.\n");
				exit(0);
		}
		
		memset(buffer, 0x00, sizeof(buffer));
		printf("WEB_Server : wating connection request.\n");
		len = sizeof(client_addr);

		while(cnt < 10)	//테스트를 위해 횟수 10번으로 설정
		{
				client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &len);
				if(client_fd < 0)
				{
						printf("WEB_Server : accept failed.\n");
						continue;
				}
				inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, temp, sizeof(temp));
				printf("WEB_Server : %s client connected.\n", temp);
				//클라이언트의 IP 정보를 받아와 서버쪽에서 출력해주는 부분

				msg_size = read(client_fd, buffer, sizeof(buffer));
				i = 0;
				j = 0;
				memset(method, 0x00, sizeof(method));	//헤더의 첫 줄을 읽어와 정보를 파악하는 부분입니다.
				memset(path, 0x00, sizeof(path));
				memset(filename, 0x00, sizeof(filename));
				memset(protocol, 0x00, sizeof(protocol));

				for(i=0; buffer[i]!=' '; i++)
				{
						method[i] = buffer[i];
						method[i+1] = NULL;
				}
				i = i+2;
				for(i; buffer[i]!=' '; i++)
				{
						path[j] = buffer[i];
						path[j+1] = NULL;
						j++;
				}
				j=0;
				i++;
				for(i; buffer[i]!='\r'; i++)
				{
						protocol[j] = buffer[i];
						protocol[j+1] = NULL;
						j++;		
				}
				
				if(strcmp(method, "GET"))
				{//GET방식이 아닐경우 무효
						printf("WEB_Server : client not support METHOD request. reset.\n");
						close(client_fd);
						continue;
				}
				
				if(strcmp(protocol, "HTTP/1.1"))
				{//HTTP/1.1 방식이 아닐경우 무효
						printf("WEB_Server : client not support PROTOCOL request. reset.\n");
						close(client_fd);
						continue;
				}

				strncpy(filename, path, strlen(path));

				if(!(file_fd = fopen(filename, "r")))
				{//존재하지 않는 파일을 요청했을시 반송하는 부분
						printf("WEB_Server : client not exist FILE %s request. reset.\n", filename);
						write(client_fd, "HTTP/1.1 404 Not Found\r\n", strlen("HTTP/1.1 404 Not Found\r\n"));
						write(client_fd, "\r\n", strlen("\r\n"));
						close(client_fd);
						continue;
				}
			
				//요청 성공시 아래의 내용이 클라이언트로 전송
				write(client_fd, "HTTP/1.1 200 OK\r\n", strlen("HTTP/1.1 200 OK\r\n"));
				write(client_fd, "Server: Apache\r\n", strlen("Server: Apache\r\n"));
				write(client_fd, "Connection: close\r\n", strlen("Connection: close\r\n"));
				write(client_fd, "Content-Type: text/html\r\n", strlen("Content-Type: text/html\r\n"));
				write(client_fd, "\r\n", strlen("\r\n"));

				while(fgets(temp, BUF_LEN, file_fd))
				{
						write(client_fd, temp, strlen(temp));
				}
				
				printf("WEB_Server : response success : %s close client socket.\n", filename);
				fclose(file_fd);
				close(client_fd);
		}
		close(server_fd);
		return 0;
}
