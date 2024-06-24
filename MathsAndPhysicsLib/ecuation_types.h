#pragma once

#include <vector>
#include <string>

#include "dmtdeclarations.h"
#include "dmutilities.h"

_DMP_BEGIN

namespace dmt{
	using namespace dmutils;
	using namespace structs;

	template<constrains::MathType value_type = int64_t>
	class symbolic
	{
		const std::string id;
		std::vector<symbolic> components;
		std::string ecuation;

		const value_type value;

		symbolic() = delete;

	public:
		constexpr symbolic(const std::string& Name)
			: id(Name), value(0) 
		{};
		constexpr symbolic(const char* Name)
			: id(Name), value(0)
		{};

		constexpr symbolic(const std::string& Ecuation, const value_type& Value)
			: id("none"), ecuation(Ecuation), value(Value)
		{};
		constexpr symbolic(const char* Ecuation, const value_type& Value)
			: id("none"), ecuation(Ecuation), value(Value)
		{};

		bool simplify() {
			return false;
		}
		const value_type& evaluate() {
			return value;
		}

		constexpr value_type operator=(const value_type& Value) {
			value = Value;
		};
		constexpr value_type operator=(const std::string& Ecuation) {
			ecuation = Ecuation;
		};

		constexpr bool operator==(const symbolic& other) {
			return this->ecuation == other.ecuation;
		}
		constexpr bool operator==(const value_type& other) {
			return evaluate() == other;
		}

		std::string operator + (const symbolic& other) {
			ecuation.append("+").append(other.ecuation);
			simplify();
		}
		std::string operator + (const value_type number) {
			ecuation.append("+").append(std::to_string(number));
			simplify();
		}

		std::string operator - (const symbolic& other) {
			ecuation.append("-").append(other.ecuation);
			simplify();
		}
		std::string operator - (const value_type& number) {
			ecuation.append("-").append(std::to_string(number));
			simplify();
		}

		std::string operator * (const symbolic& other) {
			ecuation.append("*").append(other.ecuation);
			simplify();
		}
		std::string operator * (const value_type& number) {
			ecuation.append("*").append(std::to_string(number));
			simplify();
		}

		std::string operator / (const symbolic& other) {
			ecuation.append("/").append(other.ecuation);
			simplify();
		}
		std::string operator / (const value_type& number) {
			ecuation.append("/").append(std::to_string(number));
			simplify();
		}

		std::string operator ^ (const symbolic& other) {
			ecuation = "((" + ecuation + ")^" + other.ecuation + ")";
			simplify();
		}
		std::string operator ^ (const value_type& number) {
			ecuation = "((" + ecuation + "^" + std::to_string(number) + ")";
			simplify();
		}

		std::string root(const symbolic& other) {
			ecuation = "root(" + other.ecuation + ", " + ecuation + ")";
			simplify();
			return ecuation;
		}
		std::string root(const value_type& number) {
			ecuation = "root(" + number + ", " + ecuation + ")";
			simplify();
		}

		// std::string tetration ...

		static std::string differenciate(symbolic expretion, uint16_t n_diff) {
			expretion = "diff" + std::to_string(n_diff) + "(" + expretion + ")";
			simplify();
			return expretion;
		}
		std::string differenciate(uint16_t n_diff) {
			ecuation = "diff" + std::to_string(n_diff) + "(" + ecuation + ")";
			simplify();
			return ecuation;
		}

		static std::string integrate(symbolic expretion, uint16_t n_int) {
			expretion = "int" + std::to_string(n_int) + "(" + expretion + ")";
			simplify();
			return expretion;
		}
		std::string integrate(uint16_t n_int) {
			ecuation = "int" + std::to_string(n_int) + "(" + ecuation + ")";
			simplify();
			return ecuation;
		}

	};
}



_DMP_END