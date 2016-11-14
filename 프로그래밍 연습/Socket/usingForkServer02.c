#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"
//소켓 프로그래밍에 사용될 헤더파일 선언
 
#define BUF_LEN 128
//메시지 송수신에 사용될 버퍼 크기를 선언
 
int main(int argc, char *argv[])
{
    char buffer[BUF_LEN];
    struct sockaddr_in server_addr, client_addr;
    char temp[20];
    int server_fd, client_fd;
	int pid;
    //server_fd, client_fd : 각 소켓 번호
    int len, msg_size;
 
    if(argc != 2)
    {
        printf("usage : %s [port]\n", argv[0]);
		return 1;
    }
 
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {// 소켓 생성
        printf("Server : Can't open stream socket\n");
		return 1;
    }
    memset(&server_addr, 0x00, sizeof(server_addr));
    //server_Addr 을 NULL로 초기화
 
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(atoi(argv[1]));
    //server_addr 셋팅
 
    if(bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) <0)
    {//bind() 호출
        perror("Server : Can't bind local address.\n");
		return 1;
    }
 
    if(listen(server_fd, 5) < 0)
    {//소켓을 대기모드로 설정
        perror("Server : Can't listening connect.\n");
        return 1;
    }
 
    memset(buffer, 0x00, sizeof(buffer));
    printf("Server : wating connection request.\n");
    len = sizeof(client_addr);
    while(1)
    {
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &len);
		if(client_fd < 0) {
				continue;
        }
        inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, temp, sizeof(temp));
        printf("Server : %s client connected.\n", temp);
   		
		pid = fork();
		if(pid == 0) { 
			do {
				memset(buffer, 0x00, sizeof(buffer));
				msg_size = read(client_fd, buffer, 1024);
		   	    if(msg_size == -1) {
						perror("Server : Client's data read error.\n");
						return 1;
				}
		        if(write(client_fd, buffer, msg_size) < 0 ) {
					perror("Server : Server send data error.\n"); 
					return 1;
				}
			} while(strcmp(buffer, "q\n") != 0);
		}
		else {
				printf("Server : New Connection Fork.\n");
				close(client_fd);
				continue;
		}
    	printf("Server : %s client closed.\n", temp);
    	close(client_fd);
    }
    return 0;
}
