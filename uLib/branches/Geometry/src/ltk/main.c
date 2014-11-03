
#include "DenseMatrix.h"
#include "Vector.h"
#include "Object.h"

#include "vectormath/simd/instrset.h"

/* LTK_VECTOR_DECLARE(int,LtkInt4,4) */

/* LTK_MATRIX_DECLARE(int,LtkInt2x2,2,2) */
/* LTK_MATRIX_DECLARE(int,LtkInt4x1,4,1) */
/* LTK_MATRIX_DECLARE(int,LtkInt4x4,4,4) */

int test(int a) { return 0; }
 

int main(void)
{

  // testing dense matrix //
  /****************************************************/
  /* LtkInt2x2 a;				      */
  /* LtkInt4x1 b;				      */
  /* LtkInt4x4 c;				      */
  /* LtkInt4 v, w;				      */
  /* 						      */
  /* v = LtkInt4_ltk_vector_new ();		      */
  /* w = LtkInt4_ltk_vector_new ();		      */
  /* 						      */
  /* int i;					      */
  /* for (i = 0; i < LtkInt4_ltk_vector_size (); ++i) */
  /*   {					      */
  /*     LtkInt4_ltk_vector_set (v, i, 0);	      */
  /*     LtkInt4_ltk_vector_set (w, i, 3);	      */
  /*   }					      */
  /* 						      */
  /* printf ("v = ");				      */
  /* for (i = 0; i < 4; ++i)			      */
  /*   printf ("%d ", LtkInt4_ltk_vector_get (v, i)); */
  /* printf ("\n");				      */
  /* 						      */
  /* printf ("w = ");				      */
  /* for (i = 0; i < 4; ++i)			      */
  /*   printf ("%d ", LtkInt4_ltk_vector_get (w, i)); */
  /* printf ("\n");				      */
  /****************************************************/

  // testing intrinsics //
  printf("INSTRUCTION SET -> %d\n",INSTRSET);
  __m128 aligned_float = _mm_setzero_ps();
  float *p = &aligned_float;
  printf("%f,%f,%f,%f\n",p[0],p[1],p[2],p[3]);

  // adder //
  __m128 a_1,a_2;
  a_1 = _mm_set_ps(3,3,3,3);
  a_2 = _mm_set_ps(1,2,3,4);


  aligned_float = _mm_add_ps(a_1,a_2);
  p = &aligned_float; printf("%f,%f,%f,%f\n",p[0],p[1],p[2],p[3]);



  // testing Objects //
  //LTK_MATRIX_DECLARE(TypeName, type, r, c);
  // Object *ob = New(ObjectClass);
  // int el = ObjectClass->GetElement(ob);
  

  return 0;
}
