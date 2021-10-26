#include "common_protocolo.h"
#include "client_sockt.h"
#include <iostream>
#define INT16 2

class Admin
{
private:
    ClientSocket skt;
    ProtocoloCliente protocolo;
    void definir(char *cola);
    void push(char *cola, char *a_escribir);
    void pop(char *cola);
public:
    Admin(char *host, char *port);
    bool operar(char *commando);
    ~Admin();
};

Admin::Admin(char *host, char *port): skt(host, port){
}

void Admin::definir(char *cola){
    char *mensaje;
    int largo = protocolo.construirMensajeDefinir(cola, &mensaje);
    skt.write(mensaje, largo);
    printf("se escribio\n");
}

void Admin::push(char *cola, char *a_escribir){
    char *mensaje;
    int largo = protocolo.construirMensajePush(cola, a_escribir, &mensaje);
    skt.write(mensaje, largo);
}

void Admin::pop(char *cola){
    char *mensaje;
    int largo = protocolo.construirMensajePop(cola, &mensaje);
    skt.write(mensaje, largo);
    free(mensaje);
    char largo_pop[INT16];
    skt.read(largo_pop, INT16);
    largo = protocolo.largoMensaje(largo_pop);
    mensaje = (char *)malloc(sizeof(char)*largo);
    skt.read(mensaje, largo);
    protocolo.mensaje(mensaje);
    printf("%s\n", mensaje);
    free(mensaje);
}

bool Admin::operar(char *commando){
    char *accion = strtok(commando,  " ");
    if (strcmp(accion, "define")==0){
        definir(strtok(NULL,  " "));
        return true;
    } else if (strcmp(accion, "push")==0){
        push(strtok(NULL,  " "), strtok(NULL,  " "));
        return true;
    } else if (strcmp(accion, "pop")==0){
        pop(strtok(NULL,  " "));
        return true;
    } else if (strcmp(accion, "exit")==0){
        return false;
    }
    perror("commando incorrecto");
    return true; 
}

Admin::~Admin(){
}



int main(int argc, char *argv[]){
    ProtocoloCliente proto;
    std::string linea;
    if (argc < 3){
        perror("argumentos insuficientes");
        return 1;
    }
    
    Admin admin(argv[1], argv[2]);
    bool termino = true;
    while (std::getline(std::cin, linea) && termino){
        termino = admin.operar((char *)linea.c_str());
    }
    return 0;
}
