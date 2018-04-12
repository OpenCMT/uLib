
#include "Object.h"
#include "Vector.h"

#include <stdio.h>



#ifdef __cplusplus

using namespace ltk;
int main()
{
  Object ob;
  printf("%d\n",ob.Get());

  Vector vec;
  printf("%d\n",vec.Get());
  return 0;
}

#else


static inline do_main() {
  Object ob = ltk_object_new();
  printf("%d\n",OBJECT_CLASS->get(ob));
  

  Vector vec = ltk_vector_new();
  printf("%d\n",VECTOR_CLASS->get(vec));

}

int main()
{
  do_main();
  return 0;
}

#endif
