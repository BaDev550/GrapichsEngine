cmake_minimum_required(VERSION 3.15)

# Project name
project(GraphicsEngine)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source and header files
file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.h)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE 
    include
    include/core
    include/renderer
    thirdParty/
)

# Link OpenGL
find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
    message(STATUS "OpenGL found!")
    target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)
else()
    message(FATAL_ERROR "OpenGL not found!")
endif()

# Link GLFW manually
set(GLFW_LIB_DIR ${CMAKE_SOURCE_DIR}/thirdParty/glfw)  # Path to glfw3.lib
if(EXISTS ${GLFW_LIB_DIR}/glfw3.lib)
    message(STATUS "GLFW library found!")
    target_link_directories(${PROJECT_NAME} PRIVATE ${GLFW_LIB_DIR})
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw3.lib)
else()
    message(FATAL_ERROR "GLFW library (glfw3.lib) not found in thirdParty/glfw!")
endif()

# Add Glad
set(GLAD_SOURCES ${CMAKE_SOURCE_DIR}/thirdParty/glad/src/glad.c)
if(EXISTS ${GLAD_SOURCES})
    message(STATUS "Glad found!")
    target_sources(${PROJECT_NAME} PRIVATE ${GLAD_SOURCES})
else()
    message(FATAL_ERROR "Glad source file (glad.c) not found in thirdParty/glad/src!")
endif()

# Add Assimp
set(ASSIMP_LIB_DIR ${CMAKE_SOURCE_DIR}/thirdParty/assimp)
if(EXISTS ${ASSIMP_LIB_DIR})
    message(STATUS "Assimp library found!")
    target_link_directories(${PROJECT_NAME} PRIVATE ${ASSIMP_LIB_DIR})
    target_link_libraries(${PROJECT_NAME} PRIVATE assimp-vc143-mt.lib) # Adjust the library name if needed
else()
    message(FATAL_ERROR "Assimp library not found in thirdParty/assimp/lib!")
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)
