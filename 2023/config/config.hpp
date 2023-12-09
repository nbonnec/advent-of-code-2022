#pragma once

#include <filesystem>
#include <source_location>

namespace details::config::defaults {
inline bool useSample() noexcept {
	return false;
}

inline std::filesystem::path getInput([[maybe_unused]] const int part,
									  std::source_location loc = std::source_location::current()) noexcept {
	const auto thisFileName = loc.file_name();
	return std::filesystem::path{loc.file_name()}.parent_path() / "input.txt";
}

} // namespace details::config::defaults

#if __has_include("config-tweaks.hpp")
#include "config-tweaks.hpp"
#endif