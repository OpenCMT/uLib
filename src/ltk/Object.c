#include "Object.h"


static const struct _ltkObjectClass {
  size_t class_size;
  void (* constructor)(struct _Object *);
  void (* destructor) (struct _Object *);
  int  (* GetElement) (struct _Object *);
} _ObjectClassInstance;

const struct _ltkObjectClass *ltkObjectClass = &_ObjectClassInstance;

ltkPointer Object_new(struct _ObjectClass klass)
{
  struct _Object *ob = (struct _Object)malloc(klass->class_size);
  klass->constructor(ob);
  return ob;
}
