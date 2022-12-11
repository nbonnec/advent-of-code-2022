#include <algorithm>
#include <charconv>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <ranges>
#include <source_location>
#include <variant>
#include <vector>

#include "config.hpp"
#include "misc.hpp"

namespace fs = std::filesystem;
namespace rng = std::ranges;

static std::ifstream getFile() {
	const auto thisFileName = std::source_location::current().file_name();
	const auto inputName = details::config::useSample() ? "sample.txt" : "input.txt";
	const auto filePath = fs::path{thisFileName}.parent_path() / inputName;
	return {filePath, std::ios::in};
}

struct ChangeDirectoryCommand {
	std::string name;
};

struct ListCommand {};

struct DirEntry {
	std::string name;
};

struct FileEntry {
	int size;
	std::string name;
};

using Parsed = std::variant<ChangeDirectoryCommand, ListCommand, DirEntry, FileEntry>;

[[nodiscard]] static Parsed parseLine(const std::string& line) {
	if (line.starts_with("$")) {
		if (line.starts_with("$ ls")) {
			return ListCommand{};
		} else {
			// $ cd
			std::istringstream iss{line};
			std::string prompt;
			std::string command;
			std::string dir;
			iss >> prompt >> command >> dir;
			return ChangeDirectoryCommand{dir};
		}
	} else if (line.starts_with("dir")) {
		std::istringstream iss{line};
		std::string command;
		std::string name;
		iss >> command >> name;
		return DirEntry{name};
	} else {
		std::istringstream iss{line};
		int size{};
		std::string name;
		iss >> size >> name;
		return FileEntry{size, name};
	}
}

inline std::ostream& operator<<(std::ostream& os, const Parsed& parsed) {
	std::visit(utils::Overload{[&os](const ChangeDirectoryCommand& cdCommand) { os << "$ cd " << cdCommand.name; },
							   [&os](const ListCommand&) { os << "$ ls"; },
							   [&os](const DirEntry& dir) { os << "dir " << dir.name; },
							   [&os](const FileEntry& file) { os << file.size << ' ' << file.name; }},
			   parsed);
	return os;
}

using Sizes = std::vector<int>;

static int getDirSize(std::ifstream& ifs, Sizes& sizes) {
	int currentDirSize{};

	for (std::string line{}; std::getline(ifs, line);) {
		const auto parsed = parseLine(line);
		if (auto cd = std::get_if<ChangeDirectoryCommand>(&parsed)) {
			if (cd->name == "..") {
				return currentDirSize;
			} else {
				const auto childDirSize = getDirSize(ifs, sizes);
				sizes.emplace_back(childDirSize);
				currentDirSize += childDirSize;
			}
		} else if (auto fileEntry = std::get_if<FileEntry>(&parsed)) {
			currentDirSize += fileEntry->size;
		}
	}

	return currentDirSize;
}

int main() {
	auto ifs = getFile();
	Sizes sizes;
	getDirSize(ifs, sizes);

	auto lessThan100K = sizes | std::views::filter([](const auto s) { return s < 100000; });
	std::cout << "Part one: " << std::accumulate(lessThan100K.begin(), lessThan100K.end(), int{}) << '\n';

	const auto needed = 30'000'000 - (70'000'000 - sizes.back());
	auto bigEnoughDirs = sizes | std::views::filter([needed](const auto s) { return s > needed; });

	std::cout << "Part two: " << *rng::min_element(bigEnoughDirs);
	return 0;
}
