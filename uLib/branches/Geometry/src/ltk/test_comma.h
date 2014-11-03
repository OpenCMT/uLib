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
 * File:   test_comma.h
 * Author: andrea
 *
 * Created on May 24, 2012, 4:47 PM
 */

#ifndef TEST_COMMA_H
#define	TEST_COMMA_H

#include <assert.h>

struct Vector3
{
    union
    {
	struct { float x, y, z; };
	float data[3];
    };

   struct CommaAssign;

    CommaAssign operator=(float _x)
   {
      x = _x;
      return CommaAssign(this,1);
   }

   struct CommaAssign
    {
	Vector3 *vec3;
	int index;

	explicit CommaAssign(Vector3 *vec3, int index) : vec3(vec3) {
	    this->index = index;
	}
	CommaAssign operator, (float f) {
	    vec3->data[index] = f;
	    return CommaAssign(vec3, index + 1);
	}

    };

};



struct Container
{
    union
    {
	struct { float x, y, z; };
	float data[3];
    };

    inline float *getBuffer() {
	return this->data;
    }

   template <typename T, unsigned int size> class CommaAssign
    {
    private:
	T *container;
	int index;

    public:
	inline explicit CommaAssign(T *container, float s) : container(container) {
	    this->index = 0;
	    this->container->getBuffer()[0] = s;
	}

	inline CommaAssign& operator, (float s) {
	    this->index++;
	    assert(index < size);
	    this->container->getBuffer()[this->index] = s;
	    return *this;
	}
    };

    CommaAssign<Container, 3> operator=(float s) {
	return CommaAssign<Container, 3 > (this, s);
    }

};




#endif	/* TEST_COMMA_H */

