
#include <filesystem>
#include <fmt/core.h>
#include <fstream>
#include <numeric>
#include <regex>
#include <source_location>
#include <string>

namespace fs = std::filesystem;

[[nodiscard]] static std::filesystem::path
getInput(const int part, std::source_location loc = std::source_location::current()) noexcept {
	const auto thisFileName = loc.file_name();
	const auto input = fmt::format("input.txt", part);
	return std::filesystem::path{loc.file_name()}.parent_path() / input;
}

// only 12 red cubes, 13 green cubes, and 14 blue cubes
static constexpr auto RED_MAX = 12;
static constexpr auto GREEN_MAX = 13;
static constexpr auto BLUE_MAX = 14;

static void partOne() {
	auto ifs = std::ifstream{getInput(1), std::ios::in};
	int gameIndex = 1;
	int sum = 0;
	for (std::string line{}; std::getline(ifs, line); gameIndex++) {
		fmt::print("{}\n", line);
		std::stringstream ss{line};

		bool valid = true;
		for (std::string part{}; std::getline(ss, part, ';');) {
			const std::regex reg{"([0-9]+) (red|blue|green)"};
			std::map<std::string, int> map{{"red", 0}, {"blue", 0}, {"green", 0}};
			for (auto i = std::sregex_iterator{part.begin(), part.end(), reg}; i != std::sregex_iterator{}; ++i) {
				if (i->size() == 3) {
					const auto color = (*i)[2];
					map[color] = std::stoi((*i)[1]);
				}
			}
			fmt::print("red is {}, blue is {}, green is {}\n", map["red"], map["blue"], map["green"]);
			if (map["red"] > RED_MAX || map["green"] > GREEN_MAX || map["blue"] > BLUE_MAX) {
				valid = false;
				break;
			}
		}
		if (valid) {
			fmt::print("Add {}\n", gameIndex);
			sum += gameIndex;
		}
	}
	fmt::print("Sum is {}\n", sum);
}

static void partTwo() {
	auto ifs = std::ifstream{getInput(1), std::ios::in};
	int sum = 0;
	for (std::string line{}; std::getline(ifs, line);) {
		fmt::print("{}\n", line);
		std::stringstream ss{line};

		std::map<std::string, int> map{{"red", 0}, {"blue", 0}, {"green", 0}};
		for (std::string part{}; std::getline(ss, part, ';');) {
			const std::regex reg{"([0-9]+) (red|blue|green)"};
			for (auto i = std::sregex_iterator{part.begin(), part.end(), reg}; i != std::sregex_iterator{}; ++i) {
				if (i->size() == 3) {
					const auto color = (*i)[2];
					map[color] = std::max(map[color], std::stoi((*i)[1]));
				}
			}
		}
		sum += std::accumulate(map.begin(), map.end(), 1, [](int acc, const auto& elem) { return acc * elem.second; });
	}
	fmt::print("Sum is {}\n", sum);
}

int main() {
	// partOne();
	partTwo();
}