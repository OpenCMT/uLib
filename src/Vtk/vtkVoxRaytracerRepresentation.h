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



#ifndef U_VTKVOXRAYTRACERREPRESENTATION_H
#define U_VTKVOXRAYTRACERREPRESENTATION_H


#include "Core/Macros.h"
#include "Math/Dense.h"

#include "uLibVtkInterface.h"

#include "Detectors/MuonScatter.h"

#include "Math/StructuredGrid.h"
#include "Math/VoxRaytracer.h"


class vtkActor;

namespace uLib {
namespace Vtk {

class vtkVoxRaytracerRepresentation : public Puppet {
    typedef VoxRaytracer Content;
public:
    vtkVoxRaytracerRepresentation(Content &content);
    ~vtkVoxRaytracerRepresentation();

    uLib::VoxRaytracer *GetRaytracerAlgorithm();

    vtkProp *GetProp();

    vtkPolyData *GetPolyData() const;

    enum RepresentationElements {
        RayElements,
        VoxelsElements
    };
    void SetRepresentationElements(enum RepresentationElements el);

    void SetMuon(MuonScatter &muon);

    void SetMuon(MuonScatter &muon, HPoint3f poca);

    void SetMuon(class vtkMuonEvent &muon);

    void SetMuon(class vtkMuonScatter &muon);

    VoxRaytracer::RayData GetRay();

    void SetRay(HPoint3f in, HPoint3f out);

    void SetRay(HPoint3f in, HPoint3f mid, HPoint3f out);

    void SetRay(VoxRaytracer::RayData *ray);

    void SetVoxelsColor(Vector4f rgba);
    void SetRayColor(Vector4f rgba);



private:
    void InstallPipe();

    void SetColor(vtkActor *actor, Vector4f rgba);

    friend class vtkVoxRaytracerRepresentationPimpl;
    class vtkVoxRaytracerRepresentationPimpl *d;
};


} // vtk
} // uLib


#endif // VTKVOXRAYTRACERREPRESENTATION_H
