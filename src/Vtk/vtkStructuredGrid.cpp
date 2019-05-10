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

#include "Math/StructuredGrid.h"
#include "Vtk/vtkStructuredGrid.h"

namespace uLib {
namespace Vtk {


////////////////////////////////////////////////////////////////////////////////
////// VTK STRUCTURED GRID /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////



vtkStructuredGrid::vtkStructuredGrid(Content &content) :
    m_Content(&content),
    m_Actor(vtkActor::New()),
    m_Widget(vtkBoxWidget::New()),
    m_Transform(vtkTransform::New())
{
    vtkSmartPointer<vtkWidgetCallback> callback =
        vtkSmartPointer<vtkWidgetCallback>::New();
    callback->SetGrid(this);
    m_Widget->AddObserver(vtkCommand::InteractionEvent, callback);

    this->InstallPipe();
}

vtkStructuredGrid::~vtkStructuredGrid()
{
    m_Actor->Delete();
    m_Widget->Delete();
    m_Transform->Delete();
}


void vtkStructuredGrid::SetTransform(vtkTransform *t)
{
    vtkMatrix4x4 *vmat = t->GetMatrix();
    Matrix4f mat;
    for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
            mat(i,j) = vmat->GetElement(i,j);
    m_Content->SetMatrix(mat);

    vtkSmartPointer<vtkMatrix4x4> vmat2 = vtkSmartPointer<vtkMatrix4x4>::New();
    mat = m_Content->GetWorldMatrix();
    for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
            vmat2->SetElement(i,j,mat(i,j));
    m_Transform->SetMatrix(vmat2);
    m_Transform->Update();
    this->Update();
}

vtkBoxWidget *vtkStructuredGrid::GetWidget()
{
    return m_Widget;
}

void vtkStructuredGrid::Update()
{
    m_Actor->GetMapper()->Update();
}

void vtkStructuredGrid::InstallPipe()
{
    vtkSmartPointer<vtkCubeSource> cube =
            vtkSmartPointer<vtkCubeSource>::New();
    vtkSmartPointer<vtkTransformPolyDataFilter> filter =
            vtkSmartPointer<vtkTransformPolyDataFilter>::New();

    vtkSmartPointer<vtkMatrix4x4> vmat = vtkSmartPointer<vtkMatrix4x4>::New();
    Matrix4f mat = m_Content->GetWorldMatrix();
    for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
            vmat->SetElement(i,j,mat(i,j));
    m_Transform->SetMatrix(vmat);
    filter->SetTransform(m_Transform);
    filter->SetInputConnection(cube->GetOutputPort());

    Vector3i dims = m_Content->GetDims();
    cube->SetBounds(0,dims(0),0,dims(1),0,dims(2));
    cube->Update();
    filter->Update();

    vtkSmartPointer<vtkPolyDataMapper> mapper =
            vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(filter->GetOutputPort());

    m_Actor->SetMapper(mapper);
    m_Actor->GetProperty()->SetRepresentationToSurface();
    m_Actor->GetProperty()->SetEdgeVisibility(true);
    m_Actor->GetProperty()->SetOpacity(0.4);
    m_Actor->GetProperty()->SetAmbient(0.7);
    // set content transform to actor //
    this->Update();
    m_Widget->SetProp3D(m_Actor);

    this->SetProp(m_Actor);
}


} // vtk
} // uLib
