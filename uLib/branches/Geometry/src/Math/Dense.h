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
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2012  Andrea Rigoni Garola <andrea@pcimg05>
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


#ifndef ULIB_DENSEMATRIX_H
#define ULIB_DENSEMATRIX_H

#include <stdlib.h>

#include <Eigen/Dense>
#include "Core/Types.h"
#include "Core/Serializable.h"




///////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// NEW PART //



namespace uLib {

////////////////////////////////////////////////////////////////////////////////
// DENSE MATRIX DEFINITION /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

using Eigen::Matrix;


////////////////////////////////////////////////////////////////////////////////
// DENSE TYPES DEFINITIONS /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#define EIGEN_MAKE_TYPEDEFS(Type, TypeSuffix, Size, SizeSuffix)   \
    typedef Eigen::Matrix<Type, Size, Size> Matrix##SizeSuffix##TypeSuffix;  \
    typedef Eigen::Matrix<Type, Size, 1>    Vector##SizeSuffix##TypeSuffix;  \
    typedef Eigen::Matrix<Type, 1, Size>    RowVector##SizeSuffix##TypeSuffix; \
//    /* IMPORT INTERFACES */ \
//    typedef Interface::DenseMatrix<Type, mpl::int_<Size>, mpl::int_<Size> >  IMatrix##SizeSuffix##TypeSuffix;  \
//    typedef Interface::DenseArray<Type, mpl::int_<Size> >   IVector##SizeSuffix##TypeSuffix;  \
//    typedef Interface::DenseArray<Type, mpl::int_<Size> >   IRowVector##SizeSuffix##TypeSuffix;


#define EIGEN_MAKE_TYPEDEFS_ALL_SIZES(Type, TypeSuffix) \
    EIGEN_MAKE_TYPEDEFS(Type, TypeSuffix, 2, 2) \
    EIGEN_MAKE_TYPEDEFS(Type, TypeSuffix, 3, 3) \
    EIGEN_MAKE_TYPEDEFS(Type, TypeSuffix, 4, 4)

EIGEN_MAKE_TYPEDEFS_ALL_SIZES(int,                  i)
EIGEN_MAKE_TYPEDEFS_ALL_SIZES(float,                f)
EIGEN_MAKE_TYPEDEFS_ALL_SIZES(double,               d)
EIGEN_MAKE_TYPEDEFS_ALL_SIZES(std::complex<float>,  cf)
EIGEN_MAKE_TYPEDEFS_ALL_SIZES(std::complex<double>, cd)

#undef EIGEN_MAKE_TYPEDEFS_ALL_SIZES
#undef EIGEN_MAKE_TYPEDEFS

} // uLib


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// OLD PART //

//// BOOST SERIALIZATION ///////////////////////////////////////////////////////

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/array.hpp>


namespace boost {
namespace serialization {

template<class Archive, class Scalar, int RowsAtCompileTime, int ColsAtCompileTime>
void serialize(Archive & ar, ::Eigen::Matrix<Scalar, RowsAtCompileTime, ColsAtCompileTime> & m, const unsigned int /*version*/) {
    ar & boost::serialization::make_array(m.data(), RowsAtCompileTime * ColsAtCompileTime);
}

} //  serialization
} //  boost

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// EIGEN VECTOR STREAM INTERACTIONS ////////////////////////////////////////////
// this is needed by boost::lexical_cast to cope with Eigens Vectors ///////////
namespace Eigen {

template <typename C, typename T, int size>
std::istream & operator >> (std::basic_istream<C> &is, Eigen::Matrix<T,size,1> &vec) {
    std::basic_string<C> str;
    for( unsigned int i=0; i<size; i++) {
        is >> std::skipws >> str;
        if(is.fail()) vec(i) = 0;
        else vec(i) = boost::lexical_cast<T>(str);
    }
    return is;
}

template <typename C, typename T, int size>
Eigen::Matrix<T,size,1> & operator >> (const std::basic_string<C> &str,  Eigen::Matrix<T,size,1> &vec) {
    std::stringstream ss(str);
    ss >> vec;
    return vec;
}

template <typename C, typename T, int size>
std::basic_ostream<C> & operator << (std::basic_ostream<C> &os, const Eigen::Matrix<T,size,1> &vec) {
    //    os << "[" << vec.transpose() << "]T"; // TODO: read and write Transposition with a proper symbol
    os << vec.transpose();
    return os;
}

template <typename C, typename T, int size>
std::basic_string<C> & operator << (std::basic_string<C> &str, const Eigen::Matrix<T,size,1> &vec) {
    std::basic_stringstream<C> ss;
    ss << vec;
    str += ss.str();
    return str;
}


} // Eigen
////////////////////////////////////////////////////////////////////////////////



namespace uLib {


typedef int           Scalari;
typedef unsigned int  Scalarui;
typedef long          Scalarl;
typedef unsigned long Scalarul;
typedef float         Scalarf;
typedef double        Scalard;

} // uLib

//typedef Eigen::Matrix<int,1,1> Matrix1i;
//typedef Eigen::Matrix2i Matrix2i;
//typedef Eigen::Matrix3i Matrix3i;
//typedef Eigen::Matrix4i Matrix4i;

