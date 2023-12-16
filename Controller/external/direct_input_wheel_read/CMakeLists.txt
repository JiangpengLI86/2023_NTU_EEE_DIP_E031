# Minimum required version of CMake
cmake_minimum_required(VERSION 3.17)

# Define the project name
project(direct_input_wheel_read)

# Create a library target named 'direct_input_wheel_read' from the source file 'src/direct_input_wheel_read.cpp'
add_library(direct_input_wheel_read
    src/direct_input_wheel_read.cpp)

# Specify the directories where the compiler can find the include files for the 'direct_input_wheel_read' library
target_include_directories(direct_input_wheel_read PUBLIC include)

# Link the 'direct_input_wheel_read' library with its dependencies
# 'dxguid' and 'dinput8' are the dependencies of 'direct_input_wheel_read'
target_link_libraries(direct_input_wheel_read PRIVATE
    PRIVATE dxguid
    PRIVATE dinput8
)

# Specify the C++ standard to be used for compiling the 'direct_input_wheel_read' library
target_compile_features(direct_input_wheel_read PUBLIC cxx_std_17)