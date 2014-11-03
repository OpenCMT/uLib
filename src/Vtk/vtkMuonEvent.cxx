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

#include "vtkMuonEvent.h"
#include "Math/Dense.h"

namespace uLib {

///// CALLBACK /////////////////////////////////////////////////////////////////

class vtkWidgetCallback : public vtkCommand
{
public:
  static vtkWidgetCallback *New()
    { return new vtkWidgetCallback; }
  void SetParent(uLib::vtkMuonEvent *parent) { this->parent = parent; }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
    {
      vtkSmartPointer<vtkTransform> t =
              vtkSmartPointer<vtkTransform>::New();
      vtkBoxWidget *widget = reinterpret_cast<vtkBoxWidget*>(caller);
      widget->GetTransform(t);
      //parent->SetTransform(t);
      //std::cout << "event\n";
  }
private:
  uLib::vtkMuonEvent *parent;
};


//// PIMPL /////////////////////////////////////////////////////////////////////

class vtkMuonEventPimpl {
    typedef vtkWidgetCallback Callback;
public:
    vtkMuonEventPimpl() :
        m_Prop(vtkActor::New()),
        m_PolyData(NULL),
        m_Appender(vtkAppendPolyData::New()),
        content(NULL)
    {}

    ~vtkMuonEventPimpl()
    {
        m_Prop->Delete();
    }

    // members //
    vtkMuonEvent::Content *content;
    vtkPolyData *m_PolyData;
    vtkActor    *m_Prop;

    vtkAppendPolyData *m_Appender;
    vtkBoxWidget *m_WidgetIN, *m_WidgetOUT;
    HPoint3f m_Poca;
};






////////////////////////////////////////////////////////////////////////////////
/////  VTK MUON EVENT  /////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


vtkMuonEvent::vtkMuonEvent(MuonEventData &content) :
    d(new vtkMuonEventPimpl)
{
      d->content = &content;
      InstallPipe();
}

vtkMuonEvent::vtkMuonEvent(const MuonEventData &content) :
    d(new vtkMuonEventPimpl)
{
      d->content = const_cast<MuonEventData *>(&content);
      InstallPipe();
}


vtkMuonEvent::~vtkMuonEvent()
{
    if (d->m_Prop) d->m_Prop->Delete();
}

vtkMuonEvent::Content &vtkMuonEvent::GetContent()
{
    return *d->content;
}

void vtkMuonEvent::PrintSelf(std::ostream &o) const
{
    o << "..:: MuonEvent ::..\n" \
         "\t[in]  Origin    > " << d->content->LineIn().origin.transpose()    << "\n" <<
         "\t[in]  Direction > " << d->content->LineIn().direction.transpose() << "\n" <<
         "\t[out] Origin    > " << d->content->LineOut().origin.transpose()   << "\n" <<
         "\t[out] Direction > " << d->content->LineOut().direction.transpose()<< "\n" <<
         "\tMomentum        > " << d->content->GetMomentum() << "\n" <<
         "...................\n";
}

vtkProp *vtkMuonEvent::GetProp()
{
    return d->m_Prop;
}

void vtkMuonEvent::InstallPipe()
{


    vtkAppendPolyData *appender = d->m_Appender;
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();

    if(d->content) {
        vtkSmartPointer<vtkLineSource> line_in = vtkSmartPointer<vtkLineSource>::New();
        vtkSmartPointer<vtkLineSource> line_out = vtkSmartPointer<vtkLineSource>::New();

        float distance = (d->content->LineIn().origin - d->content->LineOut().origin).norm() / 10;

        HPoint3f pt;        
        pt = d->content->LineIn().origin;
        line_in->SetPoint1(pt(0),pt(1),pt(2));
        pt= d->content->LineIn().origin + d->content->LineIn().direction * distance;
        line_in->SetPoint2(pt(0),pt(1),pt(2));
        pt = d->content->LineOut().origin;
        line_out->SetPoint1(pt(0),pt(1),pt(2));
        pt = d->content->LineOut().origin + d->content->LineOut().direction * distance;
        line_out->SetPoint2(pt(0),pt(1),pt(2));

        appender->AddInputConnection(line_in->GetOutputPort());
        appender->AddInputConnection(line_out->GetOutputPort());
    }

    appender->Update();
    mapper->SetInputConnection(appender->GetOutputPort());
    mapper->Update();
    d->m_Prop->SetMapper(mapper);
}

vtkPolyData *vtkMuonEvent::GetPolyData() const
{
    return d->m_Appender->GetOutput();
}

void vtkMuonEvent::AddPocaPoint(HPoint3f poca)
{
    d->m_Poca = poca;
    vtkSmartPointer<vtkSphereSource> sphere =
            vtkSmartPointer<vtkSphereSource>::New();
    float size = (d->content->LineIn().origin - d->content->LineOut().origin).head(3).norm();
    size /= 100;
    sphere->SetRadius(size);
    sphere->SetCenter(poca(0),poca(1),poca(2));
    sphere->Update();
    d->m_Appender->AddInputConnection(sphere->GetOutputPort());
    d->m_Appender->Update();
}

HPoint3f vtkMuonEvent::GetPocaPoint()
{
    return d->m_Poca;
}





}
