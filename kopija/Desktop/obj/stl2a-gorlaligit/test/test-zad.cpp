#include "gtest/gtest.h"
#include "../src/zadatak.h"
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <sstream>
 
using namespace std;

TEST(STL2, Zadatak1) {
   vector<string> words;
   readFile("f1.txt", words);
   ASSERT_EQ(words.size(), 8u);
   ASSERT_STREQ(words[0].c_str(), "one");
   ASSERT_STREQ(words[1].c_str(), "two");
   ASSERT_STREQ(words[2].c_str(), "three");
   ASSERT_STREQ(words[3].c_str(), "four");
   ASSERT_STREQ(words[4].c_str(), "equal");
   ASSERT_STREQ(words[5].c_str(), "new");
   ASSERT_STREQ(words[6].c_str(), "Next-three");
   ASSERT_STREQ(words[7].c_str(), "zero");
}

TEST(STL2, Zadatak2) {
    vector<string> words;
    readFile("text.txt", words);
    X xclass(words);
    ASSERT_EQ( xclass.max_br_suglasnika(), 11);
    ostringstream out;
    xclass.print(out,7);

    ASSERT_STREQ(out.str().c_str(), "JavaScript Objective-C Significant Smalltalk typically ");
   }



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
