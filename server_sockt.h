#ifndef SERVER_SOCKT_H
#define SERVER_SOCKT_H

#include "common_sockt.h"
#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

class ServerSocket
{
private:
    int fd;
	bool isClosed;
public:
    ServerSocket(char *port, int q_max);
    Socket acceptClient(bool *end);
	void shutdownAccept();
    ~ServerSocket();
};

ServerSocket::ServerSocket(char *port, int q_max): isClosed(false){
    struct addrinfo hints;
	struct addrinfo *ptr;
	int err = 0;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	err = getaddrinfo(NULL, port, &hints, &ptr);
	if (err != 0) {
        // perror(ADDINFO_ERROR_MSG);
        // return ERROR_NO;
   }
	fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

	if (fd == -1) {
		// perror(CREAR_ERROR_MSG);
		// freeaddrinfo(ptr);
		// return ERROR_NO;
	}

	err = bind(fd, ptr->ai_addr, ptr->ai_addrlen);
	if (err == -1) {
    	// perror(BIND_ERROR_MSG);
    	// close(fd);
    	// freeaddrinfo(ptr);
    	// return ERROR_NO;
	}
	freeaddrinfo(ptr);

	err = listen(fd, q_max);
	if (err == -1) {
    	// perror(LISTEN_ERROR_MSG);
    	// close(fd);
    	// return ERROR_NO;
	}
}

Socket ServerSocket::acceptClient(bool *end){
	struct sockaddr_in *cli_act;
	unsigned int len = (socklen_t)sizeof(cli_act);
	int new_fd;
	new_fd = accept(fd, (struct sockaddr *)&cli_act, &len);
	if (new_fd == -1){
		//perror(ACCEPT_ERROR_MSG);
		*end = true;
		return Socket(0);
	}
	return Socket(new_fd);
}

void ServerSocket::shutdownAccept(){
	shutdown(fd, SHUT_RDWR);
	isClosed = true;
}

ServerSocket::~ServerSocket(){
    if (!isClosed) shutdown(fd, SHUT_RDWR);
	close(fd);
}



#endif
