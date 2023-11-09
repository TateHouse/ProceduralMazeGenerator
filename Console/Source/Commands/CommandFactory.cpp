#include "Commands/CommandFactory.hpp"

#include "Commands/ExportCommand.hpp"
#include "Commands/GridCommand.hpp"
#include "Commands/QuitCommand.hpp"

namespace Console {
CommandFactory::CommandFactory(Console::Context& context) noexcept: context {context} {

}

std::unique_ptr<Command> CommandFactory::create(const std::string& name) const noexcept {
    if (name == "export") {
        return std::make_unique<ExportCommand>(context);
    }

    if (name == "grid") {
        return std::make_unique<GridCommand>(context);
    }

    if (name == "quit") {
        return std::make_unique<QuitCommand>(context);
    }
}
}