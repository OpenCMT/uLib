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
 * Copyright (C) 2012  Andrea Rigoni Garola <andrea.rigoni@pd.infn.it>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */


#ifndef TEMPLATES_H
#define TEMPLATES_H

#include <stdlib.h>      // for std allocator   //
#include <string.h>      // for memcpy //
#include <assert.h>

#include "ltkmacros.h"      // default environment //
#include "container.h"   // TODO !!! //

#include <stdio.h>





/* ////////////////////////////////////////////////////////////////////////// */
/* //////////////////////////// ALLOC FUNCTIONS ///////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////// */

C_BEGIN_DECLS

//inline ltkPointer ltk_malloc(unsigned int size) { return malloc(size); }
//inline void       ltk_free  (ltkPointer ptr)    { free(ptr); }

#define LTK_SIMPLE_ALLOC_FUNC(Type, ltkType, Class_name, size)		\
  inline ltkType ltkType##_##Class_name##_new()				        \
  {									\
    return LTK_TYPECAST(ltkType, malloc(sizeof(Type) * size));     	\
  }                                                                 \
  inline void ltkType##_##Class_name##_delete(ltkType t)		    \
  { free(t); }								                        \
  inline void ltkType##_##Class_name##_copy(ltkType dst, const ltkType src) \
  { memcpy((ltkPointer)dst, (ltkPointer)src, sizeof(Type) * size ); }

C_END_DECLS





/* ////////////////////////////////////////////////////////////////////////// */
/* //////////////////////////// ABSTRACT C BUFFER /////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////// */

C_BEGIN_DECLS

#define LTK_ABSTRACT_BUFFER_DECLARE_FUNC(Type,ltkType,Class_name,size)        \
  inline int ltkType##_##Class_name##_size() { return size; }                 \
  inline Type ltkType##_##Class_name##_get(ltkType v, unsigned int c)         \
   { assert(c < size); return *((ltkType)m + c); }                            \
  inline void ltkType##_##Class_name##_set(ltkType v, Type t, unsigned int c) \
   { assert(c < size); *((ltkType)m + c) = t; }

// FINIRE !!! //

C_END_DECLS

#ifdef __cplusplus

template <typename T, unsigned int size> class ltkAbstractBuffer
{
  typedef ltkAbstractBuffer<T, size> ThisClass;  
protected:
    typedef T ContentType;
    virtual       T* getBuffer()       = 0;
    virtual const T* getBuffer() const = 0;

    struct CommaInit
    {
	inline explicit CommaInit(ltkAbstractBuffer<T, size> *container,float s)
	: container(container) {
	    this->index = 0;
	    this->container->getBuffer()[0] = s;
	}
	inline CommaInit & operator, (float s) {
	    this->index++;
	    assert(index < size);
	    this->container->getBuffer()[this->index] = s;
	    return *this;
	}
	ltkAbstractBuffer<T, size> *container;
	unsigned int index;
    };

public:
    inline CommaInit operator =(T scalar) {
	return CommaInit(this, scalar);
    }
    inline CommaInit operator <<(T scalar) {
	return CommaInit(this, scalar);
    }    

    inline T& at(const unsigned int i) {
	return *(this->getBuffer() + i);
    }

    inline T & operator[](unsigned int i) {
	return *(this->getBuffer() + i);
    }
    inline const T & operator[](unsigned int i) const {
	return *(this->getBuffer() + i);
    }
    inline T & operator()(unsigned int i) {
	return *(this->getBuffer() + i);
    }
    inline const T & operator()(unsigned int i) const {
	return *(this->getBuffer() + i);
    }


};

#endif // __cplusplus


/* ////////////////////////////////////////////////////////////////////////// */
/* //////////////////////////// ARRAY /////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////// */

// COMING SOON //







////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/// DO NOT USE ANYTHING AFTER THIS LINE ... EXPERIMENTAL      //////////////////









/* ////////////////////////////////////////////////////////////////////////// */
/* //////////////////////////// CIRCULAR BUFFER ///////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////// */
/* CIRCULAR BUFFER */

struct _ltk_template_buffer {
  void *pos;
  void *head;
};

#define LTK_BUFFER_DECLARE(Type, Type_name, size, overlap) \
typedef struct _ltk_template_buffer *Type_name;                                \
inline Type_name Type_name##_ltk_buffer_new()                                  \
{ Type_name out = (Type_name)ltk_malloc                                        \
                  (sizeof(Type) * (size + overlap) + 2);                       \
  out->head = (void *)out + 2 + overlap * sizeof(Type); \
  out->pos = out->head; \
return out;              }                     \
inline void Type_name##_ltk_buffer_free(Type_name buffer) { ltk_free(buffer); }\



// TO BE CONTINUED.... //








///// LtkPTree ////////

struct _LtkPTreeNode
{
  struct _LtkPTreeNode *parent;
};
typedef struct _LtkPTreeNode *LtkPtree;












/*
  one way list template usable as FIFO or LIFO by macros
  Element must be a pointer to a real allocated object.
*/
// this acts as dummy node, never really instanciated //
struct _template_list_node { 
  struct _template_list_node *next; 
};
typedef struct _template_list_node *LtkListNode;
#define LTK_LIST_HEADER LtkListNode ltk_list_node_next;

struct _template_list {
  int size;
  struct _template_list_node *start;
  struct _template_list_node *end;
};

typedef struct _template_list *LtkList;
typedef struct _template_list_node *LtkListIterator;

LtkList ltk_list_new();
void ltk_list_nodepush(LtkList list,LtkListNode node);
LtkListNode ltk_list_get_start(LtkList list);
LtkListNode ltk_list_get_end(LtkList list);
void ltk_list_remove(LtkList list,LtkListNode node);
void ltk_list_pop_start(LtkList list);
void ltk_list_pop_end(LtkList list);


#define LTK_LIST_DECLARE(Type,Type_name) \
    static LtkList (* Type_name##_list_new)(void) = ltk_list_new;\
    void    (* Type_name##_list_nodepush)(LtkList list, Type *node) = (void (*)(LtkList, Type *))ltk_list_nodepush; \
    Type *  (* Type_name##_list_get_start)(LtkList list)            = (Type *(*)(LtkList))ltk_list_get_start;       \
    Type *  (* Type_name##_list_get_end)(LtkList list)              = (Type *(*)(LtkList))ltk_list_get_end;         \
    void    (* Type_name##_list_remove)(LtkList list, Type *node)   = (void (*)(LtkList, Type *))ltk_list_remove;   \
    void    (* Type_name##_list_pop_start)(LtkList list)            = (void (*)(LtkList))ltk_list_pop_start;        \
    void    (* Type_name##_list_pop_end)(LtkList list)              = (void (*)(LtkList))ltk_list_pop_end;

#define LTK_LIST_DECLARE_KEYACCESS(Type,Type_name,KeyType,key_member_name,key_function) \
    Type * Type_name##_list_key_lookup(LtkList list, KeyType key)  { \
    LtkListIterator iter = ltk_list_iterator_new(list);             \
    while(iter) { \
    if (key_function( ((Type *)iter)->key_member_name, key )) \
    return (Type *)iter; \
    iter = iter->next; } \
    return NULL; } \
    \
    void Type_name##_list_key_remove(LtkList list, KeyType key) { \
    LtkListNode node = (LtkListNode)Type_name##_list_key_lookup(list,key); \
    if(node) ltk_list_remove(list,node); } \


LtkListIterator ltk_list_iterator_new(LtkList list);

#endif // TEMPLATES_H
