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



#ifndef VOXRAYTRACER_H
#define VOXRAYTRACER_H

#include <math.h>

#include "Core/Vector.h"
#include "Math/StructuredGrid.h"

namespace uLib {

class VoxRaytracer {

public:
    class RayData {
    public:
        RayData() : m_TotalLength(0) {}

        typedef struct {
            Id_t vox_id;
            Scalarf L;
        } Element;

        inline void AddElement(Id_t id, float L);

        void AppendRay ( const RayData &in);

        uLibConstRefMacro(Data,Vector<Element>)
        uLibConstRefMacro(TotalLength,Scalarf)

        void PrintSelf(std::ostream &o);

    private:
        Vector<Element> m_Data;
        Scalarf         m_TotalLength;
    };


 public:
 VoxRaytracer(StructuredGrid &image) : m_Image(&image) {
      m_scale <<
	(m_Image->GetWorldMatrix() * Vector4f(1,0,0,0)).norm(),
	(m_Image->GetWorldMatrix() * Vector4f(0,1,0,0)).norm(),
	(m_Image->GetWorldMatrix() * Vector4f(0,0,1,0)).norm();
    }

    bool GetEntryPoint(const HLine3f &line, HPoint3f &pt);

    bool GetExitPoint(const HLine3f &line, HPoint3f &pt);

    RayData TraceBetweenPoints(const HPoint3f &in, const HPoint3f &out) const;

    RayData TraceLine(const HLine3f &line) const;

    uLibGetMacro(Image,StructuredGrid *)

private:
    StructuredGrid *m_Image;
    Vector3f        m_scale;	
};

}



#endif // VOXRAYTRACER_H
