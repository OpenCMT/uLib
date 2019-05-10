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

#include <vtkLine.h>
#include <vtkCellArray.h>

#include <vtkLineSource.h>
#include <vtkSphereSource.h>
#include <vtkBoundingBox.h>
#include <vtkCubeSource.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkAppendPolyData.h>
#include <vtkActor.h>
#include <vtkAssembly.h>
#include <vtkProp3DCollection.h>
#include <vtkProperty.h>
#include <vtkPolyData.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>

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

    VoxRaytracer                      *m_Content;

    Scalarf                            default_radius;
    vtkAssembly                       *m_Assembly;
    vtkAppendPolyData                 *m_RayLine;
    vtkActor                          *m_RayLineActor;
    vtkActor                          *m_RayRepresentationActor;
    vtkSmartPointer<vtkTransform>      m_Transform;
    VoxRaytracer::RayData              m_Ray;
    vtkSmartPointer<vtkSphereSource>   m_Sphere1;
    vtkSmartPointer<vtkSphereSource>   m_Sphere2;
    vtkSmartPointer<vtkLineSource>     m_Line1;
    vtkSmartPointer<vtkLineSource>     m_Line2;
    vtkSmartPointer<vtkLineSource>     m_Line3;
    vtkSmartPointer<vtkAppendPolyData> m_RayRepresentation;

    vtkAppendPolyData                 *m_SelectedElement;
};


} // vtk
} // uLib


#endif // VTKVOXRAYTRACERREPRESENTATION_H
