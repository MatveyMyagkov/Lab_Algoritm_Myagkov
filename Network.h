#ifndef NETWORK_H
#define NETWORK_H

#include "Pipe.h"
#include "CS.h"
#include <map>
#include <vector>
#include <set>

struct Connection {
    int pipeID;
    int sourceCS;
    int destinationCS;
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
    

    bool hasCycleDFS(int node, std::set<int>& visited, std::set<int>& recursionStack) const;
    void topologicalSortDFS(int node, std::set<int>& visited, std::vector<int>& result) const;

public:
    GasNetwork(const std::map<int, Pipe>& pipes, const std::map<int, CS>& css);

    bool connectCS(int sourceCS, int destinationCS, int diameter);
    bool disconnectPipe(int pipeID);
    void displayNetwork() const;
    bool isPipeUsed(int pipeID) const;
    std::vector<int> getAvailableDiameters() const;
    bool isPipeUsedInNetwork(int pipeID) const;
    std::vector<int> topologicalSort() const;
    bool hasCycle() const;

    const std::map<int, std::vector<Connection>>& getAdjacencyList() const { return adjacencyList; }
};

#endif