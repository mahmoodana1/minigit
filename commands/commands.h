#pragma once
#include <string>

void repoInit();
void fileAdd(const std::string &fileName);
void commitChanges(const std::string &message);
void showLog();
