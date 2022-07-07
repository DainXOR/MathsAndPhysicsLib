#pragma once

#include "dmutilities.h"

namespace dmp {
	namespace dmt { // Math Types
		using namespace dmutils;

		template<constrains::MathType ty_, size_t rn>
		class vector;

		template<constrains::MathType ty_, size_t rn>
		using point = vector<ty_, rn>;

		//template<typename dimstr>
		//template<constrains::MathType ty_, template<constrains::MathType, constrains::MathType> class dimstr>
		//requires constrains::MatrixDimention<dimstr>
		//class matrix;

	}

	namespace dms {
		using namespace dmutils;

		//template<constrains::MathType m_, constrains::MathType n_>
		//struct matrix_dimention {
		//
		//	template<typename ty1_>
		//	static constexpr ty1_ m = m_;
		//
		//	template<typename ty2_>
		//	static constexpr ty2_ m = n_;
		//
		//};
	}
	namespace a {
		
		//void fn() {
		//
		//}
	}
}