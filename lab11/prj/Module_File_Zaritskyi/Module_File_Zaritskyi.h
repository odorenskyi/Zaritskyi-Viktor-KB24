#ifndef MODULE_FILE_ZARITSKYI_H
#define MODULE_FILE_ZARITSKYI_H

#include "struct_type_project_2.h"
#include <string>
#include <fstream>
#include <iostream>

bool loadDatabase(Node*& head, const std::string& filename);
bool saveDatabase(Node* head, const std::string& filename);

#endif // MODULE_FILE_ZARITSKYI_H
