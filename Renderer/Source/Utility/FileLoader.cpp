#include "Utility/FileLoader.hpp"

#include <sstream>

namespace Renderer::Utility {
FileLoader::FileLoader(const std::filesystem::path& filePath) {
	if (!std::filesystem::exists(filePath)) {
		const auto message {std::format("ERROR: File does not exist: {}", filePath.string())};
		throw std::filesystem::filesystem_error(message, std::make_error_code(std::errc::no_such_file_or_directory));
	}
	
	fileStream.open(filePath, std::ios::in);
	if (!fileStream.is_open()) {
		const auto message {std::format("ERROR: Failed to open file: {}", filePath.string())};
		throw std::filesystem::filesystem_error(message, std::make_error_code(std::errc::io_error));
	}
	
	fileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
}

std::string FileLoader::load() {
	std::stringstream stringStream {};
	stringStream << fileStream.rdbuf();
	return stringStream.str();
}
}