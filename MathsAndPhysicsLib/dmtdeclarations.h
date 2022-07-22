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

namespace dms {
	using namespace dmutils;
}
namespace dgt { // General Types

	using real = double;
	typedef struct { double value; } imaginary;

	//using uchar = unsigned char;

}

namespace dgs { // General Structures
	using namespace dmutils;

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