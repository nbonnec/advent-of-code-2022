#pragma once

namespace details::config::defaults {

inline bool useSample() noexcept {
	return false;
}

} // namespace details::config::defaults

#if __has_include("config-tweaks.hpp")
#include "config-tweaks.hpp"
#endif