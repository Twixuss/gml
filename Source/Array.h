#pragma once
#include "Common.h"
namespace gml {
   template<class T, int S>
   struct Array {
      T v[S];
      GML_CI T& operator[](size_t i) { return v[i]; }
      GML_CI const T& operator[](size_t i)  const { return v[i]; }
   };
}