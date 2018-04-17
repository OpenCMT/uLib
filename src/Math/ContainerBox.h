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



#ifndef U_CONTAINERBOX_H
#define U_CONTAINERBOX_H

#include "Geometry.h"


namespace uLib {



class ContainerBox : public AffineTransform {
public:
    ContainerBox() : m_LocalT(this) {}

    ContainerBox(const ContainerBox &copy) :
        m_LocalT(this),
        AffineTransform(copy)
    {
        // FIX for performance //
        this->SetOrigin(copy.GetOrigin());
        this->SetSize(copy.GetSize());
    }

    inline void SetOrigin(const Vector3f &v) { m_LocalT.SetPosition(v); }

    inline Vector3f GetOrigin() const { return m_LocalT.GetPosition(); }

    void SetSize(const Vector3f &v) {
        Vector3f pos = this->GetOrigin();
        m_LocalT = AffineTransform(this);
        m_LocalT.Scale(v);
        m_LocalT.SetPosition(pos);
    }

    inline Vector3f GetSize() const { return m_LocalT.GetScale(); }

    // FIX... //
    inline void FlipLocalAxes(int first, int second)
    { m_LocalT.FlipAxes(first,second); }

    Matrix4f GetWorldMatrix() const { return m_LocalT.GetWorldMatrix(); }

    inline Vector4f GetWorldPoint(const Vector4f &v) const {
        return m_LocalT.GetWorldMatrix() * v;
    }

    inline Vector4f GetWorldPoint(const float x, const float y, const float z) {
        return this->GetWorldPoint(Vector4f(x,y,z,1));
    }

    inline Vector4f GetLocalPoint(const Vector4f &v) const {
        return m_LocalT.GetWorldMatrix().inverse() * v;
    }

    inline Vector4f GetLocalPoint(const float x, const float y, const float z) {
         return this->GetLocalPoint(Vector4f(x,y,z,1));
    }


protected:

private:
    AffineTransform  m_LocalT;
};


}



#endif // CONTAINERBOX_H
