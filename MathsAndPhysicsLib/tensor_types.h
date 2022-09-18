#pragma once

#include <stdexcept>
#include <array>
#include <string>
#include <algorithm>

#include <iostream>

#include "dmtdeclarations.h"
#include "general_utilities.h"

_DMP_BEGIN

namespace dmt{
	using namespace dmutils;

	namespace raw_structs { 

	}

	using namespace raw_structs;


	namespace tests {

		namespace newStructs {
			using namespace structs;

			template<constrains::TensorPropertiesStruct Properties, constrains::MathType buffer_type = int32_t>
			class tensor {
				tensor() {
				throw std::exception("Invalid properties type, try using dmutils::structs::TensorProperties");
				}
			};

			template<constrains::MathType buffer_type, uint16_t... dims>
			class tensor<tensor_properties<dims...>, buffer_type>{
			public:
				using properties = tensor_properties<dims...>;

				using type = buffer_type;
				using const_type = const buffer_type;
				using pointer = buffer_type*;
				using const_pointer = const buffer_type*;
				using reference = buffer_type&;
				using const_reference = const buffer_type&;

				using iterator = std::_Array_iterator<type, properties::size>;
				using const_iterator = std::_Array_const_iterator<type, properties::size>;
				
				using reverse_iterator = std::reverse_iterator<iterator>;
				using const_reverse_iterator = std::reverse_iterator<const_iterator>;


				std::array<buffer_type, properties::size> buffer = {};


			public:

				inline constexpr size_t getSize() {
					return properties::size;
				}

				inline constexpr uint16_t getRank() {
					return properties::rank;
				}

				inline constexpr std::array<type, properties::rank> getDimentions() {
					std::array<type, properties::rank> ret;
					std::copy_n(properties::dimentions.begin(), properties::rank, ret.begin());
					return ret;
				}

				inline constexpr size_t getDimentionSize(uint16_t rankPos) {
					if (rankPos > properties::rank) throw std::out_of_range("Rank too hight.\n");
					return properties::dimentions[rankPos];
				}

				inline constexpr properties getProperties() {
					return properties();
				}

				constexpr reference operator [](size_t index) {
					if(index >= properties::size){
						std::cout << "The index is outside the tensor. (Max [" + std::to_string(properties::size - 1) + "], Min [0])";
						throw std::out_of_range("The index is outside the tensor. (Max [" + std::to_string(properties::size - 1) + "], Min [0])");
					}

					return buffer[index];
				}

				constexpr const_reference operator [](size_t index) const {
					if (index >= properties::size) {
						std::cout << "The index is outside the tensor. (Max [" + std::to_string(properties::size - 1) + "], Min [0])";
						throw std::out_of_range("The index is outside the tensor. (Max [" + std::to_string(properties::size - 1) + "], Min [0])");
					}

					return buffer[index];
				}

				template<constrains::UnsignedIntegral... uitype = size_t>
				constexpr reference operator ()(uitype... indexes) {

					constexpr uint16_t IndexCount = sizeof...(indexes);
					if (!IndexCount) {
						std::cout << "No index provided.\n";
						throw std::invalid_argument("No index provided.\n");
					}

					if(IndexCount <= properties::rank) {
						std::array<size_t, IndexCount> IndexesArray = { indexes... };

						size_t index = 0;
						uint64_t indexMultiplier = 1;

						for (uint16_t i = 0; i < IndexCount; i++) {
							if (IndexesArray[i] >= properties::dimentions[i]) {
								std::cout << "The index is outside the tensor."
									"\n(Max[" + std::to_string(properties::dimentions[i] - 1) + "],"
									" Attempted[" + std::to_string(IndexesArray[i]) + "])";

								throw std::out_of_range("The index is outside the tensor."
									"\n(Max[" + std::to_string(properties::dimentions[i] - 1) + "],"
									" Attempted[" + std::to_string(IndexesArray[i]) + "])");
							}

							index += IndexesArray[i] * indexMultiplier;
							indexMultiplier *= properties::dimentions[i];
							
						}

						return buffer[index];
					}

					std::cout << "Amount of indexes provided exceed the tensor rank.";
					throw std::out_of_range("Amount of indexes provided exceed the tensor rank.");

				}

