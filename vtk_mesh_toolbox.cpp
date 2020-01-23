/*
 * vtk_mesh_toolbox.cpp
 *
 *  Created on: Jan 21, 2020
 *      Author: Ali Shakeri
 */

#include "vtk_mesh_toolbox.h"

#include <vtkSTLReader.h>
#include <vtkUnstructuredGrid.h>
#include <vtkXMLUnstructuredGridWriter.h>
#include <vtkAppendFilter.h>

#include <vtkBooleanOperationPolyDataFilter.h>
#include <vtkActor.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>

#include <vtkXMLStructuredGridWriter.h>
#include <vtkStructuredGrid.h>

using namespace VTKMeshToolBox;


vtkSmartPointer<vtkPolyData> VTKMeshToolBox::
convert_stl_to_vtu (std::string input, std::string output) {
  auto stl_reader = vtkSmartPointer<vtkSTLReader>::New();
  stl_reader->SetFileName (input.c_str());
  stl_reader->Update();
  
  // vtkAppendFilter accepts any input, and produces a vtkUnstructuredGrid
  auto appendFilter = vtkSmartPointer<vtkAppendFilter>::New();
  appendFilter->AddInputData(stl_reader->GetOutput());
  appendFilter->Update();
  
  auto unstructured_grid = vtkSmartPointer<vtkUnstructuredGrid>::New();
  unstructured_grid->ShallowCopy(appendFilter->GetOutput());
  
  auto writer = vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
  writer->SetFileName(output.c_str());
  writer->SetInputData(unstructured_grid);
  
  writer->Write();
  
  // return polydata for later use
  auto poly_data = vtkSmartPointer<vtkPolyData>::New();
  poly_data->ShallowCopy(stl_reader->GetOutput());
  return poly_data;
}


void VTKMeshToolBox::
substract (vtkSmartPointer<vtkPolyData> input1,
           vtkSmartPointer<vtkPolyData> input2, std::string output) {
  
  auto boolean_operation = vtkSmartPointer<vtkBooleanOperationPolyDataFilter>::New();
  boolean_operation->SetInputData (0, input1);
  boolean_operation->SetInputData (1, input2);
  boolean_operation->SetOperationToDifference();
  boolean_operation->Update();
  
  auto unstructured_grid = vtkSmartPointer<vtkUnstructuredGrid>::New();
  unstructured_grid->ShallowCopy(boolean_operation->GetOutput());
  
  auto writer = vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
  writer->SetFileName(output.c_str());
  writer->SetInputData(unstructured_grid);
  writer->SetDataModeToAscii();
  writer->Update();
  writer->Write();
}


void VTKMeshToolBox::
generate_grid_rectangle (double xlo, double xhi, int nx,
                         double ylo, double yhi, int ny,
                         double zlo, double zhi, int nz, std::string output) {
  
  int dims[3] = {nx, ny, nz};
  double dx {(xhi-xlo)/double(nx-1)};
  double dy {(yhi-ylo)/double(ny-1)};
  double dz {(zhi-zlo)/double(nz-1)};
  
  auto structured_grid = vtkSmartPointer<vtkStructuredGrid>::New();
  structured_grid->SetDimensions(dims);
  
  auto points = vtkSmartPointer<vtkPoints>::New();
  points->Allocate(dims[0]*dims[1]*dims[2]);
  
  for (int k=0; k<dims[2]; ++k)
    for (int j=0; j<dims[1]; ++j)
      for (int i=0; i<dims[0]; ++i)
        points->InsertPoint(i + j*dims[0] + k*dims[0]*dims[1],
                            xlo+i*dx, ylo+j*dy, zlo+k*dz);
      
  structured_grid->SetPoints(points);
  
  // Write file
  auto writer = vtkSmartPointer<vtkXMLStructuredGridWriter>::New();
  writer->SetFileName(output.c_str());
  writer->SetInputData(structured_grid);
  writer->Write();
}
