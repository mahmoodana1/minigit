#pragma once
#include "../core/Command.h"

class AddCommand : public Command {
public:
    void execute(const std::string& args = "") override;
};
