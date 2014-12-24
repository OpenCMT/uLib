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

#ifndef U_MATH_IMAGEDATA_H
#define U_MATH_IMAGEDATA_H


#include <Math/ImageSpace.h>
#include <Math/ImageMap.h>

#include <Math/DataSet.h>
#include <Math/StructuredData.h>

namespace uLib {

class ImageData : public ImageSpace, public ImageMap {

public:
    ImageData() : ImageMap(Vector3i::Zero()) {}
    ImageData(const Vector3i &size) : ImageMap(size) {}

    void     SetSize(const Vector3f v);
    Vector3f GetSize() const;

    bool IsInsideBounds(const Vector4f pt) const;

    virtual void * GetDataPointer(const Id_t id) const = 0;

    virtual float GetValue(const Vector3i id) const = 0;
    virtual float GetValue(const int id) const = 0;
    virtual void  SetValue(const Vector3i id, float value) = 0;
    virtual void  SetValue(const int id, float value) = 0;

    virtual void SetDims(const Vector3i &size) = 0;

    void ExportToVtk(const char *file, bool density_type = 0);
    void ExportToVtkXml(const char *file, bool density_type = 0);
    int ImportFromVtk(const char *file);
};


template < class SeqCnt >
class DataSetImage : public DataSet, public ImageSpace, public ImageMap {

public:
    DataSetImage() : ImageMap(Vector3i::Zero()), m_Sequence() {}
    DataSetImage(const Vector3i &size) : ImageMap(size), m_Sequence(new SeqCnt(size.prod())) {}

    void SetSize(const Vector3f v) {
//        ImageSpace::SetSize( v.array() / this->GetDims().array().cast<float>() );
    }

    Vector3f GetSize() const {
//        return ImageSpace::GetSize().array() * this->GetDims().array().cast<float>();
    }

    bool IsInsideBounds(const Vector4f pt) const {
        Vector4f ptl =  ImageSpace::GetLocalPoint(pt);
        int result = 0;
        for (int i=0; i<3; ++i) {
            result += ptl(i) > (float)this->GetDims()(i);
            result += ptl(i) < 0;
        }
        return result == 0;
    }

    void SetDims(const Vector3i &size) { m_Sequence->resize(size.prod()); }

    inline void * GetDataPointer(Id_t id) { return &m_Sequence->at(id); }

private:
    SmartPointer<SeqCnt> m_Sequence;
};





//class DataVectorImage : public ImageData {
//    typedef float ScalarT;
//public:

//    inline void * GetDataPointer(const Id_t id) const {
//        return m_Data->GetDataPointer(id);
//    }

//    float GetValue(const Vector3i id) const { return m_Scalars.Get<float>(GetDataPointer(Map(id))); }
//    float GetValue(const int id) const { return m_Scalars.Get<float>(GetDataPointer(id)); }
//    void SetValue(const Vector3i id, float value) { m_Scalars.Set<float>(GetDataPointer(Map(id)),value); }
//    void SetValue(const int id, float value) { m_Scalars.Set<float>(GetDataPointer(id),value); }

//    void SetDims(const Vector3i &size) {
//        ImageMap::SetDims(size);
//        m_Data->SetSize(size.prod());
//    }

//    uLibRefMacro(Data,SmartPointer<AbstractArray>)
//    uLibRefMacro(Scalars,ProgrammableAccessor<ScalarT>)
//private:
//    SmartPointer<AbstractArray> m_Data;
//    ProgrammableAccessor<ScalarT> m_Scalars;
//};









} // uLib

#endif // IMAGEDATA_H
