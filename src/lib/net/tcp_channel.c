#include "lib_net.h"
#include <stdlib.h>

int init_tcp_channel(tcp_channel *channel) {
	channel->sockfd = -1;

	channel->read_buffer = (char *)malloc(CHANNEL_BUFFER_SIZE * sizeof(char));
	if (channel->read_buffer == NULL) {
		return -1;
	}

	channel->write_buffer = (char *)malloc(CHANNEL_BUFFER_SIZE * sizeof(char));
	if (channel->write_buffer == NULL) {
		return -1;
	}

	return 0;
}

void close_tcp_channel(tcp_channel *channel) {
	channel->sockfd = -1;
	free(channel->read_buffer);
	free(channel->write_buffer);

	return;
}

void write_channel_unsigned(tcp_channel *channel, unsigned value) {

}
