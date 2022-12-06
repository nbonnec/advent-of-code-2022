#include <algorithm>
#include <filesystem>
#include <fstream>
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
	auto ifs = std::ifstream{filePath, std::ios::in};

	int sum{};
	for (std::string line; std::getline(ifs, line);) {
		const auto midpoint = line.size() / 2;
		const auto it =
			std::find_first_of(line.begin(), line.begin() + midpoint, line.begin() + midpoint + 1, line.end());
		const auto priority = std::islower(*it) ? *it - 'a' + 1 : *it - 'A' + 1 + 26;
		sum += priority;
	}

	return sum;
}