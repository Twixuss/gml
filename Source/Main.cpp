#include <stdlib.h>
#include "gml.h"
using namespace gml;
int main() {
   Vector3<float> angles{ 3.1415926535897932384626433832795f, 0, 0 };
   Quaternion<float> q = Euler(angles);
   Matrix4x4<float> m = q;
   m *= Matrix4x4<float>();
   system("pause");
}