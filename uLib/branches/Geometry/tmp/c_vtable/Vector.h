
#include "Object.h" // before VECTOR_C inline


#ifdef VECTOR_C
#undef INLINE 
#define INLINE
#endif

BEGIN_NAMESPACE(ltk)


C_BEGIN_DECLS


struct _Vector {
  struct _Object parent;
  int data[3];
};
#define VECTOR(ob) ((struct _Vector *)ob)
#define VECTOR_CLASS (ltk_vector_get_class())

INLINE  void ltk_vector_ctr (ltkPointer self) 
{ 
  ltk_object_ctr(self); // ctr parent //
  OBJECT(self)->element = 5552369; 
}

INLINE  void ltk_vector_dtr (ltkPointer self) 
{ 
  OBJECT(self)->element = 556;  
  ltk_object_dtr(self); // dtr parent //
}

INLINE   int ltk_vector_get_element(ltkPointer self) { return OBJECT(self)->element + 1; }


struct _VectorClass {
  size_t size;
  void (* ctr)(ltkPointer);
  void (* dtr)(ltkPointer);
  int  (* get)(ltkPointer);
  int *(* get_data)(ltkPointer);
};


INLINE const struct _VectorClass *ltk_vector_get_class()
{
  static const struct _VectorClass vtable = 
    {
      sizeof(struct _Vector),
      ltk_object_ctr,
      ltk_object_dtr,
      ltk_vector_get_element,
      NULL
    };
  return &vtable;
}
     
INLINE struct _Vector *ltk_vector_new()
{
  struct _ObjectClass *klass = (struct _ObjectClass *)ltk_vector_get_class();
  struct _Vector *vec = (struct _Vector *)ltk_object_allocator(klass);
  ltk_vector_ctr(vec);
  return vec;
}



C_END_DECLS

#ifndef __cplusplus 

typedef struct _Vector *Vector;
typedef struct _VecotrClass *VectorClass;


#else // CPP ------------------------------------------->
class Vector {
  typedef struct _Vector VectorData;
  VectorData *d;
 public:
 Vector() : d(new VectorData()) { ltk_vector_ctr(d); }
  int Get() { ltk_vector_get_element(d); }
};

#endif // <------------------------------------------ CPP

END_NAMESPACE
