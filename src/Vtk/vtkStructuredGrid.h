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



#ifndef U_VTKSTRUCTUREDGRID_H
#define U_VTKSTRUCTUREDGRID_H

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

#include "Math/Dense.h"

#include "uLibVtkInterface.h"
#include "Math/StructuredGrid.h"


namespace uLib {
namespace Vtk {

class vtkStructuredGrid : public Puppet {
    typedef StructuredGrid Content;
public:

    vtkStructuredGrid(Content &content);
    ~vtkStructuredGrid();

    void SetTransform(class vtkTransform *t);

    class vtkBoxWidget * GetWidget();

    void Update();


private:
    void InstallPipe();

    class vtkWidgetCallback : public vtkCommand
    {
    public:
        static vtkWidgetCallback *New() { return new vtkWidgetCallback; }

        void SetGrid(uLib::Vtk::vtkStructuredGrid *grid) { this->grid = grid; }

        virtual void Execute(vtkObject *caller, unsigned long, void*)
        {
          vtkSmartPointer<vtkTransform> t = vtkSmartPointer<vtkTransform>::New();
          vtkBoxWidget *widget = reinterpret_cast<vtkBoxWidget*>(caller);
          widget->GetTransform(t);
          grid->SetTransform(t);
        }
    private:
        uLib::Vtk::vtkStructuredGrid *grid;
    };

    vtkActor          *m_Actor;
    vtkBoxWidget      *m_Widget;
    StructuredGrid    *m_Content;
    vtkTransform      *m_Transform;
};


} // vtk
} // uLib


#endif // VTKSTRUCTUREDGRID_H
