#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "time.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"
//소켓 프로그래밍에 사용될 헤더파일 선언
 
#define BUF_LEN 128
//메시지 송수신에 사용될 버퍼 크기를 선언
 
int main(int argc, char *argv[])
{
	int pid, select;
    char buffer[BUF_LEN];
	char input_buf[BUF_LEN];
    struct sockaddr_in server_addr, client_addr;
    char temp[20];
    int server_fd, client_fd;
    //server_fd, client_fd : 각 소켓 번호
    int len, msg_size;
 
    if(argc != 2)
    {
        printf("usage : %s [port]\n", argv[0]);
        exit(0);
    }
 
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {// 소켓 생성
        printf("Server : Can't open stream socket\n");
        exit(0);
    }
    memset(&server_addr, 0x00, sizeof(server_addr));
    //server_Addr 을 NULL로 초기화
 
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(atoi(argv[1]));
    //server_addr 셋팅
 
    if(bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) <0)
    {//bind() 호출
        printf("Server : Can't bind local address.\n");
        exit(0);
    }
 
    if(listen(server_fd, 5) < 0)
    {//소켓을 수동 대기모드로 설정
        printf("Server : Can't listening connect.\n");
        exit(0);
    }

   	memset(buffer, 0x00, sizeof(buffer));
   	printf("Server : wating connection request.\n");
   	len = sizeof(client_addr);

	while(1) {
    	client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &len);
    	if(client_fd < 0)
    	{
    	    printf("Server: accept failed.\n");
     	   exit(0);
  	 	}
   		inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, temp, sizeof(temp));
	    printf("Server : %s client connected.\n", temp);
		write(client_fd, "Select\n1. Datetime\n2. Echo\nSelect : ", 36);
		read(client_fd, buffer, 256);
		select = atoi(buffer);
		pid = fork();
		if(!pid) {
				printf("Server : fork client.\n");
				close(server_fd);
				switch(select) {
					case 1:
						printf("Server : %s client request Timer Service.\n", temp);
						dup2(client_fd, STDIN_FILENO);
						dup2(client_fd, STDOUT_FILENO);
						close(client_fd);
						execlp("./timer", "timer", (char *)0);
						break;
					case 2:
						printf("Server : %s client request Echo Service.\n", temp);
						sprintf(buffer, "%d", client_fd);
						execlp("./echo", "echo", buffer, (char *)0);
						close(client_fd);
						break;
				}
		}
		close(client_fd);
	}
	close(server_fd);
}
