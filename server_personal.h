#ifndef SERVER_PERSONAL_H
#define SERVER_PERSONAL_H

#include "server_protocolo.h"
#include "server_queueumanager.h"

#define FAIL 'f'
#define DEFINE 'd'
#define PUSH 'u'

class Personal
{
private:
    Socket skt;
    QueueManager& colas;
    ProtocoloServer protocolo;
    void definirCola();
    void pushCola();
    void popCola();
    bool leerIntencion();
public:
    Personal(Socket skt, QueueManager& colas);
    void atender();
    ~Personal();
};

#endif
