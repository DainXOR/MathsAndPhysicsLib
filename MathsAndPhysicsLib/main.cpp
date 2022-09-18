#include <iostream>
#include <type_traits>
#include <vector>

// #include "complex_types.h"
#include "tensor_types.h"
#include "mFunctions.h"

using namespace dmp;
using namespace dmt::tests::newStructs;


template<uint16_t... dims>
using tprops = dmutils::structs::tensor_properties<dims...>;


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
	
	tensor<tprops<3, 2, 7, 5, 9, 4>> Tensor1;

	auto tensorProps = Tensor1.getProperties();
	auto tensorDims = Tensor1.getDimentions();

	std::cout << tensorProps.size << "\n";
	std::cout << tensorProps.rank << "\n";

	std::cout << "\n";
	for (auto value : tensorDims) {
		std::cout << value << "\n";
	}
	
	matrix<7, 5> Matrix1;

	std::cout << "\n";
	auto tensorDims2 = Matrix1.getDimentions();

	for (auto value : tensorDims2) {
		std::cout << value << "\n";
	}

	//Hmmmmmmmm();
	
}


void Hmmmmmmmm() {

	tensor<tprops<3, 2, 7, 5, 9, 4>> Tensor1;
	for (uint16_t i = 0; i < Tensor1.getSize(); i++) {
		Tensor1[i] = i;
	}

	matrix<7, 5> Matrix1 =
	{	1,  2,  3,  10, 11,
		4,  5,  6,  12, 13,
		7,  8,  9,  14, 15,
		16, 17, 18, 19, 20,
		21, 29, 30, 32, 33,
		22, 28, 31, 34, 35,
		23, 24, 25, 26, 27
	};


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