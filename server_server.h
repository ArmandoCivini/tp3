#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include "common_sockt.h"
#include "server_sockt.h"
#include "server_queueumanager.h"
#include "server_personal.h"
#include <thread>
#include <iostream>
#include <fstream> 
#include <memory>
#include <vector>

#define QUIT 'q'

class Server
{
private:
    ServerSocket server_skt;
    QueueManager colas;
    std::vector<std::thread> hilos;
    std::vector<std::shared_ptr<Personal>> trabajadores;
    std::thread hilo_aceptador;
    bool acceptar_cliente();
    void aceptador();
public:
    Server(char *port, int q_max);
    ~Server();
};

#endif
