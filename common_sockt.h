#ifndef COMMON_SOCKT_H
#define COMMON_SOCKT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>

class Socket
{
protected:
	int fd;
public:
    Socket(int fd);
    int read(char *buf, int exp_len);
    int write(char *buf, int exp_len);
    ~Socket();
};

Socket::Socket(int fd) : fd(fd){
}

int Socket::read(char *buf, int exp_len){
	int bytes = recv(fd, buf, exp_len, 0);
	if (bytes == -1){
		// sockt_destroy(skt);
		// perror(ERROR_MSG); TODO
		// return ERROR_NO;
	}
	if (bytes==0){
			return 0;
	}
	int bytes_sum = bytes; //bytes enviados hasta ahora
	while (bytes_sum < exp_len){
		bytes = recv(fd, &buf[bytes_sum], exp_len-bytes_sum, 0);
		if (bytes == -1){
			// sockt_destroy(skt);
			// perror(ERROR_MSG);
			// return ERROR_NO;
		}
		if (bytes==0){
			return 0;
		}
		bytes_sum += bytes;
	}
	buf[exp_len] = '\0';
	return 1;
}

int Socket::write(char *buf, int exp_len){
	int bytes = send(fd, buf, exp_len, 0);
	if (bytes == -1){
		// sockt_destroy(skt);
		// perror(ERROR_MSG);
		// return ERROR_NO;
	}
	int bytes_sum = bytes; //bytes enviados hasta ahora
	while (bytes_sum < exp_len){
		bytes = send(fd, &buf[bytes_sum], exp_len-bytes_sum, 0);
		if (bytes == -1){
			// sockt_destroy(skt);
			// perror(ERROR_MSG);
			// return ERROR_NO;
		}
		bytes_sum += bytes;
	}
	return 0;
}

Socket::~Socket(){
    shutdown(fd, SHUT_RDWR);
	close(fd);
}


#endif
