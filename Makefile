# Hardcoded by hand (just for personal use),
# but in real case it must be fixed
CXX = /opt/homebrew/opt/llvm/bin/clang++
CXXFLAGS = -std=c++20 -stdlib=libc++ -fno-implicit-modules -fno-implicit-module-maps

all: main

Vector.o: Vector.cppm
	$(CXX) $(CXXFLAGS) -fmodule-output=Vector.pcm -c $< -o $@

Vector-impl.o: Vector-impl.cpp Vector.o
	$(CXX) $(CXXFLAGS) -fprebuilt-module-path=. -c $< -o $@

main.o: main.cpp Vector.o
	$(CXX) $(CXXFLAGS) -fprebuilt-module-path=. -c $< -o $@

main: main.o Vector.o Vector-impl.o
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f *.o *.pcm main
