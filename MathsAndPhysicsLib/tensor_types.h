#pragma once

#include <stdexcept>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <optional>
#include <iostream>

#include <type_traits>

#include "dmtdeclarations.h"
#include "general_utilities.h"



_DMP_BEGIN

namespace dmt{
	using namespace dmutils;
	using namespace structs;

	template<class buffer_type = int32_t, uint16_t...dims>
	requires constrains::Arithmetic<buffer_type>
	class tensor {

		using type = buffer_type;
		using pointer = buffer_type*;
		using reference = buffer_type&;

		using tp = t_dimentions<dims...>;

		template<uint16_t _size>
		using iterator = std::_Array_iterator<type, _size>;
		template<uint16_t _size>
		using const_iterator = std::_Array_const_iterator<type, _size>;

		template<class iter>
		using reverse_iterator = std::reverse_iterator<iter>;
		template<class const_iter>
		using const_reverse_iterator = std::reverse_iterator<const_iter>;

		std::vector<type> mp_buffer = std::vector<type>(tp::size);

		tp mp_properties;

	public:
		// > Access functions and operators

		constexpr size_t size() {
			return tp::size;
		}
		constexpr uint16_t rank() {
			return tp::rank;
		}
		constexpr std::array<type, tp::rank> dimentions() {
			std::array<type, rank()> dims_vector;

			for (uint16_t i = 0; i < tp::rank; i++) {
				dims_vector[i] = tp::dimentions[i];
			}

			return dims_vector;
		}
		constexpr size_t dimention(uint16_t rankPos) {
			if (rankPos > tp::rank) throw std::out_of_range("Rank outside tensor.\n");
			return tp::dimentions[rankPos];
		}

		// inline constexpr properties getProperties() {
		// 	return properties();
		// }

		constexpr reference operator [](size_t index) {
			if (index >= size()) {
				_DMP_ERROR_LOG(std::out_of_range, "The index is outside the tensor. (Max = " + std::to_string(size() - 1) + ")");
			}

			return mp_buffer[index];
		}
		[[nodiscard]] constexpr const reference operator [](size_t index) const {
			if (index >= size()) {
				_DMP_ERROR_LOG(std::out_of_range, "The index is outside the tensor. (Max = " + std::to_string(size() - 1) + ")");
			}

			return mp_buffer[index];
		}

		constexpr std::optional<reference> operator ()(constrains::UnsignedIntegral auto... indexes){

			constexpr uint16_t IndexCount = sizeof...(indexes);
			if (!IndexCount) {
				_DMP_ERROR_LOG(std::invalid_argument, "No indexes provided.\n");
			}

			if (IndexCount <= rank()) {

				std::array<size_t, IndexCount> IndexesArray = { indexes... };
				constexpr std::array Multipliers = multipliers(dimentions());
				size_t index = 0;

				for (uint16_t i = 0; i <= rank(); i++) {
					if ((IndexesArray[i] >= dimention(i))) {
						_DMP_ERROR_LOG(std::out_of_range, "The index is outside the tensor."
									   "\n(Max =" + std::to_string(dimention(i) - 1) + ","
									   " Attempted[" + std::to_string(IndexesArray[i]) + "])");
						return std::nullopt;
					}

					index += IndexesArray[i] * Multipliers[i];
				}
				
				return mp_buffer[index];
			}

			_DMP_ERROR_LOG(std::out_of_range, "Amount of indexes provided exceed the tensor rank.");
			return std::nullopt;
		}
		
		/*
		constexpr std::optional<const reference> operator ()(constrains::UnsignedIntegral auto... indexes){

			constexpr uint16_t IndexCount = sizeof...(indexes);
			if (!IndexCount) {
				return std::nullopt;
			}

			if (IndexCount > rank()) {
				return std::nullopt;
			}

			std::array<size_t, IndexCount> IndexesArray = { indexes... };

			for (size_t i = 0; i < IndexCount; ++i) {
				if (IndexesArray[i] >= dimention(i)) {
					return std::nullopt;
				}
			}

			constexpr std::array Multipliers = multipliers(dimentions());

			size_t index = 0;
			for (size_t i = 0; i < IndexCount; ++i) {
				index += IndexesArray[i] * Multipliers[i];
			}

			return mp_buffer[index];
		}
		*/

