# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.17)

project(Controller)

add_executable(Controller WIN32
    src/main.cpp
    src/robot.cpp "external/direct_input_wheel_read/include/direct_input_wheel_read.h" "external/direct_input_wheel_read/src/direct_input_wheel_read.cpp")

target_include_directories(Controller PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_path(WINSOCK_INCLUDE_DIR WinSock2.h)
find_library(WINSOCK_LIBRARY mswsock)
find_library(WINSOCK2_LIBRARY ws2_32)
    
# Handle the REQUIRED argument and set WINSOCK_FOUND
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(WinSock DEFAULT_MSG WINSOCK_LIBRARY WINSOCK2_LIBRARY WINSOCK_INCLUDE_DIR)

# mark variables as advanced. Advanced variables do not show up in the CMake GUI by default
mark_as_advanced(WINSOCK_INCLUDE_DIR STATIC)
mark_as_advanced(WINSOCK_LIBRARY STATIC)
mark_as_advanced(WINSOCK2_LIBRARY STATIC)

# checks if the CMake generator is MinGW
if(MINGW)
    set(CMAKE_C_STANDARD_LIBRARIES "${CMAKE_C_STANDARD_LIBRARIES} -lwsock32 -lws2_32 -lbcrypt")
    set(CMAKE_CXX_STANDARD_LIBRARIES "${CMAKE_CXX_STANDARD_LIBRARIES} -lwsock32 -lws2_32 -lbcrypt")
endif()

# Inform compiler that code should be built to be compatible with Windows 7 or later
add_definitions(-D_WIN32_WINNT=0x0601)

target_link_libraries(Controller
    PRIVATE dxguid
    PRIVATE dinput8
    ws2_32)

target_compile_features(Controller PUBLIC cxx_std_17)
