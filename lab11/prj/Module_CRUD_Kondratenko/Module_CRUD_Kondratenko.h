#ifndef MODULE_CRUD_KONDRATENKO_H
#define MODULE_CRUD_KONDRATENKO_H

#include "struct_type_project_2.h"
#include <string>

using namespace std;

bool addRecord(Node*& head);
bool printAllRecords(Node* head, bool toFile = false, const string& filename = "");

#endif // MODULE_CRUD_KONDRATENKO_H
