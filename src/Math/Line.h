#ifndef U_GEO_LINE_H
#define U_GEO_LINE_H

#include "Core/Macros.h"
#include "Core/Mpl.h"
#include "Core/Serializable.h"


#include "Math/Dense.h"



namespace uLib {

////////////////////////////////////////////////////////////////////////////////
// VECTOR PAIR /////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <typename _Scalar, int _Dim>
class VectorPair {
public:
    typedef Matrix<_Scalar,_Dim,1> Vector;
    VectorPair() {}
    VectorPair(const Vector &first,
               const Vector &second) {
        this->m_data[0] = first;
        this->m_data[1] = second;
    }
    uLibArrayMacro(Data,Vector *)
protected:
    EIGEN_ALIGN16 Vector m_Data[2];
};


////////////////////////////////////////////////////////////////////////////////
// LINE ////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <typename _Scalar, int _Dim>
class Line : public VectorPair<_Scalar, _Dim> {
public:
    ULIB_SERIALIZE_ACCESS
    typedef VectorPair<_Scalar, _Dim> BaseClass;
    typedef typename BaseClass::Vector Vector;

    Line() {}
    Line(const Vector &origin, const Vector &direction) : BaseClass(origin,direction) {}

    Vector & origin() { return this->m_Data[0]; }
    Vector & direction() { return this->m_Data[1]; }
    const Vector & origin() const { return this->m_Data[0]; }
    const Vector & direction() const { return this->m_Data[1]; }
    _Scalar & origin(Id_t id) { return this->m_Data[0](id); }
    _Scalar & direction(Id_t id) { return this->m_Data[1](id); }
    const _Scalar & origin(Id_t id) const { return this->m_Data[0](id); }
    const _Scalar & direction(Id_t id) const { return this->m_Data[1](id); }
};

typedef Line<float,2> Line2f;
typedef Line<float,3> Line3f;
typedef Line<float,4> Line4f;
typedef Line4f HLine3f;

} // uLib



//ULIB_SERIALIZABLE(uLib::Line2f)
//ULIB_SERIALIZABLE(uLib::Line3f)
//ULIB_SERIALIZABLE(uLib::Line4f)


#endif // LINE_H
