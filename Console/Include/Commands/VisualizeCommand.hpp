#pragma once

#include "Command.hpp"

namespace Console {
class VisualizeCommand final : public Command {
public:
	explicit VisualizeCommand(Context& context) noexcept;
	VisualizeCommand(const VisualizeCommand& other) noexcept = default;
	VisualizeCommand(VisualizeCommand&& other) noexcept = default;
	~VisualizeCommand() noexcept override = default;

public:
	VisualizeCommand& operator=(const VisualizeCommand& other) noexcept = delete;
	VisualizeCommand& operator=(VisualizeCommand&& other) noexcept = delete;

public:
	void execute(const std::unordered_map<std::string, std::string>& parameters) override;
	[[nodiscard]] std::string getName() const noexcept override;
	[[nodiscard]] std::string getDescription() const noexcept override;
};
}