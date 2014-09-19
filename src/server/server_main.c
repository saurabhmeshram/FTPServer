/* Implementation for Server Side */
#include "common_head.h"

#define PORT 4000
#define IP_ADDR "127.0.0.1"

int sock_fd, new_fd;

int main (void)
{
	struct sockaddr_in serv;
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);

	memset(&serv, 0, sizeof(struct sockaddr_in));
	serv.sin_family = AF_INET;
	serv.sin_port = PORT;
	serv.sin_addr.s_addr = inet_addr(IP_ADDR);

	bind(sock_fd, &serv, sizeof(struct sockaddr_in));
	return 0;
}
