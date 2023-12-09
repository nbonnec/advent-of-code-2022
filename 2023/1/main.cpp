
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <numeric>
#include <ranges>
#include <source_location>

#include "config.hpp"
#include "fmt/core.h"

namespace fs = std::filesystem;
namespace rg = std::ranges;
namespace wvs = std::views;
using namespace std::string_view_literals;

static std::ifstream getFile() {
	const auto thisFileName = std::source_location::current().file_name();
	const auto inputName = details::config::useSample() ? "sample.txt" : "input.txt";
	const auto filePath = fs::path{thisFileName}.parent_path() / inputName;
	return {filePath, std::ios::in};
}

static void partOne() {
	auto combine = [](const int acc, std::string line) {
		static constexpr auto digits = "0123456789"sv;
		const auto first = rg::find_first_of(line, digits);
		const auto last = rg::find_first_of(line | wvs::reverse, digits);
		return acc + stoi(fmt::format("{}{}", *first, *last));
	};

	auto ifs = getFile();

	const auto sum =
		std::accumulate(std::istream_iterator<std::string>(ifs), std::istream_iterator<std::string>{}, 0, combine);
	fmt::print("Sum is {}\n", sum);
}

int main() {
	partOne();
}