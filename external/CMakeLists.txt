# GLM - has native cmake support

add_subdirectory(glm)


# GLFW - has native cmake support

set( GLFW_BUILD_EXAMPLES  OFF CACHE INTERNAL "" )
set( GLFW_BUILD_TESTS     OFF CACHE INTERNAL "" )
set( GLFW_BUILD_DOCS      OFF CACHE INTERNAL "" )
set( GLFW_INSTALL         OFF CACHE INTERNAL "" )
add_subdirectory(glfw)

# GLAD

set(GLAD_PATH ${CMAKE_SOURCE_DIR}/external/glad)
add_library(glad ${GLAD_PATH}/src/glad.c)
target_include_directories(glad PUBLIC ${GLAD_PATH}/include/)

# ImGUI 
set(IMGUI_PATH ${CMAKE_SOURCE_DIR}/external/imgui)

add_library(imgui 
    ${IMGUI_PATH}/imgui.cpp
    ${IMGUI_PATH}/imgui_demo.cpp
    ${IMGUI_PATH}/imgui_tables.cpp
    ${IMGUI_PATH}/imgui_draw.cpp
    ${IMGUI_PATH}/imgui_widgets.cpp
    ${IMGUI_PATH}/imgui_impl_glfw.cpp
    ${IMGUI_PATH}/imgui_impl_opengl3.cpp
    )

target_include_directories(imgui PUBLIC ${IMGUI_PATH})
target_link_libraries(imgui PUBLIC glfw)
