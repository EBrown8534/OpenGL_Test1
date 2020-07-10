cmake_minimum_required(VERSION 3.13)
project(OpenGL_Test1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++" )

# Include SFML, GLEW and SOIL dependencies for linker
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cmake/SFML-2.5.1/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/cmake/SFML-2.5.1/lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cmake/glew-2.1.0/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/cmake/glew-2.1.0/lib/Release/win32)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cmake/soil/src)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/cmake/soil/lib)

add_executable(OpenGL_Test1 main.cpp Code/Shaders.cpp Headers/Shaders.h Headers/Settings.h Headers/Utilities.h)

# Link SFML, GLEW, SOIL, and OpenGL
target_link_libraries(OpenGL_Test1 sfml-audio-d sfml-graphics-d sfml-network-d sfml-system-d sfml-window-d glew32 SOIL opengl32)

# Copy dependencies for SFML and GLEW (SOIL is statically linked)
file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/cmake/SFML-2.5.1/bin/*.dll")
foreach (file ${files})
    get_filename_component(name ${file} NAME)
    configure_file(${file} ${CMAKE_CURRENT_BINARY_DIR}/${name} COPYONLY)
endforeach()
file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/cmake/glew-2.1.0/bin/Release/win32/*.dll")
foreach (file ${files})
    get_filename_component(name ${file} NAME)
    configure_file(${file} ${CMAKE_CURRENT_BINARY_DIR}/${name} COPYONLY)
endforeach()

# Copy shaders
file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/Shaders/*.glsl")
foreach (file ${files})
    get_filename_component(name ${file} NAME)
    configure_file(${file} ${CMAKE_CURRENT_BINARY_DIR}/Shaders/${name} COPYONLY)
endforeach()

# Copy assets
file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/Images/*")
foreach (file ${files})
    get_filename_component(name ${file} NAME)
    configure_file(${file} ${CMAKE_CURRENT_BINARY_DIR}/Images/${name} COPYONLY)
endforeach()
