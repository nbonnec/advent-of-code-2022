#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ranges>
#include <source_location>
#include <string>
#include <vector>

namespace fs = std::filesystem;

int main() {
	const auto thisSourceLocation = std::source_location::current();
	const auto samplePath = fs::path{thisSourceLocation.file_name()}.parent_path() / "input.txt";
	auto ifs = std::ifstream{samplePath, std::ios::in};

	std::vector<int> elfBackpack{};

	int sum{};
	for (std::string line; std::getline(ifs, line);) {
		if (line.empty()) {
			elfBackpack.emplace_back(sum);
			sum = 0;
		} else {
			int calories{};
			auto iss = std::istringstream{line};
			iss >> calories;
			sum += calories;
		}
	}

	std::cout << std::ranges::max(elfBackpack);
}