#include "core/CommandRegistry.h"
#include <iostream>

int main() {
    std::string name;
    std::cout << "Enter command: ";
    std::cin >> name;

    auto* cmd = CommandRegistry::instance().getCommand(name);
    if (cmd)
        cmd->execute("example.txt");
    else
        std::cout << "Command not found!\n";
}
