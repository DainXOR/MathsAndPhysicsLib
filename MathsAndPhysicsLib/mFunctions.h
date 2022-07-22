#pragma once

#include "dmpconstants.h"
#include "dmath_types.h"
#include "general_utilities.h"

_DMP_BEGIN


namespace functions
{

	using namespace dmutils::constrains;

	template<Integral num_type, num_type n>
	struct factorial {};

	template<uint16_t n>
	struct factorial<uint64_t, n> {
		static constexpr uint64_t value = factorial_helper <n, 1>::value;
	};

	template<int n>
	struct factorial<int, n> {
		static constexpr int value = factorial_helper <n, 1>::value;
	};


	template<auto n, auto a>
	struct factorial_helper {
		static constexpr auto value = factorial_helper <n - 1, a * n>::value;
	};

	template<auto a>
	struct factorial_helper<1, a> {
		static constexpr auto value = a;
	};

	template<Integral num_type>
	constexpr auto ffactorial(const num_type &n) {
		//return factorial<num_type, n>::value;
	}



}


_DMP_END