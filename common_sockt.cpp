#include "common_sockt.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <utility>
#include <sys/socket.h>

#define FIN 0
#define BYTE_ERROR -1
#define EMPTY_FD -1
#define SUCCESS 1
#define ERROR_MANDAR "error al mandar en socket"
#define ERROR_RECIVIR "error al recivir en socket"

Socket::Socket(int fd) : fd(fd){
}

Socket::Socket(Socket && other){
   this->fd = other.fd;
   other.fd = EMPTY_FD;
}

Socket Socket::acceptS(int fd){
	return std::move(Socket(fd));
}

int Socket::read(char *buf, int exp_len){
	int bytes = recv(fd, buf, exp_len, 0);
	if (bytes == -1){
		throw ERROR_RECIVIR;
	}
	if (bytes==FIN){
			return FIN;
	}
	int bytes_sum = bytes; //bytes enviados hasta ahora
	while (bytes_sum < exp_len){
		bytes = recv(fd, &buf[bytes_sum], exp_len-bytes_sum, 0);
		if (bytes == BYTE_ERROR){
			throw ERROR_RECIVIR;
		}
		if (bytes==FIN){
			return FIN;
		}
		bytes_sum += bytes;
	}
	buf[exp_len] = '\0';
	return SUCCESS;
}

int Socket::write(char *buf, int exp_len){
	int bytes = send(fd, buf, exp_len, 0);
	if (bytes == BYTE_ERROR){
		throw ERROR_MANDAR;
	}
	int bytes_sum = bytes; //bytes enviados hasta ahora
	while (bytes_sum < exp_len){
		bytes = send(fd, &buf[bytes_sum], exp_len-bytes_sum, MSG_NOSIGNAL);
		if (bytes == BYTE_ERROR){
			throw ERROR_MANDAR;
		}
		bytes_sum += bytes;
	}
	return 0;
}

Socket::~Socket(){
	if (fd == EMPTY_FD){
		return;
	}	
    shutdown(fd, SHUT_RDWR);
	close(fd);
}
