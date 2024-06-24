#include <iostream>
#include <type_traits>
#include <vector>
#include <memory>

// #include "complex_types.h"
#include "tensor_types.h"
#include "mFunctions.h"

using namespace dmp;
//using namespace dmt::tests::newStructs;

template<uint16_t...dims>
void UnaPrueba() {
	std::cout << dmt::structs::tensor_size<dims...> << "\n";
	std::cin.get();
}

void Hmmmmmmmm();

int main() {
	
	//dmt::vector<int, 3> v0{3, 8, 1};
	//dmt::vector<int, 3> v1{2, 4, 1};
	//dmt::vector<int, 3> v2{ 2, 4 };
	

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

	// UnaPrueba<2, 4, 4, 5>();
	dmt::tensor a;
	dmt::tensor<short> b;
	dmt::tensor<long, 3, 2> c;

	constexpr int r = 10000;
	using value_type = int;

	std::conditional_t<r && (r < (((1 << 16) - 1) / sizeof(value_type))),
		std::array<value_type, r>,
		std::vector<value_type>> buffer = {1, 2, 3};


	buffer = { 0, 6, 10, 25 };
	//dmt::tensor<tprops<3, 2, 7, 5, 9, 4>> Tensor1;

	//auto tensorProps = Tensor1.getProperties();
	//auto tensorDims = Tensor1.getDimentions();

	//std::cout << Tensor1.getSize() << "\n";
	//std::cout << Tensor1.getRank() << "\n";

	
	//std::cout << "\n";
	//for (auto value : Tensor1.getDimentions()) {
	//	std::cout << value << "\n";
	//}
	

	//dmt::matrix<tprops<7, 5>> Matrix1;
	//
	//std::cout << "\n";
	//auto tensorDims2 = Matrix1.getDimentions();
	/*
	for (auto value : tensorDims2) {
		std::cout << value << "\n";
	}
	*/
	// Hmmmmmmmm();

	

	//std::cout << Tensor1.getSize() << "\n";
	//std::cout << Tensor1.getRank() << "\n";


	//std::cout << "\n";
	//for (auto value : Tensor1.getDimentions()) {
	//	std::cout << value << "\n";
	//}
	
}

/*
void Hmmmmmmmm() {

	dmt::tensor<tprops<3, 2, 7, 5, 9, 4>> Tensor1;
	for (uint16_t i = 0; i < Tensor1.getSize(); i++) {
		Tensor1[i] = i;
	}

	dmt::matrix<tprops<7, 5>> Matrix1;
	

	for (int r = 0; r < Tensor1.getDimentionSize(5); r++) {
		for (int q = 0; q < Tensor1.getDimentionSize(4); q++) {
			for (int p = 0; p < Tensor1.getDimentionSize(3); p++) {
				for (int o = 0; o < Tensor1.getDimentionSize(2); o++) {
					for (int n = 0; n < Tensor1.getDimentionSize(1); n++) {
						for (int m = 0; m < Tensor1.getDimentionSize(0); m++) {
							std::cout << Tensor1(m, n, o, p, q, r) << "\n";
						}
					}
				}
			}
		}
	}

	for (int n = 0; n < Matrix1.getDimentionSize(1); n++) {
		for (int m = 0; m < Matrix1.getDimentionSize(0); m++) {
			std::cout << Matrix1(m, n) << "\n";
		}
	}
}

*/