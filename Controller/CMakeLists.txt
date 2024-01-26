# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.17)

project(Controller)

# Add the direct_input_wheel_read directory as a subdirectory
add_subdirectory(external/direct_input_wheel_read)

# Find the OpenCV package
set(JSON_FILE_PATH "../configuration.json")
file(READ ${JSON_FILE_PATH} CONTENT)
string(REGEX MATCH "\"opencv_dir\" *: *\"([^\"]*)\"" _ ${CONTENT})
set(OpenCV_DIR ${CMAKE_MATCH_1})
find_package(OpenCV REQUIRED)

# Find the nlohmann_json package
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/nlohmann)

# Specify the executable and its source files
add_executable(Controller WIN32
    src/main.cpp
    src/robot.cpp
    src/camera.cpp 
    external/direct_input_wheel_read/src/direct_input_wheel_read.cpp
    external/nlohmann/json.hpp
)

target_include_directories(Controller PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/direct_input_wheel_read/include
    ${OpenCV_INCLUDE_DIRS} # Include the OpenCV include directories
    ${OpenCV_INCLUDE_DIRS}/x64/vc16/bin
    )
# ${CMAKE_CURRENT_SOURCE_DIR}/external/nlohmann_json

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
    PRIVATE direct_input_wheel_read
    PRIVATE ws2_32
    ${OpenCV_LIBS} # Link the OpenCV libraries
)

target_compile_features(Controller PUBLIC cxx_std_17)
