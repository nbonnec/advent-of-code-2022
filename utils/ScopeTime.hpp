#pragma once

#include <chrono>
#include <source_location>

/// Some useful things.
namespace utils {

/// An RAII class to measure time in a scope.
class ScopeTime {

public:
	/// Build the object with a source location to be displayed at destruction.
	/// @param current the current source location
	explicit ScopeTime(std::source_location current = std::source_location::current());

	/// On destruction the object will display elapsed time since creation.
	~ScopeTime();

private:
	std::source_location where_m;
	std::chrono::high_resolution_clock::time_point start_m{std::chrono::high_resolution_clock::now()};
};

} // namespace utils