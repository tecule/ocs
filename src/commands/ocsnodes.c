#include<stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "lib_net.h"
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 64
#define OCS_REQUEST_TYPE_NODE_STATE 100

int main(int argc, char **argv) {
	int client_socket_fd;
	if (-1 == (client_socket_fd = socket(AF_INET, SOCK_STREAM, 0))) {
		printf("%d: %s\n", errno, strerror(errno));
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in server_address;
	bzero(&server_address, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(SERVER_PORT);
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);

	if (-1 == connect(client_socket_fd, (struct sockaddr *)&server_address, sizeof(server_address))) {
		printf("%d: %s\n", errno, strerror(errno));
		exit(EXIT_FAILURE);
	}

//	char read_buffer[BUFFER_SIZE] = { 0 }, write_buffer[BUFFER_SIZE] = { 0 };
//	while (fgets(write_buffer, BUFFER_SIZE, stdin) != NULL ) {
//		ssize_t nbytes_write = write(client_socket_fd, write_buffer,
//				strlen(write_buffer));
//		if (nbytes_write > 0) {
//			printf("write %d bytes\n", (int) nbytes_write);
//
//			read(client_socket_fd, read_buffer, BUFFER_SIZE);
//			fprintf(stdout, "%s\n", read_buffer);
//			fflush(stdout);
//		} else if (nbytes_write < 0) {
//			printf("%d: %s\n", errno, strerror(errno));
//		}
//	}

	tcp_channel channel;
	if (-1 == init_tcp_channel(&channel)) {
		close(client_socket_fd);
		printf("%d: %s\n", errno, strerror(errno));
		exit(EXIT_FAILURE);
	}

	close_tcp_channel(&channel);

	close(client_socket_fd);

	exit(EXIT_SUCCESS);
}
