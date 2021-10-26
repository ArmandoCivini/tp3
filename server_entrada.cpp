#include "common_protocolo.h"
#include "server_safequeuestring.h"
#include "common_sockt.h"
#include "server_sockt.h"
#include <thread>
#include <iostream>
#include <fstream> 

class QueueManager
{
private:
    std::vector<std::shared_ptr<SafeQueueString>> colas;
    bool queueExiste(char *nombre);
public:
    QueueManager();
    std::string popIn(char *nombre);
    void pushIn(char *nombre, char *mnj);
    void nuevaQueue(char *nombre);
    ~QueueManager();
};

QueueManager::QueueManager(){
}

bool QueueManager::queueExiste(char *nombre){
    for(auto& cola : colas){
        if (cola->isNombre(nombre)){
            return true;
        }
    }
    return false;
}

std::string QueueManager::popIn(char *nombre){
    std::string mensaje;
    bool termino;
    for(auto& cola : colas){
        if (cola->isNombre(nombre)){
            mensaje = cola->pop(&termino);
            return mensaje;
        }
    }
    return mensaje;
}

void QueueManager::pushIn(char *nombre, char *mnj){
    std::string mensaje(mnj);
    for(auto& cola : colas){
        if (cola->isNombre(nombre)){
            cola->push(mensaje);
            return;
        }
    }
}

void QueueManager::nuevaQueue(char *nombre){
    if (queueExiste(nombre)) return;
    std::shared_ptr<SafeQueueString> p(new SafeQueueString(nombre));
    colas.push_back(p);
}

QueueManager::~QueueManager()
{
}


class Personal
{
private:
    Socket skt;
    QueueManager& colas;
    ProtocoloServer& protocolo;
    void definirCola(int largo);
    void pushCola(int largo);
    void popCola(int largo);
    bool leerIntencion();
public:
    Personal(Socket skt, QueueManager& colas, ProtocoloServer& proto);
    void atender();
    ~Personal();
};

Personal::Personal(Socket skt, QueueManager& colas, ProtocoloServer& proto)
: skt(skt), colas(colas), protocolo(proto){
}

void Personal::definirCola(int largo){
    char *buf = (char *)malloc(sizeof(char)*(largo+1));
    skt.read(buf, largo);
    buf[largo] = '\0';
    printf("%s\n", buf);
    colas.nuevaQueue(buf);
    free(buf);
}

void Personal::pushCola(int largo){
    char *buf = (char *)malloc(sizeof(char)*(largo+1));
    skt.read(buf, largo);
    buf[largo] = '\0';
    char *men_data = (char *)malloc(sizeof(char)*2);
    skt.read(men_data, 2);
    int largo_men = (int)protocolo.largoMensaje(men_data);
    char *buf_men = (char *)malloc(sizeof(char)*(largo_men+1));
    buf_men[largo_men] = '\0';
    colas.pushIn(buf, buf_men);
    free(buf);
    free(men_data);
    free(buf_men);
}

void Personal::popCola(int largo){
    char *buf = (char *)malloc(sizeof(char)*(largo+1));
    skt.read(buf, largo);
    buf[largo] = '\0';
    std::string mensaje = colas.popIn(buf);
    char *mnsj = (char *)malloc(sizeof(char)*(largo+2));
    protocolo.crearMensaje(largo, (char *)mensaje.c_str(), mnsj);
    skt.write(mnsj, largo+2);
    free(buf);
}

bool Personal::leerIntencion(){
    printf("intenciones\n");
    char *buf = (char *)malloc(sizeof(char)*3);
    int estado = skt.read(buf, 3);
    printf("se lee\n");
    if (estado == 0) return false;
    
    uint16_t largo = protocolo.largoMensaje(&buf[1]);
    if (buf[0]=='d'){
        definirCola(largo);
    } else if (buf[0]=='u'){
        pushCola(largo);
    } else{
        popCola(largo);
    }
    free(buf);
    return true;
}

void Personal::atender(){
    while(leerIntencion());
}

Personal::~Personal(){
}

void hilo_personal(Personal& personal){
    personal.atender();
}

class Server
{
private:
    ServerSocket server_skt;
    ProtocoloServer protocolo;
    QueueManager colas;
    std::vector<std::thread> hilos;
    std::vector<Personal> trabajadores;
    std::thread hilo_aceptador;
    bool acceptar_cliente();
    void aceptador();
public:
    Server(char *port, int q_max);
    ~Server();
};


Server::Server(char *port, int q_max): server_skt(port, q_max){
    hilo_aceptador = std::thread{&Server::aceptador, this};
    char ch;
    while (std::cin.get(ch)) {
        if (ch=='q') break;
    }
    printf("cierre\n");
    server_skt.shutdownAccept();
    hilo_aceptador.join();
}

bool Server::acceptar_cliente(){
    bool termino = false;
    Socket skt = server_skt.acceptClient(&termino);
    if (termino) return false;
    Personal personal(skt, colas, protocolo);
    trabajadores.push_back(personal);
    hilos.push_back(std::thread(hilo_personal, std::ref(personal)));
    printf("thread creada\n");
    return true;
}

void Server::aceptador(){
    while (this->acceptar_cliente());
}

Server::~Server(){
    for (std::thread & hilo : hilos){
        hilo.join();
    }
}


int main(int argc, char *argv[]){
    Server server(argv[1], 5);
    return 0;
}
