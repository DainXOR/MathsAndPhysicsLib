#pragma once


#if !defined(_DMP_BEGIN) && !defined(_DMP_END)

// Macros used to enclose the functionality of the library in the "dmp" namespace
#define _DMP_BEGIN namespace dmp {
#define _DMP_END }

#endif // Namespace macros

#define CONSTEXPR_TEST(function_call) constexpr bool b1 = noexcept(function_call); std::cout << b1 << "\n"





