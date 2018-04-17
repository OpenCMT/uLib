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




#include <vtkBoxWidget.h>
#include <vtkSmartPointer.h>
#include <vtkCommand.h>


#include <Detectors/MuonScatter.h>
#include <Math/VoxRaytracer.h>

#include "Vtk/vtkMuonScatter.h"
#include "Vtk/vtkStructuredGrid.h"
#include "Vtk/vtkVoxRaytracerRepresentation.h"
#include "Vtk/uLibVtkViewer.h"

// remove
#include <vtkCornerAnnotation.h>

#include "testing-prototype.h"

using namespace uLib;



class vtkWidgetCallback : public vtkCommand
{
public:
  static vtkWidgetCallback *New() { return new vtkWidgetCallback; }

  void SetTracer(Vtk::vtkVoxRaytracerRepresentation *parent)
  {
      this->vtk_raytr = parent;
  }

  void SetMuon  (uLib::MuonScatter *muon) { this->muon = muon; }

  void SetAnnotation ( vtkCornerAnnotation *annotation) {
      this->annotation = annotation;
  }

  virtual void Execute(vtkObject *caller, unsigned long, void*)
  {
      char str[40];
      vtk_raytr->SetMuon(*muon);
      if(annotation)
      {
          sprintf(str,"total length = %f",vtk_raytr->GetRay().TotalLength());
          annotation->SetText(1,str);
          for(int i=0; i<vtk_raytr->GetRay().Data().size(); ++i)
          {
              std::cout << "L[" << i << "] = "
                        << vtk_raytr->GetRay().Data().at(i).L << "\n";
          }
          std::cout << "\n";
      }
  }

private:
  vtkWidgetCallback() :
      vtk_raytr(NULL),
      muon(NULL),
      annotation(NULL) {}

  uLib::VoxRaytracer *raytracer;
  Vtk::vtkVoxRaytracerRepresentation *vtk_raytr;
  uLib::MuonScatter *muon;
  vtkCornerAnnotation *annotation;
};




int main()
{
    BEGIN_TESTING(vtk VoxRaytracer);


    // muon scatter //
    MuonScatter muon;
    muon.LineIn().origin << -6, 12, -6, 1;
    muon.LineIn().direction << 1 , -1 , 1 , 0;
    muon.LineOut().origin << 6 , -4 , 6 , 1;
    muon.LineOut().direction << 1 , -1 , 1 , 0;

    Vtk::vtkMuonScatter v_muon(muon);


    // structured grid //
    StructuredGrid grid(Vector3i(12,10,12));
    grid.SetSpacing(Vector3f(1,1,1));
    grid.SetPosition(Vector3f(0,0,0));


    Vtk::vtkStructuredGrid v_grid(grid);


    // voxraytracer //
    VoxRaytracer rt(grid);
    HPoint3f pt;
    rt.GetEntryPoint(muon.LineIn(),pt);
    std::cout << pt.transpose() << "\n";

    Vtk::vtkVoxRaytracerRepresentation v_rt(rt);
    v_rt.SetMuon(muon);
    v_rt.SetRayColor(Vector4f(1,0,0,1));

    //    // renderer //
    Vtk::Viewer viewer;

    // widget //
    vtkBoxWidget *widget = v_grid.GetWidget();


    vtkWidgetCallback *cbk = vtkWidgetCallback::New();
    cbk->SetTracer(&v_rt);
    cbk->SetMuon(&muon);
    cbk->SetAnnotation(viewer.GetAnnotation());
    widget->AddObserver(vtkCommand::InteractionEvent, cbk);
    widget->SetInteractor(viewer.GetInteractor());
    widget->PlaceWidget();
    widget->On();

    viewer.AddPuppet(v_grid);
    viewer.AddPuppet(v_rt);
    viewer.AddPuppet(v_muon);
    viewer.Start();


    END_TESTING;
}
