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


////////////////////////////////////////////////////////////////////////////////
/////  VTK MUON EVENT  /////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


vtkMuonEvent::vtkMuonEvent(MuonEventData &content) :
    m_Prop(vtkActor::New()),
    m_PolyData(NULL),
    m_Appender(vtkAppendPolyData::New()),
    content(&content)
{
    InstallPipe();
}

vtkMuonEvent::vtkMuonEvent(const MuonEventData &content) :
    m_Prop(vtkActor::New()),
    m_PolyData(NULL),
    m_Appender(vtkAppendPolyData::New()),
    content(const_cast<MuonEventData *>(&content))
{
    InstallPipe();
}


vtkMuonEvent::~vtkMuonEvent()
{
    if (m_Prop) m_Prop->Delete();
}

vtkMuonEvent::Content &vtkMuonEvent::GetContent()
{
    return *content;
}

void vtkMuonEvent::PrintSelf(std::ostream &o) const
{
    o << "..:: MuonEvent ::..\n" \
         "\t[in]  Origin    > " << content->LineIn().origin.transpose()    << "\n" <<
         "\t[in]  Direction > " << content->LineIn().direction.transpose() << "\n" <<
         "\t[out] Origin    > " << content->LineOut().origin.transpose()   << "\n" <<
         "\t[out] Direction > " << content->LineOut().direction.transpose()<< "\n" <<
         "\tMomentum        > " << content->GetMomentum() << "\n" <<
         "...................\n";
}

vtkProp *vtkMuonEvent::GetProp()
{
    return m_Prop;
}

void vtkMuonEvent::InstallPipe()
{


    vtkAppendPolyData *appender = m_Appender;
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();

    if(content) {
        vtkSmartPointer<vtkLineSource> line_in = vtkSmartPointer<vtkLineSource>::New();
        vtkSmartPointer<vtkLineSource> line_out = vtkSmartPointer<vtkLineSource>::New();

        float distance = (content->LineIn().origin - content->LineOut().origin).norm() / 10;

        HPoint3f pt;
        pt = content->LineIn().origin;
        line_in->SetPoint1(pt(0),pt(1),pt(2));
        pt= content->LineIn().origin + content->LineIn().direction * distance;
        line_in->SetPoint2(pt(0),pt(1),pt(2));
        pt = content->LineOut().origin;
        line_out->SetPoint1(pt(0),pt(1),pt(2));
        pt = content->LineOut().origin + content->LineOut().direction * distance;
        line_out->SetPoint2(pt(0),pt(1),pt(2));

        appender->AddInputConnection(line_in->GetOutputPort());
        appender->AddInputConnection(line_out->GetOutputPort());
    }

    appender->Update();
    mapper->SetInputConnection(appender->GetOutputPort());
    mapper->Update();
    m_Prop->SetMapper(mapper);
}

vtkPolyData *vtkMuonEvent::GetPolyData() const
{
    return m_Appender->GetOutput();
}

void vtkMuonEvent::AddPocaPoint(HPoint3f poca)
{
    m_Poca = poca;
    vtkSmartPointer<vtkSphereSource> sphere =
            vtkSmartPointer<vtkSphereSource>::New();
    float size = (content->LineIn().origin - content->LineOut().origin).head(3).norm();
    size /= 100;
    sphere->SetRadius(size);
    sphere->SetCenter(poca(0),poca(1),poca(2));
    sphere->Update();
    m_Appender->AddInputConnection(sphere->GetOutputPort());
    m_Appender->Update();
}

HPoint3f vtkMuonEvent::GetPocaPoint()
{
    return m_Poca;
}





}
