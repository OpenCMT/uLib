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



#ifndef ULIBVTKVIEWER_H
#define ULIBVTKVIEWER_H

#include <iostream>
#include "uLibVtkInterface.h"

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkCornerAnnotation.h>
#include <vtkOrientationMarkerWidget.h>

class vtkProp;
class vtk3DWidget;
class vtkCornerAnnotation;
class vtkRenderWindowInteractor;
class vtkRenderer;

namespace uLib {
namespace Vtk {


template <class T>
class Tie {
public:
    void DoAction() {
        std::cout << "Tie::DoAction -> generic Tie does nothing\n";
    }
};


class Viewer {

public:
    Viewer();
    ~Viewer();


    void AddPuppet(Puppet &prop);

    void RemovePuppet(Puppet &prop);

    void AddWidget(vtk3DWidget *widget);

    void Reset();

    void Start();

    vtkCornerAnnotation *GetAnnotation();

    vtkRenderer * GetRenderer();

    vtkRenderWindowInteractor * GetInteractor();

    void addProp(vtkProp *prop);

    void RemoveProp(vtkProp *prop);

private:
    void InstallPipe();
    void UninstallPipe();

    vtkRenderer                *m_Renderer;
    vtkRenderWindow            *m_RenderWindow;
    vtkCornerAnnotation        *m_Annotation;
    vtkOrientationMarkerWidget *m_Marker;
};

template <>
class Tie<Viewer> {
public:
    void DoAction() {
        std::cout << " VIEWER TIE !!! \n";
    }
};


} // vtk
} // uLib

#endif // ULIBVTKVIEWER_H
