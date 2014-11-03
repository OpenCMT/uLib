/*//////////////////////////////////////////////////////////////////////////////
// CMT Cosmic Muon Tomography project //////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

  Copyright (c) 2014, Universita' degli Studi di Padova, INFN sez. di Padova
  All rights reserved

  Authors: Andrea Rigoni Garola < andrea.rigoni@pd.infn.it >

  ------------------------------------------------------------------
  This library is free software;  you  can  redistribute  it  and/or
  modify it  under the  terms  of  the  GNU  Lesser  General  Public
  License as published  by  the  Free  Software  Foundation;  either
  version 3.0 of the License, or (at your option) any later version.

  This library is  distributed in  the hope that it will  be useful,
  but  WITHOUT ANY WARRANTY;  without  even  the implied warranty of
  MERCHANTABILITY  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of  the GNU Lesser General  Public
  License along with this library.

//////////////////////////////////////////////////////////////////////////////*/



#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkStructuredPoints.h>
#include <vtkStructuredPointsWriter.h>

#include <vtkPointDataToCellData.h>


#include <vtkCellData.h>
#include <vtkPointData.h>

int main(int, char *[])
{
  // Create an image data
  vtkSmartPointer<vtkImageData> imageData =
    vtkSmartPointer<vtkImageData>::New();

  // Specify the size of the image data
  imageData->SetDimensions(10,20,15);
#if VTK_MAJOR_VERSION <= 5
  imageData->SetNumberOfScalarComponents(1);
  imageData->SetScalarTypeToDouble();
#else
  imageData->AllocateScalars(VTK_DOUBLE,1);
#endif

  int* dims = imageData->GetDimensions();
  // int dims[3]; // can't do this

  std::cout << "Dims: " << " x: " << dims[0] << " y: " << dims[1] << " z: " << dims[2] << std::endl;

  std::cout << "Number of points: " << imageData->GetNumberOfPoints() << std::endl;
  std::cout << "Number of cells: " << imageData->GetNumberOfCells() << std::endl;

  // Fill every entry of the image data with "2.0"
  for (int z = 0; z < dims[2]; z++)
    {
    for (int y = 0; y < dims[1]; y++)
      {
      for (int x = 0; x < dims[0]; x++)
        {
        double* pixel = static_cast<double*>(imageData->GetScalarPointer(x,y,z));
        pixel[0] = (double)x+y+z;
        }
      }
    }

  //  imageData->GetCellData()->SetScalars(imageData->GetPointData()->GetScalars());

  vtkSmartPointer<vtkPointDataToCellData> ptoc =
          vtkSmartPointer<vtkPointDataToCellData>::New();

  ptoc->SetInputConnection(imageData->GetProducerPort());

  ptoc->Update();

  vtkSmartPointer<vtkStructuredPointsWriter> writer =
    vtkSmartPointer<vtkStructuredPointsWriter>::New();


  writer->SetInput(ptoc->GetImageDataOutput());
  writer->SetFileTypeToASCII();
  writer->SetFileName("output.vtk");
  writer->Update();

  return EXIT_SUCCESS;
}
