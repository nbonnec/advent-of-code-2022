#include <algorithm>
#include <array>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <source_location>

#include "config.hpp"

namespace fs = std::filesystem;

// Config
static std::ifstream getFile() {
	const auto filePath = []() {
		const auto thisFileName = std::source_location::current().file_name();
		const std::string inputName = details::config::useSample() ? "sample.txt" : "input.txt";
		return fs::path{thisFileName}.parent_path() / inputName;
	}();
	return {filePath, std::ios::in};
}

static int partOne() {
	return 0;
}

static int partTwo() {
	return 0;
}

int main() {
	std::cout << "Part one: " << partOne() << '\n';
	std::cout << "Part two: " << partTwo() << '\n';
	return 0;
}
