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


vtkContainerBox::vtkContainerBox(vtkContainerBox::Content &content) :
    m_Cube(vtkActor::New()),
    m_Axes(vtkActor::New()),
    m_Pivot(vtkActor::New()),
    m_Content(&content)
{
    this->InstallPipe();
}

vtkContainerBox::~vtkContainerBox()
{
    m_Cube->Delete();
    m_Axes->Delete();
    m_Pivot->Delete();
}

vtkPolyData *vtkContainerBox::GetPolyData() const
{
    // TODO
}

void vtkContainerBox::InstallPipe()
{
    if(!m_Content) return;
    Content *c = m_Content;

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
    m_Cube->SetMapper(mapper);
    m_Cube->GetProperty()->SetRepresentationToWireframe();
    m_Cube->GetProperty()->SetAmbient(0.7);

    // AXES //
    vtkSmartPointer<vtkAxes> axes = vtkSmartPointer<vtkAxes>::New();
    axes->SetOrigin(p1(0),p1(1),p1(2));
    mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(axes->GetOutputPort());
    mapper->Update();
    m_Axes->SetMapper(mapper);
    Vector3f s = c->GetSize();
    //    m_Axes->SetScale(s(0),s(1),s(2));
    m_Axes->GetProperty()->SetLineWidth(3);
    m_Axes->GetProperty()->SetAmbient(0.4);
    m_Axes->GetProperty()->SetSpecular(0);

    // PIVOT //
    axes = vtkSmartPointer<vtkAxes>::New();
    axes->SetOrigin(p(0),p(1),p(2));
    mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(axes->GetOutputPort());
    mapper->Update();
    m_Pivot->SetMapper(mapper);
    s = c->GetScale();
    //    m_Pivot->SetScale(s(0),s(1),s(2));
    m_Pivot->GetProperty()->SetLineWidth(3);
    m_Pivot->GetProperty()->SetAmbient(0.4);
    m_Pivot->GetProperty()->SetSpecular(0);

    this->SetProp(m_Cube);
    this->SetProp(m_Axes);
    this->SetProp(m_Pivot);
}



} // vtk
} // uLib
