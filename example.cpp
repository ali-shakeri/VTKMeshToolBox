/*
 * example.cpp
 * This example tests the STL Converter
 *
 *  Created on: Jan 21, 2020
 *      Author: Ali Shakeri
 */

#include "vtk_mesh_toolbox.h"
#include <vtkSphereSource.h>

using namespace VTKMeshToolBox;

int main () {
  std::string input_filename {"Data/BodyMesh.stl"};
  std::string output_filename {"Data/BodyMesh.vtu"};
  std::string input_filename2 {"Data/servo.stl"};
  std::string output_filename2 {"Data/servo.vtu"};
  std::string subtract_filename {"Data/subtract.vtu"};
  
  vtkSmartPointer<vtkPolyData> input1;
  vtkSmartPointer<vtkPolyData> input2;
  
  input1 = convert_stl_to_vtu(input_filename, output_filename);
  input2 = convert_stl_to_vtu(input_filename2, output_filename2);
  
  substract(input1, input1, subtract_filename);
  
  return 0;
}
