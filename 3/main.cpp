#include <filesystem>
#include <iostream>
#include <source_location>

#include "config.hpp"

namespace fs = std::filesystem;

// Config
// TODO return the file directly
const auto filePath = []() {
	const auto thisFileName = std::source_location::current().file_name();
	const std::string inputName = details::config::useSample() ? "sample.txt" : "input.txt";
	return fs::path{thisFileName}.parent_path() / inputName;
}();

int main() {
	std::cout << filePath;
	return 0;
}