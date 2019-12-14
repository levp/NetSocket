#pragma once

#include <sstream>

template <typename ...TArgs>
[[noreturn]]
void FAIL(const TArgs& ... args) {
	std::ostringstream oss;
	(oss<<... << args);
	throw std::runtime_error{oss.str()};
}
