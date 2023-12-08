#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <numeric>
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

	std::cout << "Part one\n";
	std::cout << std::ranges::max(elfBackpack) << '\n';

	std::ranges::sort(elfBackpack, std::ranges::greater{});
	const auto total = std::accumulate(elfBackpack.begin(), elfBackpack.begin() + 3, 0);

	std::cout << "Part two\n";
	std::cout << total << '\n';

	return 0;
}