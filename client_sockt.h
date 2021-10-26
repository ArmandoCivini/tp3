#ifndef CLIENT_SOCKT_H
#define CLIENT_SOCKT_H

#include "common_sockt.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <stdbool.h>

class ClientSocket : public Socket
{
private:
    struct addrinfo *resultado;
    void connection();
public:
    ClientSocket(char *host, char *port);
    ~ClientSocket();
};

ClientSocket::ClientSocket(char *host, char *port): Socket(-1){
    struct addrinfo hints;
	int err = 0;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = 0; 

	err = getaddrinfo(host, port, &hints, &resultado);

	if (err != 0) {
    	// perror(ADDINFO_ERROR_MSG);
    	// freeaddrinfo(resultado);
    	// return -1;
	}
    connection();
}

void ClientSocket::connection(){
	int err = 0;
	bool conexion_exitosa = false;
	struct addrinfo *ptr = resultado;

	while (ptr != NULL && conexion_exitosa == false){
   		fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    	if (fd == -1) {
    		ptr = ptr->ai_next;
        	continue;
   		}
   		err = connect(fd, ptr->ai_addr, ptr->ai_addrlen);
   		if (err == -1) {
        	close(fd);
        	ptr = ptr->ai_next;
        	continue;
        }
        conexion_exitosa = true;
   	}

   	if (conexion_exitosa == false){
   		// perror(CONECCION_ERROR_MSG);
   		// return -1;
   	}
}

ClientSocket::~ClientSocket(){
    freeaddrinfo(resultado);
}


#endif
