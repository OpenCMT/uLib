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




#if VTK_MAJOR_VERSION <= 5
#
#else
# include <vtkAutoInit.h>
#endif

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif


#include <vtkConfigure.h>
#include <vtkProp.h>
#include <vtkActor.h>
#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkPropCollection.h>
#include <vtkRendererCollection.h>
#include <vtkPropAssembly.h>

#include <vtkPolyData.h>
#include <vtkPolyDataWriter.h>
#include <vtkXMLPolyDataWriter.h>

#include "uLibVtkInterface.h"







namespace uLib {
namespace Vtk {



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// POLYDATA //


void Polydata::SaveToFile(const char *vtk_file)
{
    vtkSmartPointer<vtkPolyDataWriter> writer =
      vtkSmartPointer<vtkPolyDataWriter>::New();
    writer->SetFileName(vtk_file);
    vtkPolyData * data = GetPolyData();
    if(data) {
#       if VTK_MAJOR_VERSION <= 5
        writer->SetInputConnection(data->GetProducerPort());
#       else
        writer->SetInputData(data);
#       endif
        writer->Update();
    }
}

void Polydata::SaveToXMLFile(const char *vtp_file)
{
    vtkSmartPointer<vtkXMLPolyDataWriter> writer =
      vtkSmartPointer<vtkXMLPolyDataWriter>::New();
    writer->SetFileName(vtp_file);
    vtkPolyData * data = GetPolyData();
    if(data) {
#       if VTK_MAJOR_VERSION <= 5
        writer->SetInputConnection(data->GetProducerPort());
#       else
        writer->SetInputData(data);
#       endif
        writer->Update();
    }
}



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// PUPPET //

// PIMPL -------------------------------------------------------------------- //

class PuppetData {
public:
    PuppetData() :
        m_Renderers(vtkRendererCollection::New()),
        m_Assembly(vtkPropAssembly::New())
    {}

    ~PuppetData() {
        m_Renderers->RemoveAllItems();
        m_Assembly->GetParts()->RemoveAllItems();
        m_Renderers->Delete();
        m_Assembly->Delete();
    }

    // members //
    vtkRendererCollection *m_Renderers;
    vtkPropAssembly       *m_Assembly;
};

// -------------------------------------------------------------------------- //




Puppet::Puppet() : d(new PuppetData) { }

Puppet::~Puppet()
{
    delete d;
}

vtkProp *Puppet::GetProp()
{
    if (d->m_Assembly->GetParts()->GetNumberOfItems() == 1)
    {
        //        d->m_Assembly->GetParts()->InitTraversal();
        //        return d->m_Assembly->GetParts()->GetNextProp();
        return d->m_Assembly->GetParts()->GetLastProp();
    }
    else return d->m_Assembly;
}

void Puppet::SetProp(vtkProp *prop)
{
    if(prop) d->m_Assembly->AddPart(prop);
}

void Puppet::RemoveProp(vtkProp *prop)
{
    // TODO
}


vtkPropCollection *Puppet::GetProps()
{
    return d->m_Assembly->GetParts();
}

void Puppet::ConnectRenderer(vtkRenderer *renderer)
{
    if(renderer) {
        this->GetRenderers()->AddItem(renderer);
        if(d->m_Assembly->GetParts()->GetNumberOfItems() == 1)
            renderer->AddActor(this->GetProp());
        else if(d->m_Assembly->GetParts()->GetNumberOfItems() >0)
        {
            vtkPropCollection *props = d->m_Assembly->GetParts();
            props->InitTraversal();
            for (int i=0; i<props->GetNumberOfItems(); ++i)
                renderer->AddActor(props->GetNextProp());
        }
    }
}

void Puppet::DisconnectRenderer(vtkRenderer *renderer)
{
    if(renderer) {
        if(this->GetProp())
            renderer->RemoveViewProp(this->GetProp());
        else if(d->m_Assembly->GetParts()->GetNumberOfItems() >0)
        {
            vtkPropCollection *props = d->m_Assembly->GetParts();
            props->InitTraversal();
            for (int i=0; i<props->GetNumberOfItems(); ++i)
                renderer->RemoveViewProp(props->GetNextProp());
        }
        this->GetRenderers()->RemoveItem(renderer);
    }
}

void Puppet::ConnectViewer(Viewer *viewer)
{
    // TODO
}

void Puppet::DisonnectViewer(Viewer *viewer)
{
    // TODO
}

vtkRendererCollection *Puppet::GetRenderers() const
{
    return d->m_Renderers;
}

void Puppet::PrintSelf(std::ostream &o) const
{
    o << "Props Assembly: \n";
    d->m_Assembly->PrintSelf(o,vtkIndent(1));

    o << "Connected Renderers: \n";
    d->m_Renderers->PrintSelf(o,vtkIndent(1));
}










} // Vtk
} // uLib
