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



#ifdef HAVE_CONFIG_H
#include "config.h"
#endif


#include <vtkSmartPointer.h>
#include <vtkVolume.h>
#include <vtkImageData.h>
#include <vtkImageImport.h>
#include <vtkImageExport.h>

#include <vtkFloatArray.h>
#include <vtkPointData.h>

#include <vtkXMLImageDataReader.h>
#include <vtkXMLImageDataWriter.h>
#include <vtkGenericDataObjectReader.h>
#include <vtkImageShiftScale.h>

#include <vtkSmartVolumeMapper.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkVolumeProperty.h>

#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkCubeSource.h>
#include <vtkPolyDataMapper.h>


#include <Math/VoxImage.h>

#include "vtkVoxImage.h"


namespace uLib {
namespace Vtk {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// PIMPL

class vtkVoxImagePimpl {
public:
    vtkVoxImagePimpl(vtkVoxImage::Content &content) :
        m_Content(content),
        m_Actor(vtkVolume::New()),
        m_Image(vtkImageData::New()),
        m_Outline(vtkCubeSource::New()),
        m_Reader(NULL),
        m_Writer(NULL)
    {}

    ~vtkVoxImagePimpl()
    {
        m_Image->Delete();
        m_Actor->Delete();
        m_Outline->Delete();
    }    

    void GetContent();

    void SetContent();

    // members //
    vtkVolume      *m_Actor;
    vtkImageData   *m_Image;
    vtkCubeSource  *m_Outline;

    // io //
    vtkXMLImageDataReader *m_Reader;
    vtkXMLImageDataWriter *m_Writer;

    // content //
    vtkVoxImage::Content &m_Content;

