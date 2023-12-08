#include <algorithm>
#include <filesystem>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <fstream>
#include <iostream>
#include <ranges>
#include <set>
#include <source_location>
#include <vector>

#include "config.hpp"
#include "misc.hpp"

namespace fs = std::filesystem;
namespace rng = std::ranges;
namespace vws = std::views;

static std::ifstream getFile() {
	const auto thisFileName = std::source_location::current().file_name();
	const auto inputName = details::config::useSample() ? "sample.txt" : "input.txt";
	const auto filePath = fs::path{thisFileName}.parent_path() / inputName;
	return {filePath, std::ios::in};
}

using Trees = std::vector<std::vector<int>>;
using Coordinates = std::pair<int, int>;
using Visible = std::vector<Coordinates>;

static void drawVisible(const Trees& trees, const Visible& visible) { // Draw the visible trees!
	for (int r{}; r < trees.size(); r++) {
		for (int c{}; c < trees[r].size(); c++) {
			const auto v =
				rng::find_if(visible, [r, c](const auto& pair) { return pair.first == r && pair.second == c; });
			std::cout << (v == visible.end() ? ' ' : '*');
		}
		std::cout << '\n';
	}
}
static int partOne(const Trees& trees, Visible& visible) {

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

	drawVisible(trees, visible);

	return s.size();
}

static int partTwo(const Trees& trees, const Visible& visible) {
	std::vector<std::size_t> scenicViews{};
	for (int rowIndex{}; rowIndex < trees.size(); rowIndex++) {
		const auto& row = trees[rowIndex];
		for (int columnIndex{}; columnIndex < row.size(); columnIndex++) {
			const auto rowIt = row.begin() + columnIndex;
			fmt::print("Row {}, column {}, value {}\n", rowIndex, columnIndex, *rowIt);

			std::size_t scenicView{1};
			// Looking up is like looking left in the column
			{
				int count{};
				if (rowIndex >= 0) {
					for (int r = rowIndex - 1; r >= 0; r--) {
						count++;
						if (*rowIt <= trees[r][columnIndex]) {
							break;
						}
					}
				}
				fmt::print("up {}\n", count);
				scenicView *= count;
			}
			// Looking left
			{
				int count{};
				if (columnIndex >= 0) {
					for (int c = columnIndex - 1; c >= 0; c--) {
						count++;
						if (*rowIt <= trees[rowIndex][c]) {
							break;
						}
					}
				}
				fmt::print("left {}\n", count);
				scenicView *= count;
			}
			// Looking right
			{
				int count{};
				if (columnIndex < row.size() - 1) {
					for (int c = columnIndex + 1; c < row.size(); c++) {
						count++;
						if (*rowIt <= trees[rowIndex][c]) {
							break;
						}
					}
				}
				fmt::print("right {}\n", count);
				scenicView *= count;
			}

			// Looking down is like looking right in the column
			{
				int count{};
				if (rowIndex < row.size() - 1) {
					for (int r = rowIndex + 1; r < trees.size(); r++) {
						count++;
						if (*rowIt <= trees[r][columnIndex]) {
							break;
						}
					}
				}
				fmt::print("down {}\n", count);
				scenicView *= count;
			}
			fmt::print("\n");
			scenicViews.emplace_back(scenicView);
		}
	}
	return *rng::max_element(scenicViews);
}

int main() {
	auto ifs = getFile();

	Trees trees;

	for (std::string line; std::getline(ifs, line);) {
		std::vector<int> lineTrees;
		rng::transform(line, std::back_inserter(lineTrees), [](auto c) -> int { return c - '0'; });
		trees.emplace_back(lineTrees);
	}

	Visible visible{};

	//	std::cout << "Part one: " << partOne(trees, visible) << '\n';
	std::cout << "Part two:\n " << partTwo(trees, visible) << '\n';
	return 0;
}
