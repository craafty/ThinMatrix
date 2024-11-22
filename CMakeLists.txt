cmake_minimum_required (VERSION 3.16)

project ("ThinMatrix")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "Disable Assimp tests")
set(ASSIMP_INSTALL OFF CACHE BOOL "Disable Assimp installation targets")
set(ASSIMP_BUILD_SAMPLES OFF CACHE BOOL "Disable Assimp sample programs")
set(ASSIMP_BUILD_DOCS OFF CACHE BOOL "Disable Assimp documentation build")

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

add_subdirectory(libs/glfw)
add_subdirectory(libs/glad)
add_subdirectory(libs/glm)
add_subdirectory(libs/stb_image)
add_subdirectory(libs/assimp)

# Add source to this project's executable.
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp"
)
add_executable(${PROJECT_NAME} ${MY_SOURCES})

target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}/include/"
	"${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE 
	glfw
	glad
	glm
	stb_image
	assimp
)