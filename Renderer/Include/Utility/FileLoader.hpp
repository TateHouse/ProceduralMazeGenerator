#pragma once

#include <filesystem>
#include <fstream>
#include <string>

namespace Renderer::Utility {
class FileLoader final {
public:
	explicit FileLoader(const std::filesystem::path& filePath);
	FileLoader(const FileLoader& other) = delete;
	FileLoader(FileLoader&& other) noexcept = default;
	~FileLoader() noexcept = default;

public:
	FileLoader& operator=(const FileLoader& other) = delete;
	FileLoader& operator=(FileLoader&& other) noexcept = default;

public:
	std::string load();

private:
	std::ifstream fileStream {};
};
}