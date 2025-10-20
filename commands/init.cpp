#include "commands.h"
#include <filesystem>
#include <iostream>

void repoInit() {
    if (std::filesystem::exists(".minigit")) {
        std::cout << "Repo already initialized.\n";
        return;
    }

    std::filesystem::create_directory(".minigit");
    std::filesystem::create_directory(".minigit/addedFiles");
    std::filesystem::create_directory(".minigit/commits");
    std::filesystem::create_directory(".minigit/logs");

    std::cout << "Repo initialized";
}
