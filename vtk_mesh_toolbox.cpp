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
  boolean_operation->SetOperationToDifference();
  boolean_operation->ReorientDifferenceCellsOn();
//   boolean_operation->SetOperationToIntersection();
//   boolean_operation->SetOperationToUnion();
  
  boolean_operation->SetInputData(0, input1);
  boolean_operation->SetInputData(1, input2);
  boolean_operation->Update();
  
//   auto bool_op_mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//   bool_op_mapper->SetInputConnection(boolean_operation->GetOutputPort());
//   bool_op_mapper->ScalarVisibilityOff();
//   
//   auto bool_op_actor = vtkSmartPointer<vtkActor>::New();
//   bool_op_actor->SetMapper(bool_op_mapper);
//   bool_op_actor->GetProperty()->SetDiffuseColor(colors->GetColor3d("Banana").GetData());
//   bool_op_actor->GetProperty()->SetSpecular(.6);
//   bool_op_actor->GetProperty()->SetSpecularPower(20);
  
  auto unstructured_grid = vtkSmartPointer<vtkUnstructuredGrid>::New();
  unstructured_grid->ShallowCopy(boolean_operation->GetOutput());
  
  auto writer = vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
  writer->SetFileName(output.c_str());
  writer->SetInputData(unstructured_grid);
  writer->SetDataModeToAscii();
  writer->Update();
  writer->Write();
}
