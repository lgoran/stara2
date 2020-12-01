#include "gtest/gtest.h"
#include "../src/zadatak.h"
#include <vector>
#include <list>
#include <deque>
#include <array>
#include <map>
#include <unordered_map>
#include <complex>
#include <string>
#include <fstream>
#include <stdexcept>
 
using namespace std;


TEST(STL1, nextperm){
	std::string str("gfc");
	print_permutation(str);
}


TEST(STL1, zipgeneral1){
	std::list<int> l1{1,2,3,4,5};
	std::vector<char> v1{'a','b','c'};
	std::vector<std::pair<int,char>> v2(3);
	zip(l1.begin(), l1.end(), v1.begin(), v1.end(), v2.begin());

	ASSERT_EQ(v2[2].first, 3);
	ASSERT_EQ(v2[1].second, 'b');

}

TEST(STL1, zipgeneral2){
	std::deque<int> l1{1,2,3,4,5};
	std::vector<char> v1{'a','b','c'};
	std::array<std::pair<int,char>, 3> v2;
	zip(l1.begin(), l1.end(), v1.begin(), v1.end(), v2.begin());

	ASSERT_EQ(v2[2].second, 'c');
	ASSERT_EQ(v2[1].second, 'b');
	ASSERT_EQ(v2[0].second, 'a');

}

TEST(STL1, zipvec1){
	std::vector<char> v1{'a','b','c'};
	std::vector<std::complex<double>> v2{ {0,1}, {1,0}, {1,1},{2,1}};
	auto v3 = zip(v1,v2);

	ASSERT_EQ(v3.size(),3u);
	ASSERT_EQ(v3[2].first, 'c');
	ASSERT_EQ(v3[1].first, 'b');
	ASSERT_EQ(v3[0].first, 'a');
	ASSERT_DOUBLE_EQ(v3[0].second.real(), std::complex<double>(0,1).real());
	ASSERT_DOUBLE_EQ(v3[1].second.real(), std::complex<double>(1,0).real());
	ASSERT_DOUBLE_EQ(v3[2].second.real(), std::complex<double>(1,1).real());

	ASSERT_DOUBLE_EQ(v3[0].second.imag(), std::complex<double>(0,1).imag());
	ASSERT_DOUBLE_EQ(v3[1].second.imag(), std::complex<double>(1,0).imag());
	ASSERT_DOUBLE_EQ(v3[2].second.imag(), std::complex<double>(1,1).imag());
}


TEST(STL1, phone){
	std::vector<std::string>  vec_str{ "0911234567", "011  23 45  67", "021 1234 56", 
		                               "+385 1 1234567", "385 1 1234567", "1234567"  };
	normalize_phone_number(vec_str);
	ASSERT_STREQ(vec_str[0].c_str(), "+385911234567");
	ASSERT_STREQ(vec_str[1].c_str(), "+38511234567");
	ASSERT_STREQ(vec_str[2].c_str(), "+38521123456");
	ASSERT_STREQ(vec_str[3].c_str(), "+38511234567");
	ASSERT_STREQ(vec_str[4].c_str(), "+38511234567");
	ASSERT_STREQ(vec_str[5].c_str(), "+38511234567");
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
