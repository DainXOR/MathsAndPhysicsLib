#include <iostream>

#include "complex_types.h"
#include "matrix_types.h"

using namespace dmp;

int main() {

	//dmt::vector<int, 3> v0{3, 8, 1};
	//dmt::vector<int, 3> v1{2, 4, 1};
	//dmt::vector<int, 3> v2{ 2, 4 };

	dmt::matrix <dmt::matrixrow<3>> mtrow { 1,  2,  3, };
	dmt::matrix <dmt::matrixcol<3>> mtcol { 1,  4,  7, };

	// dmt::matrix <dmt::matrix3d<3, 3, 3>> mt3d1     {1,  2,  3,  4,  5,  6,  7,  8,  9,
	// 												10, 11, 12, 13, 14, 15, 16, 17, 18,
	// 												19, 20, 21, 22, 23, 24, 25, 26, 27 };
	// 
	// dmt::matrix <dmt::matrix3d<3, 3, 3>> mt3d2{{{
	// 											{{{1,  2,  3},  {4,  5,  6},  {7,  8,  9}}},
	// 											{{{10, 11, 12}, {13, 14, 15}, {16, 17, 18}}},
	// 											{{{19, 20, 21}, {22, 23, 24}, {25, 26, 27}}}
	// 											}}};
	// 
	// dmt::matrix <dmt::matrix2d<3, 3>> mt2d{ std::array<dgt::real, 3>{1,  2,  3},
	// 										std::array<dgt::real, 3>{4,  5,  6},
	// 										std::array<dgt::real, 3>{7,  8,  9} };

	// dmt::init_array_3d<dgt::real, 3, 3, 3> arr0{ 1,  2,  3,  4,  5,  6,  7,  8,  9,
	// 												10, 11, 12, 13, 14, 15, 16, 17, 18,
	// 												19, 20, 21, 22, 23, 24, 25, 26, 27 };
	// dmt::matrix mt3d0 = dmt::make_matrix(arr0);
	// 
	// 
	// dmt::init_list_3d<dgt::real> list0{ {{1,  2,  3},  {4,  5,  6},  {7,  8,  9}},
	// 									{{10, 11, 12}, {13, 14, 15}, {16, 17, 18}},
	// 									{{19, 20, 21}, {22, 23, 24}, {25, 26, 27}} };
	// dmt::matrix testeanding = dmt::make_matrix<dgt::real, 3, 3, 3>(list0);

	//v2 += v1 + v0;
	//dmt::vector<float, 3> v2 = v0 + v1;
	//v2 - 5;

	/// // dmt::complex Test0;
	dmt::complex Test1 = { 1, -5 };
	/// // dmt::complex Test2 = { 32.f, 110.4 };
	/// // dmt::complex Test3 = { 7.4, 3.2f };
	/// // dmt::complex Test4 = { '7', 69 }; 


	/// // Test0 += (Test3 + Test2);

	/// > Task: Overload << operator
	
	/// // std::cout << std::string(Test0) << "\n";
	std::cout << Test1 << "\n";
	// CONSTEXPR_TEST(abs(-5));
	/// // std::cout << std::string(Test2) << "\n";
	/// // std::cout << std::string(Test3) << "\n";
	/// // std::cout << std::string(Test4) << "\n";


}
