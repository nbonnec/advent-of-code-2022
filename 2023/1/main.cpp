
#include <charconv>
#include <filesystem>
#include <fstream>
#include <future>
#include <iostream>
#include <source_location>

#include "config.hpp"
#include "fmt/core.h"

namespace fs = std::filesystem;

static std::ifstream getFile() {
	const auto thisFileName = std::source_location::current().file_name();
	const auto inputName = details::config::useSample() ? "sample.txt" : "input.txt";
	const auto filePath = fs::path{thisFileName}.parent_path() / inputName;
	return {filePath, std::ios::in};
}

static void partOne() {
	auto ifs = getFile();
	for (std::string line; std::getline(ifs, line);) {
		fmt::print("Line is {}\n", line);
		int firstDigit{};
		int secondDigit{};
		std::string combine{};
		auto [ptr, ec] = std::from_chars(line.c_str(), line.c_str() + line.size(), firstDigit);
		const auto remainder = std::string{ptr};
		fmt::print("Remainder is {}\n", remainder);

		if (auto [ptr2, ec2] = std::from_chars(remainder.c_str(), remainder.c_str() + remainder.size(), secondDigit);
			ec2 != std::errc{}) {
			std::cout << "Errc= " << std::make_error_code(ec2) << '\n';
			std::cout << ptr2;
			secondDigit = firstDigit;
		}

		fmt::print("First digit= {}\n", firstDigit);
		fmt::print("Second digit= {}\n", secondDigit);

		combine = fmt::format("{}{}", firstDigit, secondDigit);
		fmt::print("Combine is {}\n", combine);
	}
}

int main() {
	partOne();
}