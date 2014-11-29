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



#ifndef U_CORE_STATICINTERFACE_H
#define U_CORE_STATICINTERFACE_H

namespace uLib {


// SFINAE //
/*
template <typename T>
struct has_type_info {
    typedef char yes[1];
    typedef char no[2];
    template <typename U> static yes& test(typename U::type_info::BaseList*);
    template <typename   > static no&  test(...);
    //        struct apply {
    static const bool value = sizeof(test<T>(0)) == sizeof(yes);
    typedef boost::mpl::bool_<value> type;
    //        };
};
*/


#define MAKE_TRAITS ; // TODO

#define uLibCheckFunction(class_name,name,out, ... ) \
{ out (class_name::*x)(__VA_ARGS__) = &class_name::name; (void) x; }

#define uLibCheckConstFunction(class_name,name,out,...) \
{ out (class_name::*x)(__VA_ARGS__) const = &class_name::name; (void) x; }

#define uLibCheckMember(class_name,name,type) \
{ class_name x; type *y = &x.name; (void) y; }


namespace Interface {

// EXAMPLE :
//template <class T> struct Voxel {
//    MAKE_TRAITS;
//    template<class Self> void check_structural() {
//        { float & (Self::*x)() = &Self::Density;    (void) x; }
//        { int   & (Self::*x)() = &Self::TrackCount; (void) x; }
//    }
//protected:
//    ~Voxel() {}
//};

template <class T, class SI>
static inline void IsA(T *t = 0) {
    (void) ((void (SI::*)()) &SI::template check_structural<T>);
}

template <class T, class SI>
static inline void IsA(T &t) {
    (void) ((void (SI::*)()) &SI::template check_structural<T>);
}

template <class T, class SI>
struct StaticIsA {
    StaticIsA() {
        void (SI::*x)() = &SI::template check_structural<T>;
        (void) x;
    }
};

} // Interface
} // uLib

#endif // STATICINTERFACE_H
