#pragma once

#include "dmpconstants.h"
#include "dmath_types.h"
#include "general_utilities.h"

_DMP_BEGIN


namespace functions
{
	using namespace dmutils::constrains;
	using namespace dmutils::template_traits;

	namespace {

		template<auto n, auto a, uint8_t step>
		struct factorial_helper {
			static constexpr auto value =
				factorial_helper<
				(n > step && step > 0) * (n - step),
				a * n,
				step>::value;
		};

		template<auto a, uint8_t step>
		struct factorial_helper<0, a, step> {
			static constexpr auto value = a;
		};

		template<auto n, uint8_t step>
		struct factorial_s {
			static constexpr auto value = factorial_helper<n, 1, step>::value;
		};

		//template<>
		//struct perfect_sqr_down {
		//
		//};
		//
		//template<auto n, auto a, auto step>
		//struct sqrt_helper {
		//	static constexpr double value = n + ;
		//};
		//
		//using namespace dmutils::template_traits;
		//template<Float num_type, num_type n, num_type step>
		//struct sqrt_s {
		//	static constexpr double value = sqrt_helper<n, tr>::value;
		//};

	}

	template<auto n>
	constexpr auto factorial = factorial_s<n, 1>::value;

	template<auto n>
	constexpr auto factorial_double = factorial_s<n, 2>::value;

	template<auto n, auto step>
	constexpr auto factorial_n = factorial_s<n, step>::value;

	//template<auto n, Float num_type = float>
	//inline constexpr num_type sqrt = sqrt_s<num_type, n, 1>::value;

}


_DMP_END