				/*
				template<constrains::UnsignedIntegral... uitype = size_t>
				constexpr const_reference operator ()(uitype... indexes) {

					constexpr uint16_t IndexCount = sizeof...(indexes);
					if (!IndexCount) {
						std::cout << "No index provided.\n";
						throw std::invalid_argument("No index provided.\n");
					}

					if (IndexCount <= rank) {
						std::array<size_t, IndexCount> IndexesArray = { indexes... };

						size_t index = 0; // IndexesArray[1];
						uint64_t indexMultiplier = 1;

						for (uint16_t i = 0; i < IndexCount; i++) {
							if (IndexesArray[i] >= dimentions[i]) {
								std::cout << "The index is outside the tensor."
									"\n(Max[" + std::to_string(dimentions[i] - 1) + "],"
									" Attempted[" + std::to_string(IndexesArray[i]) + "])";

								throw std::out_of_range("The index is outside the tensor."
									"\n(Max[" + std::to_string(dimentions[i] - 1) + "],"
									" Attempted[" + std::to_string(IndexesArray[i]) + "])");
							}

							index += IndexesArray[i] * indexMultiplier;
							indexMultiplier *= dimentions[i];

						}

						return buffer[index];
					}

					std::cout << "Amount of indexes provided exceed the tensor rank.";
					throw std::out_of_range("Amount of indexes provided exceed the tensor rank.");

				}
				*/




			};

			template<uint16_t m, uint16_t n, constrains::MathType buffer_type = int32_t>
			using matrix = tensor<tensor_properties<m, n>, buffer_type>;

			template<uint16_t r, constrains::MathType buffer_type = int32_t>
			using vector = tensor<tensor_properties<r>, buffer_type>;


		}
		

		/*

		template<uint16_t m_, uint16_t n_, uint16_t o_, constrains::MathType ty_>
		class t_matrix < matrix3d<m_, n_, o_>, ty_ >
		{
		public:

			using dim_type = matrix3d<m_, n_, o_>;


			dim_type dim;
			std::array<ty_, m_* n_* o_> buffer;

			ty_& operator()(uint16_t index_m, uint16_t index_n, uint16_t index_o) {
				if((index_m >= dim.m) || (index_n >= dim.n) || (index_o >= dim.o) || (index_m * index_n * index_o == 0) ) {
					throw std::out_of_range("Tried to access a position outside of the matrix");
				}

				return buffer[index_n + index_m * dim.n + index_o * dim.m * dim.o];

				///index_n + 
				///	(index_m * dim.n) + 
				///	(index_o * dim.m * dim.o) + 
				///	(index_p * dim.m * dim.o * dim.n) + 
				///	(index_q * dim.m * dim.o * dim.n * dim.p);

			}

		};

		*/


	}


	/*


	template<constrains::MatrixDim dim_type, constrains::MathType ty_ = dgt::real>
	class matrix 
	{
		matrix() {
			throw std::exception ("This should never be constructed.");
		}
	};

	template<uint16_t m_, uint16_t n_, uint16_t o_, constrains::MathType ty_>
	class matrix < matrix3d<m_, n_, o_>, ty_ >
	{
	public:

		using dim = matrix3d<m_, n_, o_>;

		std::array<std::array<std::array<ty_, o_ >, n_>, m_> buffer;

	};

	template<uint16_t m_, uint16_t n_, constrains::MathType ty_>
	class matrix < matrix2d<m_, n_>, ty_ >
	{
	public:

		using dim = matrix2d<m_, n_>;

		std::array<std::array<ty_, n_>, m_> buffer;

	};

	template<uint16_t n_, constrains::MathType ty_>
	class matrix < matrixrow<n_>, ty_ >
	{
	public:

		using dim = matrixrow<n_>;

		std::array<std::array<ty_, n_>, 1> buffer;

	};

	template<uint16_t m_, constrains::MathType ty_>
	class matrix < matrixcol<m_>, ty_ >
	{
	public:

		using dim = matrixcol<m_>;

		std::array<std::array<ty_, 1>, m_> buffer;

	};
	
	*/

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

}

_DMP_END