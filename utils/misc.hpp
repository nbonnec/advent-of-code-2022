// In any good project, there is always a misc file somewhere

#pragma once

#include <iostream>

namespace utils {

// Do it for numerics
constexpr void printRange(const auto& r, const char separator = '\n') {
	for (const auto& s : r) {
		std::cout << s << separator;
	}
}

} // namespace utils