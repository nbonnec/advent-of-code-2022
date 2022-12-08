#include <iostream>

#include "ScopeTime.hpp"

namespace utils {

using namespace std::chrono;

ScopeTime::ScopeTime(std::source_location current) : where_m{current} {
}

ScopeTime::~ScopeTime() {
	const auto elapsed = duration_cast<microseconds>(high_resolution_clock::now() - start_m);
	std::cout << "Elapsed time for " << where_m.function_name() << " in " << where_m.file_name() << ": "
			  << elapsed.count() << " µs";
}

} // namespace utils
