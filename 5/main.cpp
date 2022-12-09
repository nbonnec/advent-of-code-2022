#include <algorithm>
#include <array>
#include <cassert>
#include <charconv>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <numeric>
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

struct Instruction {
	int count{};
	int from{};
	int to{};
};

using Instructions = std::vector<Instruction>;

static Instructions getInstructions() {
	auto ifs = getFile();

	// Seek to empty line
	for (std::string line; std::getline(ifs, line);) {
		if (line.empty()) {
			break;
		}
	}

	Instructions instructions{};
	for (std::string line; std::getline(ifs, line);) {
		std::vector<int> instr{};
		std::istringstream iss{line};
		for (std::string word; std::getline(iss, word, ' ');) {
			int result;
			auto [ptr, ec] = std::from_chars(word.data(), word.data() + word.size(), result);
			if (ec == std::errc{}) {
				instr.emplace_back(result);
			}
		}
		assert(instr.size() == 3);
		instructions.push_back({instr[0], instr[1], instr[2]});
	}

	return instructions;
}

static std::string partOne() {
	auto stacks = getStacks();

	for (auto instructions = getInstructions(); auto i : instructions) {
		auto& from = stacks[i.from - 1];
		auto& to = stacks[i.to - 1];
		auto toMove = from | std::views::reverse | std::views::take(i.count);
		to = std::accumulate(toMove.begin(), toMove.end(), to);
		from.erase(from.end() - i.count, from.end());
	}
	return std::accumulate(stacks.begin(), stacks.end(), std::string{},
						   [](const std::string& acc, const auto s) { return acc + s.back(); });
}

static int partTwo() {
	return 0;
}

int main() {
	std::cout << "Part one: " << partOne() << '\n';
	std::cout << "Part two: " << partTwo() << '\n';
	return 0;
}
