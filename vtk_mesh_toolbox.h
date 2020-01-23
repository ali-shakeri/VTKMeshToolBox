/*
 * vtk_mesh_toolbox.h
 *
 *  Created on: Jan 21, 2020
 *      Author: Ali Shakeri
 */

#ifndef STL_CONVERTER_H
#define STL_CONVERTER_H

#include <string>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>


namespace VTKMeshToolBox {
  enum class FileType {ASCII, BINARY};
    
  vtkSmartPointer<vtkPolyData>
  convert_stl_to_vtu (std::string input,std::string output);
    
  void substract (vtkSmartPointer<vtkPolyData> input1,
                  vtkSmartPointer<vtkPolyData> input2, std::string output);
  
  void generate_grid_rectangle (double xlo, double xhi, int nx,
                                double ylo, double yhi, int ny,
                                double zlo, double zhi, int nz,
                                std::string output);
}

#endif
