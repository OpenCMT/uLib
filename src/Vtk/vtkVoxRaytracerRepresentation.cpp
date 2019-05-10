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


#include "vtkVoxRaytracerRepresentation.h"

#include "Math/VoxRaytracer.h"

//#include "vtkMuonEvent.h"
#include "vtkMuonScatter.h"


namespace uLib {
namespace Vtk {

////////////////////////////////////////////////////////////////////////////////
////// VOX RAYTRACER REPRESENTATION  ///////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////



vtkVoxRaytracerRepresentation::vtkVoxRaytracerRepresentation(Content &content) :
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

    InstallPipe();
}

vtkVoxRaytracerRepresentation::~vtkVoxRaytracerRepresentation()
{
    m_Assembly->Delete();
    m_RayLine->Delete();
    m_RayLineActor->Delete();
    m_RayRepresentationActor->Delete();
    m_Transform->Delete();
}

VoxRaytracer *vtkVoxRaytracerRepresentation::GetRaytracerAlgorithm()
{
    return m_Content;
}

vtkProp *vtkVoxRaytracerRepresentation::GetProp()
{
    return m_Assembly;
}

vtkPolyData *vtkVoxRaytracerRepresentation::GetPolyData() const
{
    std::cout << "get Raytracer polydata\n";
    m_SelectedElement->Update();
    return m_SelectedElement->GetOutput();
}

void vtkVoxRaytracerRepresentation::SetRepresentationElements(vtkVoxRaytracerRepresentation::RepresentationElements el)
{
    switch(el) {
    case Vtk::vtkVoxRaytracerRepresentation::RayElements:
        m_SelectedElement = m_RayLine;
        break;
    case Vtk::vtkVoxRaytracerRepresentation::VoxelsElements:
        m_SelectedElement = m_RayRepresentation;
        break;
    default:
        m_SelectedElement = m_RayLine;
        break;
    }
}


void vtkVoxRaytracerRepresentation::SetMuon(MuonScatter &muon)
{
    HPoint3f pt1,pt2,src;
    src = muon.LineIn().origin;
    m_Content->GetEntryPoint(muon.LineIn(),pt1);
    m_Sphere1->SetCenter(pt1(0),pt1(1),pt1(2));
    m_Line1->SetPoint1(src(0),src(1),src(2));
    m_Line1->SetPoint2(pt1(0),pt1(1),pt1(2));

    HLine3f line_out = muon.LineOut();
    src = line_out.origin;
    float *direction = line_out.direction.data();
    for(int i=0;i<3;++i) direction[i] *= -1;
    m_Content->GetEntryPoint(line_out,pt2);
    m_Sphere2->SetCenter(pt2(0),pt2(1),pt2(2));
    m_Line2->SetPoint1(src(0),src(1),src(2));
    m_Line2->SetPoint2(pt2(0),pt2(1),pt2(2));

    m_Line3->SetPoint1(pt1(0),pt1(1),pt1(2));
    m_Line3->SetPoint2(pt2(0),pt2(1),pt2(2));

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

      m_RayLine->RemoveAllInputs();
#     if VTK_MAJOR_VERSION <= 5
      m_RayLine->AddInputConnection(linesPolyData->GetProducerPort());
#     endif
      m_RayLine->AddInputConnection(m_Line1->GetOutputPort());
      m_RayLine->AddInputConnection(m_Sphere1->GetOutputPort());
      m_RayLine->AddInputConnection(m_Line2->GetOutputPort());
      m_RayLine->AddInputConnection(m_Sphere2->GetOutputPort());


    vtkSmartPointer<vtkMatrix4x4> vmat = vtkSmartPointer<vtkMatrix4x4>::New();
    Matrix4f mat = m_Content->GetImage()->GetWorldMatrix();
    for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
            vmat->SetElement(i,j,mat(i,j));
    m_Transform->SetMatrix(vmat);

    this->SetRay(pt1,pt2);
}

void vtkVoxRaytracerRepresentation::SetMuon(MuonScatter &muon, HPoint3f poca)
{
    HPoint3f pt1,pt2,src;
    src = muon.LineIn().origin;
    m_Content->GetEntryPoint(muon.LineIn(),pt1);
    m_Sphere1->SetCenter(pt1(0),pt1(1),pt1(2));
    m_Line1->SetPoint1(src(0),src(1),src(2));
    m_Line1->SetPoint2(pt1(0),pt1(1),pt1(2));

    HLine3f line_out = muon.LineOut();
    src = line_out.origin;
    float *direction = line_out.direction.data();
    for(int i=0;i<3;++i) direction[i] *= -1;
    m_Content->GetEntryPoint(line_out,pt2);
    m_Sphere2->SetCenter(pt2(0),pt2(1),pt2(2));
    m_Line2->SetPoint1(src(0),src(1),src(2));
    m_Line2->SetPoint2(pt2(0),pt2(1),pt2(2));

    m_Line3->SetPoint1(pt1(0),pt1(1),pt1(2));
    m_Line3->SetPoint2(pt2(0),pt2(1),pt2(2));

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

      m_RayLine->RemoveAllInputs();
#     if VTK_MAJOR_VERSION <= 5
      m_RayLine->AddInputConnection(linesPolyData->GetProducerPort());
#     endif
      m_RayLine->AddInputConnection(m_Line1->GetOutputPort());
      m_RayLine->AddInputConnection(m_Sphere1->GetOutputPort());
      m_RayLine->AddInputConnection(m_Line2->GetOutputPort());
      m_RayLine->AddInputConnection(m_Sphere2->GetOutputPort());


      vtkSmartPointer<vtkSphereSource> poca_sphere =
              vtkSmartPointer<vtkSphereSource>::New();
      poca_sphere->SetRadius(default_radius);
      poca_sphere->SetCenter(poca(0),poca(1),poca(2));
      m_RayLine->AddInputConnection(poca_sphere->GetOutputPort());


    vtkSmartPointer<vtkMatrix4x4> vmat = vtkSmartPointer<vtkMatrix4x4>::New();
    Matrix4f mat = m_Content->GetImage()->GetWorldMatrix();
    for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
            vmat->SetElement(i,j,mat(i,j));
    m_Transform->SetMatrix(vmat);

    if(m_Content->GetImage()->IsInsideBounds(poca))
        this->SetRay(pt1,poca,pt2);
    else
        this->SetRay(pt1,pt2);
}


void vtkVoxRaytracerRepresentation::SetMuon(vtkMuonScatter &muon)
{
    HPoint3f poca = muon.GetPocaPoint();
    MuonScatter &mu = muon.GetContent();
    this->SetMuon(mu,poca);
}


VoxRaytracer::RayData vtkVoxRaytracerRepresentation::GetRay()
{
    return m_Ray;
}

void vtkVoxRaytracerRepresentation::SetRay(HPoint3f in, HPoint3f out)
{
    m_Ray = m_Content->TraceBetweenPoints(in,out);
    this->SetRay(&m_Ray);
}

void vtkVoxRaytracerRepresentation::SetRay(HPoint3f in, HPoint3f mid, HPoint3f out)
{
    m_Ray = m_Content->TraceBetweenPoints(in,mid);
    m_Ray.AppendRay( m_Content->TraceBetweenPoints(mid,out) );
    this->SetRay(&m_Ray);
}

void vtkVoxRaytracerRepresentation::SetRay(VoxRaytracer::RayData *ray)
{
    vtkAppendPolyData *appender = m_RayRepresentation;
    appender->RemoveAllInputs();

    for(int i=0; i<ray->Data().size(); ++i) {
        int id = ray->Data().at(i).vox_id;
        Vector3i idv = m_Content->GetImage()->UnMap(id);
        vtkSmartPointer<vtkCubeSource> cube =
                vtkSmartPointer<vtkCubeSource>::New();
        cube->SetBounds(idv(0),idv(0)+1,idv(1),idv(1)+1,idv(2),idv(2)+1);
        cube->Update();
#       if VTK_MAJOR_VERSION <= 5
        appender->AddInput(cube->GetOutput());
#       endif
        appender->Update();
    }

}

void vtkVoxRaytracerRepresentation::SetVoxelsColor(Vector4f rgba)
{
    this->SetColor(m_RayRepresentationActor,rgba);
}

void vtkVoxRaytracerRepresentation::SetRayColor(Vector4f rgba)
{
    this->SetColor(m_RayLineActor,rgba);
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
    append->AddInputConnection(m_Sphere1->GetOutputPort());
    append->AddInputConnection(m_Sphere2->GetOutputPort());
    append->AddInputConnection(m_Line1->GetOutputPort());
    append->AddInputConnection(m_Line2->GetOutputPort());

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
    mapper->SetInputConnection(m_RayLine->GetOutputPort());
    mapper->Update();

    m_RayLineActor->SetMapper(mapper);
    m_RayLineActor->GetProperty()->SetColor(1,0,0);
    this->SetProp(m_RayLineActor);

    vtkSmartPointer<vtkTransformPolyDataFilter> polyfilter =
            vtkSmartPointer<vtkTransformPolyDataFilter>::New();

    polyfilter->SetInputConnection(m_RayRepresentation->GetOutputPort());
    polyfilter->SetTransform(m_Transform);

    mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(polyfilter->GetOutputPort());
    mapper->Update();

    vtkActor *vra = m_RayRepresentationActor;
    vra->SetMapper(mapper);
    vra->GetProperty()->SetOpacity(0.2);
    vra->GetProperty()->SetEdgeVisibility(true);
    vra->GetProperty()->SetColor(0.5,0.5,0.5);

    this->SetProp(vra);
}







} // vtk
} // uLib
