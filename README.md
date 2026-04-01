## About 

In this project I try to write my implementation of simple generic vector. The idea is to practice my skills of *metaprogramming*, namely templates, concepts, etc. 

I do not focus on implementation details or any math logic behind it. My attention is concentrated on types and compile-time checks (basically, concepts).

*C++20* is used for this project.

## Structure

- **src** with implementation of vector and sample
- **tests** of vector library

## Build

It's done with *CMake*. By default I set up a *cmake preset* for Visual Studio 2022 (I use this IDE in development).

## Vector class

What does this Vector class provide and can do? I set the following requirements for the Vector:

- it can be a 1-, 2-, 3-dimensional. No other values.
- it consists of only arithmetic values, like int, float and double, or custom values that define arithmetic operations.
- operations that can be run with this class: addition, subtraction, scalar multiplication, printing to output.
