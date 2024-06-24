#pragma once

#include <concepts>
#include <string>
#include <type_traits>

#include <iostream>
#include <vector>

#include "general_utilities.h"


_DMP_BEGIN
namespace dmutils {

	namespace constrains {

		template<typename value_type>
		concept Integral = requires{
			std::integral<value_type>;
			!std::is_same_v<value_type, bool>;
		};

		template<typename value_type>
		concept Float = requires{
			std::is_floating_point_v<value_type>;
		};

		template<typename value_type>
		concept UnsignedIntegral = requires{
			std::integral<value_type>;
			!std::is_same_v<value_type, bool>;
			std::is_unsigned_v<value_type>;
		};

		template<typename value_type>
		concept Arithmetic = requires{
			Integral<value_type> || std::is_floating_point_v<value_type>;
		};
			
		namespace {
			template<typename ty_>
			struct is_math_type {
				static constexpr bool value = MathType<ty_>;
			};
		}

		template<typename value_type>
		concept MathType = requires(value_type A, value_type B) {
			Arithmetic<value_type>;

			std::disjunction_v<
				std::is_same<value_type, decltype(A + B)>, 
				is_math_type<decltype(A + B)>>;

			{A + B};
			{A - B}; // -> std::same_as<ty_>;
			{A * B}; // -> std::same_as<ty_>;
			{A / B}; // -> std::same_as<ty_>;

			std::cout << A;
			//std::to_string(A);
		};


		template<template <uint16_t...> class properties_struct, uint16_t...args>
		concept TensorProperties = requires (properties_struct<args...> props) {

			std::convertible_to<decltype(props.rank), uint16_t>;
			std::convertible_to<decltype(props.size), size_t>;

			std::is_assignable_v<
				std::array<size_t, properties_struct<args...>::size>, 
				decltype(properties_struct<args...>::dimentions)
			>;
			
			props.rank != 0;
			props.size != 0;

			props.dimentions[0];
			props.dimentions.size();
		};
		

		template<template <uint16_t...> class properties_struct, uint16_t...args>
		concept MatrixProperties = requires(properties_struct<args...> ps) {
			TensorProperties<properties_struct>;
			ps.rank == 2;

		};

		template<template <uint16_t...> class properties_struct, uint16_t...args>
		concept VectorProperties = requires(properties_struct<args...> ps) {
			TensorProperties<properties_struct>;
			ps.rank == 1;
		};


	}

	namespace helper {

		template <typename size_type, std::size_t Size>
		constexpr std::array<size_type, Size> multipliers(const std::array<size_type, Size>& values) noexcept {

			std::array<size_type, Size> multipliersArray{};

			//multipliersArray[Size - 1] = 1;
			//((multipliersArray[Size - i - 2] = multipliersArray[Size - i - 1] * values[Size - i - 1]), ...);

			return multipliersArray;
		}
		
	}

	namespace structs {

		template<size_t... dimentions>
		constexpr size_t tensor_size = sizeof... (dimentions) ? (dimentions * ... * 1) : 0;

		template<uint16_t... dimentions>
		constexpr uint16_t tensor_rank = sizeof... (dimentions);

		template<uint16_t... dimentions>
		constexpr std::array<uint16_t, tensor_rank<dimentions...>> tensor_dimentions = { dimentions... };


		template<uint64_t... dims>
		struct tensor_properties {
			uint16_t				rank		= tensor_rank<dims...>;
			size_t					size		= tensor_size<dims...>;
			std::vector<size_t>		dimentions	= tensor_dimentions<dims...>;
			
		};

		template<uint64_t... dims>
		struct t_dimentions {
			constexpr static uint16_t	rank = tensor_rank<dims...>;
			constexpr static size_t		size = tensor_size<dims...>;
			constexpr static auto		dimentions = tensor_dimentions<dims...>;
			//inline const static uint64_t... d_ = d...;

		};

		

	}

	namespace casts {

		
	}

	namespace template_traits {
		namespace {
			template<bool test, auto val>
			struct false_or_value_s {
			};

			template<auto val>
			struct false_or_value_s<false, val> {
				static constexpr bool value = false;
			};

			template<auto val>
			struct false_or_value_s<true, val> {
				static constexpr auto value = val;
			};
		}
		
		template<bool test, auto value>
		inline constexpr auto false_or_value = false_or_value_s<test, value>::value;

		template<bool test, auto value>
		inline constexpr auto true_or_value = false_or_value_s<!test, value>::value;

	}

}
_DMP_END

