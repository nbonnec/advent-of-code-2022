// In any good project, there is always a misc file somewhere

#pragma once

#include <iostream>

namespace utils {

template <typename... Ts>
struct Overload : public Ts... {
	using Ts::operator()...;
};
template <class... Ts>
Overload(Ts...) -> Overload<Ts...>;

} // namespace utils