// In any good project, there is always a misc file somewhere

#pragma once

#include <iostream>

namespace utils {

// Do it for numerics
constexpr void printRange(const auto& r) {
	for (const auto& s : r) {
		std::cout << s << '\n';
	}
}

} // namespace utils