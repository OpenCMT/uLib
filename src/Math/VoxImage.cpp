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



#include <stdlib.h>
#include <stdio.h>

#include "VoxImage.h"

#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkXMLImageDataReader.h>
#include <vtkXMLImageDataWriter.h>
#include <vtkStringArray.h>
#include <vtkInformation.h>
#include <vtkInformationStringKey.h>

namespace uLib {

void Abstract::VoxImage::ExportToVtk (const char *file, bool density_type)
{
    FILE * vtk_file = fopen(file,"wb");
    assert(vtk_file);
    Abstract::VoxImage *voxels = this;
    float norm;
    if (density_type) {
        norm = 1;
    } else norm = 1.E6;
    int nx = voxels->GetDims()(0);
    int ny = voxels->GetDims()(1);
    int nz = voxels->GetDims()(2);

    fprintf(vtk_file,
            "# vtk DataFile Version 2.0\n"
            "Image Builder vtk output\n"
            "ASCII\n"
            "DATASET STRUCTURED_POINTS\n"
            "DIMENSIONS %d %d %d\n"
            "SPACING %f %f %f\n"
            "ORIGIN %f %f %f\n"
            "POINT_DATA %d\n"
            "SCALARS volume_scalars float 1\n"
            "LOOKUP_TABLE default\n",
            nx , ny , nz ,
            voxels->GetSpacing()(0),
            voxels->GetSpacing()(1),
            voxels->GetSpacing()(2),
            voxels->GetPosition()(0), // FIX FOR ORIGIN //
            voxels->GetPosition()(1),
            voxels->GetPosition()(2),
            nx * ny * nz
            );

    Vector3i index(0,0,0);
    for (int zv = 0; zv < nz; ++zv) {
        for (int yv = 0; yv < ny; ++yv) {
            for (int xv = 0; xv < nx; ++xv) {
                index << xv,yv,zv;
                // write voxel density in mrad^2/cm //
                float density = (voxels->GetValue(index)) * norm;
                fprintf(vtk_file, "%f ", density);
            }
        }
    }

    fclose(vtk_file);
    printf("%s vtk file saved\n",file);
}



void Abstract::VoxImage::ExportToVti (const char *file, bool density_type, bool compressed)
{
    Abstract::VoxImage *voxels = this;

    vtkSmartPointer<vtkImageData> image = vtkSmartPointer<vtkImageData>::New();
    image->SetDimensions(voxels->GetDims()(0), voxels->GetDims()(1), voxels->GetDims()(2));
    image->SetSpacing(voxels->GetSpacing()(0), voxels->GetSpacing()(1), voxels->GetSpacing()(2));
    image->SetOrigin(voxels->GetOrigin()(0), voxels->GetOrigin()(1), voxels->GetOrigin()(2));
    image->AllocateScalars(VTK_FLOAT, 1);

    float norm;
    if (density_type) {
        norm = 1;
    } else norm = 1.E6;

    int nx = voxels->GetDims()(0);
    int ny = voxels->GetDims()(1);
    int nz = voxels->GetDims()(2);

    size_t npoints = nx*ny*nz;
    float *scalar = static_cast<float*>(image->GetScalarPointer());

    for (size_t i = 0; i < npoints; i++) {
        scalar[i] = static_cast<float>(voxels->GetValue(i) * norm);
    }

    // Create a custom string key
    static vtkInformationStringKey* ConfigNote =
        vtkInformationStringKey::MakeKey("cmt.config", "Config");

    // Attach metadata
    vtkInformation *info = image->GetInformation();
    info->Set(ConfigNote, 

    "This image was generated with uLib\n"
    "-----------------------------------\n"
    "Author: Andrea Rigoni\n"
    "Version: 0.1\n"
    "Date: 2025\n"

    );

    // std::cout << info->Get(ConfigNote) << std::endl;
    vtkSmartPointer<vtkXMLImageDataWriter> writer = vtkSmartPointer<vtkXMLImageDataWriter>::New();
    writer->SetFileName(file);
    writer->SetInputData(image);
    if(compressed) {
        writer->SetDataModeToBinary();
        writer->SetCompressorTypeToZLib();
    }
    writer->Write();
}


int Abstract::VoxImage::ImportFromVti(const char *file, bool density_type) {
    
    vtkSmartPointer<vtkXMLImageDataReader> reader = vtkSmartPointer<vtkXMLImageDataReader>::New();
    reader->SetFileName(file);
    reader->Update();
    vtkImageData *image = reader->GetOutput();
    if(!image) return false;
    
    Abstract::VoxImage *voxels = this;
    int nx = image->GetDimensions()[0];
    int ny = image->GetDimensions()[1];
    int nz = image->GetDimensions()[2];
    
    voxels->SetDims(Vector3i(nx,ny,nz));
    voxels->SetSpacing(Vector3f(image->GetSpacing()[0],image->GetSpacing()[1],image->GetSpacing()[2]));
    voxels->SetOrigin(Vector3f(image->GetOrigin()[0],image->GetOrigin()[1],image->GetOrigin()[2]));

    float norm;
    if (density_type) {
        norm = 1;
    } else norm = 1.E6;

    size_t npoints = nx*ny*nz;
    float *scalar = static_cast<float*>(image->GetScalarPointer());
    for (size_t i = 0; i < npoints; i++) {
        voxels->SetValue(i, scalar[i] / norm);
    }

    return true;
}



int Abstract::VoxImage::ImportFromVtk(const char *file, bool density_type)
{
    FILE * vtk_file = fopen(file, "r");
    if (!vtk_file) return false;

    char word[20];
    int dx, dy, dz, n_tot;
    float sx, sy, sz, ox, oy, oz;
    do {
        fscanf(vtk_file, "%s", word);
    } while (strcmp(word, "DIMENSIONS"));
    fscanf(vtk_file, "%d %d %d", &dx, &dy, &dz);
    do {
        fscanf(vtk_file, "%s", word);
        } while (strcmp(word, "SPACING"));
    fscanf(vtk_file, "%f %f %f", &sx, &sy, &sz);
    do {
        fscanf(vtk_file, "%s", word);
        } while (strcmp(word, "ORIGIN"));
    fscanf(vtk_file, "%f %f %f", &ox, &oy, &oz);
    do {
        fscanf(vtk_file, "%s", word);
    } while (strcmp(word, "POINT_DATA"));
    fscanf(vtk_file, "%d", &n_tot);
    do {
        fscanf(vtk_file, "%s", word);
    } while (strcmp(word, "default"));

    this->SetDims(Vector3i(dx,dy,dz));
    this->SetSpacing(Vector3f(sx,sy,sz));
    this->SetPosition(Vector3f(ox,oy,oz));

    float norm;
    if (density_type) {
        norm = 1;
    } else norm = 1.E6;

    for (int k = 0; k < dz; ++k) {
        for (int j = 0; j < dy; ++j) {
            for (int i = 0; i < dx; ++i) {
                Vector3i idx(i, j, k);
                float tmp_val;
                fscanf(vtk_file, "%f", &tmp_val);
                this->SetValue(idx,tmp_val / norm);
            }
        }
    }
    fclose(vtk_file);
    return true;
}

void Abstract::VoxImage::ExportToVtkXml(const char *file, bool density_type)
{
    // Not implemented yet //
    FILE * vtk_file = fopen(file,"wb");
    assert(vtk_file);
    Abstract::VoxImage *voxels = this;
    float norm;
    if (density_type) {
        norm = 40000;
    } else norm = 1.E6;
    int nx = voxels->GetDims()(0);
    int ny = voxels->GetDims()(1);
    int nz = voxels->GetDims()(2);

    fprintf(vtk_file,
            "<?xml version=\"1.0\"?>\n"

            "<VTKFile type=\"ImageData\" version=\"0.1\" "
            "byte_order=\"LittleEndian\">\n"

            "<ImageData WholeExtent=\"0 %d 0 %d 0 %d\" "
            "Origin=\"%f %f %f\" Spacing=\"%f %f %f\">\n"

            "<Piece Extent=\"0 %d 0 %d 0 %d\">\n"

            "<CellData Scalars=\"lambda\">\n"
            "<DataArray format=\"ascii\" Name=\"lambda\" type=\"Float32\" >\n",
            nx, ny, nz,
            voxels->GetPosition()(0), // FIX FOR ORIGIN //
            voxels->GetPosition()(1),
            voxels->GetPosition()(2),
            voxels->GetSpacing()(0),
            voxels->GetSpacing()(1),
            voxels->GetSpacing()(2),
            nx, ny, nz
            );
    Vector3i index(0,0,0);
    for (int zv = 0; zv < nz; ++zv) {
        for (int yv = 0; yv < ny; ++yv) {
            for (int xv = 0; xv < nx; ++xv) {
                index << xv,yv,zv;
                // write voxel density in mrad^2/cm //
                float density = fabs(voxels->GetValue(index)) * norm;
                fprintf(vtk_file, "%f ", density);
            }
        }
    }
    fprintf(vtk_file,
            "\n </DataArray>\n </CellData>\n");

    fprintf(vtk_file,
            "</Piece>\n </ImageData>\n </VTKFile>\n");
    fclose(vtk_file);
    printf("%s vtk file saved\n",file);
}




}

