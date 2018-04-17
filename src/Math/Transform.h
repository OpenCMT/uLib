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



/* 
 * Copyright (C) 2012  Andrea Rigoni Garola <andrea.rigoni@pd.infn.it>
 * 
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1 of the
 * License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301 USA
 * 
 */


#ifndef U_TRANSFORM_H
#define U_TRANSFORM_H

#include <Core/Macros.h>
#include <Eigen/Geometry>


namespace uLib {

////////////////////////////////////////////////////////////////////////////////
/////////  AFFINE TRANSFORM  WRAPPER  //////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class AffineTransform {
protected:
    Eigen::Affine3f  m_T;
    AffineTransform *m_Parent;
public:
    AffineTransform() :
        m_T(Matrix4f::Identity()),
        m_Parent(NULL)
    {}

    AffineTransform(AffineTransform *parent) :
        m_T(Matrix4f::Identity()),
        m_Parent(parent)
    {}

    AffineTransform(const AffineTransform &copy) :
        m_T(copy.m_T),
        m_Parent(copy.m_Parent)
    {}

    Eigen::Affine3f& GetTransform() { return m_T; }
    uLibGetSetMacro(Parent,AffineTransform *)

    inline void SetMatrix (Matrix4f &mat) { m_T.matrix() = mat; }
    inline Matrix4f& GetMatrix () { return m_T.matrix(); }

    Matrix4f GetWorldMatrix() const
    {
        if(!m_Parent) return m_T.matrix();
        else return  m_Parent->GetWorldMatrix() * m_T.matrix(); // T = B * A //
    }

    inline void SetPosition(const Vector3f &v) { this->m_T.translation() = v; }

    inline Vector3f GetPosition() const { return this->m_T.translation(); }

    inline void SetRotation(const Matrix3f &m) { this->m_T.linear() = m; }

    inline Matrix3f GetRotation() const { return this->m_T.rotation(); }

    inline void Translate(const Vector3f &v) { this->m_T.translate(v); }

    inline void Scale(const Vector3f &v) { this->m_T.scale(v); }

    inline Vector3f GetScale() const { return this->m_T.linear() * Vector3f(1,1,1); } // FIXXXXXXX


    inline void Rotate(const Matrix3f &m) { this->m_T.rotate(m); }


    inline void PreRotate(const Matrix3f &m) { this->m_T.prerotate(m); }

    inline void QuaternionRotate(const Vector4f &q)
    { this->m_T.rotate(Eigen::Quaternion<float>(q)); }

    inline void EulerYZYRotate(const Vector3f &e) {
        Matrix3f mat;
        mat =     Eigen::AngleAxisf(e.x(), Vector3f::UnitY())
                * Eigen::AngleAxisf(e.y(), Vector3f::UnitZ())
                * Eigen::AngleAxisf(e.z(), Vector3f::UnitY());
        m_T.rotate(mat);
    }

    inline void FlipAxes(int first, int second)
    {
        Matrix3f mat = Matrix3f::Identity();
        mat.col(first).swap(mat.col(second));
        m_T.rotate(mat);
    }
};



}



#endif//U_TRANSFORM_H
