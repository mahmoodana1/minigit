#pragma once
#include <filesystem>

void transferDirToDir(std::filesystem::path src, std::filesystem::path des,
                      bool inMainDir = false);