    // visual //
    float m_Window;
    float m_Level;
};



void vtkVoxImagePimpl::GetContent()
{
    // ULIB -> VTK //
    const int *dims = static_cast<const int *>(m_Content.GetDims().data());
    m_Image->SetDimensions(dims);

    float *spacing = m_Content.GetSpacing().data();
    m_Image->SetSpacing(spacing[0],spacing[1],spacing[2]);

    // Warning .. TODO: Read complete Transform matrix //
    float *pos = m_Content.GetPosition().data();
    m_Image->SetOrigin(pos[0],pos[1],pos[2]);

    vtkFloatArray *array = vtkFloatArray::SafeDownCast
            (m_Image->GetPointData()->GetScalars());
    array->SetNumberOfTuples(m_Content.GetDims().prod());
    Vector3i index(0,0,0);
    int i=0;
    for (int zv = 0; zv < dims[2]; ++zv) {
        for (int yv = 0; yv < dims[1]; ++yv) {
            for (int xv = 0; xv < dims[0]; ++xv) {
                index << xv,yv,zv;
                array->SetValue(i++,m_Content.GetValue(index));
            }
        }
    }
    m_Image->GetPointData()->SetScalars(array);
    //    m_Image->Update();
}

void vtkVoxImagePimpl::SetContent()
{
    // VTK -> ULIB //
    int *ext = m_Image->GetExtent();
    int dims[3] = { ext[1]-ext[0] + 1, ext[3]-ext[2] + 1, ext[5]-ext[4] + 1 };
    m_Content.SetDims(Vector3i(dims[0],dims[1],dims[2]));

    double *spacing = m_Image->GetSpacing();
    m_Content.SetSpacing(Vector3f(spacing[0],spacing[1],spacing[2]));

    // Warning .. TODO: Read complete Transform matrix //
    double *pos = m_Image->GetOrigin();
    m_Content.SetPosition(Vector3f(pos[0],pos[1],pos[2]));

    vtkFloatArray *array = vtkFloatArray::SafeDownCast
            (m_Image->GetPointData()->GetScalars());
    if(array) {
        Vector3i index(0,0,0);
        int i=0;
        for (int zv = 0; zv < dims[2]; ++zv) {
            for (int yv = 0; yv < dims[1]; ++yv) {
                for (int xv = 0; xv < dims[0]; ++xv) {
                    index << xv,yv,zv;
                    m_Content.SetValue(index,array->GetValue(i++));
                }
            }
        }
    }
    else {
        std::cerr << "Error reading array Value Data\n";
    }
}




////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// VTK VOXIMAGE

vtkVoxImage::vtkVoxImage(Content &content) :
    d(new vtkVoxImagePimpl(content))
{    
    init_properties();
    d->GetContent();
    InstallPipe();
}

vtkVoxImage::~vtkVoxImage()
{
    delete d;
}

vtkImageData *vtkVoxImage::GetImageData()
{
    d->GetContent();
    return d->m_Image;
}

void vtkVoxImage::SaveToXMLFile(const char *fname)
{
    vtkSmartPointer<vtkXMLImageDataWriter> writer =
            vtkSmartPointer<vtkXMLImageDataWriter>::New();
    writer->SetFileName(fname);
    d->GetContent();
    vtkSmartPointer<vtkImageShiftScale> vtkscale =
            vtkSmartPointer<vtkImageShiftScale>::New();

#   if VTK_MAJOR_VERSION <= 5
    vtkscale->SetInputConnection(d->m_Image->GetProducerPort());
#   else
    vtkscale->SetInputData(d->m_Image);
#   endif
    vtkscale->SetScale(p().writer_factor);
    vtkscale->Update();
    writer->SetInputConnection(vtkscale->GetOutputPort());
    writer->Update();
    writer->Write();
}

void vtkVoxImage::ReadFromVKTFile(const char *fname)
{
    vtkSmartPointer<vtkGenericDataObjectReader> reader =
            vtkSmartPointer<vtkGenericDataObjectReader>::New();
    reader->SetFileName(fname);
    reader->Update();        
    if(reader->IsFileStructuredPoints())
    {
        vtkSmartPointer<vtkImageShiftScale> vtkscale =
                vtkSmartPointer<vtkImageShiftScale>::New();
        vtkscale->SetInputConnection(reader->GetOutputPort());
        vtkscale->SetScale(1/p().writer_factor);
        vtkscale->Update();

        d->m_Image->DeepCopy(vtkscale->GetOutput()); // FIX! (pipe connection)        
        d->SetContent();
    }
    else {
        std::cerr << "Error: file does not contain structured points\n";
    }
    d->m_Actor->Update();
}

void vtkVoxImage::ReadFromXMLFile(const char *fname)
{
    vtkSmartPointer<vtkXMLImageDataReader> reader =
            vtkSmartPointer<vtkXMLImageDataReader>::New();
    reader->SetFileName(fname);
    reader->Update();
    vtkSmartPointer<vtkImageShiftScale> vtkscale =
            vtkSmartPointer<vtkImageShiftScale>::New();
    vtkscale->SetInputConnection(reader->GetOutputPort());
    vtkscale->SetScale(1/p().writer_factor);
    vtkscale->Update();

    d->m_Image->DeepCopy(vtkscale->GetOutput());
    d->SetContent();
}


void vtkVoxImage::setShadingPreset(int blendType)
{
    vtkSmartVolumeMapper *mapper =
            (vtkSmartVolumeMapper *)d->m_Actor->GetMapper();
    vtkVolumeProperty  *property = d->m_Actor->GetProperty();

    static vtkColorTransferFunction *colorFun = vtkColorTransferFunction::New();
    static vtkPiecewiseFunction *opacityFun = vtkPiecewiseFunction::New();

    float window = 40 / $$.writer_factor;
    float level  = 20 / $$.writer_factor;

    property->SetColor(colorFun);
    property->SetScalarOpacity(opacityFun);
    property->SetInterpolationTypeToLinear();

    if(blendType != 6) {
        colorFun->RemoveAllPoints();
        opacityFun->RemoveAllPoints();
    }

    switch (blendType) {
        // MIP
        // Create an opacity ramp from the window and level values.
        // Color is white. Blending is MIP.
    case 0:
        colorFun->AddRGBSegment(0.0, 1.0, 1.0, 1.0, 255.0, 1.0, 1.0, 1.0);
        opacityFun->AddSegment(level - 0.5 * window, 0.0,
                               level + 0.5 * window, 1.0);
        mapper->SetBlendModeToMaximumIntensity();
        break;

        // CompositeRamp
        // Create a ramp from the window and level values. Use compositing
        // without shading. Color is a ramp from black to white.
    case 1:
        colorFun->AddRGBSegment(level - 0.5 * window, 0.0, 0.0, 0.0,
                                level + 0.5 * window, 1.0, 1.0, 1.0);
        opacityFun->AddSegment(level - 0.5 * window, 0.0,
                               level + 0.5 * window, 1.0);
        mapper->SetBlendModeToComposite();
        property->ShadeOff();
        break;

        // CompositeShadeRamp
        // Create a ramp from the window and level values. Use compositing
        // with shading. Color is white.
    case 2:
        colorFun->AddRGBSegment(0.0, 1.0, 1.0, 1.0, 255.0, 1.0, 1.0, 1.0);
        opacityFun->AddSegment(level - 0.5 * window, 0.0,
                               level + 0.5 * window, 1.0);
        mapper->SetBlendModeToComposite();
        property->ShadeOn();
        break;

        // CT_Skin
        // Use compositing and functions set to highlight skin in CT data
        // Not for use on RGB data
    case 3:
        colorFun->AddRGBPoint(-3024, 0, 0, 0, 0.5, 0.0);
        colorFun->AddRGBPoint(-1000, .62, .36, .18, 0.5, 0.0);
        colorFun->AddRGBPoint(-500, .88, .60, .29, 0.33, 0.45);
        colorFun->AddRGBPoint(3071, .83, .66, 1, 0.5, 0.0);

        opacityFun->AddPoint(-3024, 0, 0.5, 0.0);
        opacityFun->AddPoint(-1000, 0, 0.5, 0.0);
        opacityFun->AddPoint(-500, 1.0, 0.33, 0.45);
        opacityFun->AddPoint(3071, 1.0, 0.5, 0.0);

        mapper->SetBlendModeToComposite();
        property->ShadeOn();
        property->SetAmbient(0.1);
        property->SetDiffuse(0.9);
        property->SetSpecular(0.2);
        property->SetSpecularPower(10.0);
        property->SetScalarOpacityUnitDistance(0.8919);
        break;


    default:
        vtkGenericWarningMacro("Unknown blend type.");
        break;
    }
}

void vtkVoxImage::Update() {
    d->m_Actor->Update();
    d->m_Outline->SetBounds(d->m_Image->GetBounds());
    d->m_Outline->Update();
}

void vtkVoxImage::InstallPipe()
{
    vtkSmartPointer<vtkSmartVolumeMapper> mapper =
            vtkSmartPointer<vtkSmartVolumeMapper>::New();
#   if VTK_MAJOR_VERSION <= 5
    mapper->SetInputConnection(d->m_Image->GetProducerPort());
#   else
    mapper->SetInputData(d->m_Image);
#   endif
    mapper->Update();

    d->m_Actor->SetMapper(mapper);
    this->setShadingPreset(0);
    mapper->Update();

    d->m_Outline->SetBounds(d->m_Image->GetBounds());
    vtkSmartPointer<vtkPolyDataMapper> mmapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mmapper->SetInputConnection(d->m_Outline->GetOutputPort());
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mmapper);
    actor->GetProperty()->SetRepresentationToWireframe();
    actor->GetProperty()->SetAmbient(0.7);

    //    this->SetProp(actor);
    this->SetProp(d->m_Actor);
}


} // vtk
} // uLib
