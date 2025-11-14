#!/bin/bash

# Format all .cpp, .hpp, .h, .cc files under the project
find . \( -name '*.cpp' -o -name '*.hpp' -o -name '*.h' -o -name '*.cppm' \) \
    -exec clang-format -i {} \;

echo "All files formatted."
