#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ranges>
#include <source_location>

#include "config.hpp"

namespace fs = std::filesystem;
namespace rng = std::ranges;
namespace vws = std::views;

static std::ifstream getFile() {
	const auto thisFileName = std::source_location::current().file_name();
	const auto inputName = details::config::useSample() ? "sample.txt" : "input.txt";
	const auto filePath = fs::path{thisFileName}.parent_path() / inputName;
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
