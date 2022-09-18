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

		template<auto n1, auto n2>
		struct greater_s {
			static constexpr bool value = n1 > n2;
		};

		template<auto n1, auto n2>
		struct equals_s {
			static constexpr bool value = n1 == n2;
		};

		 
		template<auto n, auto a, auto step>
		struct factorial_helper {
			static constexpr auto value = 
				factorial_helper<
					false_or_value<
						greater<n, step> && greater<step, 0>,
						n - step>, 
					a * n, 
					step>::value;
		};

		template<auto a, auto step>
		struct factorial_helper<0, a, step> {
			static constexpr auto value = a;
		};

		template<UnsignedIntegral num_type, num_type n, std::make_unsigned_t<num_type> step>
		struct factorial_s {
			static constexpr num_type value = factorial_helper<n, 1, step>::value;
		};

	}

	template<auto n1, auto n2>
	inline constexpr bool greater = greater_s<n1, n2>::value;

	template<auto n1, auto n2>
	inline constexpr bool lesser = !(greater_s<n1, n2>::value || equals_s<n1, n2>::value);

	template<auto n1, auto n2>
	inline constexpr bool equals = equals_s<n1, n2>::value;

	template<auto n, UnsignedIntegral num_type = uint64_t>
	inline constexpr num_type factorial = factorial_s<num_type, n, 1>::value;

	template<auto n, UnsignedIntegral num_type = uint64_t>
	inline constexpr num_type factorial_double = factorial_s<num_type, n, 2>::value;

	template<auto n, auto step, UnsignedIntegral num_type = uint64_t>
	inline constexpr num_type factorial_n = factorial_s<num_type, n, step>::value;

}


_DMP_END