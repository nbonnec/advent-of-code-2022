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

static int getPriority(char c) {
	return islower(c) ? c - 'a' + 1 : c - 'A' + 1 + 26;
}

static int partOne() {
	auto ifs = getFile();

	int sum{};
	for (std::string line; std::getline(ifs, line);) {
		const auto midpoint = line.size() / 2;
		const auto it =
			std::find_first_of(line.begin(), line.begin() + midpoint, line.begin() + midpoint + 1, line.end());
		sum += getPriority(*it);
	}
	return sum;
}

static int partTwo() {
	auto ifs = getFile();

	int sum{};
	while (!ifs.eof()) {
		// Take 3 lines
		std::array<std::string, 3> lines{};
		for (auto& line : lines) {
			std::getline(ifs, line);
		}

		// Find same letters in first and second line
		std::string sames{};
		for (int offset{};;) {
			const auto it =
				std::find_first_of(lines[0].begin() + offset, lines[0].end(), lines[1].begin(), lines[1].end());
			if (it == lines[0].end()) {
				break;
			}
			sames += *it;
			offset = std::distance(lines[0].begin(), it + 1);
		}

		// Find those letters in the third line
		const auto it = std::ranges::find_first_of(sames, lines[2]);
		if (it != lines[2].end()) {
			sum += getPriority(*it);
		}
	}

	return sum;
}

int main() {
	std::cout << "Part one: " << partOne() << '\n';
	std::cout << "Part two: " << partTwo() << '\n';
	return 0;
}
