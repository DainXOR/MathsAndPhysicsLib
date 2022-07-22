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

		template<uint16_t m_, uint16_t n_, uint16_t o_ = 0>
		struct matrix_dimention
		{
			using type = uint16_t;

			const uint16_t m = m_;
			const uint16_t n = n_;
			const uint16_t o = o_;
		};

		//template<uint16_t m_ = 2, uint16_t n_ = 2, uint16_t o_ = 0>
		//using mat_dim = matrix_dimention<m_, n_, o_>;

		template<uint16_t m_, uint16_t n_>
		struct matrix_dimention <m_, n_, 0>
		{
			using type = uint16_t;

			const uint16_t m = m_;
			const uint16_t n = n_;
		};

		template<uint16_t m_>
		struct matrix_dimention <m_, 1, 0>
		{
			using type = uint16_t;

			const uint16_t m = m_;
			const uint16_t n = 1;
		};

		template<uint16_t n_>
		struct matrix_dimention <1, n_, 0>
		{
			using type = uint16_t;

			const uint16_t m = 1;
			const uint16_t n = n_;
		};
	}

	using namespace raw_structs;

	template<uint16_t m_, uint16_t n_, uint16_t o_>
	using matrix3d = matrix_dimention<m_, n_, o_>;

	template<uint16_t m_, uint16_t n_>
	using matrix2d = matrix_dimention<m_, n_, 0>;

	template<uint16_t n_>
	using matrixcol = matrix_dimention<1, n_, 0>;

	template<uint16_t m_>
	using matrixrow = matrix_dimention<m_, 1, 0>;


	template<constrains::Arithmetic ty_>
	using init_list_3d = std::initializer_list <std::initializer_list<std::initializer_list<ty_>>>;
	template<constrains::Arithmetic ty_, uint16_t m_, uint16_t n_, uint16_t o_>
	using init_array_3d = std::array<std::array<std::array<ty_, o_>, n_>, m_>;

	template<constrains::Arithmetic ty_>
	using init_list_2d = std::initializer_list <std::initializer_list<ty_>>;
	template<constrains::Arithmetic ty_, uint16_t m_, uint16_t n_>
	using init_array_2d = std::array<std::array<ty_, n_>, m_>;

	template<constrains::Arithmetic ty_>
	using init_list_col = std::initializer_list <std::initializer_list<ty_>>;
	template<constrains::Arithmetic ty_, uint16_t n_>
	using init_array_col = std::array<std::array<ty_, n_>, 1>;

	template<constrains::Arithmetic ty_>
	using init_list_row = std::initializer_list <std::initializer_list<ty_>>;
	template<constrains::Arithmetic ty_, uint16_t m_>
	using init_array_row = std::array<std::array<ty_, 1>, m_>;






	namespace tests {

		namespace newStructs {
			using namespace structs;

			//template<constrains::TensorProps<,>>
			class Pruebas {


			};

			template<typename Properties, constrains::MathType buffer_type = uint16_t>
			class tensor {
				tensor() {
				throw std::exception("Invalid properties type, try using dmutils::structs::TensorProperties");
			}
			};

			template<constrains::MathType buffer_type, uint16_t... dims>
			class tensor<TensorProperties<dims...>, buffer_type>{
			public:
				using type = buffer_type;
				using const_type = const buffer_type;
				using pointer = buffer_type*;
				using const_pointer = const buffer_type*;
				using reference = buffer_type&;
				using const_reference = const buffer_type&;

				using properties = TensorProperties<dims...>;

			protected:
				const uint16_t rank = properties::rank;
				const uint16_t size = properties::size;
				const std::array<uint16_t, properties::rank> dimentions = properties::dimentions;

			public:

				constexpr reference operator [](size_t index) {
					if(index >= size){
						throw std::out_of_range("The index is outside the tensor. (Max [" + std::to_string(size - 1) + "], Min [0])");
					}

					return buffer[index];
				}

				constexpr const_reference operator [](size_t index) const {
					if (index >= size) {
						throw std::out_of_range("The index is outside the tensor. (Max [" + std::to_string(size - 1) + "], Min [0])");
					}

					return buffer[index];
				}

				constexpr reference operator ()(uint16_t index_0, uint16_t indexes...) {
					static uint16_t dim_index = 0;

					if (index_0 >= dimentions[dim_index]) {
						throw std::out_of_range("The index is outside the tensor. (Max [" + std::to_string(size - 1) + "], Min [0])");
					}
					dim_index++;
					return this.operator()(indexes...);
				}

				constexpr const_reference operator ()(uint16_t index_n) const {
					if (index_n >= size) {
						throw std::out_of_range("The index is outside the tensor. (Max [" + std::to_string(size - 1) + "], Min [0])");
					}

					return buffer[index_n];
				}

			public:

				std::array<buffer_type, properties::size> buffer = {};
			};
		}
		


		template<constrains::MatrixDim dim_type, constrains::MathType ty_ = dgt::real>
		class t_matrix
		{
			t_matrix() {
				throw std::exception("This should never be constructed.");
			}
		};

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


		template<constrains::Arithmetic ty_>
		using init_list_3d = std::initializer_list <std::initializer_list<std::initializer_list<ty_>>>;
		template<constrains::Arithmetic ty_, uint16_t m_, uint16_t n_, uint16_t o_>
		using init_array_3d = std::array<ty_, m_* n_* o_>;



		template<constrains::MathType ty_, uint16_t m_, uint16_t n_, uint16_t o_>
		t_matrix< matrix3d<m_, n_, o_>, ty_> make_matrix(const init_list_3d<ty_>& list_) {
			init_array_3d<ty_, m_, n_, o_> array_ = {};

			{
				int i = 0, j = 0, k = 0;
				for (auto inner1 : list_) {
					for (auto inner2 : inner1) {
						for (auto inner3 : inner2) {

							array_[i][j][k++] = inner3;

						}
						k = 0;
						j++;
					}
					j = 0;
					i++;
				}
			}

			return { array_ };
		}
		template<constrains::MathType ty_, uint16_t m_, uint16_t n_, uint16_t o_>
		t_matrix< matrix3d<m_, n_, o_>, ty_> make_matrix(const init_array_3d<ty_, m_, n_, o_>& array_) {
			return { array_ };
		}


	}





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
	
	
	template<constrains::MathType ty_, uint16_t m_, uint16_t n_, uint16_t o_>
	matrix< matrix3d<m_, n_, o_>, ty_> make_matrix(const init_list_3d<ty_>& list_) {
		init_array_3d<ty_, m_, n_, o_> array_ = {};
		
		{
			int i = 0, j = 0, k = 0;
			for (auto inner1 : list_) {
				for (auto inner2 : inner1) {
					for (auto inner3 : inner2) {

						array_[i][j][k++] = inner3;

					}
					k = 0;
					j++;
				}
				j = 0;
				i++;
			}
		}

		return { array_ };
	}
	template<constrains::MathType ty_, uint16_t m_, uint16_t n_, uint16_t o_>
	matrix< matrix3d<m_, n_, o_>, ty_> make_matrix(const init_array_3d<ty_, m_, n_, o_>& array_) {
		return { array_ };
	}

	template<constrains::MathType ty_, uint16_t m_, uint16_t n_>
	matrix< matrix2d<m_, n_>, ty_> make_matrix(const init_list_2d<ty_>& list_) {
		init_array_2d<ty_, m_, n_> array_ = {};

		{
			int i = 0, j = 0;
			for (auto inner1 : list_) {
				for (auto inner2 : inner1) {
					array_[i][j++] = inner2;
				}
				j = 0;
				i++;
			}
		}

		return { array_ };
	}
	template<constrains::MathType ty_, uint16_t m_, uint16_t n_>
	matrix< matrix2d<m_, n_>, ty_> make_matrix(const init_array_2d<ty_, m_, n_>& array_) {
		return { array_ };
	}


	template<constrains::MathType ty_, uint16_t n_>
	matrix< matrixcol<n_>, ty_> make_matrix(const init_list_col<ty_>& list_) {
		init_array_col<ty_, n_> array_ = {};

		{
			int j = 0;
			for (auto inner1 : list_) {
				for (auto inner2 : inner1) {
					array_[0][j++] = inner2;
				}
				j = 0;
			}
		}

		return { array_ };
	}
	template<constrains::MathType ty_, uint16_t n_>
	matrix< matrixcol<n_>, ty_> make_matrix(const init_array_col<ty_, n_>& array_) {
		return { array_ };
	}

	template<constrains::MathType ty_, uint16_t m_>
	matrix< matrixrow<m_>, ty_> make_matrix(const init_list_row<ty_>& list_) {
		init_array_row<ty_, m_> array_ = {};

		{
			int i = 0;
			for (auto inner1 : list_) {
				for (auto inner2 : inner1) {
					array_[i][0] = inner2;
				}
				i = 0;
			}
		}

		return { array_ };
	}
	template<constrains::MathType ty_, uint16_t m_>
	matrix< matrixrow<m_>, ty_> make_matrix(const init_array_row<ty_, m_>& array_) {
		return { array_ };
	}

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