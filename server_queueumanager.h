#ifndef SERVER_QUEUEMANAGER_H
#define SERVER_QUEUEMANAGER_H

#include "server_safequeuestring.h"
#include <vector>
#include <string>
#include <memory>

class QueueManager
{
private:
    std::vector<std::shared_ptr<SafeQueueString>> colas;
    std::mutex m;
    bool queueExiste(std::string nombre);
public:
    QueueManager();
    std::string popIn(std::string nombre);
    void pushIn(std::string nombre, std::string mensaje);
    void nuevaQueue(std::string nombre);
    ~QueueManager();
};

#endif
