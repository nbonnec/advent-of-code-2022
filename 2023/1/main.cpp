
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <numeric>
#include <ranges>
#include <source_location>
#include <vector>

#include "config.hpp"
#include "fmt/core.h"

namespace fs = std::filesystem;
namespace rg = std::ranges;
namespace wvs = std::views;
using namespace std::string_view_literals;

struct LettersDigit {
	char digit;
	std::string_view letters;
};

static constexpr auto digits = "0123456789"sv;
static constexpr auto digit0 = LettersDigit{'0', "zero"sv};
static constexpr auto digit1 = LettersDigit{'1', "one"sv};
static constexpr auto digit2 = LettersDigit{'2', "two"sv};
static constexpr auto digit3 = LettersDigit{'3', "three"sv};
static constexpr auto digit4 = LettersDigit{'4', "four"sv};
static constexpr auto digit5 = LettersDigit{'5', "five"sv};
static constexpr auto digit6 = LettersDigit{'6', "six"sv};
static constexpr auto digit7 = LettersDigit{'7', "seven"sv};
static constexpr auto digit8 = LettersDigit{'8', "eight"sv};
static constexpr auto digit9 = LettersDigit{'9', "nine"sv};
static constexpr std::array lettersDigits{digit0, digit1, digit2, digit3, digit4,
										  digit5, digit6, digit7, digit8, digit9};

static void partOne() {
	auto combine = [](const int acc, std::string line) {
		const auto first = rg::find_first_of(line, digits);
		const auto last = rg::find_first_of(line | wvs::reverse, digits);
		return acc + stoi(fmt::format("{}{}", *first, *last));
	};

	auto ifs = std::ifstream{details::config::getInput(1), std::ios::in};

	const auto sum =
		std::accumulate(std::istream_iterator<std::string>(ifs), std::istream_iterator<std::string>{}, 0, combine);
	fmt::print("Sum is {}\n", sum);
}

static void partTwo() {
	auto combine = [](const int acc, std::string line) {
		fmt::print("For line {}\n", line);
		struct DigitAndPos {
			std::size_t pos;
			char digit;
		};
		const auto firstDigit = rg::find_first_of(line, digits);
		const auto firstDigitAndPos = firstDigit != line.end() ? std::optional{
			DigitAndPos{.pos = static_cast<std::size_t>(std::distance(line.begin(), firstDigit)), .digit = *firstDigit}} : std::nullopt;
		const auto reverseLine = line | wvs::reverse;
		const auto lastDigit = rg::find_first_of(reverseLine, digits);
		const auto lastDigitAndPos =
			DigitAndPos{static_cast<std::size_t>(std::distance(lastDigit, reverseLine.end()) - 1), *lastDigit};

		// For letters, first we have to find all occurences
		// We need to store all occurences and their int counterpart
		const auto digitAndPos = std::accumulate(lettersDigits.begin(), lettersDigits.end(), std::vector<DigitAndPos>{},
												 [&line](auto vec, const LettersDigit& ld) {
													 const auto pos = line.find(ld.letters);
													 if (pos != std::string::npos) {
														 vec.emplace_back(DigitAndPos{pos, ld.digit});
													 }
													 return vec;
												 });
		const auto [min, max] = std::minmax_element(digitAndPos.begin(), digitAndPos.end(),
													[](const auto& a, const auto& b) { return a.pos < b.pos; });

		const auto finalFirst = firstDigitAndPos.pos < min->pos ? firstDigitAndPos.digit : min->digit;
		const auto lastFirst = lastDigitAndPos.pos > max->pos ? lastDigitAndPos.digit : max->digit;
		return std::stoi(fmt::format("{}{}", finalFirst, lastFirst));
	};
	auto ifs = std::ifstream{details::config::getInput(2), std::ios::in};
	const auto sum =
		std::accumulate(std::istream_iterator<std::string>(ifs), std::istream_iterator<std::string>{}, 0, combine);
	fmt::print("Sum is {}\n", sum);
}

int main() {
	partOne();
	partTwo();
}