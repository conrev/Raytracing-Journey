cmake_minimum_required(VERSION 3.16)
project(RayTracer)

add_subdirectory(external)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/objects/sphere.cc
)


target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE glm)