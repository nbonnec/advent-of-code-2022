#include <algorithm>
#include <array>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ranges>
#include <set>
#include <source_location>

#include "config.hpp"
#include "misc.hpp"

namespace fs = std::filesystem;
namespace rng = std::ranges;

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
	auto ifs = getFile();

	for (std::string line; std::getline(ifs, line);) {
		std::string fourChars{};
		const auto it = rng::find_if(line, [&fourChars](auto c) {
			fourChars += std::string{c};
			if (fourChars.size() > 4) {
				fourChars.erase(fourChars.begin());
			}
			if (fourChars.size() == 4) {
				const auto s = std::set<char>{fourChars.begin(), fourChars.end()};
				return s.size() == 4;
			}
			return false;
		});
		std::cout << std::distance(line.begin(), it) + 1 << ' ';
	}

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
