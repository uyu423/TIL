#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
	char buffer[256];
	int len, client_fd;

	client_fd = atoi(argv[1]);

	do {
		len = read(client_fd, buffer, 256);
		write(client_fd, buffer, len);
	} while(strcmp(buffer, "quit\n") == 0);

	return 0;
}
