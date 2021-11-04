#include "client_sockt.h"
#include "common_sockt.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <stdbool.h>

#define EMPTY_FD -1
#define EMPTY_ERR -1
#define ERROR_ADDR "error al obtener info de la direccion"
#define ERROR_CONEXION "error al conectar al servidor"

ClientSocket::ClientSocket(char *host, char *port): Socket(-1), resultado(NULL){
    struct addrinfo hints;
	int err = 0;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = 0; 

	err = getaddrinfo(host, port, &hints, &resultado);

	if (err != 0) {
    	throw ERROR_ADDR;
	}
    connection();
}

void ClientSocket::connection(){
	int err = 0;
	bool conexion_exitosa = false;
	struct addrinfo *ptr = resultado;

	while (ptr != NULL && conexion_exitosa == false){
   		fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    	if (fd == EMPTY_FD) {
    		ptr = ptr->ai_next;
        	continue;
   		}
   		err = connect(fd, ptr->ai_addr, ptr->ai_addrlen);
   		if (err == EMPTY_ERR) {
        	close(fd);
        	ptr = ptr->ai_next;
        	continue;
        }
        conexion_exitosa = true;
   	}

   	if (conexion_exitosa == false){
   		throw ERROR_CONEXION;
   	}
}

ClientSocket::~ClientSocket(){
    if (resultado != NULL) freeaddrinfo(resultado);
}
