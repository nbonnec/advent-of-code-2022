#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ranges>
#include <set>
#include <source_location>
#include <vector>

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
	auto ifs = getFile();

	std::cout << '\n';

	std::vector<std::vector<int>> trees;
	for (std::string line; std::getline(ifs, line);) {
		std::vector<int> lineTrees;
		rng::transform(line, std::back_inserter(lineTrees), [](auto c) -> int { return c - '0'; });
		trees.emplace_back(lineTrees);
	}

	using Coordinates = std::pair<int, int>;
	std::vector<Coordinates> visible{};

	// Borders are all visible
	for (auto row : vws::iota(0, int(trees.size()))) {
		visible.emplace_back(row, 0);
		visible.emplace_back(row, trees[0].size() - 1);
	}

	// Borders are all visible
	for (auto colum : vws::iota(0, int(trees[0].size()))) {
		visible.emplace_back(0, colum);
		visible.emplace_back(trees.size() - 1, colum);
	}

	//
	//
	//       ┌──────────┐
	// ────► │          │
	//       │          │
	//       │          │
	//       └──────────┘
	//
	//
	for (int rowIndex{}; const auto& row : trees) {
		auto max{0};
		for (int columnIndex{}; auto height : row) {
			if (height > max) {
				visible.emplace_back(rowIndex, columnIndex);
				max = height;
			}
			columnIndex++;
		}
		rowIndex++;
	}

	//
	//
	//       ┌──────────┐
	//       │          │ ◄───
	//       │          │
	//       │          │
	//       └──────────┘
	//
	//
	for (int rowIndex{}; const auto& row : trees) {
		auto max{0};
		for (int columnIndex = row.size() - 1; auto height : row | vws::reverse) {
			if (height > max) {
				visible.emplace_back(std::make_pair(rowIndex, columnIndex));
				max = height;
			}
			columnIndex--;
		}
		rowIndex++;
	}

	//        │
	//        ▼
	//       ┌──────────┐
	//       │          │
	//       │          │
	//       │          │
	//       └──────────┘
	//
	//
	for (int columnIndex{}; columnIndex < trees[0].size(); columnIndex++) {
		auto max{0};
		for (int rowIndex{}; rowIndex < trees.size(); rowIndex++) {
			if (const auto height = trees[rowIndex][columnIndex]; height > max) {
				visible.emplace_back(rowIndex, columnIndex);
				max = height;
			}
		}
	}

	//
	//
	//       ┌──────────┐
	//       │          │
	//       │          │
	//       │          │
	//       └──────────┘
	//        ▲
	//        │
	for (int columnIndex{}; columnIndex < trees[0].size(); columnIndex++) {
		auto max{0};
		for (int rowIndex = trees.size() - 1; rowIndex >= 0; rowIndex--) {
			if (const auto height = trees[rowIndex][columnIndex]; height > max) {
				visible.emplace_back(rowIndex, columnIndex);
				max = height;
			}
		}
	}
	const auto s = std::set(visible.begin(), visible.end());

	// Draw the visible trees!
	for (int r{}; r < trees.size(); r++) {
		for (int c{}; c < trees[r].size(); c++) {
			const auto v =
				rng::find_if(visible, [r, c](const auto& pair) { return pair.first == r && pair.second == c; });
			std::cout << (v == visible.end() ? ' ' : '*');
		}
		std::cout << '\n';
	}

	return s.size();
}

static int partTwo() {
	return 0;
}

int main() {
	std::cout << "Part one: " << partOne() << '\n';
	std::cout << "Part two: " << partTwo() << '\n';
	return 0;
}
