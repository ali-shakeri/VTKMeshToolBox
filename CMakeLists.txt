cmake_minimum_required(VERSION 2.8)

PROJECT(VTKMeshToolBox)

add_compile_options(-std=c++14)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(VTKMeshToolBox MACOSX_BUNDLE vtk_mesh_toolbox.cpp example.cpp)

target_link_libraries(VTKMeshToolBox ${VTK_LIBRARIES})
