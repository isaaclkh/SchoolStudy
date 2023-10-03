#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void error_handling(char *message);

int main(int argc, char **argv)
{
	int serv_sock;
	int clnt_sock;
	char message[atoi(argv[2])];
	int str_len;

	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;

	if (argc != 3)
	{
		printf("Usage : %s <port> <BUFSIZE>\n", argv[0]);
		exit(1);
	}

	serv_sock = socket(PF_INET, SOCK_DGRAM, 0);
	if (serv_sock == -1)
		error_handling("socket() error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));

	if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
		error_handling("blind() error");

	clnt_addr_size = sizeof(clnt_addr);
	str_len = recvfrom(serv_sock, message, atoi(argv[2]), 0, (struct sockdaddr *)&clnt_addr, &clnt_addr_size);
	sendto(serv_sock, message, str_len, 0, (struct sockaddr *)&clnt_addr, sizeof(clnt_addr));
	message[str_len] = 0;

	printf("message : %s", message);

	close(serv_sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}