/*
 * example.cpp
 * This example tests the STL Converter
 *
 *  Created on: Jan 21, 2020
 *      Author: Ali Shakeri
 */

#include "vtk_mesh_toolbox.h"
// #include <vtkCubeSource.h>
// #include <vtkCylinderSource.h>
// #include <vtkCleanPolyData.h>
// #include <vtkTriangleFilter.h>
// #include <vtkBooleanOperationPolyDataFilter.h>

using namespace VTKMeshToolBox;

int main () {
  std::string input_filename {"Data/input_1.stl"};
  std::string output_filename {"Data/input_1.vtu"};
  std::string input_filename2 {"Data/input_2.stl"};
  std::string output_filename2 {"Data/input_2.vtu"};
  std::string subtract_filename {"Data/subtract.vtu"};
  

  auto input1 = vtkSmartPointer<vtkPolyData>::New();
  auto input2 = vtkSmartPointer<vtkPolyData>::New();
  
  input1 = convert_stl_to_vtu(input_filename, output_filename);
  input2 = convert_stl_to_vtu(input_filename2, output_filename2);
  
  substract (input1, input2, subtract_filename);
   

  std::string filename {"Data/rectangle.vts"};
  generate_grid_rectangle (-0.1, 0.1, 10, 
                           -0.2, 0.2, 10,
                           -0.3, 0.3, 10, filename);
  
  return 0;
}
