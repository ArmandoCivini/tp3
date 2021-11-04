#include "server_sockt.h"
#include "common_sockt.h"
#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <utility>

#define EMPTY_FD -1
#define EMPTY_ERR -1
#define ERR_CORRECTO 0
#define ERROR_ADDR "error al obtener info de la direccion"
#define ERROR_INIT "error al iniciar socket"
#define ERROR_BIND "error al bindear socket"
#define ERROR_LISTEN "error al escuchar"

ServerSocket::ServerSocket(char *port, int q_max): Socket(-1), isClosed(true){
    struct addrinfo hints;
	struct addrinfo *ptr;
	int err = ERR_CORRECTO;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	err = getaddrinfo(NULL, port, &hints, &ptr);
	if (err != ERR_CORRECTO) {
        throw ERROR_ADDR;
   }
	fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
	isClosed = false;
	if (fd == EMPTY_FD) {
		freeaddrinfo(ptr);
		throw ERROR_INIT;
	}

	err = bind(fd, ptr->ai_addr, ptr->ai_addrlen);
	freeaddrinfo(ptr);
	if (err == EMPTY_ERR) {
    	throw ERROR_BIND;
	}

	err = listen(fd, q_max);
	if (err == EMPTY_ERR) {
    	throw ERROR_LISTEN;
	}
}

Socket ServerSocket::acceptClient(bool *end){
	struct sockaddr_in *cli_act;
	unsigned int len = (socklen_t)sizeof(cli_act);
	int new_fd;
	new_fd = accept(fd, (struct sockaddr *)&cli_act, &len);
	if (new_fd == EMPTY_FD){
		*end = true;
		return Socket::acceptS(EMPTY_FD);
	}
	return Socket::acceptS(new_fd);
}

void ServerSocket::shutdownAccept(){
	shutdown(fd, SHUT_RDWR);
	isClosed = true;
}

ServerSocket::~ServerSocket(){
    if (!isClosed) shutdown(fd, SHUT_RDWR);
	close(fd);
}
