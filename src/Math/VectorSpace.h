#ifndef U_GEO_VECTORSPACE_H
#define U_GEO_VECTORSPACE_H

#include "Core/Macros.h"
#include "Core/Mpl.h"

#include "Math/Dense.h"
#include "Math/Line.h"



//#include "boost/geometry.hpp"
//#include "boost/geometry/geometries/adapted/c_array.hpp"
//#include "boost/geometry/geometries/adapted/boost_array.hpp"
//#include "boost/geometry/geometries/adapted/std_pair_as_segment.hpp"

//#include "boost/geometry/geometries/register/point.hpp"
//#include "boost/geometry/geometries/register/linestring.hpp"


namespace uLib {



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// VECTOR SPACE ////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// VECTOR UTILS ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


inline Vector4f HVector3f(float x, float y, float z) { return Vector4f(x,y,z,0); }
inline Vector4f HVector3f(const Vector4f &v) { return Vector4f(v(0),v(1),v(2),0); }

inline Vector4f HPoint3f(float x, float y, float z) { return Vector4f(x,y,z,1); }
inline Vector4f HPoint3f(const Vector4f &v) { return Vector4f(v(0),v(1),v(2),1); }


// this is an example of function imported from eigen //
//using boost::geometry::distance;

} // uLib



// BOOST GEOMETRY REGISTRATION //

//BOOST_GEOMETRY_REGISTER_POINT_2D(uLib::Vector2i, int, boost::geometry::cs::cartesian, operator()(0), operator()(1))
//BOOST_GEOMETRY_REGISTER_POINT_3D(uLib::Vector3i, int, boost::geometry::cs::cartesian, operator()(0), operator()(1), operator()(2))
//BOOST_GEOMETRY_REGISTER_POINT_3D(uLib::Vector4i, int, boost::geometry::cs::cartesian, operator()(0), operator()(1), operator()(2))

//BOOST_GEOMETRY_REGISTER_POINT_2D(uLib::Vector2f, float, boost::geometry::cs::cartesian, operator()(0), operator()(1))
//BOOST_GEOMETRY_REGISTER_POINT_3D(uLib::Vector3f, float, boost::geometry::cs::cartesian, operator()(0), operator()(1), operator()(2))
//BOOST_GEOMETRY_REGISTER_POINT_3D(uLib::Vector4f, float, boost::geometry::cs::cartesian, operator()(0), operator()(1), operator()(2))

//BOOST_GEOMETRY_REGISTER_POINT_2D(uLib::Vector2d, double, boost::geometry::cs::cartesian, operator()(0), operator()(1))
//BOOST_GEOMETRY_REGISTER_POINT_3D(uLib::Vector3d, double, boost::geometry::cs::cartesian, operator()(0), operator()(1), operator()(2))
//BOOST_GEOMETRY_REGISTER_POINT_3D(uLib::Vector4d, double, boost::geometry::cs::cartesian, operator()(0), operator()(1), operator()(2))





#endif // VECTORSPACE_H
