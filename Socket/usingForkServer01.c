#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "fcntl.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"
//소켓 프로그래밍에 사용될 헤더파일 선언
 
#define BUF_LEN 128
//메시지 송수신에 사용될 버퍼 크기를 선언

int printFile(char *filename, int client_fd, char *temp) {
		char buf[512];
		char message[256] = "Are You Attacking My Server?\nAre You Attacking My Server??\nAre You Really Attacking My Server???\nBye.";
		int size;
		filename[strlen(filename) - 1] = 0;
		int fd = open(filename, O_RDONLY);
		if(fd == -1) {
				printf("Server : Open File '%s' Error.\n", filename);
				perror("");
				return -1;
		}
		if(strstr(filename, "..") || filename[0] == '/') {
			printf("Server : !!!%s client request upper file. kick user!!!\n", temp);
			write(client_fd, message, strlen(message));
		}
		else {
			printf("Server : %s client request %s file.\n", temp, filename);
			while((size = read(fd, buf, 256)) > 0) {
					write(client_fd, buf, size);
			}
		}

}
 
int main(int argc, char *argv[])
{
    char buffer[BUF_LEN];
    struct sockaddr_in server_addr, client_addr;
    char temp[20];
	int pid;
    int server_fd, client_fd;
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
			strcpy(buffer, "Useable text File : lipsum.txt, dark.txt\nUseable source File : my08.c, my09server,c my10server.c\n");
			write(client_fd, buffer, strlen(buffer));
   			strcpy(buffer, "Please input File name : "); 
			write(client_fd, buffer, strlen(buffer)); 
			memset(buffer, 0x00, sizeof(buffer));
			msg_size = read(client_fd, buffer, 1024);
   	    	if(msg_size == -1) {
				perror("Server : Client's data read error.\n");
					return 1;
				}
	
			if(printFile(buffer, client_fd, temp) == -1) {
					return 1;
			}
		}
		else {
				printf("Server : New Connection Applyed Server. try Fork.\n");
				close(client_fd);
				continue;
		}
        printf("Server : %s client closed.\n", temp);
        close(client_fd);
    }
    close(server_fd);
    return 0;
}
