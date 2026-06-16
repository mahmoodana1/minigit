#include "AddCommand.h"
#include "../core/CommandRegistry.h"
#include <iostream>

void AddCommand::execute(const std::string& args) {
    std::cout << "Running AddCommand with args: " << args << std::endl;
}

namespace {
    struct AddCommandRegistrar {
        AddCommandRegistrar() {
            CommandRegistry::instance().registerCommand("add", std::make_unique<AddCommand>());
        }
    };
    static AddCommandRegistrar registrar;
}
