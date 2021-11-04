#ifndef COMMON_SOCKT_H
#define COMMON_SOCKT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>

#define FIN 0
#define BYTE_ERROR -1
#define EMPTY_FD -1
#define SUCCESS 1
#define ERROR_MANDAR "error al mandar en socket"
#define ERROR_RECIVIR "error al recivir en socket"

class Socket
{
protected:
	int fd;
	explicit Socket(int fd);
	Socket acceptS(int fd);
public:
	Socket(Socket && other);
    int read(char *buf, int exp_len);
    int write(char *buf, int exp_len);
    ~Socket();
};

#endif
