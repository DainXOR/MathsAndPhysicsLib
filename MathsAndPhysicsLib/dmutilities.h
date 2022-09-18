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
		concept UnsignedIntegral = requires{
			std::integral<ty_>;
			!std::is_same_v<ty_, bool>;
			std::is_unsigned_v<ty_>;
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


		template<typename propsStr>
		concept TensorPropertiesStruct = requires (propsStr ps) {
			
			std::convertible_to<decltype(propsStr::rank), uint16_t>;
			std::convertible_to<decltype(propsStr::size), size_t>;

			std::is_assignable_v<std::array<size_t, propsStr::size>, decltype(propsStr::dimentions)>;

		};
		

		template<class str>
		concept MatrixDim = requires(str dimStr) {
			Integral<typename str::type>;
			dimStr.m;
			dimStr.n;
		};

		template<class ty_>
		concept VectorDim = requires() {
			MatrixDim<ty_>;
			ty_::n == 1;
		};


	}


	namespace structs {
		namespace {

			template<constrains::Arithmetic type, type ans, type head, type... tail>
			struct variadic_mult
			{
				const static type value = variadic_mult<type, ans * head, tail...>::value;
			};

			template<constrains::Arithmetic type, type ans, type tail>
			struct variadic_mult<type, ans, tail>
			{
				const static type value = ans * tail;
			};

			
		}

		template<size_t... dims>
		constexpr size_t tensor_size = variadic_mult<size_t, 1, dims...>::value;

		template<uint16_t... dims>
		constexpr uint16_t tensor_rank = sizeof... (dims);

		template<uint16_t... dims>
		constexpr std::array<size_t, sizeof... (dims)> tensor_dimentions = { dims... };


		template<uint64_t... dims>
		struct tensor_properties {
			inline const static uint16_t	rank		= tensor_rank<dims...>;
			inline const static size_t		size		= tensor_size<dims...>;
			inline const static auto		dimentions	= tensor_dimentions<dims...>;
			
		};

		

	}

	namespace casts {

		
	}

	namespace tricks{
	}

	namespace template_traits {
		namespace {
			template<bool test, auto val>
			struct false_or_value_s {
			};

			template<auto val>
			struct false_or_value_s<false, val> {
				static constexpr auto value = 0;
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

