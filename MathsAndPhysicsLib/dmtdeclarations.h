#pragma once

#include "dmutilities.h"
#include "dmbasic_functions.h"

#include "general_utilities.h"

_DMP_BEGIN
namespace dmt { // Math Types
	using namespace dmutils;

	template<constrains::MathType ty_, size_t rn>
	class vector;

	template<constrains::MathType ty_, size_t rn>
	using point = vector<ty_, rn>;

}

namespace dms { // Math Structures
	using namespace dmutils;
}

namespace dgt { // General Types

	using real = double;
	typedef struct { double value; } imaginary;

	//using uchar = unsigned char;

}




_DMP_END