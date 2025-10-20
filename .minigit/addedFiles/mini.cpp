#include "commands/commands.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Error, Usage: minigit <command> <option>\n";
        return 1;
    }

    std::string command = argv[1];

    if (command == "init") {
        repoInit();
    } else if (command == "add") {
        if (argc < 3) {
            std::cout << "Error, Usage: minigit add <option>\n";
            return 1;
        }

        fileAdd(argv[2]);
    } else if (command == "commit") {
        if (argc < 4) {
            std::cout << "Error, Usage: minigit commit -m \"...\"\n";
            return 1;
        }

        commitChanges(argv[3]);
    } else if (command == "log") {
        showLog();
    } else {
        std::cout << "Error, unknown";
        return 1;
    }
    return 0;
}
