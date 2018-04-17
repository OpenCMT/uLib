#include <stdio.h>
#include "testing-prototype.h"
#include "../Vector.h"


LTK_VECTOR_DECLARE (float, uFloat4, 4)

int main()
{
  BEGIN_TESTING (Vector);
  uFloat4 f = uFloat4_ltk_vector_new ();

  END_TESTING;
}
