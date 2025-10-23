#ifndef PIPELINESYSTEM_H
#define PIPELINESYSTEM_H

#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "Pipe.h"
#include "CS.h"

extern std::map<int, Pipe> pipes;
extern std::map<int, CS> css;

std::string toLower(const std::string& str);
int getNextID();

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

void ChangePipeStatusByID(int id, bool newStatus);
void BatchChangePipeStatus(const std::vector<int>& pipeIDs, bool newStatus);
void BatchDeletePipes(const std::vector<int>& pipeIDs);

#endif