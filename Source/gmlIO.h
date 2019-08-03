#pragma once
#include <stdio.h>
#include "gml.h"
namespace gml {
   void Print(const Vector4<float>& v) {
      printf("%f %f %f %f", v[0], v[1], v[2], v[3]);
   }
}