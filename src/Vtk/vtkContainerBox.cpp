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
#include <vtkCubeSource.h>
#include <vtkActor.h>
#include <vtkAxes.h>
#include <vtkAssembly.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkLineSource.h>

#include "vtkContainerBox.h"

namespace uLib {
namespace Vtk {


// PIMPL -------------------------------------------------------------------- //

class vtkContainerBoxPimpl {
public:
    vtkContainerBoxPimpl() :
        m_Cube(vtkActor::New()),
        m_Axes(vtkActor::New()),
        m_Pivot(vtkActor::New()),
        m_Content(NULL)
    {}

    ~vtkContainerBoxPimpl()
    {
        m_Cube->Delete();
        m_Axes->Delete();
        m_Pivot->Delete();
    }

    // MEMBERS //
    vtkActor      *m_Cube;
    vtkActor      *m_Axes;
    vtkActor      *m_Pivot;
    vtkContainerBox::Content *m_Content;
};

// -------------------------------------------------------------------------- //




vtkContainerBox::vtkContainerBox(vtkContainerBox::Content &content) :
    d( new vtkContainerBoxPimpl)
{
    d->m_Content = &content;
    this->InstallPipe();
}

vtkContainerBox::~vtkContainerBox()
{
    delete d;
}

vtkPolyData *vtkContainerBox::GetPolyData() const
{
    // TODO
}

void vtkContainerBox::InstallPipe()
{
    if(!d->m_Content) return;
    Content *c = d->m_Content;

    // CUBE
    vtkSmartPointer<vtkCubeSource> cube = vtkSmartPointer<vtkCubeSource>::New();
    Vector3f p = c->GetPosition();
    cube->SetCenter(p(0),p(1),p(2));
    Vector4f p1 = c->GetWorldPoint(HPoint3f(0,0,0));
    Vector4f p2 = c->GetWorldPoint(HPoint3f(1,1,1));
    vtkSmartPointer<vtkLineSource> line = vtkSmartPointer<vtkLineSource>::New();
    line->SetPoint1(p1(0),p1(1),p1(2));
    line->SetPoint2(p2(0),p2(1),p2(2));
    line->Update();
    cube->SetBounds(line->GetOutput()->GetBounds());
    vtkSmartPointer<vtkPolyDataMapper> mapper =
            vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(cube->GetOutputPort());
    mapper->Update();
    d->m_Cube->SetMapper(mapper);
    d->m_Cube->GetProperty()->SetRepresentationToWireframe();
    d->m_Cube->GetProperty()->SetAmbient(0.7);

    // AXES //
    vtkSmartPointer<vtkAxes> axes = vtkSmartPointer<vtkAxes>::New();
    axes->SetOrigin(p1(0),p1(1),p1(2));
    mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(axes->GetOutputPort());
    mapper->Update();
    d->m_Axes->SetMapper(mapper);
    Vector3f s = c->GetSize();
    //    d->m_Axes->SetScale(s(0),s(1),s(2));
    d->m_Axes->GetProperty()->SetLineWidth(3);
    d->m_Axes->GetProperty()->SetAmbient(0.4);
    d->m_Axes->GetProperty()->SetSpecular(0);

    // PIVOT //
    axes = vtkSmartPointer<vtkAxes>::New();
    axes->SetOrigin(p(0),p(1),p(2));
    mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(axes->GetOutputPort());
    mapper->Update();
    d->m_Pivot->SetMapper(mapper);
    s = c->GetScale();
    //    d->m_Pivot->SetScale(s(0),s(1),s(2));
    d->m_Pivot->GetProperty()->SetLineWidth(3);
    d->m_Pivot->GetProperty()->SetAmbient(0.4);
    d->m_Pivot->GetProperty()->SetSpecular(0);

    this->SetProp(d->m_Cube);
    this->SetProp(d->m_Axes);
    this->SetProp(d->m_Pivot);
}



} // vtk
} // uLib
