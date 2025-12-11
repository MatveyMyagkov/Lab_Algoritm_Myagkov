#ifndef NETWORK_H
#define NETWORK_H

#include "Pipe.h"
#include "CS.h"
#include <map>
#include <vector>
#include <set>
#include <queue>
#include <limits>
#include <algorithm>
#include <cmath>

struct Connection {
    int pipeID;
    int sourceCS;
    int destinationCS;
    bool isConnected;
    static const double infinity;
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
    
    static const double performanceCoefficient;
    
    static const double infinity;
    
    static const std::vector<int> allowedDiameters;
    
    static const std::map<int, double> diameterPerformance;

    bool hasCycleDFS(int node, std::set<int>& visited, std::set<int>& recursionStack) const;
    void topologicalSortDFS(int node, std::set<int>& visited, std::vector<int>& result) const;
    
    double calculatePipePerformance(int pipeID) const;
    double calculatePipeWeight(int pipeID) const;
    bool bfsForMaxFlow(int source, int sink, std::map<int, int>& parent) const;
    std::vector<int> dijkstraShortestPath(int start, int end) const;

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
    
    double calculateMaxFlow(int source, int sink) const;
    std::pair<double, std::vector<int>> findShortestPath(int start, int end) const;
    double getPipePerformance(int pipeID) const;
    double getPipeWeight(int pipeID) const;
    static double getInfinity() { return infinity; }
    const std::map<int, std::vector<Connection>>& getAdjacencyList() const { return adjacencyList; }
};

#endif