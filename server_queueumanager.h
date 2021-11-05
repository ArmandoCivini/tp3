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
    bool queueExiste(const std::string& nombre);
public:
    QueueManager();
    std::string popIn(const std::string& nombre);
    void pushIn(const std::string& nombre, const std::string& mensaje);
    void nuevaQueue(const std::string& nombre);
    ~QueueManager();
};

#endif
