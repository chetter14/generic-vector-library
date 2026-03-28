#include <gtest/gtest.h>
#include <string>
import Vector;

TEST(String, Comparison) {
  std::string a{"hello"};
  const char* b = "hello";
  EXPECT_STREQ(a.c_str(), b);
}

TEST(Integer, Comparison) {
  long long a = 2;
  short b = 2;
  EXPECT_EQ(a, b);
}