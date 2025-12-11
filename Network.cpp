#include "Network.h"
#include <iostream>
#include <algorithm>
#include <queue>
#include <cmath>

const std::vector<int> GasNetwork::allowedDiameters = { 500, 700, 1000, 1400 };

const std::map<int, double> GasNetwork::diameterPerformance = {
    {500, 1500.0},
    {700, 3000.0},
    {1000, 6000.0},
    {1400, 12000.0}
};

const double GasNetwork::performanceCoefficient = 1000.0;
const double GasNetwork::infinity = 1e100;

GasNetwork::GasNetwork(const std::map<int, Pipe>& pipes, const std::map<int, CS>& css)
    : pipesRef(pipes), cssRef(css) {
}

std::vector<int> GasNetwork::getAvailableDiameters() const {
    return allowedDiameters;
}

bool GasNetwork::isPipeUsed(int pipeID) const {
    return usedPipes.find(pipeID) != usedPipes.end();
}

double GasNetwork::calculatePipePerformance(int pipeID) const {
    auto pipeIt = pipesRef.find(pipeID);
    if (pipeIt == pipesRef.end()) {
        return 0.0;
    }

    const Pipe& pipe = pipeIt->second;

    if (pipe.getStatus()) {
        return 0.0;
    }

    auto perfIt = diameterPerformance.find(pipe.getDiameter());
    if (perfIt != diameterPerformance.end()) {
        return perfIt->second;
    }

    double diameterM = pipe.getDiameter() / 1000.0;
    double lengthKm = pipe.getLength();
    double lengthM = lengthKm * 1000.0;

    if (lengthM <= 0) {
        return 0.0;
    }

    double performance = performanceCoefficient * sqrt(pow(diameterM, 5) / lengthM);
    return performance;
}

double GasNetwork::calculatePipeWeight(int pipeID) const {
    auto pipeIt = pipesRef.find(pipeID);
    if (pipeIt == pipesRef.end()) {
        return infinity;
    }

    const Pipe& pipe = pipeIt->second;

    if (pipe.getStatus()) {
        return infinity;
    }

    return pipe.getLength();
}

