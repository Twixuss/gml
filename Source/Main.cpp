#include <stdlib.h>
#include "gml.h"
#include "gmlIO.h"
using namespace gml;
int main() {
   Vector4<float> a(1, 2, 3, 4);
   Vector4<float> b(5, 6, 7, 8);

   -a;
   +a;

   a + b;
   a += b;

   a + 1;
   a += 1;

   a += b.x;
   a += b.xzyw;

   -a.xyz;
   +a.zyw;

   a.wzyx + b;
   a.wzyx += b;

   a.wzyx + 1;
   a.wzyx += 1;

   a.wzyx + b.wwww;
   a.wzyx += b.zwzw;

   1 + b;
   1 + b.zyw;
   
   Matrix4x4<float> m(
      0,0,0,0,
      1,1,1,1,
      2,2,2,2,
      3,3,3,3
   );
   Print(m[0]);
   puts("");
   Print(m[1]);
   puts("");
   Print(m[2]);
   puts("");
   Print(m[3]);
   puts("");
   puts("");
   m = Transpose(m);
   Print(m[0]);
   puts("");
   Print(m[1]);
   puts("");
   Print(m[2]);
   puts("");
   Print(m[3]);
   system("pause");
}