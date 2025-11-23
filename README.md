## About 

In this project I try to write my implementation of generic vector. The idea is to practice my skills of *metaprogramming*, namely templates, concepts, etc. 

I do not focus on implementation details or any math logic behind it. My attention is concentrated on types and compile-time checks (basically, concepts).

*C++20* is used for this project.

## Vector class

What does this Vector class provide and can do? I set the following requirements for the Vector:

- it can be a 1-, 2-, 3-dimensional. No other values.
- it consists of only arithmetic values, like int, float and double, or custom values that define arithmetic operations.
- operations that can be run with this class: addition, subtraction, scalar multiplication, printing to output.

## Sample

In `main.cpp` I have:
1) static assertions to test concepts that I defined for Vector module
2) custom types for static assertions
3) simple operations on vectors to show how they work