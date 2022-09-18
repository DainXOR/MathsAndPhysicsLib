#pragma once


#if !defined(_DMP_BEGIN) && !defined(_DMP_END)

// Macros used to enclose the functionality of the library in the "dmp" namespace
#define _DMP_BEGIN namespace dmp {
#define _DMP_END }

#endif // Namespace macros

#define CONSTEXPR_TEST(function_call) constexpr bool b1 = noexcept(function_call); std::cout << b1 << "\n"


_DMP_BEGIN

namespace dgs { // General Structures

	template<typename ty1_, typename ty2_>
	struct pair
	{
		ty1_ first;
		ty2_ second;
	};

	template<typename ty1_, typename ty2_, typename ty3_>
	struct triplet {
		ty1_ first;
		ty2_ second;
		ty3_ third;
	};
}

_DMP_END




