# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("2023_NTU_EEE_DIP_E031")

# Include sub-projects.
add_subdirectory ("Controller")

# ---------------------- Build the Antenna project (C#) ---------------------- #
# Build the Antenna project (C#) together with the C++ project. Since I cannot find a way to convert
# the C# project's csproj file to a cmake file, I have to use a custom command to build the C# project.

# Set the output path for the C# project
set(CSHARP_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/out/Antenna-x64-release")

# Custom command to build C# project
add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/CSharpBuildFlag
    COMMAND msbuild /property:Configuration=Release /property:OutputPath=${CSHARP_OUTPUT_PATH} ${CMAKE_SOURCE_DIR}/Antenna/PGRtls/D-DWM-PG.csproj
    COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_BINARY_DIR}/CSharpBuildFlag
    COMMENT "Building C# Project..."
)

# Custom target that depends on the above custom command
add_custom_target(
    BuildCSharpProject ALL
    DEPENDS ${CMAKE_BINARY_DIR}/CSharpBuildFlag
)

# ---------------------- Build the Antenna project (C#) ---------------------- #

# By adding this line, the compiler will not rebuild the C# project if it is not modified, which will save a lot of time.
add_dependencies(Controller BuildCSharpProject)