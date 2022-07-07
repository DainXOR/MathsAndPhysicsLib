#include <iostream>

#include "complex_types.h"

using namespace dmp;

int main() {

	

	dmt::vector<int, 3> v0{3, 8, 1};
	dmt::vector<int, 3> v1{2, 4, 1};
	dmt::vector<int, 3> v2{ 2, 4 };

	//dmt::vector<float, 3> v2 = v0 + v1;
	//v2 - 5;

	//dmt::complex<dmt::vector<int, 1>> Test1 = { 1, 0 };
	dmt::complex Test1 = { 1, 0 };
	dmt::complex Test2 = { 32.f, 110.4 };
	dmt::complex Test3 = { 7.4, 3.2f };
	dmt::complex Test4 = { '7', 69 };
	
	dmt::complex Test0;
	Test0 += (Test3 + Test2);

	std::cout << std::string(Test0) << "\n";
	std::cout << std::string(Test1) << "\n";
	std::cout << std::string(Test2) << "\n";
	std::cout << std::string(Test3) << "\n";
	std::cout << std::string(Test4) << "\n";


}
