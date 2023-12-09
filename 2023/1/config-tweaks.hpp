#pragma once

#include <filesystem>
#include <fmt/core.h>
#include <source_location>

namespace details::config {

inline bool useSample() noexcept {
	return true;
}

inline std::filesystem::path getInput(const int part,
									  std::source_location loc = std::source_location::current()) noexcept {
	const auto thisFileName = loc.file_name();
	const auto input = fmt::format("sample{}.txt", part);
	return std::filesystem::path{loc.file_name()}.parent_path() / input;
}

} // namespace details::config
