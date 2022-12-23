#include <algorithm>
#include <charconv>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ranges>
#include <source_location>

#include "config.hpp"
#include "fmt/core.h"
#include "magic_enum.hpp"

namespace fs = std::filesystem;
namespace rng = std::ranges;
namespace vws = std::views;

static std::ifstream getFile() {
	const auto thisFileName = std::source_location::current().file_name();
	const auto inputName = details::config::useSample() ? "sample.txt" : "input.txt";
	const auto filePath = fs::path{thisFileName}.parent_path() / inputName;
	return {filePath, std::ios::in};
}

struct Motion {
	enum class Direction { Right, Left, Up, Down };
	Direction direction{};
	int steps{};
	[[nodiscard]] bool operator==(const Motion&) const = default;
};

[[nodiscard]] static Motion parse(std::string_view sv) {
	const auto dir = [sv]() -> Motion::Direction {
		// clang-format off
		switch (sv[0]) {
			using enum Motion::Direction;
			case 'R': return Right;
			case 'L': return Left;
			case 'U': return Up;
			case 'D': return Down;
		}
		return {};
		// clang-format on
	}();

	int steps{};
	std::from_chars(sv.begin() + 2, sv.end(), steps);
	return {dir, steps};
}

static int partOne() {
	const auto p = parse("R 4");
	fmt::print("{} {}\n", magic_enum::enum_name(p.direction), p.steps);
	return 0;
}

void test();

static int partTwo() {
	test();
	return 0;
}

int main() {
	std::cout << "Part one: " << partOne() << '\n';
	std::cout << "Part two: " << partTwo() << '\n';
	return 0;
}

void test() {
	struct Data {
		std::string_view sv;
		Motion motion;
	};
	std::array tests = {Data{"R 4", Motion{Motion::Direction::Right, 4}},
						Data{"L 8", Motion{Motion::Direction::Left, 8}}, Data{"U 1", Motion{Motion::Direction::Up, 1}},
						Data{"D 23", Motion{Motion::Direction::Down, 23}}};
	for (const auto& t : tests) {
		const auto p = parse(t.sv);
		fmt::print("{} {} == {} {} -> {}\n", magic_enum::enum_name(p.direction), p.steps,
				   magic_enum::enum_name(t.motion.direction), t.motion.steps, parse(t.sv) == t.motion);
	}
}
