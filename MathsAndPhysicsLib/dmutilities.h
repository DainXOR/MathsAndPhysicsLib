#pragma once

#include <concepts>
#include <string>

#include "general_utilities.h"

_DMP_BEGIN
namespace dmutils {

	namespace constrains {

		template<typename ty_>
		concept Integral = requires{
			std::integral<ty_>;
			!std::is_same_v<ty_, bool>;
		};
			

		template<typename ty_>
		concept Arithmetic = requires{
			Integral<ty_> || std::is_floating_point_v<ty_>;
		};
			

		template<typename ty_>
		concept MathType = requires(ty_ A, ty_ B) {
			Arithmetic<ty_>;
			{A + B}; // -> std::same_as<ty_>;
			{A - B}; // -> std::same_as<ty_>;
			{A * B}; // -> std::same_as<ty_>;
			{A / B}; // -> std::same_as<ty_>;
			ty_();
			std::to_string(ty_());

		};

		template<class str>
		concept MatrixDim = requires(str dimStr) {
			Integral<typename str::type>;
			dimStr.m;
			dimStr.n;
			//dimStr.o; // Optional
		};

		template<class ty_>
		concept VectorDim = requires() {
			MatrixDim<ty_>;
			ty_::n == 1;
		};

	}
	
	//template<class ty_>
	//void function() requires constrains::MathType<ty_>
	//{}

	namespace casts {

		//template<class from, class to, from var>
		//using sc = static_cast<to>(var);
	}

	namespace tricks{
	}

}
_DMP_END