bool GasNetwork::connectCS(int sourceCS, int destinationCS, int diameter) {
    if (cssRef.find(sourceCS) == cssRef.end() || cssRef.find(destinationCS) == cssRef.end()) {
        std::cout << "Ошибка: Одна или обе КС не существуют!" << std::endl;
        return false;
    }

    if (std::find(allowedDiameters.begin(), allowedDiameters.end(), diameter) == allowedDiameters.end()) {
        std::cout << "Ошибка: Диаметр " << diameter << " мм не поддерживается!" << std::endl;
        std::cout << "Допустимые диаметры: ";
        for (int d : allowedDiameters) std::cout << d << " ";
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
        << " (труба ID: " << foundPipeID << ", производительность: "
        << calculatePipePerformance(foundPipeID) << " м³/ч)" << std::endl;
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
        auto csIt = cssRef.find(node.first);
        std::cout << "КС " << node.first;
        if (csIt != cssRef.end()) {
            std::cout << " (" << csIt->second.getName() << ")";
        }
        std::cout << " соединена с:" << std::endl;

        for (const auto& conn : node.second) {
            auto pipeIt = pipesRef.find(conn.pipeID);
            auto destCSIt = cssRef.find(conn.destinationCS);

            if (pipeIt != pipesRef.end()) {
                std::cout << "  -> КС " << conn.destinationCS;
                if (destCSIt != cssRef.end()) {
                    std::cout << " (" << destCSIt->second.getName() << ")";
                }
                std::cout << " (труба ID: " << conn.pipeID
                    << ", диаметр: " << pipeIt->second.getDiameter() << " мм"
                    << ", длина: " << pipeIt->second.getLength() << " км"
                    << ", производительность: " << calculatePipePerformance(conn.pipeID) << " м³/ч"
                    << ", вес: " << calculatePipeWeight(conn.pipeID) << " км)" << std::endl;
            }
        }
    }

    std::cout << "Всего соединений: " << usedPipes.size() << std::endl;
}
// BFS (поиск в ширину) для алгоритма Форда-Фалкерсона
bool GasNetwork::bfsForMaxFlow(int source, int sink, std::map<int, int>& parent) const {
    std::set<int> visited;
    std::queue<int> q;

    q.push(source);
    visited.insert(source);
    parent[source] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        auto it = adjacencyList.find(u);
        if (it != adjacencyList.end()) {
            for (const auto& conn : it->second) {
                int v = conn.destinationCS;

                if (visited.find(v) == visited.end() && calculatePipePerformance(conn.pipeID) > 0) {
                    parent[v] = u;
                    visited.insert(v);
                    q.push(v);

                    if (v == sink) {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

double GasNetwork::calculateMaxFlow(int source, int sink) const {
    if (cssRef.find(source) == cssRef.end() || cssRef.find(sink) == cssRef.end()) {
        std::cout << "Ошибка: КС источника или стока не существует!" << std::endl;
        return 0.0;
    }

    if (source == sink) {
        std::cout << "Ошибка: Источник и сток совпадают!" << std::endl;
        return 0.0;
    }

    std::cout << "\n=== Отладочная информация ===" << std::endl;
    std::cout << "Ищем путь от КС " << source << " до КС " << sink << std::endl;

    std::cout << "Содержимое adjacencyList:" << std::endl;
    for (const auto& node : adjacencyList) {
        std::cout << "  КС " << node.first << " соединена с: ";
        for (const auto& conn : node.second) {
            std::cout << "КС " << conn.destinationCS << " ";
        }
        std::cout << std::endl;
    }

    std::map<int, std::map<int, double>> capacity;

    std::cout << "Матрица пропускных способностей:" << std::endl;
    for (const auto& node : adjacencyList) {
        int u = node.first;
        for (const auto& conn : node.second) {
            int v = conn.destinationCS;
            double perf = calculatePipePerformance(conn.pipeID);
            capacity[u][v] = perf;
            std::cout << "  КС " << u << " -> КС " << v << ": " << perf << " м3/ч" << std::endl;
        }
    }

    double maxFlow = 0.0;
    int iteration = 0;

    while (true) {
        iteration++;
        std::cout << "\nИтерация " << iteration << ":" << std::endl;

        // BFS для поиска пути
        std::map<int, int> parent;
        std::queue<int> q;
        std::set<int> visited;

        q.push(source);
        visited.insert(source);
        parent[source] = -1;

        bool found = false;
        while (!q.empty()) {
            int u = q.front();
            q.pop();

            std::cout << "  Обрабатываем КС " << u << std::endl;

            // Проверка всех соседей u
            if (capacity.find(u) != capacity.end()) {
                for (const auto& neighbor : capacity[u]) {
                    int v = neighbor.first;
                    double cap = neighbor.second;

                    std::cout << "    КС " << u << " -> КС " << v << " (пропускная способность: " << cap << ")" << std::endl;

                    if (visited.find(v) == visited.end() && cap > 0) {
                        std::cout << "    Нашли доступное соединение!" << std::endl;
                        parent[v] = u;
                        visited.insert(v);
                        q.push(v);

                        if (v == sink) {
                            std::cout << "    Достигли стока КС " << sink << "!" << std::endl;
                            found = true;
                            break;
                        }
                    }
                }
            }

            if (found) break;
        }

        if (!found) {
            std::cout << "Путь не найден. Завершение алгоритма." << std::endl;
            break;
        }

        std::vector<int> path;
        for (int v = sink; v != source; v = parent[v]) {
            path.push_back(v);
        }
        path.push_back(source);
        std::reverse(path.begin(), path.end());

        std::cout << "Найден путь: ";
        for (size_t i = 0; i < path.size(); i++) {
            std::cout << "КС " << path[i];
            if (i < path.size() - 1) std::cout << " -> ";
        }
        std::cout << std::endl;

        double pathFlow = infinity;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = std::min(pathFlow, capacity[u][v]);
        }

        std::cout << "Минимальная пропускная способность на пути: " << pathFlow << " м3/ч" << std::endl;

        if (pathFlow <= 0) {
            std::cout << "Путь имеет нулевую пропускную способность!" << std::endl;
            break;
        }

        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            capacity[u][v] -= pathFlow;
            capacity[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
        std::cout << "Текущий максимальный поток: " << maxFlow << " м3/ч" << std::endl;
    }

    std::cout << "Итоговый максимальный поток: " << maxFlow << " м3/ч" << std::endl;
    std::cout << "=== Конец отладочной информации ===\n" << std::endl;

    return maxFlow;
}

std::vector<int> GasNetwork::dijkstraShortestPath(int start, int end) const {
    std::map<int, double> distances;
    std::map<int, int> previous;
    std::set<int> visited;

    for (const auto& node : adjacencyList) {
        distances[node.first] = infinity;
    }
    for (const auto& cs : cssRef) {
        distances[cs.first] = infinity;
    }

    distances[start] = 0.0;

    auto cmp = [&distances](int a, int b) { return distances[a] > distances[b]; };
    std::priority_queue<int, std::vector<int>, decltype(cmp)> pq(cmp);
    pq.push(start);

    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();

        if (visited.find(u) != visited.end()) {
            continue;
        }

        visited.insert(u);

        if (u == end) {
            break;
        }

        auto it = adjacencyList.find(u);
        if (it != adjacencyList.end()) {
            for (const auto& conn : it->second) {
                int v = conn.destinationCS;
                double weight = calculatePipeWeight(conn.pipeID);

                if (distances[u] + weight < distances[v]) {
                    distances[v] = distances[u] + weight;
                    previous[v] = u;
                    pq.push(v);
                }
            }
        }
    }

    std::vector<int> path;
    if (distances[end] == infinity) {
        return path;
    }

    for (int at = end; at != start; at = previous[at]) {
        path.push_back(at);
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());

    return path;
}

std::pair<double, std::vector<int>> GasNetwork::findShortestPath(int start, int end) const {
    if (cssRef.find(start) == cssRef.end() || cssRef.find(end) == cssRef.end()) {
        std::cout << "Ошибка: КС старта или финиша не существует!" << std::endl;
        return { infinity, {} };
    }

    if (start == end) {
        std::cout << "Старт и финиш совпадают!" << std::endl;
        return { 0.0, {start} };
    }

    std::vector<int> path = dijkstraShortestPath(start, end);

    if (path.empty()) {
        return { infinity, {} };
    }

    double totalDistance = 0.0;
    for (size_t i = 0; i < path.size() - 1; i++) {
        int u = path[i];
        int v = path[i + 1];

        auto it = adjacencyList.find(u);
        if (it != adjacencyList.end()) {
            for (const auto& conn : it->second) {
                if (conn.destinationCS == v) {
                    totalDistance += calculatePipeWeight(conn.pipeID);
                    break;
                }
            }
        }
    }

    return { totalDistance, path };
}

double GasNetwork::getPipePerformance(int pipeID) const {
    return calculatePipePerformance(pipeID);
}

double GasNetwork::getPipeWeight(int pipeID) const {
    return calculatePipeWeight(pipeID);
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

bool GasNetwork::isPipeUsedInNetwork(int pipeID) const {
    return isPipeUsed(pipeID);
}


