#pragma once

namespace details::config {

namespace defaults {

inline bool useSample() noexcept {
	return false;
}

} // namespace defaults
} // namespace details::config

#if __has_include("config-tweaks.hpp")
#include "config-tweaks.hpp"
#endif