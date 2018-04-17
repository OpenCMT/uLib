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


#include <vtkConfigure.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkAppendPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkLineSource.h>
#include <vtkActor.h>

#include <vtk3DWidget.h>
#include <vtkBoxWidget.h>

#include <vtkRenderWindowInteractor.h>

#include <vtkCommand.h>
#include <vtkTransform.h>

#include "vtkMuonScatter.h"
#include "Math/Dense.h"

namespace uLib {
namespace Vtk {

///// CALLBACK /////////////////////////////////////////////////////////////////

//namespace {

//class vtkWidgetCallback : public vtkCommand
//{
//public:
//  static vtkWidgetCallback *New()
//    { return new vtkWidgetCallback; }
//  void SetParent(uLib::vtkMuonScatter *parent) { this->parent = parent; }
//  virtual void Execute(vtkObject *caller, unsigned long, void*)
//    {
//      vtkSmartPointer<vtkTransform> t =
//              vtkSmartPointer<vtkTransform>::New();
//      vtkBoxWidget *widget = reinterpret_cast<vtkBoxWidget*>(caller);
//      widget->GetTransform(t);
//      //parent->SetTransform(t);
//      //std::cout << "Scatter\n";
//  }
//private:
//  uLib::vtkMuonScatter *parent;
//};

//}

//// PIMPL /////////////////////////////////////////////////////////////////////

class vtkMuonScatterPimpl {
public:
    vtkMuonScatterPimpl() :
        m_Content(NULL),
        m_LineIn(vtkLineSource::New()),
        m_LineOut(vtkLineSource::New()),
        m_PolyData(vtkPolyData::New()),
        m_SpherePoca(NULL)
    {}

    ~vtkMuonScatterPimpl()
    {
        m_LineIn->Delete();
        m_LineOut->Delete();
        if(m_SpherePoca) m_SpherePoca->Delete();
    }

    // members //
    vtkMuonScatter::Content *m_Content;
    vtkLineSource   *m_LineIn, *m_LineOut;
    vtkSphereSource *m_SpherePoca;
    vtkPolyData *m_PolyData;
};






////////////////////////////////////////////////////////////////////////////////
/////  VTK MUON Scatter  /////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


vtkMuonScatter::vtkMuonScatter(MuonScatter &content) :
    d(new vtkMuonScatterPimpl)
{
      d->m_Content = &content;
      InstallPipe();
}

vtkMuonScatter::vtkMuonScatter(const MuonScatter &content) :
    d(new vtkMuonScatterPimpl)
{
      d->m_Content = const_cast<MuonScatter *>(&content);
      InstallPipe();
}


vtkMuonScatter::~vtkMuonScatter()
{
    delete d;
}

vtkMuonScatter::Content &vtkMuonScatter::GetContent()
{
    return *d->m_Content;
}

void vtkMuonScatter::PrintSelf(std::ostream &o) const
{
    //    o << d->content;
}


void vtkMuonScatter::InstallPipe()
{
    if(d->m_Content) {
        vtkLineSource *line_in = d->m_LineIn;
        vtkLineSource *line_out = d->m_LineOut;

        float distance = (d->m_Content->LineIn().origin - d->m_Content->LineOut().origin).norm() / 10;

        HPoint3f pt;
        pt = d->m_Content->LineIn().origin;
        line_in->SetPoint1(pt(0),pt(1),pt(2));
        pt= d->m_Content->LineIn().origin + d->m_Content->LineIn().direction * distance;
        line_in->SetPoint2(pt(0),pt(1),pt(2));
        pt = d->m_Content->LineOut().origin;
        line_out->SetPoint1(pt(0),pt(1),pt(2));
        pt = d->m_Content->LineOut().origin + d->m_Content->LineOut().direction * distance;
        line_out->SetPoint2(pt(0),pt(1),pt(2));
    }

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(d->m_LineIn->GetOutputPort());
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    this->SetProp(actor);

    mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(d->m_LineOut->GetOutputPort());
    actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    this->SetProp(actor);
}

vtkPolyData *vtkMuonScatter::GetPolyData() const
{
    vtkSmartPointer<vtkAppendPolyData> append = vtkSmartPointer<vtkAppendPolyData>::New();
//#   if VTK_MAJOR_VERSION <= 5
    append->AddInputConnection(d->m_LineIn->GetOutputPort());
    append->AddInputConnection(d->m_LineOut->GetOutputPort());
    if(d->m_SpherePoca) append->AddInputConnection(d->m_SpherePoca->GetOutputPort());
//#   else
//    append->AddInputData(d->m_LineIn->GetOutput());
//    append->AddInputData(d->m_LineOut->GetOutput());
//    if(d->m_SpherePoca) append->AddInputData(d->m_SpherePoca->GetOutput());
//#   endif
    append->Update();
    d->m_PolyData->DeepCopy(append->GetOutput());
    return d->m_PolyData;
}

void vtkMuonScatter::AddPocaPoint(HPoint3f poca)
{
    vtkSphereSource *sphere = vtkSphereSource::New();
    float size = (d->m_Content->LineIn().origin - d->m_Content->LineOut().origin).head(3).norm();
    size /= 100;
    sphere->SetRadius(size);
    sphere->SetCenter(poca(0),poca(1),poca(2));
    sphere->Update();
    d->m_SpherePoca = sphere;

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(d->m_SpherePoca->GetOutputPort());
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    this->SetProp(actor);
}

HPoint3f vtkMuonScatter::GetPocaPoint()
{
    double center[3];
    if(d->m_SpherePoca) {
        d->m_SpherePoca->GetCenter(center);
        return HPoint3f(center[0],center[1],center[2]);
    }
    else {
        return HPoint3f(0,0,0);
    }
}


void vtkMuonScatter::ConnectInteractor(vtkRenderWindowInteractor *interactor)
{
    // TODO
}




} // vtk
} // uLib
