cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(nlohmann_json CONFIG REQUIRED)

file(GLOB SRC_FILES ./QueryAppLib/*.cpp)
add_library(QueryAppLib STATIC ${SRC_FILES})
target_include_directories(QueryAppLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/QueryAppLib/include)

target_link_libraries(QueryAppLib PUBLIC nlohmann_json::nlohmann_json)

project(QueryApp VERSION 1.0)
add_executable(QueryApp ./QueryApp/QueryApp.cpp)

target_link_libraries(QueryApp PUBLIC QueryAppLib)

enable_testing()
find_package(GTest REQUIRED)
add_executable(QueryApp_gtest ./TestQueryApp/test.cpp)
target_link_libraries(QueryApp_gtest PRIVATE GTest::GTest GTest::Main)
target_link_libraries(QueryApp_gtest PUBLIC QueryAppLib)
target_include_directories(QueryApp_gtest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/QueryAppLib/include)

add_test(NAME TestQueryApp COMMAND QueryApp_gtest --gtest_output=xml:./output.xml)