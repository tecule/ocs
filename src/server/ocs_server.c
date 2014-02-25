/*
 * the server is currently protocol-dependent on IPv4, use getaddrinfo() for a protocol-independent version
 */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include "lib_net.h"
#include "ocs_error.h"
#include "lib_log.h"
#include <errno.h>
#include <stdio.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 64

int main(int argc, char **argv) {
	int listening_socket_fd = init_socket();
	if (-1 == listening_socket_fd) {
		exit(E_OCS_SOCKET_CREATE);
	}

	struct sockaddr_in server_address;
	bzero(&server_address, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(SERVER_PORT);
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	if (-1 == bind(listening_socket_fd, (struct sockaddr *)&server_address, sizeof(server_address))) {
		close(listening_socket_fd);
		exit(E_OCS_SOCKET_BIND);
	}

	if (-1 == listen(listening_socket_fd, SOCKET_PENDING_QUEUE_LENGTH)) {
		close(listening_socket_fd);
		exit(E_OCS_SOCKET_LISTEN);
	}

	for(; ; ) {
		struct sockaddr_in client_address;
		// value-result argument as unpv1 said, must initialized before use
		socklen_t client_address_length = sizeof(struct sockaddr_in);
		int connected_socket_fd = accept(listening_socket_fd, (struct sockaddr*)&client_address, &client_address_length);
		if (-1 == connected_socket_fd) {
			// errno
		} else {
//			int reuse_addr_on = 1;
//			setsockopt(connected_socket_fd, SOL_SOCKET, SO_REUSEADDR, &reuse_addr_on, sizeof(reuse_addr_on));
			// process request

//			fd_set read_fds;
//			FD_SET(connected_socket_fd, &read_fds);

			printf("client address is %s:%d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

			char read_buffer[BUFFER_SIZE] = { 0 }, write_buffer[BUFFER_SIZE] = { 0 };
			ssize_t nbytes_read;
			while ((nbytes_read = read(connected_socket_fd, read_buffer, BUFFER_SIZE)) > 0) {
				read_buffer[nbytes_read] = '\0';

				fprintf(stdout, "%s\n", read_buffer);
				fflush(stdout);

				snprintf(write_buffer, BUFFER_SIZE, "response: %s", read_buffer);
				write(connected_socket_fd, write_buffer, strlen(write_buffer));
			}
			if (nbytes_read < 0) {
				printf("%d: %s", errno, strerror(errno));
			}

//			int write_length = write(connected_socket_fd, write_buffer, strlen(write_buffer));
//			printf("write %d bytes\t", write_length);

			close(connected_socket_fd);
		}
	}

	close(listening_socket_fd);

	exit(EXIT_SUCCESS);
}
