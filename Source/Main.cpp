#include <stdlib.h>
#include "gml.h"
#include "gmlIO.h"
using namespace gml;
int main() {
   Vector4<float> a(1,2,3,4);
   Print(a);
   puts("");
   Print(a.wzyx);
   system("pause");
}