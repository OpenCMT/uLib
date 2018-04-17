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

#include <vtkLineSource.h>
#include <vtkBoundingBox.h>
#include <vtkCubeSource.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>

#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkBoxWidget.h>
#include <vtkCommand.h>

#include "Math/StructuredGrid.h"
#include "Vtk/vtkStructuredGrid.h"

namespace uLib {
namespace Vtk {

////////////////////////////////////////////////////////////////////////////////
////// PIMPL  //////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


class vtkStructuredGridPimpl {

    // ---- WIDGET CBK ------------------------------------------------------ //
    class vtkWidgetCallback : public vtkCommand
    {
    public:
      static vtkWidgetCallback *New() { return new vtkWidgetCallback; }
      void SetParent(uLib::Vtk::vtkStructuredGrid *parent) { this->parent = parent; }
      virtual void Execute(vtkObject *caller, unsigned long, void*)
        {
          vtkSmartPointer<vtkTransform> t =
                  vtkSmartPointer<vtkTransform>::New();
          vtkBoxWidget *widget = reinterpret_cast<vtkBoxWidget*>(caller);
          widget->GetTransform(t);
          parent->SetTransform(t);
          //std::cout << "event\n";
      }
    private:
      uLib::Vtk::vtkStructuredGrid *parent;
    };
    // ---------------------------------------------------------------------- //

public:
    vtkStructuredGridPimpl(vtkStructuredGrid *parent, StructuredGrid &content) :
        p(parent),
        m_Content(&content),
        m_Actor(vtkActor::New()),
        m_Widget(vtkBoxWidget::New()),
        m_Transform(vtkTransform::New())
    {
        vtkSmartPointer<vtkWidgetCallback> callback =
            vtkSmartPointer<vtkWidgetCallback>::New();
        callback->SetParent(p);
        m_Widget->AddObserver(vtkCommand::InteractionEvent, callback);
    }

    ~vtkStructuredGridPimpl()
    {
        m_Actor->Delete();
        m_Widget->Delete();
        m_Transform->Delete();
    }

    // members //
    vtkActor       *m_Actor;
    vtkBoxWidget   *m_Widget;
    StructuredGrid *m_Content;
    vtkTransform   *m_Transform;
private:
    vtkStructuredGrid *p;
};


////////////////////////////////////////////////////////////////////////////////
////// VTK STRUCTURED GRID /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////



vtkStructuredGrid::vtkStructuredGrid(Content &content) :
    d(new vtkStructuredGridPimpl(this,content))
{
    this->InstallPipe();
}

vtkStructuredGrid::~vtkStructuredGrid()
{
    delete d;
}


void vtkStructuredGrid::SetTransform(vtkTransform *t)
{
    vtkMatrix4x4 *vmat = t->GetMatrix();
    Matrix4f mat;
    for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
            mat(i,j) = vmat->GetElement(i,j);
    d->m_Content->SetMatrix(mat);

    vtkSmartPointer<vtkMatrix4x4> vmat2 = vtkSmartPointer<vtkMatrix4x4>::New();
    mat = d->m_Content->GetWorldMatrix();
    for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
            vmat2->SetElement(i,j,mat(i,j));
    d->m_Transform->SetMatrix(vmat2);
    d->m_Transform->Update();
    this->Update();
}

vtkBoxWidget *vtkStructuredGrid::GetWidget()
{
    return d->m_Widget;
}

void vtkStructuredGrid::Update()
{
    d->m_Actor->GetMapper()->Update();
}

void vtkStructuredGrid::InstallPipe()
{
    vtkSmartPointer<vtkCubeSource> cube =
            vtkSmartPointer<vtkCubeSource>::New();
    vtkSmartPointer<vtkTransformPolyDataFilter> filter =
            vtkSmartPointer<vtkTransformPolyDataFilter>::New();

    vtkSmartPointer<vtkMatrix4x4> vmat = vtkSmartPointer<vtkMatrix4x4>::New();
    Matrix4f mat = d->m_Content->GetWorldMatrix();
    for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
            vmat->SetElement(i,j,mat(i,j));
    d->m_Transform->SetMatrix(vmat);
    filter->SetTransform(d->m_Transform);
    filter->SetInputConnection(cube->GetOutputPort());

    Vector3i dims = d->m_Content->GetDims();
    cube->SetBounds(0,dims(0),0,dims(1),0,dims(2));
    cube->Update();
    filter->Update();

    vtkSmartPointer<vtkPolyDataMapper> mapper =
            vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(filter->GetOutputPort());

    d->m_Actor->SetMapper(mapper);
    d->m_Actor->GetProperty()->SetRepresentationToSurface();
    d->m_Actor->GetProperty()->SetEdgeVisibility(true);
    d->m_Actor->GetProperty()->SetOpacity(0.4);
    d->m_Actor->GetProperty()->SetAmbient(0.7);
    // set content transform to actor //
    this->Update();
    d->m_Widget->SetProp3D(d->m_Actor);

    this->SetProp(d->m_Actor);
}


} // vtk
} // uLib
