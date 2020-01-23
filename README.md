# VTKMeshToolBox
This library provides set of tools based on VTK library to convert and modify meshes.

## Prerequisites
You will need VTK library. However you can turn off rendering when you install from source.

## Install
Create a build directory (recommended) and run cmake from there:
```
mkdir build
cd build
cmake ..
```
Then run make for making example:
```
make
```

## Current functionalities
- Convert STL format to vtu (VTK unstructured grid)
- Substract a mesh from another one
- Generate mesh for basic geometries

