#pragma once

#include <concepts>
#include <string>
#include <type_traits>

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


		template<template<uint16_t...>class propsStr, uint16_t...dims>
		concept TensorPropertiesStruct = requires() {
			propsStr<dims...>::rank;

			propsStr<dims...>::dimentions;
			propsStr<dims...>::size;

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


	namespace structs {
		namespace {

			template<uint16_t... dims>
			struct tensor_properties {
				const uint16_t rank = sizeof... (dims);
				const std::array<uint16_t, sizeof... (dims)> dimentions = { dims... };
				const size_t size = TensorSize<dims...>::size;
			};

			
		}

		template<uint16_t... dims>
		using TensorProperties = tensor_properties<dims...>;

		template<uint16_t dim_0, uint16_t... dim_n>
		struct TensorSize
		{
			const static size_t size = dim_0 * TensorSize<dim_n...>::size;
		};

		template<uint16_t dim_n>
		struct TensorSize<dim_n>
		{
			const static size_t size = dim_n;
		};

		template<uint16_t... dims>
		constexpr uint16_t TensorRank = tensor_properties<dims...>().rank;
		
		template<uint16_t... dims>
		constexpr auto TensorDimentions = tensor_properties<dims...>().dimentions;

	}

	namespace casts {

		//template<class from, class to, from var>
		//using sc = static_cast<to>(var);
	}

	namespace tricks{
	}

}
_DMP_END

