#include "server_queueumanager.h"
#include "server_safequeuestring.h"

QueueManager::QueueManager(){
}

bool QueueManager::queueExiste(std::string nombre){
    for (auto& cola : colas){
        if (cola->isNombre(nombre)){
            return true;
        }
    }
    return false;
}

std::string QueueManager::popIn(std::string nombre){
    std::string mensaje("");
    bool termino;
    for (auto& cola : colas){
        if (cola->isNombre(nombre)){
            mensaje = cola->pop(&termino);
            return mensaje;
        }
    }
    return mensaje;
}

void QueueManager::pushIn(std::string nombre, std::string mensaje){
    std::lock_guard<std::mutex> lock(m);
    for (auto& cola : colas){
        if (cola->isNombre(nombre)){
            cola->push(mensaje);
            return;
        }
    }
}

void QueueManager::nuevaQueue(std::string nombre){
    std::lock_guard<std::mutex> lock(m);
    std::string nombre_s(nombre);
    if (queueExiste(nombre)) return;
    std::shared_ptr<SafeQueueString> p(new SafeQueueString(nombre_s));
    colas.push_back(p);
}

QueueManager::~QueueManager(){
}
