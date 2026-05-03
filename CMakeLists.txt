cmake_minimum_required(VERSION 3.24)
project(rubik LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

# Place the binary in build/, with shaders alongside it.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include(FetchContent)

# ── GLFW ──────────────────────────────────────────────────────────
set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL        OFF CACHE BOOL "" FORCE)

FetchContent_Declare(glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.4
    GIT_SHALLOW    TRUE)
FetchContent_MakeAvailable(glfw)

# ── GLM (header-only) ─────────────────────────────────────────────
FetchContent_Declare(glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        1.0.1
    GIT_SHALLOW    TRUE)
FetchContent_MakeAvailable(glm)

# ── GLAD (vendored under external/glad/) ──────────────────────────
add_library(glad STATIC external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

# ── OpenGL ────────────────────────────────────────────────────────
find_package(OpenGL REQUIRED)

# ── Dear ImGui (in-app menus + help overlay) ──────────────────────
FetchContent_Declare(imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG        v1.91.5
    GIT_SHALLOW    TRUE)
FetchContent_MakeAvailable(imgui)

add_library(imgui STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp)
target_include_directories(imgui PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends)
target_link_libraries(imgui PUBLIC glfw)

# ── Sources ───────────────────────────────────────────────────────
file(GLOB_RECURSE SOLVER_SOURCES CONFIGURE_DEPENDS "include/solver/*.cpp")

add_executable(rubik
    main.cpp
    ${SOLVER_SOURCES})

target_include_directories(rubik PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(rubik PRIVATE
    glm::glm
    glad
    imgui          # transitively brings glfw
    OpenGL::GL)

# ── Warning level ─────────────────────────────────────────────────
if(MSVC)
    target_compile_options(rubik PRIVATE /W3)
else()
    target_compile_options(rubik PRIVATE -Wall -Wno-unused-variable -Wno-unused-but-set-variable)
endif()

# ── Copy shaders next to the binary so relative paths just work ───
add_custom_command(TARGET rubik POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/shaders
            $<TARGET_FILE_DIR:rubik>/shaders)
