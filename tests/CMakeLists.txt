add_executable(UnitTests main.cpp)

target_link_libraries(UnitTests PRIVATE
	GTest::gtest_main
	VectorLib
)

include(GoogleTest)
gtest_discover_tests(UnitTests)