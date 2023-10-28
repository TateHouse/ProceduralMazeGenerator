#pragma once

#include <filesystem>
#include <fstream>
#include <string>

namespace Renderer::Utility {
class FileLoader final {
public:
    explicit FileLoader(const std::filesystem::path& filePath) noexcept;

public:
    [[nodiscard]] std::string load() noexcept;
    void close() noexcept;

private:
    std::ifstream fileStream {};
};
}