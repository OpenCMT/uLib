#include "Math/ImageData.h"

using namespace uLib;



void ImageData::SetSize(const Vector3f v)
{
    ImageSpace::SetSize( v.array() / this->GetDims().array().cast<float>() );
}

Vector3f ImageData::GetSize() const
{
    return ImageSpace::GetSize().array() * this->GetDims().array().cast<float>();
}

bool ImageData::IsInsideBounds(const Vector4f pt) const
{
    Vector4f ptl =  ImageSpace::GetLocalPoint(pt);
    int result = 0;
    for ( int i=0; i<3 ;++i) {
        result += ptl(i) > (float)this->GetDims()(i);
        result += ptl(i) < 0;
    }
    return result == 0;
}




void ImageData::ExportToVtk (const char *file, bool density_type)
{
    FILE * vtk_file = fopen(file,"wb");
    assert(vtk_file);
    ImageData *voxels = this;
    float norm;
    if (density_type) {
        norm = 40000;
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
                float density = fabs(voxels->GetValue(index)) * norm;
                fprintf(vtk_file, "%f ", density);
            }
        }
    }

    fclose(vtk_file);
    printf("%s vtk file saved\n",file);
}

int ImageData::ImportFromVtk(const char *file)
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

    for (int k = 0; k < dz; ++k) {
        for (int j = 0; j < dy; ++j) {
            for (int i = 0; i < dx; ++i) {
                Vector3i idx(i, j, k);
                float tmp_val;
                fscanf(vtk_file, "%f", &tmp_val);
                this->SetValue(idx,fabs(tmp_val)*1E-6);
            }
        }
    }
    fclose(vtk_file);
    return true;
}

void ImageData::ExportToVtkXml(const char *file, bool density_type)
{
    // Not implemented yet //
    FILE * vtk_file = fopen(file,"wb");
    assert(vtk_file);
    ImageData *voxels = this;
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
