# CMake treats the module interface as a library target that 'provides' the module
add_library(VectorLib STATIC Vector.cppm Vector-impl.cpp)
# Specify explicitly
set_target_properties(VectorLib PROPERTIES CXX_SCAN_FOR_MODULES ON)

add_executable(GenericVectorLibrary main.cpp)
# Ensure that it waits for 'VectorLib' to compile its BMI (Binary Module Interface)
target_link_libraries(GenericVectorLibrary PRIVATE VectorLib)