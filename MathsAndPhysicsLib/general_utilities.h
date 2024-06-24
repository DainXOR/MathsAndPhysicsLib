#pragma once

//#define _DTLIB -1

#ifndef _DTLIB

#define _DTLIB 1

#if !defined(_DMP_BEGIN) && !defined(_DMP_END)

// Macros used to enclose the functionality of the library in the "dmp" namespace
#define _DMP_BEGIN namespace dmp {
#define _DMP_END }

#ifdef _DEBUG
#define _DMP_DEBUG 1

#define _DMP_INFO_LOG(x) std::cout << "[DEBUG INFO]" << x << "\n";
#define _DMP_WARN_LOG(x) std::cout << "[WARN INFO]" << x << "\n";
#define _DMP_ERROR_LOG(std_err, x) std::cout << "[ERROR INFO]" << x << "\n"; throw std_err(x)

#define _DMP_INFO_PAUSE(x) std::cout << "[DEBUG PAUSE]" << x << "\n"
#define _DMP_WARN_PAUSE(x) std::cout << "[WARN PAUSE]" << x << "\n"
#define _DMP_ERROR_PAUSE(x) std::cout << "[ERROR PAUSE]" << x << "\n"

#define _DMP_COMPARE(x, y)
#define _DMP_TEST(expression, expected, succeed, error)
#define _DMP_TEST_RESULT(expression, expected)

#else

#define _DMP_INFO_LOG(x)
#define _DMP_WARN_LOG(x)
#define _DMP_ERROR_LOG(std_err, x) throw std_err(x)

#define _DMP_INFO_PAUSE(x)
#define _DMP_WARN_PAUSE(x)
#define _DMP_ERROR_PAUSE(x)

#define _DMP_COMPARE(x, y)
#define _DMP_TEST(expression, expected, succeed, error)
#define _DMP_TEST_RESULT(expression, expected)

#endif // _DEBUG

#define CONSTEXPR_TEST(function_call) std::cout << noexcept(function_call) << "\n"

#endif // Namespace macros


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

#elif _DTLIB == 1
#define _DTLIB -1
#define _DTLMSG "La macro ya ha sido definida antes.\nNo es posible iniciar la libreria.\n"

#elif _DTLIB == 0
#define _DTLMSG "No se ha iniciado la libreria correctamente.\n"

#elif _DTLIB == 0
#define _DTLMSG "Ha ocurrido un error al iniciar.\n"

#endif // !_DTLIB






