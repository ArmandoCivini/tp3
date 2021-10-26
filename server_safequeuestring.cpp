#include "server_safequeuestring.h"
#include <queue>
#include <mutex>
#include <condition_variable>
#include <string.h>

SafeQueueString::SafeQueueString(char *nombre) 
: size(0), fin(false), nombre(nombre){
}

bool SafeQueueString::isNombre(char *is_nombre){
    return (strcmp(this->nombre, is_nombre)==0);
}

void SafeQueueString::push(std::string dato){
    std::lock_guard<std::mutex> lock(m);
    cola.push(dato);
    ++this->size;
    block_empty.notify_one();
}

std::string SafeQueueString::pop(bool *termino){
    std::unique_lock<std::mutex> lock(m);
    std::string dato = {};
    while (size == 0){
        if (fin){
            *termino = fin;
            return dato;
        }
        block_empty.wait(lock);
    }
    dato = cola.front();
    cola.pop();
    --this->size;
    return dato;
}


void SafeQueueString::end(){
    std::lock_guard<std::mutex> lock(m);
    fin = true;
    block_empty.notify_all();
}


SafeQueueString::~SafeQueueString(){
}