		// > Math operations functions and operators
		tensor& operator+(const tensor& other) {
			if (this->getProperties() == other.getProperties()) {
				for (size_t i = 0; i < this.size(); i++) {
					this[i] += other[i];
				}
				return this;
			}

			// Do Einstain Summation

			return 0;
		}
		tensor& operator+(const auto& scalar) {
			for (size_t i = 0; i < this.size(); i++) {
				this[i] += scalar;
			}
			return this;
		}
	
		tensor& operator-(const tensor& other) {
			if (this->getProperties() == other.getProperties()) {
				for (size_t i = 0; i < this.size(); i++) {
					this[i] -= other[i];
				}
				return this;
			}

			// Do Einstain Summation

			return 0;
		}
		tensor& operator-(const auto& scalar) {
			for (size_t i = 0; i < this.size(); i++) {
				this[i] -= scalar;
			}
			return this;
		}
		
		float determinant() /*requires constrains::MatrixProperties<properties>*/ {
			return 0.f;
		}

	private:

		template<constrains::UnsignedIntegral... size_type = size_t>
		void changeDims(size_type... dims) {

		}

	};
	namespace tests {

		namespace newStructs {
			

			


		}
		

		


	}


	/*
	template<constrains::MathType ty_, size_t rn>
	class vector
	{
		using buffer_type = ty_;
		using const_type = const ty_;
		using pointer = ty_*;
		using const_pointer = const ty_*;
		using reference = ty_&;
		using const_reference = const ty_&;

	public:
		//constexpr vector() noexcept 
		//	: m_Coords() {}
		//
		//constexpr vector(const std::array<buffer_type, rn>& arr) noexcept
		//	: m_Coords(arr) {}
		//
		//vector(const_type arr[rn]) noexcept
		//{
		//	std::copy_n(std::begin(arr), rn, std::begin(m_Coords));
		//}

		[[nodiscard]] reference value(size_t _axis) {
			((_axis >= rn) || (_axis < 0)) && (throw std::out_of_range("Tried to access a position greater than the size of the container"), false);

			return m_Points._Elems[_axis];
		}

		[[nodiscard]] constexpr const_reference value(size_t _axis) const noexcept {
			return m_Points[_axis];
		}

		constexpr const size_t dim() const noexcept {
			return rn;
		}

		/// > Array operators

		reference operator [](size_t _axis) {
			((_axis >= rn) || (_axis < 0)) && (throw std::out_of_range("Tried to access a position greater than the size of the container"), false);

			return m_Points._Elems[_axis];
		}

		[[nodiscard]] constexpr const_reference operator [](size_t _axis) const {
			((_axis >= rn) || (_axis < 0)) && (throw std::out_of_range("Tried to access a position greater than the size of the container"), false);
			return m_Points[_axis];
		}

		/// > Assign operator

		template<typename other_type>
		vector<buffer_type, rn> operator =(const vector<other_type, rn> &other) noexcept {
			vector<buffer_type, rn> ans;

			for (int i = 0; i < rn; i++) {
				(*this)[i] = other[i];
			}
			return (*this);
		}

		/// > Arithmetic operators

		template<typename other_type>
		vector<buffer_type, rn> operator +(const vector<other_type, rn> &other) const noexcept {
			vector<buffer_type, rn> ans;

			for (int i = 0; i < rn; i++) {
				ans[i] = (*this)[i] + other[i];
			}
			return ans;
		}
		template<typename other_type>
		vector<buffer_type, rn> operator +=(const vector<other_type, rn> &other) noexcept {
			
			for (int i = 0; i < rn; i++) {
				(*this)[i] = (*this)[i] + other[i];
			}
			return (*this);
		}

		template<typename other_type>
		vector<buffer_type, rn> operator +(const other_type &other) const noexcept {
			vector<buffer_type, rn> ans;

			for (int i = 0; i < rn; i++) {
				ans[i] = (*this)[i] + other;
			}
			return ans;
		}
		template<typename other_type>
		vector<buffer_type, rn> operator +=(other_type other) noexcept {
			
			for (int i = 0; i < rn; i++) {
				(*this)[i] = (*this)[i] + other;
			}
			return (*this);
		}


		template<typename other_type>
		vector<buffer_type, rn> operator -(vector<other_type, rn> other) const noexcept {
			vector<buffer_type, rn> ans;

			for (int i = 0; i < rn; i++) {
				ans[i] = (*this)[i] - other[i];
			}
			return ans;
		}
		template<typename other_type>
		vector<buffer_type, rn> operator -=(vector<other_type, rn> other) noexcept {
			
			for (int i = 0; i < rn; i++) {
				(*this)[i] -= other[i];
			}
			return (*this);
		}

		template<typename other_type>
		vector<buffer_type, rn> operator -(other_type other) const noexcept {
			vector<buffer_type, rn> ans;

			for (int i = 0; i < rn; i++) {
				ans[i] = (*this)[i] - other;
			}
			return ans;
		}
		template<typename other_type>
		vector<buffer_type, rn> operator -=(other_type other) noexcept {
			
			for (int i = 0; i < rn; i++) {
				(*this)[i] -= other;
			}
			return (*this);
		}


		template<typename other_type>
		vector<buffer_type, rn> operator *(vector<other_type, rn> other) const noexcept {
			vector<buffer_type, rn> ans;

			for (int i = 0; i < rn; i++) {
				ans[i] = (*this)[i] * other[i];
			}
			return ans;
		}
		template<typename other_type>
		vector<buffer_type, rn> operator *=(vector<other_type, rn> other) noexcept {
			
			for (int i = 0; i < rn; i++) {
				(*this)[i] *= other[i];
			}
			return (*this);
		}

		template<typename other_type>
		vector<buffer_type, rn> operator *(other_type other) const noexcept {
			vector<buffer_type, rn> ans;

			for (int i = 0; i < rn; i++) {
				ans[i] = (*this)[i] * other;
			}
			return ans;
		}
		template<typename other_type>
		vector<buffer_type, rn> operator *=(other_type other) noexcept {
			
			for (int i = 0; i < rn; i++) {
				(*this)[i] *= other;
			}
			return (*this);
		}


		template<typename other_type>
		vector<buffer_type, rn> operator /(other_type other) const noexcept {
			vector<buffer_type, rn> ans;

			for (int i = 0; i < rn; i++) {
				ans[i] = (*this)[i] / other;
			}
			return ans;
		}
		template<typename other_type>
		vector<buffer_type, rn> operator /=(other_type other) noexcept {
			
			for (int i = 0; i < rn; i++) {
				(*this)[i] /= other;
			}
			return (*this);
		}

		/// > Boolean operators

		template<typename other_type>
		bool operator ==(const vector<other_type, rn> &other) const noexcept {}
		template<typename other_type>
		vector<buffer_type, rn> operator ==(const vector<other_type, rn>& other) const noexcept {}

		template<typename other_type>
		bool operator !=(const vector<other_type, rn>& other) const noexcept {}
		template<typename other_type>
		vector<buffer_type, rn> operator !=(const vector<other_type, rn>& other) const noexcept {}

		template<typename other_type>
		bool operator <=(const vector<other_type, rn>& other) const noexcept {}
		template<typename other_type>
		vector<buffer_type, rn> operator <=(const vector<other_type, rn>& other) const noexcept {}

		template<typename other_type>
		bool operator >=(const vector<other_type, rn>& other) const noexcept {}
		template<typename other_type>
		vector<buffer_type, rn> operator >=(const vector<other_type, rn>& other) const noexcept {}

		template<typename other_type>
		bool operator <(const vector<other_type, rn>& other) const noexcept {}
		template<typename other_type>
		vector<buffer_type, rn> operator <(const vector<other_type, rn>& other) const noexcept {}

		template<typename other_type>
		bool operator >(const vector<other_type, rn>& other) const noexcept {}
		template<typename other_type>
		vector<buffer_type, rn> operator >(const vector<other_type, rn>& other) const noexcept {}

		template<typename other_type>
		bool operator !() const noexcept {
			return true; //this->magnitude();
		}
		template<typename other_type>
		vector<buffer_type, rn> operator !() const noexcept {}


		/// > Cast operators

		template<typename other_type>
		operator other_type() {
			vector<other_type, rn> ret;
			for (int i = 0; i < rn; i++) {
				ret[i] = other_type((*this)[i]);
			}
			
			return ret;
		}



	//protected:
		std::array<buffer_type, rn> m_Points;

	};
	*/
}

_DMP_END