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
#include <vtkRendererCollection.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkTextProperty.h>
#include <vtkAxesActor.h>
#include <vtkCamera.h>

#include "uLibVtkViewer.h"

namespace uLib {
namespace Vtk {


////////////////////////////////////////////////////////////////////////////////
///// VTK VIEWER  //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


Viewer::Viewer() :
    m_RenderWindow(vtkRenderWindow::New()),
    m_Renderer(vtkRenderer::New()),
    m_Annotation(vtkCornerAnnotation::New()),
    m_Marker(vtkOrientationMarkerWidget::New())
{
    InstallPipe();
}

Viewer::~Viewer()
{
    UninstallPipe();

    m_Annotation->Delete();
    m_Marker->Delete();
    m_Renderer->Delete();
    m_RenderWindow->Delete();
}

void Viewer::InstallPipe()
{
    m_RenderWindow->AddRenderer(m_Renderer);
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
            vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(m_RenderWindow);

    // annotation //
    m_Annotation->GetTextProperty()->SetColor(1,1,1);
    m_Annotation->GetTextProperty()->SetFontFamilyToArial();
    m_Annotation->GetTextProperty()->SetOpacity(0.5);
    m_Annotation->SetMaximumFontSize(10);
    m_Annotation->SetText(0,"uLib VTK Viewer - OpenCMT all right reserved.");
    m_Renderer->AddViewProp(m_Annotation);

    // orientation marker //
    vtkSmartPointer<vtkAxesActor> axes =
            vtkSmartPointer<vtkAxesActor>::New();
    m_Marker->SetInteractor(renderWindowInteractor);
    m_Marker->SetOrientationMarker(axes);
    m_Marker->SetViewport(0.0,0.0,0.2,0.2);
    m_Marker->SetEnabled(true);
    m_Marker->InteractiveOff();

    // Must be rendered here in Vtk-6.0 or seg-fault //
    m_RenderWindow->Render();
}

void Viewer::UninstallPipe()
{
    m_Renderer->RemoveAllViewProps();
    m_Renderer->Clear();
}

void Viewer::addProp(vtkProp *prop)
{
    m_Renderer->AddActor(prop);
    m_Renderer->Render();
}

void Viewer::RemoveProp(vtkProp *prop)
{
    m_Renderer->RemoveViewProp(prop);
    m_Renderer->Render();
}

void Viewer::AddPuppet(Puppet &prop)
{
    prop.ConnectRenderer(m_Renderer);
    m_Renderer->Render();
}

void Viewer::RemovePuppet(Puppet &prop)
{
    prop.DisconnectRenderer(m_Renderer);
    m_Renderer->Render();
}

void Viewer::Start()
{
    m_RenderWindow->GetInteractor()->Start();
}

vtkCornerAnnotation *Viewer::GetAnnotation()
{
    return m_Annotation;
}

vtkRenderer *Viewer::GetRenderer()
{
    return m_Renderer;
}

vtkRenderWindowInteractor *Viewer::GetInteractor()
{
    return m_RenderWindow->GetInteractor();
}

void Viewer::Reset()
{
    m_Renderer->ResetCameraClippingRange();
    m_Renderer->ResetCamera();
    m_Renderer->Render();
}


} // vtk
} // uLib

