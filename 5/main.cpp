#include <algorithm>
#include <array>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ranges>
#include <source_location>
#include <vector>

#include "config.hpp"
#include "misc.hpp"

namespace fs = std::filesystem;
namespace rng = std::ranges;

using Crates = std::vector<std::string>;

// Config
static std::ifstream getFile() {
	const auto filePath = []() {
		const auto thisFileName = std::source_location::current().file_name();
		const std::string inputName = details::config::useSample() ? "sample.txt" : "input.txt";
		return fs::path{thisFileName}.parent_path() / inputName;
	}();
	return {filePath, std::ios::in};
}

static int offsetToStackIndex(int offset) {
	return offset / 4;
}

static Crates getStacks() {
	auto ifs = getFile();

	// Push lines of crates in a vector to process them in reverse after
	std::vector<std::string> cratesLines{};
	for (std::string line; std::getline(ifs, line);) {
		if (line.empty()) {
			break;
		}
		cratesLines.emplace_back(line);
	}

	// Now we have the lines with crates, make a vector representing stacks
	// First character of the stacks are the index, it is convenient to be sure an allocation is done for all stacks
	std::vector<std::string> stacks{};
	rng::transform(cratesLines.back() | std::views::filter(::isdigit), std::back_inserter(stacks),
						   [](auto const c) { return std::string{c}; });

	cratesLines.erase(cratesLines.end());

	// Now we process all lines bottom to top
	for (auto const& line : cratesLines | std::views::reverse) {
		for (int i{}; auto const c : line) {
			if (std::isupper(c)) {
				stacks[offsetToStackIndex(i)] += c;
			}
			i++;
		}
	}

	return stacks;
}

static int partOne() {
	auto stacks = getStacks();
	utils::printRange(stacks);
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
