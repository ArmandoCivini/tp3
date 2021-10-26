#ifndef _SAFEQUEUESTRING_H
#define _SAFEQUEUESTRING_H

#include <queue>
#include <mutex>
#include <condition_variable>

class SafeQueueString
{
private:
    std::queue<std::string> cola;
    std::mutex m;
    std::condition_variable block_empty;
    int size;
    bool fin;
    char *nombre;
public:
    SafeQueueString(char *is_nombre);
    bool isNombre(char *nombre);
    void push(std::string dato);
    std::string pop(bool *termino);
    void end();
    ~SafeQueueString();
};



#endif
