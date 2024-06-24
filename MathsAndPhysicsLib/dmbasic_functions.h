#pragma once

#include "dmutilities.h"

#include "general_utilities.h"


_DMP_BEGIN

/// \Warn Funtions that only works with native types, other types are undefined behavior
namespace dmbasic_functions
{
	[[nodiscard]] constexpr auto abs(const auto& num) noexcept { return num * ((num > 0) - (num < 0)); }
}

_DMP_END