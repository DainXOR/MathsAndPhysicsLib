#pragma once

#include <array>
#include <stdexcept>
#include <algorithm>

#include "dmath_types.h"
#include "dphysics_types.h"

namespace dmp {
	

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

	namespace dmt {
		using namespace dmutils;


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

			[[nodiscard]] constexpr const_reference operator [](size_t _axis) const noexcept {
				return m_Points[_axis];
			}

			/// > Asignaton operator

			template<typename other_type>
			vector<buffer_type, rn> operator =(vector<other_type, rn> other) const noexcept {
				vector<buffer_type, rn> ans;

				for (int i = 0; i < rn; i++) {
					ans[i] = ((*this)[i] = other[i]);
				}
				return ans;
			}

			/// > Arithmetic operators

			template<typename other_type>
			vector<buffer_type, rn> operator +(vector<other_type, rn> other) const noexcept {
				vector<buffer_type, rn> ans;

				for (int i = 0; i < rn; i++) {
					ans[i] = (*this)[i] + other[i];
				}
				return ans;
			}
			template<typename other_type>
			vector<buffer_type, rn> operator +=(vector<other_type, rn> other) const noexcept {
				vector<buffer_type, rn> ans;

				for (int i = 0; i < rn; i++) {
					ans[i] = (*this)[i] + other[i];
				}
				return ans;
			}

			template<typename other_type>
			vector<buffer_type, rn> operator +(other_type other) const noexcept {
				vector<buffer_type, rn> ans;

				for (int i = 0; i < rn; i++) {
					ans[i] = (*this)[i] + other;
				}
				return ans;
			}
			template<typename other_type>
			vector<buffer_type, rn> operator +=(other_type other) const noexcept {
				vector<buffer_type, rn> ans;

				for (int i = 0; i < rn; i++) {
					ans[i] = (*this)[i] + other;
				}
				return ans;
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
			vector<buffer_type, rn> operator -=(vector<other_type, rn> other) const noexcept {
				vector<buffer_type, rn> ans;

				for (int i = 0; i < rn; i++) {
					ans[i] = (*this)[i] - other[i];
				}
				return ans;
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
			vector<buffer_type, rn> operator -=(other_type other) const noexcept {
				vector<buffer_type, rn> ans;

				for (int i = 0; i < rn; i++) {
					ans[i] = (*this)[i] - other;
				}
				return ans;
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
			vector<buffer_type, rn> operator *=(vector<other_type, rn> other) const noexcept {
				vector<buffer_type, rn> ans;

				for (int i = 0; i < rn; i++) {
					ans[i] = (*this)[i] * other[i];
				}
				return ans;
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
			vector<buffer_type, rn> operator *=(other_type other) const noexcept {
				vector<buffer_type, rn> ans;

				for (int i = 0; i < rn; i++) {
					ans[i] = (*this)[i] * other;
				}
				return ans;
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
			vector<buffer_type, rn> operator /=(other_type other) const noexcept {
				vector<buffer_type, rn> ans;

				for (int i = 0; i < rn; i++) {
					ans[i] = (*this)[i] / other;
				}
				return ans;
			}

			/// > Boolean operators


			/// > Cast operators

			template<typename other_type>
			operator other_type() { 
				vector<other_type, rn> ret;
				for (int i = 0; i < rn; i++) {
					ret[i] = (*this)[i];
				}
				return ret;
			}



			

			// void setCoordinates(std::vector<buffer_type> coords) {}
			// void setCoordinates(std::array<buffer_type, rn> coords) {}
			// void setCoordinates(buffer_type value0, buffer_type... values) {}

		//protected:
			std::array<buffer_type, rn> m_Points;

		};


	}



}

