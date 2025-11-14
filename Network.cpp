#include "Network.h"
#include <iostream>
#include <algorithm>

GasNetwork::GasNetwork(const std::map<int, Pipe>& pipes, const std::map<int, CS>& css)
    : pipesRef(pipes), cssRef(css) {
}

std::vector<int> GasNetwork::getAvailableDiameters() const {
    return { 500, 700, 1000, 1400 };
}

bool GasNetwork::isPipeUsed(int pipeID) const {
    return usedPipes.find(pipeID) != usedPipes.end();
}

bool GasNetwork::connectCS(int sourceCS, int destinationCS, int diameter) {
    if (cssRef.find(sourceCS) == cssRef.end() || cssRef.find(destinationCS) == cssRef.end()) {
        std::cout << "Ошибка: Одна или обе КС не существуют!" << std::endl;
        return false;
    }

    std::vector<int> diameters = getAvailableDiameters();
    if (std::find(diameters.begin(), diameters.end(), diameter) == diameters.end()) {
        std::cout << "Ошибка: Диаметр " << diameter << " мм не поддерживается!" << std::endl;
        std::cout << "Допустимые диаметры: ";
        for (int d : diameters) std::cout << d << " ";
        std::cout << "мм" << std::endl;
        return false;
    }

    int foundPipeID = -1;
    for (const auto& pipePair : pipesRef) {
        const Pipe& pipe = pipePair.second;
        if (!isPipeUsed(pipe.getID()) && pipe.getDiameter() == diameter) {
            foundPipeID = pipe.getID();
            break;
        }
    }

    if (foundPipeID == -1) {
        std::cout << "Свободная труба диаметром " << diameter << " мм не найдена." << std::endl;
        std::cout << "Необходимо создать новую трубу." << std::endl;
        return false;
    }

    Connection conn(foundPipeID, sourceCS, destinationCS);
    adjacencyList[sourceCS].push_back(conn);
    usedPipes.insert(foundPipeID);

    std::cout << "Соединение создано: КС " << sourceCS << " -> КС " << destinationCS
        << " (труба ID: " << foundPipeID << ")" << std::endl;
    return true;
}

bool GasNetwork::disconnectPipe(int pipeID) {
    for (auto& node : adjacencyList) {
        auto& connections = node.second;
        for (auto it = connections.begin(); it != connections.end(); ++it) {
            if (it->pipeID == pipeID) {
                connections.erase(it);
                usedPipes.erase(pipeID);
                std::cout << "Труба ID " << pipeID << " отключена от сети." << std::endl;
                return true;
            }
        }
    }
    return false;
}

void GasNetwork::displayNetwork() const {
    std::cout << "=== Газотранспортная сеть ===" << std::endl;

    if (adjacencyList.empty()) {
        std::cout << "Сеть пуста." << std::endl;
        return;
    }

    for (const auto& node : adjacencyList) {
        std::cout << "КС " << node.first << " соединена с:" << std::endl;
        for (const auto& conn : node.second) {
            auto pipeIt = pipesRef.find(conn.pipeID);
            if (pipeIt != pipesRef.end()) {
                std::cout << "  -> КС " << conn.destinationCS
                    << " (труба ID: " << conn.pipeID
                    << ", диаметр: " << pipeIt->second.getDiameter() << " мм)" << std::endl;
            }
        }
    }

    std::cout << "Всего соединений: " << usedPipes.size() << std::endl;
}
bool GasNetwork::hasCycleDFS(int node, std::set<int>& visited, std::set<int>& recursionStack) const {
    if (recursionStack.find(node) != recursionStack.end()) {
        return true;
    }
    if (visited.find(node) != visited.end()) {
        return false;
    }

    visited.insert(node);
    recursionStack.insert(node);

    auto it = adjacencyList.find(node);
    if (it != adjacencyList.end()) {
        for (const auto& conn : it->second) {
            if (hasCycleDFS(conn.destinationCS, visited, recursionStack)) {
                return true;
            }
        }
    }

    recursionStack.erase(node);
    return false;
}

bool GasNetwork::hasCycle() const {
    std::set<int> visited;
    std::set<int> recursionStack;

    for (const auto& node : adjacencyList) {
        if (hasCycleDFS(node.first, visited, recursionStack)) {
            return true;
        }
    }
    return false;
}

void GasNetwork::topologicalSortDFS(int node, std::set<int>& visited, std::vector<int>& result) const {
    visited.insert(node);

    auto it = adjacencyList.find(node);
    if (it != adjacencyList.end()) {
        for (const auto& conn : it->second) {
            if (visited.find(conn.destinationCS) == visited.end()) {
                topologicalSortDFS(conn.destinationCS, visited, result);
            }
        }
    }

    result.push_back(node);
}

std::vector<int> GasNetwork::topologicalSort() const {
    std::vector<int> result;
    std::set<int> visited;

    if (hasCycle()) {
        std::cout << "Предупреждение: Сеть содержит циклы! Топологическая сортировка невозможна для циклических графов." << std::endl;
        return result;
    }

    for (const auto& node : adjacencyList) {
        if (visited.find(node.first) == visited.end()) {
            topologicalSortDFS(node.first, visited, result);
        }
    }

    std::reverse(result.begin(), result.end());
    return result;
}
