

#ifdef  __cplusplus
# define C_BEGIN_DECLS  extern "C" {
# define C_END_DECLS    }
#define BEGIN_NAMESPACE(name) namespace name {
#define END_NAMESPACE         }
#else
# define C_BEGIN_DECLS
# define C_END_DECLS
#define BEGIN_NAMESPACE(name)
#define END_NAMESPACE
#endif

#ifndef INLINE
# if __GNUC__ && !__GNUC_STDC_INLINE__
#  define INLINE extern inline
# else
#  define INLINE inline
# endif
#endif


#ifndef OBJECT_H
#define OBJECT_H


#ifdef OBJECT_C
#undef INLINE
#define INLINE
#endif


#include <stdlib.h>


BEGIN_NAMESPACE(ltk)

typedef void *ltkPointer;

C_BEGIN_DECLS


struct _Object {
  int element;
};
#define OBJECT(ob) ((struct _Object *)ob)
#define OBJECT_CLASS (ltk_object_get_class())


INLINE  void ltk_object_ctr (ltkPointer self) { OBJECT(self)->element = 5552368; }
INLINE  void ltk_object_dtr (ltkPointer self) { OBJECT(self)->element = 555;  }
INLINE   int ltk_object_get_element(ltkPointer self) { return OBJECT(self)->element; }


struct _ObjectClass {
  size_t size;
  void (* ctr)(ltkPointer);
  void (* dtr)(ltkPointer);
  int  (* get)(ltkPointer);
};




INLINE const struct _ObjectClass *ltk_object_get_class() {
  // vtable is defined as ...
  //  static:  to be filled up in code segment
  //  const :  to make compiler able to inline function pointers
  static const struct _ObjectClass vtable = 
    {
      sizeof(struct _Object),
      ltk_object_ctr,
      ltk_object_dtr,
      ltk_object_get_element
    };
  return &vtable;
}

INLINE ltkPointer ltk_object_allocator(const struct _ObjectClass *klass)
{
  struct _Object *ob = (struct _Object *)malloc(klass->size);
  return (ltkPointer)ob;
}

INLINE struct _Object *ltk_object_new()
{
  struct _Object *ob = (struct _Object *)ltk_object_allocator(OBJECT_CLASS);
  ltk_object_ctr(ob);
  return ob;
}


C_END_DECLS


#ifndef __cplusplus 

typedef struct _Object *Object;
typedef struct _ObjectClass *ObjectClass;

#else // CPP ------------------------------------------->
class Object {
  typedef struct _Object ObjectData;
  ObjectData *d;
 public:
 Object() : d(new ObjectData()) { ltk_object_ctr(d); }
  int Get() { ltk_object_get_element(d); }
};

#endif // <------------------------------------------ CPP


// FUNCTIONS SHARED BETWEEN C AND CPP THAT CAN BE INLINED //






END_NAMESPACE
















#endif // OBJEC_H
