cmake_minimum_required (VERSION 2.8.9)

project (md2view)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -stdlib=libc++")
include_directories (./)

# pkgconfig
find_package(PkgConfig)

# boost
find_package (Boost COMPONENTS system program_options unit_test_framework REQUIRED)
include_directories (${Boost_INCLUDE_DIRS})
message("** Boost Include: ${Boost_INCLUDE_DIR}")
message("** Boost Libraries: ${Boost_LIBRARY_DIRS}")
message("** Boost Libraries: ${Boost_LIBRARIES}")

# opengl
find_package (OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
message("** OpenGL Include: ${OPENGL_INCLUDE_DIR}")
message("** OpenGL Libraries: ${OPENGL_LIBRARY_DIRS}")
message("** OpenGL Libraries: ${OPENGL_LIBRARIES}")

# sdl2
pkg_check_modules(SDL2 sdl2)
include_directories(${SDL2_INCLUDE_DIRS})
message("** SDL Include: ${SDL2_INCLUDE_DIRS}")
message("** SDL Libraries: ${SDL2_LIBRARY_DIR}")
message("** SDL Libraries: ${SDL2_LIBRARIES}")
link_directories(/usr/local/lib)

add_executable (md2view
	main.cpp
	Application.cpp
	Frustum.cpp
	Camera.cpp
	KeyManager.cpp
	Program.cpp
	Renderer.cpp
	MD2.cpp
	Model.cpp)

target_link_libraries (md2view
	${Boost_SYSTEM_LIBRARY}
	${Boost_PROGRAM_OPTIONS_LIBRARY}
	${SDL2_LIBRARY_DIR}
	${SDL2_LIBRARIES}
	${OPENGL_LIBRARIES})

add_library (md2view_tests SHARED
	tests/ComparatorTests.cpp
	tests/FloatTests.cpp
	tests/Vector3Tests.cpp
	tests/Vector4Tests.cpp
	tests/Matrix4Tests.cpp)

target_link_libraries (md2view_tests ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_executable (tests tests/tests.cpp)

target_link_libraries (tests ${Boost_SYSTEM_LIBRARY} md2view_tests)

enable_testing ()
add_test (UnitTests tests)
