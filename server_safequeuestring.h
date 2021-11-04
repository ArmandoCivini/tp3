#ifndef _SAFEQUEUESTRING_H
#define _SAFEQUEUESTRING_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>

class SafeQueueString
{
private:
    std::queue<std::string> cola;
    std::mutex m;
    std::condition_variable block_empty;
    int size;
    bool fin;
    std::string nombre;
public:
    explicit SafeQueueString(const std::string& is_nombre);
    bool isNombre(const std::string& nombre);
    void push(std::string dato);
    std::string pop(bool *termino);
    void end();
    ~SafeQueueString();
};



#endif
