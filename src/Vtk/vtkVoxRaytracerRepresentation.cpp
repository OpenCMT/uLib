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

#include <vtkLine.h>
#include <vtkCellArray.h>

#include <vtkLineSource.h>
#include <vtkSphereSource.h>
#include <vtkBoundingBox.h>
#include <vtkCubeSource.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkAppendPolyData.h>
#include <vtkActor.h>
#include <vtkAssembly.h>
#include <vtkProp3DCollection.h>
#include <vtkProperty.h>
#include <vtkPolyData.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>



#include "vtkVoxRaytracerRepresentation.h"

#include "Math/VoxRaytracer.h"

//#include "vtkMuonEvent.h"
#include "vtkMuonScatter.h"


namespace uLib {
namespace Vtk {

///// PIMPL ////////////////////////////////////////////////////////////////////

class vtkVoxRaytracerRepresentationPimpl {

public:
    vtkVoxRaytracerRepresentationPimpl(VoxRaytracer &content) :
        m_Content(&content),
        m_Assembly(vtkAssembly::New()),
        m_Sphere1(vtkSphereSource::New()),
        m_Sphere2(vtkSphereSource::New()),
        m_Line1(vtkLineSource::New()),
        m_Line2(vtkLineSource::New()),
        m_Line3(vtkLineSource::New()),
        m_RayLine(vtkAppendPolyData::New()),
        m_RayLineActor(vtkActor::New()),
        m_RayRepresentation(vtkAppendPolyData::New()),
        m_RayRepresentationActor(vtkActor::New()),
        m_Transform(vtkTransform::New())
    {
        default_radius = content.GetImage()->GetSpacing()(0)/4;
        m_Sphere1->SetRadius(default_radius);
        m_Sphere2->SetRadius(default_radius);
        m_SelectedElement = m_RayLine;
    }
    ~vtkVoxRaytracerRepresentationPimpl()
    {
        m_Assembly->Delete();
        m_RayLine->Delete();
        m_RayLineActor->Delete();
        m_RayRepresentationActor->Delete();
        m_Transform->Delete();
    }

    // members //
    VoxRaytracer *m_Content;

    Scalarf                            default_radius;
    vtkAssembly                       *m_Assembly;
    vtkAppendPolyData                 *m_RayLine;
    vtkActor                          *m_RayLineActor;
    vtkActor                          *m_RayRepresentationActor;
    vtkSmartPointer<vtkTransform>      m_Transform;
    VoxRaytracer::RayData              m_Ray;
    vtkSmartPointer<vtkSphereSource>   m_Sphere1,m_Sphere2;
    vtkSmartPointer<vtkLineSource>     m_Line1,  m_Line2, m_Line3;
    vtkSmartPointer<vtkAppendPolyData> m_RayRepresentation;

