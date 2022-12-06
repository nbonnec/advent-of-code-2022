#include <algorithm>
#include <array>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ranges>
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

	std::cout << "Using " << filePath << '\n';

	return {filePath, std::ios::in};
}

static auto splitStrings(const std::string& s, const char delim) {
	const auto mid = s.find(delim);
	const auto remainer = std::distance(s.begin() + mid, s.end());
	const auto s1 = s.substr(0, mid);
	const auto s2 = s.substr(mid + 1, remainer);
	return std::pair{s1, s2};
}

static auto getSectionsView(const std::string& s) {
	const auto [section1, section2] = splitStrings(s, '-');
	const auto beginSection = std::stoi(section1);
	const auto endSection = std::stoi(section2);
	return std::views::iota(beginSection, endSection + 1);
}

static int partOne() {
	auto ifs = getFile();

	int sum{};
	for (std::string line; std::getline(ifs, line);) {
		const auto [elf1, elf2] = splitStrings(line, ',');
		const auto v1 = getSectionsView(elf1);
		const auto v2 = getSectionsView(elf2);
		sum += !std::ranges::search(v1, v2).empty() || !std::ranges::search(v2, v1).empty();
	}

	return sum;
}

static int partTwo() {
	return 0;
}

int main() {
	std::cout << "Part one: " << partOne() << '\n';
	std::cout << "Part two: " << partTwo() << '\n';
	return 0;
}
