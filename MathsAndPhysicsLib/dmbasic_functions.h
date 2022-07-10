#pragma once

#include "dmutilities.h"

#include "general_utilities.h"


_DMP_BEGIN

// Funtions that only works with native types, other types are not defined behavior
namespace dmbasic_functions
{
	[[nodiscard]] constexpr auto abs(const auto& num) noexcept { return num * ((num > 0) - (num < 0)); }
}

_DMP_END