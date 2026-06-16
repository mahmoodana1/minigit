#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include "Command.h"

class CommandRegistry {
public:
    static CommandRegistry& instance();
    void registerCommand(const std::string& name, std::unique_ptr<Command> cmd);
    Command* getCommand(const std::string& name);

private:
    std::unordered_map<std::string, std::unique_ptr<Command>> commands;
    CommandRegistry() = default;
    CommandRegistry(const CommandRegistry&) = delete;
    CommandRegistry& operator=(const CommandRegistry&) = delete;
};
