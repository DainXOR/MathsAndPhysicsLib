#pragma once

#include <concepts>
#include <string>

#include "general_utilities.h"

_DMP_BEGIN
namespace dmutils {

	namespace constrains {

		template<typename ty_>
		concept MathType = requires(ty_ A, ty_ B) {
			std::is_arithmetic<ty_>::value;
			!std::is_same<ty_, bool>::value;
			{A + B}; // -> std::same_as<ty_>;
			{A - B}; // -> std::same_as<ty_>;
			{A * B}; // -> std::same_as<ty_>;
			{A / B}; //->std::same_as<ty_>;
			ty_();
			std::to_string(ty_());

		};

		//template<template<typename, typename> class dim>
		//concept MatrixDimention = requires() {
		//	dim::m;
		//	dim::n;
		//};

	}
	
	//template<class ty_>
	//void function() requires constrains::MathType<ty_>
	//{}

	namespace casts {

		//template<class from, class to, from var>
		//using sc = static_cast<to>(var);
	}

	namespace tricks{
		//using short_circuit = void(*)(bool cond_, auto if_, auto else_);
	}

}
_DMP_END

