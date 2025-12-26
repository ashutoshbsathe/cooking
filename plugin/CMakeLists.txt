cmake_minimum_required(VERSION 3.16)
project(p2agent LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(SOURCE_SDK_DIR "/home/ashutosh/HDD/MachineLearning/source-sdk-2013")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -m32")

add_library(p2agent SHARED src/p2agent.cpp)

# Include paths (this replaces -I flags)
target_include_directories(p2agent PRIVATE
    ${SOURCE_SDK_DIR}/src/public
    ${SOURCE_SDK_DIR}/src/public/tier0
    ${SOURCE_SDK_DIR}/src/public/tier1
    ${SOURCE_SDK_DIR}/src/public/tier2
    ${SOURCE_SDK_DIR}/src/public/engine
    ${SOURCE_SDK_DIR}/src/common
)

# Required compile definitions (this replaces -D flags)
target_compile_definitions(p2agent PRIVATE
    POSIX
    LINUX
    _LINUX
    GNUC
    NO_HOOK_MALLOC
    NO_MALLOC_OVERRIDE
)

# C++ standard
target_compile_features(p2agent PRIVATE cxx_std_14)

target_link_directories(p2agent PRIVATE
    "/home/ashutosh/HDD/SteamLibrary/steamapps/common/Portal 2/bin"
)

# Link only what the engine exports
target_link_libraries(p2agent PRIVATE
    tier0
    vstdlib
)


set_target_properties(p2agent PROPERTIES
    PREFIX ""
    OUTPUT_NAME "p2agent"
)
