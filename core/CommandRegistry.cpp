#include "CommandRegistry.h"
#include <iostream>

CommandRegistry& CommandRegistry::instance() {
    static CommandRegistry instance;
    return instance;
}

void CommandRegistry::registerCommand(const std::string& name, std::unique_ptr<Command> cmd) {
    if (commands.find(name) != commands.end()) {
        std::cerr << "Command '" << name << "' already exists!\n";
        return;
    }
    commands[name] = std::move(cmd);
}

Command* CommandRegistry::getCommand(const std::string& name) {
    auto it = commands.find(name);
    if (it != commands.end())
        return it->second.get();
    return nullptr;
}
