/**
 * @file lib_net.h
 * @brief net library header file
 * @details net library header file
 * @author WANG Xiangqian
 * @version
 * @date 2013
 * @copyright undefined
 */

#ifndef __LIB_NET_
#define __LIB_NET_

#include <sys/socket.h>

/**
 * @brief server socket port
 */
#define SERVER_PORT 16001
#define SOCKET_PENDING_QUEUE_LENGTH	256
/**
 * @brief channel buffer size
 */
#define CHANNEL_BUFFER_SIZE 65536

/**
 * @brief channel buffer struct
 */
struct channel_buffer {
	char *buffer;												///< channel buffer
	size_t size;												///< channel buffer size
	size_t count;												///< channel buffer used
};
typedef struct channel_buffer channel_buffer;

/**
 * @brief tcp channel struct
 */
struct tcp_channel {
	int sockfd;													///< tcp channel socket file descriptor
	channel_buffer read_buffer;									///< tcp channel read buffer
	channel_buffer write_buffer;								///< tcp channel write buffer
};
typedef struct tcp_channel tcp_channel;

/**
 * @brief initialize a socket
 * @return
 * - newly created socket file descriptor: on success
 * - -1: on error, check errno for details
 */
int init_socket();
/**
 * @brief strive to read n bytes from file
 * @param fd file (descriptor) read from
 * @param buffer buffer to store read content
 * @param n number of bytes should read
 * @return
 * - number of bytes read: on success
 * - -1: on error, check errno for details
 */
ssize_t read_nbytes(int fd, void *buffer, size_t n);
/**
 * @brief strive to write n bytes to file
 * @param fd file (descriptor) write to
 * @param buffer buffer to read content from
 * @param n number of bytes should write
 * @return
 * - number of bytes write: on success
 * - -1: on error, check errno for details
 */
ssize_t write_nbytes(int fd, const void *buffer, size_t n);
/**
 * @brief initialize a tcp channel
 * @param channel tcp channel to be initialized
 * @return
 * - 0: on sucess
 * - -1: on error, check errno for details
 */
int init_tcp_channel(tcp_channel *channel);
/**
 * @brief close tcp channel to free any allocated resource
 * @param channel tcp channel to be closed
 */
void close_tcp_channel(tcp_channel *channel);

#endif