//typedef Eigen::Matrix<float,1,1> Matrix1f;
//typedef Eigen::Matrix2f Matrix2f;
//typedef Eigen::Matrix3f Matrix3f;
//typedef Eigen::Matrix4f Matrix4f;

//typedef Eigen::Matrix<int,1,1> Vector1i;
//typedef Eigen::Vector2i Vector2i;
//typedef Eigen::Vector3i Vector3i;
//typedef Eigen::Vector4i Vector4i;

//typedef Eigen::Matrix<float,1,1> Vector1f;
//typedef Eigen::Vector2f Vector2f;
//typedef Eigen::Vector3f Vector3f;
//typedef Eigen::Vector4f Vector4f;




////////////////////////////////////////////////////////////////////////////////
// Vector String interaction ///////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

///*! Given a string consisting of a series of doubles with some
//*  delimiter, return an Eigen::Vector populated with those
//*  values, in the same order as they are given in the string.
//*
//*  \param vec A double vector to be populated with the results
//*  \param str A string to be parsed as a series of doubles.
//*  \param delim Delimiters of the text (a typical default is " ," for comma and space-delimited text
//*
//*/
//template <typename T, int size>
//void VectorxT_StringTo(Eigen::Matrix<T,size,1> &vec, std::string str, const char *delim = " ,;\t\n") {
//    std::vector<std::string> strvec;

//    boost::algorithm::trim_if( str, boost::algorithm::is_any_of(delim));
//    boost::algorithm::split(strvec,str,boost::algorithm::is_any_of(delim), boost::algorithm::token_compress_on);

//    for( unsigned int i=0; i<size; i++) {
//        vec(i) = boost::lexical_cast<T>(strvec[i]);
//    }
//}

//template <typename T, int size>
//std::string VectorxT_ToString(const Eigen::Matrix<T,size,1> &vec) {
//    std::stringstream sst;
//    sst << vec.transpose();
//    return sst.str();
//}


////template <typename T, int size>
////Eigen::Matrix<T,size,1> & operator >> (std::istream &is, Eigen::Matrix<T,size,1> &vec) {
////}

//template <typename T, int size>
//void operator>> (std::string& str, Eigen::Matrix<T,size,1> &vec){
//    VectorxT_StringTo(vec,str);
//}


////////////////////////////////////////////////////////////////////////////////
//////   HOMOGENEOUS VECTORS  //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//template <bool p>
//class _HPoint3f : public Eigen::Matrix< Scalarf,4,1 > {
//public:
//    typedef Eigen::Matrix< Scalarf,4,1 > BaseClass;

//    _HPoint3f<p>() : BaseClass(0,0,0,p) {}
//    _HPoint3f<p>(float x,float y,float z) : BaseClass(x,y,z,p) {}
//    _HPoint3f<p>(Vector3f &in) : BaseClass(in.homogeneous()) { this->w = p; }

//    // This constructor allows to construct MyVectorType from Eigen expressions
//    template<typename OtherDerived>
//    inline _HPoint3f<p>(const Eigen::MatrixBase<OtherDerived>& other)
//        : BaseClass(other)
//    { }

//    // This method allows to assign Eigen expressions to Vector3H
//    template<typename OtherDerived>
//    inline _HPoint3f<p> & operator= (const Eigen::MatrixBase <OtherDerived>& other)
//    {
//        this->BaseClass::operator=(other);
//        return *this;
//    }

//};
//typedef _HPoint3f<false> Vector4f;
//typedef _HPoint3f<true> HPoint3f;




////////////////////////////////////////////////////////////////////////////////
//////   HOMOGENEOUS LINE     //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


//struct _HLine3f
//{
//    HPoint3f origin;
//    Vector4f direction;
//};
//typedef struct _HLine3f HLine3f;

//inline std::ostream&
//operator<< (std::ostream& stream, const HLine3f &line) {
//    stream << "HLine3f(" << "pt[" << line.origin.transpose() <<"] , dr[" << line.direction.transpose() << "]) ";
//    return stream;
//}




//struct _HError3f
//{
//    Vector4f position_error;
//    Vector4f direction_error;
//};
//typedef struct _HError3f HError3f;

//inline std::ostream&
//operator<< (std::ostream& stream, const HError3f &err) {
//    stream << "HError3f(" << "ept[" << err.position_error.transpose() <<"] , edr[" << err.direction_error.transpose() << "]) ";
//    return stream;
//}


//}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// SERIALIZTION //

// NEW //
ULIB_SERIALIZABLE(uLib::Vector2i)
ULIB_SERIALIZABLE(uLib::Vector3i)
ULIB_SERIALIZABLE(uLib::Vector4i)
ULIB_SERIALIZABLE(uLib::Vector2f)
ULIB_SERIALIZABLE(uLib::Vector3f)
ULIB_SERIALIZABLE(uLib::Vector4f)
ULIB_SERIALIZABLE(uLib::Vector2d)
ULIB_SERIALIZABLE(uLib::Vector3d)
ULIB_SERIALIZABLE(uLib::Vector4d)



//ULIB_SERIALIZABLE(uLib::HPoint3f)
//ULIB_SERIALIZABLE(uLib::Vector4f)
//ULIB_SERIALIZABLE(uLib::HLine3f)
//ULIB_SERIALIZABLE(uLib::HError3f)





#endif  // U_DENSEMATRIX_H
