cmake_minimum_required(VERSION 3.0.2)
project(miniroscpp_demo)

add_subdirectory(thirdparty/miniroscpp)

add_executable(${PROJECT_NAME} src/main.cpp)

# Linking miniros using a direct name.
# All necessary includes will be added to target `some_executable` automatically
target_link_libraries(${PROJECT_NAME} miniroscpp)

# message(FATAL_ERROR "includes: ${MINIROS_INCLUDE_DIRS} ${MINIROS_INCLUDE_GENERATED_DIRS}")
# This is empty
# include_directories(${MINIROS_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR}/thirdparty/miniroscpp)
include_directories(thirdparty/miniroscpp/include)

# Adding paths to pregenerated headers.
target_include_directories(${PROJECT_NAME} PRIVATE ${MINIROS_INCLUDE_GENERATED_DIRS})