    vtkAppendPolyData                *m_SelectedElement;
};




////////////////////////////////////////////////////////////////////////////////
////// VOX RAYTRACER REPRESENTATION  ///////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////



vtkVoxRaytracerRepresentation::vtkVoxRaytracerRepresentation(Content &content) :
    d(new vtkVoxRaytracerRepresentationPimpl(content))
{
    InstallPipe();
}

vtkVoxRaytracerRepresentation::~vtkVoxRaytracerRepresentation()
{
    delete d;
}

VoxRaytracer *vtkVoxRaytracerRepresentation::GetRaytracerAlgorithm()
{
    return d->m_Content;
}

vtkProp *vtkVoxRaytracerRepresentation::GetProp()
{
    return d->m_Assembly;
}

vtkPolyData *vtkVoxRaytracerRepresentation::GetPolyData() const
{
    std::cout << "get Raytracer polydata\n";
    d->m_SelectedElement->Update();
    return d->m_SelectedElement->GetOutput();
}

void vtkVoxRaytracerRepresentation::SetRepresentationElements(vtkVoxRaytracerRepresentation::RepresentationElements el)
{
    switch(el) {
    case Vtk::vtkVoxRaytracerRepresentation::RayElements:
        d->m_SelectedElement = d->m_RayLine;
        break;
    case Vtk::vtkVoxRaytracerRepresentation::VoxelsElements:
        d->m_SelectedElement = d->m_RayRepresentation;
        break;
    default:
        d->m_SelectedElement = d->m_RayLine;
        break;
    }
}


void vtkVoxRaytracerRepresentation::SetMuon(MuonScatter &muon)
{
    Vector4f pt1,pt2,src;
    src = muon.LineIn().origin();
    d->m_Content->GetEntryPoint(muon.LineIn(),pt1);
    d->m_Sphere1->SetCenter(pt1(0),pt1(1),pt1(2));
    d->m_Line1->SetPoint1(src(0),src(1),src(2));
    d->m_Line1->SetPoint2(pt1(0),pt1(1),pt1(2));

    HLine3f line_out = muon.LineOut();
    src = line_out.origin();
    float *direction = line_out.direction().data();
    for(int i=0;i<3;++i) direction[i] *= -1;
    d->m_Content->GetEntryPoint(line_out,pt2);
    d->m_Sphere2->SetCenter(pt2(0),pt2(1),pt2(2));
    d->m_Line2->SetPoint1(src(0),src(1),src(2));
    d->m_Line2->SetPoint2(pt2(0),pt2(1),pt2(2));

    d->m_Line3->SetPoint1(pt1(0),pt1(1),pt1(2));
    d->m_Line3->SetPoint2(pt2(0),pt2(1),pt2(2));

    // Create a vtkPoints object and store the points in it
      vtkSmartPointer<vtkPoints> points =
        vtkSmartPointer<vtkPoints>::New();
      points->InsertNextPoint(pt1(0),pt1(1),pt1(2));
      points->InsertNextPoint(pt2(0),pt2(1),pt2(2));

      // Create a cell array to store the lines in and add the lines to it
      vtkSmartPointer<vtkCellArray> lines =
        vtkSmartPointer<vtkCellArray>::New();

      vtkSmartPointer<vtkLine> line =
              vtkSmartPointer<vtkLine>::New();
      line->GetPointIds()->SetId(0,0);
      line->GetPointIds()->SetId(1,1);
      lines->InsertNextCell(line);

      // Create a polydata to store everything in
      vtkSmartPointer<vtkPolyData> linesPolyData =
              vtkSmartPointer<vtkPolyData>::New();

      // Add the points to the dataset
      linesPolyData->SetPoints(points);

      // Add the lines to the dataset
      linesPolyData->SetLines(lines);

      d->m_RayLine->RemoveAllInputs();
#     if VTK_MAJOR_VERSION <= 5
      d->m_RayLine->AddInputConnection(linesPolyData->GetProducerPort());
#     else
      d->m_RayLine->AddInputData(linesPolyData);
#     endif
      d->m_RayLine->AddInputConnection(d->m_Line1->GetOutputPort());
      d->m_RayLine->AddInputConnection(d->m_Sphere1->GetOutputPort());
      d->m_RayLine->AddInputConnection(d->m_Line2->GetOutputPort());
      d->m_RayLine->AddInputConnection(d->m_Sphere2->GetOutputPort());
//      d->m_RayLine->AddInputConnection(d->m_Line3->GetOutputPort());


    vtkSmartPointer<vtkMatrix4x4> vmat = vtkSmartPointer<vtkMatrix4x4>::New();
    Matrix4f mat = d->m_Content->GetImage()->GetWorldMatrix();
    for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
            vmat->SetElement(i,j,mat(i,j));
    d->m_Transform->SetMatrix(vmat);

    this->SetRay(pt1,pt2);
}

void vtkVoxRaytracerRepresentation::SetMuon(MuonScatter &muon, Vector4f poca)
{
    Vector4f pt1,pt2,src;
    src = muon.LineIn().origin();
    d->m_Content->GetEntryPoint(muon.LineIn(),pt1);
    d->m_Sphere1->SetCenter(pt1(0),pt1(1),pt1(2));
    d->m_Line1->SetPoint1(src(0),src(1),src(2));
    d->m_Line1->SetPoint2(pt1(0),pt1(1),pt1(2));

    HLine3f line_out = muon.LineOut();
    src = line_out.origin();
    float *direction = line_out.direction().data();
    for(int i=0;i<3;++i) direction[i] *= -1;
    d->m_Content->GetEntryPoint(line_out,pt2);
    d->m_Sphere2->SetCenter(pt2(0),pt2(1),pt2(2));
    d->m_Line2->SetPoint1(src(0),src(1),src(2));
    d->m_Line2->SetPoint2(pt2(0),pt2(1),pt2(2));

    d->m_Line3->SetPoint1(pt1(0),pt1(1),pt1(2));
    d->m_Line3->SetPoint2(pt2(0),pt2(1),pt2(2));

    // Create a vtkPoints object and store the points in it
      vtkSmartPointer<vtkPoints> points =
        vtkSmartPointer<vtkPoints>::New();
      points->InsertNextPoint(pt1(0),pt1(1),pt1(2));
      points->InsertNextPoint(poca(0),poca(1),poca(2));
      points->InsertNextPoint(pt2(0),pt2(1),pt2(2));

      // Create a cell array to store the lines in and add the lines to it
      vtkSmartPointer<vtkCellArray> lines =
        vtkSmartPointer<vtkCellArray>::New();

      for(unsigned int i = 0; i < 2; i++)
          {
          vtkSmartPointer<vtkLine> line =
                  vtkSmartPointer<vtkLine>::New();
          line->GetPointIds()->SetId(0,i);
          line->GetPointIds()->SetId(1,i+1);
          lines->InsertNextCell(line);
      }

      // Create a polydata to store everything in
      vtkSmartPointer<vtkPolyData> linesPolyData =
              vtkSmartPointer<vtkPolyData>::New();

      // Add the points to the dataset
      linesPolyData->SetPoints(points);

      // Add the lines to the dataset
      linesPolyData->SetLines(lines);

      d->m_RayLine->RemoveAllInputs();
#     if VTK_MAJOR_VERSION <= 5
      d->m_RayLine->AddInputConnection(linesPolyData->GetProducerPort());
#     else
      d->m_RayLine->AddInputData(linesPolyData);
#     endif
      d->m_RayLine->AddInputConnection(d->m_Line1->GetOutputPort());
      d->m_RayLine->AddInputConnection(d->m_Sphere1->GetOutputPort());
      d->m_RayLine->AddInputConnection(d->m_Line2->GetOutputPort());
      d->m_RayLine->AddInputConnection(d->m_Sphere2->GetOutputPort());
//      d->m_RayLine->AddInputConnection(d->m_Line3->GetOutputPort());


      vtkSmartPointer<vtkSphereSource> poca_sphere =
              vtkSmartPointer<vtkSphereSource>::New();
      poca_sphere->SetRadius(d->default_radius);
      poca_sphere->SetCenter(poca(0),poca(1),poca(2));
      d->m_RayLine->AddInputConnection(poca_sphere->GetOutputPort());


    vtkSmartPointer<vtkMatrix4x4> vmat = vtkSmartPointer<vtkMatrix4x4>::New();
    Matrix4f mat = d->m_Content->GetImage()->GetWorldMatrix();
    for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
            vmat->SetElement(i,j,mat(i,j));
    d->m_Transform->SetMatrix(vmat);

    if(d->m_Content->GetImage()->IsInsideBounds(poca))
        this->SetRay(pt1,poca,pt2);
    else
        this->SetRay(pt1,pt2);
}


void vtkVoxRaytracerRepresentation::SetMuon(vtkMuonScatter &muon)
{
    Vector4f poca = muon.GetPocaPoint();
    MuonScatter &mu = muon.GetContent();
    this->SetMuon(mu,poca);
}


VoxRaytracer::RayData vtkVoxRaytracerRepresentation::GetRay()
{
    return d->m_Ray;
}

void vtkVoxRaytracerRepresentation::SetRay(Vector4f in, Vector4f out)
{
    d->m_Ray = d->m_Content->TraceBetweenPoints(in,out);
    this->SetRay(&d->m_Ray);
}

void vtkVoxRaytracerRepresentation::SetRay(Vector4f in, Vector4f mid, Vector4f out)
{
    d->m_Ray = d->m_Content->TraceBetweenPoints(in,mid);
    d->m_Ray.AppendRay( d->m_Content->TraceBetweenPoints(mid,out) );
    this->SetRay(&d->m_Ray);
}

void vtkVoxRaytracerRepresentation::SetRay(VoxRaytracer::RayData *ray)
{
    vtkAppendPolyData *appender = d->m_RayRepresentation;
    appender->RemoveAllInputs();

    for(int i=0; i<ray->Data().size(); ++i) {
        int id = ray->Data().at(i).vox_id;
        Vector3i idv = d->m_Content->GetImage()->UnMap(id);
        vtkSmartPointer<vtkCubeSource> cube =
                vtkSmartPointer<vtkCubeSource>::New();
        cube->SetBounds(idv(0),idv(0)+1,idv(1),idv(1)+1,idv(2),idv(2)+1);
        cube->Update();
#       if VTK_MAJOR_VERSION <= 5
        appender->AddInput(cube->GetOutput());
#       else
        appender->AddInputData(cube->GetOutput());
#       endif
        appender->Update();
    }

}

void vtkVoxRaytracerRepresentation::SetVoxelsColor(Vector4f rgba)
{
    this->SetColor(d->m_RayRepresentationActor,rgba);
}

void vtkVoxRaytracerRepresentation::SetRayColor(Vector4f rgba)
{
    this->SetColor(d->m_RayLineActor,rgba);
}

void vtkVoxRaytracerRepresentation::SetColor(vtkActor *actor, Vector4f rgba)
{
    if(!actor) return;
    vtkProperty *pr = actor->GetProperty();
    pr->SetDiffuseColor( rgba(0),
                         rgba(1),
                         rgba(2) );
    pr->SetOpacity( rgba(3) );
    pr->SetDiffuse(1);
}




void vtkVoxRaytracerRepresentation::InstallPipe()
{

    vtkSmartPointer<vtkAppendPolyData> append =
            vtkSmartPointer<vtkAppendPolyData>::New();
    append->AddInputConnection(d->m_Sphere1->GetOutputPort());
    append->AddInputConnection(d->m_Sphere2->GetOutputPort());
    append->AddInputConnection(d->m_Line1->GetOutputPort());
    append->AddInputConnection(d->m_Line2->GetOutputPort());

    append->Update();
    vtkSmartPointer<vtkPolyDataMapper> mapper =
            vtkSmartPointer<vtkPolyDataMapper>::New();

    mapper->SetInputConnection(append->GetOutputPort());
    mapper->Update();

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(0.6,0.6,1);
    this->SetProp(actor);

    mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(d->m_RayLine->GetOutputPort());
    mapper->Update();

    d->m_RayLineActor->SetMapper(mapper);
    d->m_RayLineActor->GetProperty()->SetColor(1,0,0);
    this->SetProp(d->m_RayLineActor);

//    mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//    mapper->SetInputConnection(d->m_Line3->GetOutputPort());
//    mapper->Update();

//    actor = vtkSmartPointer<vtkActor>::New();
//    actor->SetMapper(mapper);
//    actor->GetProperty()->SetColor(1,0,0);
//    d->m_Assembly->AddPart(actor);


    vtkSmartPointer<vtkTransformPolyDataFilter> polyfilter =
            vtkSmartPointer<vtkTransformPolyDataFilter>::New();

    polyfilter->SetInputConnection(d->m_RayRepresentation->GetOutputPort());
    polyfilter->SetTransform(d->m_Transform);

    mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(polyfilter->GetOutputPort());
    mapper->Update();

    vtkActor *vra = d->m_RayRepresentationActor;
    vra->SetMapper(mapper);
    vra->GetProperty()->SetOpacity(0.2);
    vra->GetProperty()->SetEdgeVisibility(true);
    vra->GetProperty()->SetColor(0.5,0.5,0.5);

    this->SetProp(vra);
}







} // vtk
} // uLib
