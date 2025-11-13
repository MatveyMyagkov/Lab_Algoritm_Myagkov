#ifndef NETWORK_H
#define NETWORK_H

#include "Pipe.h"
#include "CS.h"
#include <map>
#include <vector>
#include <set>
#include <memory>

struct Connection {
    int pipeID;
    int sourceCS;    // КС входа
    int destinationCS; // КС выхода
    bool isConnected;

    Connection(int pipeId, int src, int dest)
        : pipeID(pipeId), sourceCS(src), destinationCS(dest), isConnected(true) {
    }
};

class GasNetwork {
private:
    std::map<int, std::vector<Connection>> adjacencyList;
    std::set<int> usedPipes;

    const std::map<int, Pipe>& pipesRef;
    const std::map<int, CS>& cssRef;

public:
    GasNetwork(const std::map<int, Pipe>& pipes, const std::map<int, CS>& css);

    bool connectCS(int sourceCS, int destinationCS, int diameter);
    bool disconnectPipe(int pipeID);
    void displayNetwork() const;
    bool isPipeUsed(int pipeID) const;
    std::vector<int> getAvailableDiameters() const;

    const std::map<int, std::vector<Connection>>& getAdjacencyList() const { return adjacencyList; }
};

#endif