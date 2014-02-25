#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <signal.h>
#include <unistd.h>
#include <string.h>

#include <stddef.h>
#include <errno.h>

int init_socket() {
	// ?
	signal(SIGPIPE, SIG_IGN);

	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == socket_fd) {
		return -1;
	}

	int reuse_addr_on = 1;
	if (-1 == setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &reuse_addr_on, sizeof(reuse_addr_on))) {
		close(socket_fd);
		return -1;
	}

	struct linger linger_delay;
	memset(&linger_delay, 0, sizeof(linger_delay));
	linger_delay.l_onoff = 0;
	if (-1 == setsockopt(socket_fd, SOL_SOCKET, SO_LINGER, &linger_delay, sizeof(linger_delay))) {
		close(socket_fd);
		return -1;
	}

	return socket_fd;
}

ssize_t read_nbytes(int fd, void *buffer, size_t n) {
	void *to = buffer;
	size_t nbytes_left = n;
	ssize_t nr = 0;

	while (nbytes_left > 0) {
		nr = read(fd, to, nbytes_left);
		if (nr < 0) {
			if (errno == EINTR) {
				// read again
				continue;
			} else {
				return -1;
			}
		} else if (nr == 0) {
			// EOF
			break;
		}

		to += nr;
		nbytes_left -= nr;
	}

	return (ssize_t)(n - nbytes_left);
}

ssize_t write_nbytes(int fd, const void *buffer, size_t n) {
	const void *from = buffer;
	size_t nbytes_left = n;
	ssize_t nw = 0;

	while (nbytes_left > 0) {
		nw = write(fd, from, nbytes_left);
		if (nw < 0) {
			if (errno == EINTR) {
				// write again
				nw = 0;
			} else {
				return -1;
			}
		}

		from += nw;
		nbytes_left -= nw;
	}

	return (ssize_t)(n - nbytes_left);
}
