#include "server_server.h"
#include "common_sockt.h"
#include "server_sockt.h"
#include "server_queueumanager.h"
#include "server_personal.h"
#include <thread>
#include <iostream>
#include <fstream> 
#include <utility>
#include <memory>

#define QUIT 'q'

void hilo_personal(Personal& personal){
    try{
    personal.atender();
    }
    catch(const std::exception& e){
        std::cerr << e.what() << '\n';
    }
}

Server::Server(char *port, int q_max): server_skt(port, q_max){
    hilo_aceptador = std::thread{&Server::aceptador, this};
    char ch;
    while (std::cin.get(ch)) {
        if (ch==QUIT) break;
    }
    server_skt.shutdownAccept();
    hilo_aceptador.join();
    for (std::thread & hilo : hilos){
        hilo.join();
    }
}

bool Server::acceptar_cliente(){
    bool termino = false;
    Socket skt = server_skt.acceptClient(&termino);
    if (termino) return false;
    std::shared_ptr<Personal> personal(new Personal (std::move(skt), colas));
    trabajadores.push_back(personal);
    hilos.push_back(std::thread(hilo_personal, std::ref(*personal)));
    return true;
}

void Server::aceptador(){
    while (this->acceptar_cliente()){}
}

Server::~Server(){
}
