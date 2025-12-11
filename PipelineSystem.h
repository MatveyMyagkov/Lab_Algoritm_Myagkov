#ifndef PIPELINESYSTEM_H
#define PIPELINESYSTEM_H

#include "Pipe.h"
#include "CS.h"
#include "Network.h"
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <fstream>

extern std::map<int, Pipe> pipes;
extern std::map<int, CS> css;

extern GasNetwork gasNetwork;
void TopologicalSort();
void Addpipe();
void Addcs();
void ViewAllObjects();
void EditPipe();
void EditCS();
void RemoveAnyObjectByID();
void SaveToCustomFile();
void LoadFromCustomFile();
void SearchCS();
void SearchPipesWithBatchOperations();
void ConnectCSWithPipe();
void DisplayGasNetwork();
void DisconnectPipeFromNetwork();
void TopologicalSort();
void CalculateMaxFlow();
void FindShortestPath();
#endif